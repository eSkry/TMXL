# TMXL. [![Build Status](https://travis-ci.com/eSkry/TMXL.svg?branch=TMXL_V1)](https://travis-ci.com/eSkry/TMXL) [![Coverage Status](https://coveralls.io/repos/github/eSkry/TMXL/badge.svg?branch=TMXL_V1)](https://coveralls.io/github/eSkry/TMXL?branch=TMXL_V1)  [![CodeFactor](https://www.codefactor.io/repository/github/eskry/tmxl/badge)](https://www.codefactor.io/repository/github/eskry/tmxl) ![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)

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
