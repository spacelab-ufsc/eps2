#!/bin/bash

# directory of script
script=$(readlink -f "$0")
scriptDir=$(dirname "$script")

ln -sf "$scriptDir"/ccs_base/common/bin/libstdc++.so.6.0.28 "$scriptDir"/ccs_base/common/bin/libstdc++.so
ln -sf "$scriptDir"/ccs_base/common/bin/libstdc++.so.6.0.28 "$scriptDir"/ccs_base/common/bin/libstdc++.so.6
ln -sf "$scriptDir"/ccs_base/common/bin/libxerces-c_2_8.so "$scriptDir"/ccs_base/common/bin/libxerces-c.so.28
ln -sf "$scriptDir"/ccs_base/common/bin/libxerces-c_2_8.so "$scriptDir"/ccs_base/common/bin/libxerces-c.so.28.0
echo "Done"
