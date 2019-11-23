# DMTC Project

## What is Dmtc?
---

Dmtc is a next-generation blockchain protocol that was created for the diploma project. 

## License 
---

Dmtc Core is released under the terms of the MIT license. See https://opensource.org/licenses/MIT for more information.

## Developing
---

The `master0` branch is regularly built and tested by Dmtc's core developer Dmytro, and is typically the most stable version of the software, but this cannot be guaranteed at any given time.

## Building
---

To build from source on UNIX systems, follow these instructions.

### System requirements

C++ compilers are memory-hungry. It is recommended to have at least 1 GB of
memory available when compiling DMTC Core. With 512MB of memory or less
compilation will take much longer due to swap thrashing.

### Dependencies

These dependencies are required:

 Library     | Purpose          | Description
 ------------|------------------|----------------------
 libssl      | SSL Support      | Secure communications
 libboost    | Boost            | C++ Library

Optional dependencies:

 Library     | Purpose          | Description
 ------------|------------------|----------------------
 miniupnpc   | UPnP Support     | Firewall-jumping support
 libdb4.8    | Berkeley DB      | Wallet storage (only needed when wallet enabled)
 qt          | GUI              | GUI toolkit (only needed when GUI enabled)
 protobuf    | Payments in GUI  | Data interchange format used for payment protocol (only needed when GUI enabled)
 libqrencode | QR codes in GUI  | Optional for generating QR codes (only needed when GUI enabled)

For the versions used in the release, see [release-process.md](./dmtc/doc/release-process.md) under *Fetch and build inputs*.

For additional information about dependencies see [build-unix.md](./dmtc/doc/build-unix.md)
```
./autogen.sh
./configure --disable-tests --without-gui
make
make install # optional
```

