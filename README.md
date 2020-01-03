# Plugin

The OpenSceneryX Plugin.  This is experimental at this stage, but in future the plugin may be able to let the user know whether their OpenSceneryX install is up to date, as well as provide information on which scenery is using the library.

## Initial setup

1. Download latest X-Plane SDK from the [X-Plane Developer Website](https://developer.x-plane.com/sdk/plugin-sdk-downloads/) and put it into `src/lib/` (e.g. `src/lib/XPSDK301`).

1. Download latest CURL Windows binary from [the official CURL website](https://curl.haxx.se/windows/) and:

    1. Put the contents of `lib/` into `src/lib/CURL/` (i.e. `src/lib/CURL/libcurl.a` and `src/lib/CURL/libcurl.dll.a`).
    1. Copy `include/` into `src/lib/CURL/` (i.e. `src/lib/CURL/include/`).

1. Check out latest CURL from https://github.com/curl/curl.git into src (e.g. `src/curl`).

1. Copy the special MacOSX Framework file that William Good has produced to create a static curl lib on Mac from https://github.com/sparker256/LiveTraffic/blob/master/docs/MacOSX-Framework64Lib into `src/curl`.

1. Build curl on Mac:

    ```
    ./buildconf
    ./configure
    ./MacOSX-Framework64Lib
    ```

1. Copy built `libcurl.framework` into `src/lib/CURL/` (i.e. `src/lib/CURL/libcurl.framework`).

1. Install and setup Docker. e.g. on the Mac:

    ```bash
    brew install docker
    brew install docker-machine
    brew services start docker-machine
    brew install virtualbox  # Requires SystemPreferences intervention
    docker-machine create default --virtualbox-cpu-count 6 --virtualbox-memory 8192
    ```

1. If you want syntax highlighting in your IDE to work correctly (e.g. IntelliSense in VSCode) then add the following defines to your environment setup. Set the appropriate architecture to `1` (`APL` in this example for Mac):

    ```
    XPLM200
    XPLM210
    XPLM300
    XPLM301
    APL=1
    LIN=0
    IBM=0
    ```

    _See https://developer.x-plane.com/sdk/plugin-sdk-downloads/ for the latest info on SDK versions_

## Shell Setup

```bash
eval $(docker-machine env default)
```

## Building

```bash
./build.sh
```
