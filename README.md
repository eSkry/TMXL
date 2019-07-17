<h1 align="center">TMXL</h1>

<div align="center">
 <a href="https://travis-ci.com/eSkry/TMXL"><img src="https://travis-ci.com/eSkry/TMXL.svg?branch=TMXL_V1" /></a>
 <a href="https://coveralls.io/github/eSkry/TMXL?branch=TMXL_V1"><img src="https://coveralls.io/repos/github/eSkry/TMXL/badge.svg?branch=TMXL_V1" /></a>
 <a href="https://www.codefactor.io/repository/github/eskry/tmxl"><img src="https://www.codefactor.io/repository/github/eskry/tmxl/badge" /></a>
 <a href="https://github.com/eSkry/TMXL/blob/TMXL_V1/LICENSE.md"><img src="https://img.shields.io/badge/License-MIT-blue.svg" /></a>
</div>

## Build
Project uses [CMake](https://cmake.org) to generate platform and compiler-specific build files.

### Dependencies
- [SFML](https://www.sfml-dev.org)
- [pugixml](https://pugixml.org)

### Building on Linux (Unix Makefiles)
1. Install SFML: `apt-get install sfml-dev libsfml-*2.4`
1. Clone repository, enter to TMXL directory and run init script: `git clone https://github.com/eSkry/TMXL && cd ./TMXL && chmod +x ./initsubmodules.sh && ./initsubmodules.sh`
1. Build TMXL:
 - By script: `chmod +x ./build.sh && ./build.sh`
 - By command: `mkdir build && cd build && cmake -G "Unix Makefiles" .. -DCMAKE_BUILD_TYPE=Debug -DTMXL_BUILD_TESTS=ON -DBUILD_EXAMPLES=ON && cmake --build .`

## Contributing
Please read [CONTRIBUTING.md](CONTRIBUTING.md) for details on our code of conduct, and the process for submitting pull requests to us.

## License
This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Badges
![Badge_status](https://www.code-inspector.com/project/226/status/svg) ![Badge_score](https://www.code-inspector.com/project/226/score/svg) 
