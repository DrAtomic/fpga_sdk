#define NOB_IMPLEMENTATION
#define NOB_STRIP_PREFIX
#define NOB_WARN_DEPRECATED
#include "nob.h"

#define TOOLS_DIR "tools/"
#define SOURCES_DIR TOOLS_DIR"sources/"

int main(int argc, char **argv)
{
	NOB_GO_REBUILD_URSELF(argc, argv);

	Cmd cmd = {0};
	Procs procs = {0};

	if (!mkdir_if_not_exists(TOOLS_DIR)) return 1;
	if (!mkdir_if_not_exists(SOURCES_DIR)) return 1;

	static struct {
		const char *repos;
		const char *branch;
		const char *outputs;
	} targets[] = {
		{ .repos = "https://github.com/YosysHQ/yosys.git", .branch = "--branch=v0.57", .outputs = SOURCES_DIR"yosys"},
		{ .repos = "https://github.com/ghdl/ghdl.git", .branch = "--branch=v5.1.1", .outputs = SOURCES_DIR"ghdl"},
		{ .repos = "https://github.com/DrAtomic/ghdl-yosys-plugin.git", .branch = "--branch=v0.0.1", .outputs = SOURCES_DIR"ghdl-yosys-plugin"},
		{ .repos = "https://github.com/DrAtomic/icestorm", .branch = "--branch=v0.0.1", .outputs = SOURCES_DIR"icestorm"},
		{ .repos = "https://github.com/YosysHQ/nextpnr.git", .branch = "--branch=nextpnr-0.9", .outputs = SOURCES_DIR"nextpnr"},
		{ .repos = "https://github.com/DrAtomic/gtkwave.git", .branch = "--branch=v0.0.1", .outputs = SOURCES_DIR"gtkwave"},
	};

	for (size_t i = 0; i < ARRAY_LEN(targets); ++i) {
		if (!dir_exists(targets[i].outputs)) {
			cmd_append(&cmd, "git", "clone", targets[i].branch, "--depth=1" ,targets[i].repos, targets[i].outputs);
			if (!cmd_run(&cmd, .async = &procs)) return 1;
		}
	}

	if (!procs_flush(&procs)) return 1;

	return 0;
}
