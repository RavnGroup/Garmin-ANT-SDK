# Unofficial ANT SDK

This is an altered version of the last released version of the ANT SDK from Dynastream Innovations, rearranged to compile the "ANT_DLL" to a shared library on both Linux and MacOS.

On Linux it requires that libusb be installed, and uses the IOKit framework on OS X.

It's a work in progress, distributed under the terms of the ANT+ Shared Source License. See License.md for details.


## Additional Build Dependencies

The project now uses a [cmake](https://cmake.org/) build system, so you'll need
to install that first.


## Building

    $ cmake -S . -B build
    $ cd build
    $ make
    $ make install


