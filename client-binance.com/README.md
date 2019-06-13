# binance.com websocket client

Client for binance.com public WebSocket APIs. Built with oat++ (AKA oatpp) web framework.

See more:

- [Oat++ Website](https://oatpp.io/)
- [Oat++ Github Repository](https://github.com/oatpp/oatpp)
- [Get Started With Oat++](https://oatpp.io/docs/start)

## Overview

This websocket client connects to stream.binance.com, listens to events and prints data to log-output.

Listeners are implemented for the following streams:

- Aggregate Trade Streams
- Trade Streams
- Kline/Candlestick Streams

*more detailes on binance.com API [here](https://github.com/binance-exchange/binance-official-api-docs/blob/master/web-socket-streams.md)*

### Project layout

```
|- CMakeLists.txt                         // projects CMakeLists.txt
|- src/
|    |
|    |- Model.hpp                         // DTOs for binance.com API models
|    |- AggregateTradesListener.hpp       // WebSocket listener for AggregateTrades streams
|    |- TradesListener.hpp                // WebSocket listener for Trades streams
|    |- KlineCandlestickListener.hpp      // WebSocket listener for Kline/Candlestick streams
|    |- WSEventListener.hpp               // Template listener for stream objects. Deserialize received message to an event object.
|    |- WSListener.hpp                    // Base WebSocket listener. Implements "pongs" and reads messages.
|    |- App.cpp
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
$ ./ws-client-binance.com-exe       # - run application.
```

## Install MbedTLS

```bash
git clone -b 'mbedtls-2.16.1' --single-branch --depth 1 --recurse-submodules https://github.com/ARMmbed/mbedtls

cd mbedtls
mkdir build && cd build

cmake ..
make install
```

