<h1 align="center">
	<br>
	EPS 2.0 FIRMWARE
	<br>
</h1>

<h4 align="center">Electrical power system module firmware project (sources, configs and documentation).</h4>

<p align="center">
    <a href="https://github.com/spacelab-ufsc/spacelab#versioning">
        <img src="https://img.shields.io/badge/status-in%20development-red?style=for-the-badge">
    </a>
    <a href="https://github.com/spacelab-ufsc/eps2/releases">
        <img alt="GitHub release (latest by date)" src="https://img.shields.io/github/v/release/spacelab-ufsc/eps2?style=for-the-badge">
    </a>
    <a href="https://github.com/spacelab-ufsc/eps2/blob/dev_firmware/firmware/version.h">
        <img alt="GitHub commits since latest release (by date) for a branch" src="https://img.shields.io/github/commits-since/spacelab-ufsc/eps2/latest/dev_firmware?style=for-the-badge">
    </a>
    <a href="https://github.com/spacelab-ufsc/eps2/commits/master">
        <img alt="GitHub last commit (branch)" src="https://img.shields.io/github/last-commit/spacelab-ufsc/eps2/dev_firmware?style=for-the-badge">
    </a>
    <a href="">
    	<img alt="GitHub issues by-label" src="https://img.shields.io/github/issues/spacelab-ufsc/eps2/firmware?style=for-the-badge">
	</a>
    <a href="https://github.com/spacelab-ufsc/eps2/blob/master/firmware/main.c">
        <img src="https://img.shields.io/badge/language-C-green?style=for-the-badge">
    </a>
    <a href="">
        <img src="https://img.shields.io/badge/IDE%20tool-CCS%20v9.0-yellow?style=for-the-badge">
    </a>
    <a href="#license">
        <img src="https://img.shields.io/badge/license-GPL3-yellow?style=for-the-badge">
    </a>
    <a href="https://github.com/spacelab-ufsc/eps">
        <img src="https://img.shields.io/badge/flight-heritage-lightgray?style=for-the-badge">
    </a>
</p>

<p align="center">
  	<a href="#overview">Overview</a> •
  	<a href="#architecture">Architecture</a> •
  	<a href="#dependencies">Dependencies</a> •
  	<a href="#development">Development</a> •
  	<a href="#version">Version</a> •
  	<a href="#license">License</a> •
  	<a href="#notes">Notes</a>
</p>

<br>

## Overview

TBD

## Architecture

TBD 

## Dependencies
	- MSP430 DriverLib v2.91.11.01
	- FreeRTOS v10.2.1

## Development

#### Toolchain setup

This tutorial is a reference to install and setup the Code Composer Studio (CCS), a suggested tool for the development and deployment of the EPS2 firmware. The CCSv9.0 (or later) can be downloaded [here](http://software-dl.ti.com/ccs/esd/documents/ccs_downloads.html). After downloaded, start the install process. For the EPS2, only the `MSP430 Ultra Low Power MCUs` package is required. More instructions for Linux environment, click [here](https://software-dl.ti.com/ccs/esd/documents/ccs_linux_host_support.html). 

#### Compiling and building
	
Clone [this repository](https://github.com/spacelab-ufsc/eps2.git). After this, import the source project into CCS:
`File -> Import -> Code Composer Studio -> CCS Projects -> Select the source folder: obdh/firmware -> Leave 'Copy projects into workspace' unchecked / Finish`. Then, click in the Build button or press "Ctrl+B" to compile and build the sources. 

> Alternatively, it is possible to use the available makefile to import, compile and build the firmware in the linux environment. It is necessary to update the directories to correspond to those in the running machine, hit "make import" in the linux terminal and hit "make".  

#### Debugging

TBD  

## Version

Refer to the [releases](https://github.com/spacelab-ufsc/eps2/releases) page and the [version](https://github.com/spacelab-ufsc/eps2/blob/master/firmware/version.h) file.

## License

This repository containing firmware files is licensed under GPLv3 license.

## Notes

Project under development!