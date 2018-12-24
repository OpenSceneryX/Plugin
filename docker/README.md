# OpenSceneryX cross-compiling environment

Scripts in this directory provide an easy way to build the OpenSceneryX plugin for Windows,
Linux and OS X in a reproducible way. This is useful when you want to verify
that your changes work (or at least compile) for all supported platforms
without manually setting up three independent build environments.

These build tools are derived from the FlyWithLua project by Carsten Lynker (https://github.com/X-Friese/FlyWithLua).

## Prerequisites

  1. [Docker](https://docs.docker.com/install/) — provides containers for
     a reproducible build environment independent from the host system.
  2. GNU Make — provides an easy way to build container image and launch build
     processes.

## Usage

Assuming we're in the root directory of git repository, to build for all platforms:

    $ (cd docker; make)
    $ ls src/build-*/*.xpl
    src/build-lin/lin.xpl src/build-mac/mac.xpl src/build-win/win.xpl 

Build for a specific platform (`lin`, `mac` or `win`):

    $ (cd docker; make lin)

Start bash shell inside container, useful for various debugging needs or to
access platform-specific tools:

    $ (cd docker; make bash)
