<h1 align="center">
	EPS2 FIRMWARE
	<br>
</h1>

<p align="center">
    <!-- Versioning -->
    <a href="https://github.com/spacelab-ufsc/spacelab#versioning"><img alt="Versioning" src="https://img.shields.io/badge/status-in_development-red"></a>
    <!-- Releases -->
    <a href="https://github.com/spacelab-ufsc/eps2/releases"><img alt="GitHub release" src="https://img.shields.io/github/v/release/spacelab-ufsc/eps2"></a>
    <!-- Firmware-related commits since the latest release -->
    <a href="https://github.com/spacelab-ufsc/eps2/releases"><img alt="GitHub commits since latest release (by date)" src="https://img.shields.io/github/commits-since/spacelab-ufsc/eps2/latest/dev_firmware"></a>
    <!-- Last firmware-related commit -->
    <a href="https://github.com/spacelab-ufsc/eps2/commits/master"><img alt="GitHub last commit (branch)" src="https://img.shields.io/github/last-commit/spacelab-ufsc/eps2/dev_firmware"></a>
    <!-- Hardware-related issues -->
    <a href="https://github.com/spacelab-ufsc/eps2/issues"><img alt="GitHub issues or pull requests" src="https://img.shields.io/github/issues/spacelab-ufsc/eps2/firmware"></a>
    <!-- Code language used -->
    <a href=""><img alt="Code language" src="https://img.shields.io/badge/language-C-yellow"></a></a>
    <!-- IDE used -->
    <a href=""><img alt="IDE" src="https://img.shields.io/badge/ide_tool-CCS_v9.0-yellow"></a></a>
    <!-- License adopted -->
    <a href=""><img alt="License" src="https://img.shields.io/badge/license-GPL3-yellow"></a></a>
    <!--Build status -->
    <a href="https://github.com/spacelab-ufsc/eps2/actions"><img alt="Build status" src="https://img.shields.io/github/actions/workflow/status/spacelab-ufsc/eps2/test-workflow.yml"></a>
</p>

<details>
    <summary><b>Summary</b></summary>
    <ol>
        <li>
            <a href="#overview">Overview</a>
        </li>
        <li>
            <a href="#license">License</a>
        </li>
        <li>
            <a href="#notes">Notes</a>
        </li>
        <li>
            <a href="#references">References</a>
        </li>
    </ol>
</details>

## Overview
The EPS2 board has a MSP430 low-power microcontroller that runs the firmware application. It manages the others sub-modules within the board, synchronizes actions, handles communication with the Earth's segment, and manages the data flow. The programming language used is C and firmware was developed in the Code Composer Studio IDE (a.k.a. CCS).

### Architecture
The EPS2 module has many tasks, such interfacing peripherals and other MCUs, over distinct protocols and time requirements. Then, it requires a real time operating system (RTOS) to assure that it will deal with its deadlines, even under a fault in some task routine. The RTOS chosen is the FreeRTOS (v10.2.1), since it is designed for embedded systems applications and it was already validated in space applications. The software was made to have abstraction layers through the use of low-level register manipulation libraries, drivers to manage internal and external peripherals, devices to handle ICs and other modules, and over the top a application layer. Refer to the **documentation** in the firmware-related chapter.

### Dependencies
	- MSP430 DriverLib v2.91.11.01
	- FreeRTOS v10.2.1
	- libcsp v1.5.16

### Development

#### Toolchain setup

This tutorial is a reference to install and setup the Code Composer Studio (CCS), a suggested tool for the development and deployment of the EPS2 firmware. The CCSv9.0 (or later) can be downloaded [here](http://software-dl.ti.com/ccs/esd/documents/ccs_downloads.html). After downloaded, start the install process. For the EPS2, only the `MSP430 Ultra Low Power MCUs` package is required. More instructions for Linux environment, click [here](https://software-dl.ti.com/ccs/esd/documents/ccs_linux_host_support.html).

#### Compiling and building
	
Clone [this repository](https://github.com/spacelab-ufsc/eps2.git). After this, import the source project into CCS:
`File -> Import -> Code Composer Studio -> CCS Projects -> Select the source folder: eps2/firmware -> Leave 'Copy projects into workspace' unchecked / Finish`. Then, click in the Build button or press "Ctrl+B" to compile and build the sources.

> Alternatively, it is possible to use the available makefile to import, compile and build the firmware in the linux environment. It is necessary to update the directories to correspond to those in the running machine, hit "make import" in the linux terminal and hit "make".

#### Debugging

Before deploying the program into the microcontroller via the JTAG interface, follow the [power-on procedures](https://github.com/spacelab-ufsc/eps2/tree/master/hardware). Using the [MSP-FET](http://www.ti.com/tool/MSP-FET) is possible to program the microcontroller and start a debug session, which allows full control of the firmware in execution. For that, with the project opened in the CCS, click in the "Debug" button or press "F11" to upload the code into the EPS2 board.

Besides the JTAG, there is the debugging performed through a serial UART port, using as default a baud rate of 115200, 1 stop bit, and no parity bit. The interface uses a log system standard to improve readability. Refer to the **documentation** in the instructions-related chapter.

> Alternatively, it is possible to use the available makefile to perform the deployment of the firmware image into the microcontroller in the linux environment using the MSP-FET. It is necessary to follow the power-on procedures, connect the programmer and hit "make flash" in the terminal.

## License
This project is open-source under the following license: GNU General Public License v3.0.

## Notes
For more info about the SpaceLab, access our [GitHub](https://github.com/spacelab-ufsc/spacelab), [Linkedin](https://br.linkedin.com/company/spacelab-ufsc) or our [website](https://spacelab.ufsc.br/en/home/).

## References
