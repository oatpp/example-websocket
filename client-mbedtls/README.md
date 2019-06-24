# secure websocket client with mbedtls

Simple example of the secure websocket client. Built with oat++ (AKA oatpp) web framework.  
TLS backend - MbedTLS.

See more:

- [Oat++ Website](https://oatpp.io/)
- [Oat++ Github Repository](https://github.com/oatpp/oatpp)
- [Get Started With Oat++](https://oatpp.io/docs/start)

## Overview

### Project layout

```
|- CMakeLists.txt                         // projects CMakeLists.txt
|- src/
|    |
|    |- WSListener.hpp                    // WebSocket listeners are defined here
|    |- App.cpp                           // main() is here
|
|- utility/install-oatpp-modules.sh       // utility script to install required oatpp-modules.  
```

## Build and Run

### Using CMake

**Requires** 
- MbedTLS installed - see [install mbedtls](#install-mbedtls). 
- [oatpp](https://github.com/oatpp/oatpp), [oatpp-websocket](https://github.com/oatpp/oatpp-websocket), 
and [oatpp-mbedtls](https://github.com/oatpp/oatpp-mbedtls) modules installed. You may run `utility/install-oatpp-modules.sh` 
script to install required oatpp modules.

```
$ mkdir build && cd build
$ cmake ..
$ make 
$ ./websocket-client-mbedtls-exe       # - run application.
```

## Install MbedTLS

```bash
git clone -b 'mbedtls-2.16.1' --single-branch --depth 1 --recurse-submodules https://github.com/ARMmbed/mbedtls

cd mbedtls
mkdir build && cd build

cmake ..
make install
```
