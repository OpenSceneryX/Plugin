# Plugin

The OpenSceneryX Plugin.  This is experimental at this stage, but in future the plugin may be able to let the user know whether their OpenSceneryX install is up to date, as well as provide information on which scenery is using the library.

## Initial setup

1. Download latest X-Plane SDK from the [X-Plane Developer Website](https://developer.x-plane.com/sdk/plugin-sdk-downloads/) and put it in `src/` (e.g. `src/XPSDK301`).

2. Install and setup Docker. e.g. on the Mac:
    ```bash
    brew install docker
    brew install docker-machine
    brew services start docker-machine
    brew install virtualbox  # Requires SystemPreferences intervention
    docker-machine create default --virtualbox-cpu-count 6 --virtualbox-memory 8192
    ```

3. If you want syntax highlighting in your IDE to work correctly (e.g. IntelliSense in VSCode) then add the following defines to your environment setup. Set the appropriate architecture to `1` (`APL` in this example for Mac):

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
