# R-Type

## Description
The R-Type is an Epitech project whose goal is to replicate the famous [r-type game](http://www.hardcoregaming101.net/r-type/) with online multi-player capability.

More information about the project can be found [here](./docs/subject.pdf).

## Documentation
The documentation for this project can be generated with [Doxygen](http://www.doxygen.nl/) by using the following commands:
```shell script
cd server
doxygen ./Doxyfile
cd ../client
doxygen ./Doxyfile
cd ..
```
You can then open the client documentation by opening `client/docs/html/index.html` and the server documentation by opening `server/docs/html/index.html`.

The rfc for the r-type binary protocol can be found [here](./docs/rfc42069).

## Install and run
### Dependencies
* [conan](https://conan.io/): for c++ dependencies
* [cmake](https://cmake.org/): to build the project
#### Windows
* [msvc](https://docs.microsoft.com/fr-fr/visualstudio/install/install-visual-studio?view=vs-2017): compiler and linker (version Visual Studio 15 2017 used for this project)
#### Linux
* [g++](https://gcc.gnu.org/): compiler and linker

### Install
Add the required conan remotes:
```shell script
conan remote add conan-center https://bintray.com/conan/conan-center
conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
conan remote add epitech https://api.bintray.com/conan/epitech/public-conan
```
Then make a build folder and go into it:
```shell script
mkdir build
cd build
```
Run conan to install all dependencies to your computer:
```shell script
conan install .. --build missing
```
Then run CMake:
```shell script
# Windows ONLY
cmake .. -G "Visual Studio 15 2017 Win64"
cmake --build . --config Release

# Linux ONLY
cmake .. -G "Unix Makefiles"
cmake --build . --config Release
```
To change the configuration change between Debug and Release

## Build RFC

To build the RFC as HTMl or TXT you must use the script [generate_rfc.sh](./docs/generate_rfc.sh)

## FAQ
CLion fails to load CMakeList.txt, why?

> You need to go into your cmake-build-* folder and run `conan install .. --build missing` before using CLion.

## Contributing
See [CONTRIBUTING.md](./CONTRIBUTING.md) to get involved.

## Authors
* [Lilian Arago](https://github.com/NahisWayard)
* [Titouan Pautier](https://github.com/BillyTheD1ck)
* [Etienne Guillet](https://github.com/EtienneGuillet)
* [Julian Fräbel](https://github.com/Eldriann)