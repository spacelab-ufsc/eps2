TARGET=eps2
CCS_WORKSPACE=$(HOME)/workspace_v9

DEV_CONFIG_FILE=targetConfigs/MSP430F6659.ccxml
IMG=Debug/$(TARGET).out

CC=$(HOME)/ti/ccs920/ccs/eclipse/./ccstudio
FL=uniflash/ccs_base/DebugServer/bin/./DSLite

all:
	$(CC) -noSplash -data $(CCS_WORKSPACE) -application com.ti.ccstudio.apps.projectBuild -ccs.projects $(TARGET)

import:
	$(CC) -noSplash -data $(CCS_WORKSPACE) -application com.ti.ccstudio.apps.projectImport -ccs.overwrite -ccs.location .

flash:
	$(FL) flash -c $(DEV_CONFIG_FILE) -l uniflash/user_files/settings/generated.ufsettings -s VerifyAfterProgramLoad=2 -e -f -v "$(IMG)" -n 0

clean:
	$(CC) -noSplash -data $(CCS_WORKSPACE) -application com.ti.ccstudio.apps.projectBuild -ccs.projects $(TARGET) -ccs.clean
