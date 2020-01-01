# Plugin

The OpenSceneryX Plugin.  This is experimental at this stage, but in future the plugin may be able to let the user know whether their OpenSceneryX install is up to date, as well as provide information on which scenery is using the library.

## Initial setup of Docker on Mac (using Brew)

```bash
brew install docker
brew install docker-machine
brew services start docker-machine
brew install virtualbox  # Requires SystemPreferences intervention
docker-machine create default --virtualbox-cpu-count 6 --virtualbox-memory 8192
```

## Shell Setup

```bash
eval $(docker-machine env default)
```

## Building

```bash

```
