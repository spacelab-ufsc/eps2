<h1 align="center">
	ELECTRICAL POWER SYSTEM 2.0
	<br>
</h1>

<h4 align="center">Electrical power system module designed and developed by SpaceLab.</h4>

<p align="center">
	<a href="https://github.com/spacelab-ufsc/eps2/releases">
		<img src="https://img.shields.io/badge/status-development-9cf?style=for-the-badge">
	</a>
    <a href="https://github.com/spacelab-ufsc/eps2/releases">
        <img alt="GitHub release (latest by date)" src="https://img.shields.io/github/v/release/spacelab-ufsc/eps2?style=for-the-badge">
    </a>
    <a href="https://github.com/spacelab-ufsc/eps2/releases">
        <img alt="GitHub commits since latest release (by date)" src="https://img.shields.io/github/commits-since/spacelab-ufsc/eps2/latest?style=for-the-badge">
    </a>
    <a href="https://github.com/spacelab-ufsc/eps2/commits/master">
        <img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/spacelab-ufsc/eps2?style=for-the-badge">
	</a>
    <a href="https://github.com/spacelab-ufsc/eps2/issues">
        <img alt="GitHub issues" src="https://img.shields.io/github/issues/spacelab-ufsc/eps2?style=for-the-badge">
	</a>
    <a href="https://github.com/spacelab-ufsc/eps2/graphs/contributors">
            <img alt="GitHub contributors" src="https://img.shields.io/github/contributors/spacelab-ufsc/eps2?color=yellow&style=for-the-badge">
	</a>
</p>

<p align="center">
  	<a href="#overview">Overview</a> •
  	<a href="#repository-organization">Repository Organizarion</a> •
  	<a href="#license">License</a> •
  	<a href="#releases">Releases</a> •
  	<a href="#notes">Notes</a>
</p>

<p align="center">
    <img width="70%" src="https://github.com/spacelab-ufsc/eps2/blob/master/doc/figures/eps2-pcb-3d.png">
</p>

## Overview

The EPS2 has been designed to harvest, store and distribute energy for the GOLDS-UFSC CubeSat mission. The energy harvesting system is based on solar energy conversion through 10 solar panels attached to the structure. The EPS is designed to operate the solar panels at their maximum power point. The harvested solar energy is stored in 4 lithium-ion batteries connected in series/parallel. The energy distribution is done by several integrated DC-DC converters. The full EPS system is composed of the solar panels, the EPS PCB, and the Batteries PCB.

## Repository Organization
	- doc: Technical EPS2 documentation (including firmware, hardware, user guide, and datasheet).
	- firmware: Electrical power system module firmware project (sources and configs).
	- hardware: Electrical power system module hardware project (sources and outputs).

## License

This project is open-source and under the GPLv3 license, but some third-part files and libraries are subjected to specific terms and comercial use might be prohibited. Therefore, the purpose of the open access approach is to support further educational use and academic projects.

## Releases

The EPS2 software and hardware releases are synchronized in order to garantee compatibility. Then, using diferent versions might lead to unpredictable behavior. Refer to the [documentation](https://github.com/spacelab-ufsc/eps2/tree/master/doc/) for compatibility notes.

## Notes

More info about the EPS2 target mission: [FloripaSat-2](https://github.com/spacelab-ufsc/floripasat2-doc)

More info about the SpaceLab: [GitHub](https://github.com/spacelab-ufsc/spacelab) and [Website](https://spacelab.ufsc.br/en/home/)
