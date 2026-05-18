<h1 align="center">
	ELECTRICAL POWER SYSTEM 2.0 (EPS2)
	<br>
</h1>

<p align="center">
    <!-- Versioning -->
    <a href="https://github.com/spacelab-ufsc/spacelab#versioning"><img alt="Versioning" src="https://img.shields.io/badge/status-in_development-red"></a>
    <!-- Releases -->
    <a href="https://github.com/spacelab-ufsc/eps2/releases"><img alt="GitHub release" src="https://img.shields.io/github/v/release/spacelab-ufsc/eps2"></a>
    <!-- Commits since the latest release -->
    <a href="https://github.com/spacelab-ufsc/eps2/releases"><img alt="GitHub commits since latest release (by date)" src="https://img.shields.io/github/commits-since/spacelab-ufsc/eps2/latest"></a>
    <!-- Last commit -->
    <a href="https://github.com/spacelab-ufsc/eps2/commits/master"><img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/spacelab-ufsc/eps2"></a>
    <!-- Issues -->
    <a href="https://github.com/spacelab-ufsc/eps2/issues"><img alt="GitHub issues or pull requests" src="https://img.shields.io/github/issues/spacelab-ufsc/eps2"></a>
    <!-- PRs -->
    <a href="https://github.com/spacelab-ufsc/eps2/pulls"><img alt="GitHub issues or pull requests" src="https://img.shields.io/github/issues-pr/spacelab-ufsc/eps2"></a>
    <!-- Contributors -->
    <a href="https://github.com/spacelab-ufsc/eps2/graphs/contributors"><img alt="GitHub contributors" src="https://img.shields.io/github/contributors/spacelab-ufsc/eps2"></a>
</p>

<details>
    <summary><b>Summary</b></summary>
    <ol>
        <li>
            <a href="#overview">Overview</a>
        </li>
        <li>
            <a href="#repository-organization">Repository Organization</a>
        </li>
        <li>
            <a href="#license">License</a>
        </li>
        <li>
            <a href="#releases">Releases</a>
        </li>
        <li>
            <a href="#notes">Notes</a>
        </li>
        <li>
            <a href="#references">References</a>
        </li>
    </ol>
</details>

## Repository Organization
`documentation`: Technical EPS2's documentation.

`firmware`: EPS2's firmware project (sources and configs).

`hardware`: EPS2's hardware project (sources and outputs).

## Overview
The **EPS2** [[1]](#1) was designed to collect, store, and distribute energy for GOLDS-UFSC and future SpaceLab missions, prioritizing practicality. It is highly based on the EPS1, used in FloripaSat-1 [[2]](#2). Supporting both 1U and 2U CubeSats, this EPS can interface with up to 10 solar panels attached to the structure. It operates the solar panels at their maximum power point (MPP) using the perturb and observe (P&O) technique to control three DC-DC converters at the input. The collected energy is stored in lithium-ion batteries, with power distribution managed by integrated DC-DC converters, generating 5V, 6V and 3.3V buses. This model features a microprocessor, the MSP430, which collects internal data (e.g., current, voltage, temperature) and manages their storage and transmission to the OBDH.

<p align="center">
    <img src="https://github.com/spacelab-ufsc/eps2/blob/master/doc/figures/eps2-pcb-3d.png">
</p>

<p align="center">
    <a href="https://github.com/spacelab-ufsc/eps2/issues/new?labels=bug"><img alt="Static Badge" src="https://img.shields.io/badge/open_an_issue-to_report_a_bug-red"></a>
    <a href="https://github.com/spacelab-ufsc/eps2/issues/new?labels=enhancement"><img alt="Static Badge" src="https://img.shields.io/badge/open_an_issue-to_request_a_feature-yellow"></a>
    <a href="https://github.com/spacelab-ufsc/eps2/issues/new?labels=question,help+wanted"><img alt="Static Badge" src="https://img.shields.io/badge/open_an_issue-to_request_more_information_or_help-brightgreen"></a>
</p>

## License
This project is open-source under three different licenses: CERN Open Hardware License v2.0 for hardware, GNU General Public License v3.0 for firmware, and CC BY-SA 4.0 for documentation.

## Releases
Releases are published after verifying that all components of the project — hardware, firmware, and documentation — are synchronized and compatible, ensuring functionality and cohesion. Using different versions of hardware, firmware, or documentation projects can lead to misunderstandings or unpredictable behavior. Please refer to the **documentation** for more details.

## Notes
For more info about the SpaceLab, access our [GitHub](https://github.com/spacelab-ufsc/spacelab), [Linkedin](https://br.linkedin.com/company/spacelab-ufsc) or our [website](https://spacelab.ufsc.br/en/home/).

## References
<a id="1">[1]</a> G. M. Marcelino, A. M. P. de Mattos, J. C. E. Barcellos, B. F. Ribeiro, L. O. Seman, E. M. Filho and E. A. Bezerra, "FloripaSat-2: An Open-Source Platform for CubeSats," in IEEE Embedded Systems Letters, vol. 16, no. 1, pp. 77-80, 2024, available at <a href="https://repositorio.ufsc.br/bitstream/handle/123456789/247559/PEEL2103-D.pdf?sequence=1&isAllowed=y"> this link</a>.

<a id="1">[2]</a> SpaceLab, "Electrical Power System (EPS)," in GitHub, 2019, available at <a href="https://github.com/spacelab-ufsc/eps"> this link</a>.