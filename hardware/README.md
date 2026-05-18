<h1 align="center">
	EPS2 HARDWARE
	<br>
</h1>

<p align="center">
    <!-- Versioning -->
    <a href="https://github.com/spacelab-ufsc/spacelab#versioning"><img alt="Versioning" src="https://img.shields.io/badge/status-in_development-red"></a>
    <!-- Releases -->
    <a href="https://github.com/spacelab-ufsc/eps2/releases"><img alt="GitHub release" src="https://img.shields.io/github/v/release/spacelab-ufsc/eps2"></a>
    <!-- Hardware-related commits since the latest release -->
    <a href="https://github.com/spacelab-ufsc/eps2/releases"><img alt="GitHub commits since latest release (by date)" src="https://img.shields.io/github/commits-since/spacelab-ufsc/eps2/latest/dev_hardware"></a>
    <!-- Last hardware-related commit -->
    <a href="https://github.com/spacelab-ufsc/eps2/commits/master"><img alt="GitHub last commit (branch)" src="https://img.shields.io/github/last-commit/spacelab-ufsc/eps2/dev_hardware"></a>
    <!-- Hardware-related issues -->
    <a href="https://github.com/spacelab-ufsc/eps2/issues"><img alt="GitHub issues or pull requests" src="https://img.shields.io/github/issues/spacelab-ufsc/eps2/hardware"></a>
    <!-- CAD tool used -->
    <a href=""><img alt="CAD tool" src="https://img.shields.io/badge/cad_tool-Altium_v19.2-yellow"></a></a>
    <!-- License adopted -->
    <a href=""><img alt="License" src="https://img.shields.io/badge/license-CERN_OHL_2-yellow"></a></a>
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
The **EPS2** [[1]](#1) was designed to collect, store, and distribute energy for GOLDS-UFSC and future SpaceLab's missions, with a focus on practicality. It is higly based on the EPS1, used in FloripaSat-1 [[2]](#2). Then, it can be used in 1U and 2U CubeSats, this EPS can interface with up to 10 solar panels attached to the structure. It is also capable of operating the solar panels at their maximum power point (MPP). The collected energy is stored in lithium-ion batteries, and power distribution is managed by integrated DC-DC converters, generating 5V and 3.3V buses. This model is predominantly analog, enhancing its reliability in the challenging space environment. It also features redundancies in its energy harvesting unit (EHU) and power distribution unit (PDU).

<p align="center">
    <img src="https://github.com/spacelab-ufsc/eps2/blob/master/doc/figures/eps2-pcb-top.png" width="400"><img src="https://github.com/spacelab-ufsc/eps2/blob/master/doc/figures/eps2-pcb-bottom.png" width="400">
</p>

### Architecture
The EPS2 includes an MSP430 microcontroller, which is responsible for reading various sensors and controlling its main units, such as the energy harvesting unit (EHU), power distribution unit (PDU), and power storage unit (PSU). It also features I²C and SPI interfaces for communication with the main modules of the satellite's service module. For more details, please refer to the **documentation**.

<p align="center">
    <img src="https://github.com/spacelab-ufsc/eps2/blob/master/doc/figures/eps2_mcu_diagram.png">
</p>

### Development
#### Manufacture
The folder [fabrication](https://github.com/spacelab-ufsc/eps2/tree/master/hardware/fabrication) contains three "ready to go" files: the Gerbers and NC drill files for manufacturing the board, the BOM (Bill of Materials) with all required components, and the pick-and-place file for automated assembly. Additional files are available in the [outputs](https://github.com/spacelab-ufsc/eps2/tree/master/hardware/outputs) folder, which includes several useful files and documents such as 3D models, the bill of materials, schematics, layout prints, and draftsman files.

#### Assembly
The board has components that should not be soldered simultaneously. Please refer to the **documentation** in the assembly-related chapter for more details.

#### Power-on Procedure
To power on the board, you need to connect a battery (either the [BAT4C](https://github.com/spacelab-ufsc/battery-module-4c) model or the [BAT2C](https://github.com/spacelab-ufsc/battery-module-2c) model) or, at a minimum, emulate a battery using a power supply. For this, simply connect the power supply to provide 7.4V on `VBAT+`, GND on `VBAT-`, and 3.7V on `V_CM`. You can use the `P5` connector for this purpose. Refer to the **documentation** in the instructions-related chapter for more details.

## License
This project is open-source under the following license: CERN Open Hardware License v2.0.

## Notes
For more info about the SpaceLab, access our [GitHub](https://github.com/spacelab-ufsc/spacelab), [Linkedin](https://br.linkedin.com/company/spacelab-ufsc) or our [website](https://spacelab.ufsc.br/en/home/).

## References
