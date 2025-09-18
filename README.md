# FPGA sdk install

only works for linux

First install the fpga dependencies by running the script `install_fpga_dependencies.sh`

`install_fpga_dependencies.sh` only works for ubuntu (haven't tested on debian).

```bash
cd scripts
./install_fpga_dependencies.sh
```

then install the sdk, once the dependencies are install this should work for any linux distro

```bash
./install_fpga_sdk.sh
```

then source the sdk

```bash
source fpga_sdk
```

to make sure the sdk is sourced run `yosys --help`
