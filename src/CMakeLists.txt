# OpenSceneryX build script.
#
# Useful command line flags:
#   * -DCMAKE_BUILD_TYPE=XXX, where XXX is one of Debug, Release,
#     RelWithDebInfo and MinSizeRel. Default is Release.

cmake_minimum_required(VERSION 3.9)
project(OpenSceneryX VERSION 1.0.0 DESCRIPTION "OpenSceneryX X-Plane plugin")

# By default, use optimized release configuration.
if (NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif ()

set(CMAKE_CXX_STANDARD 14)

# Set include directories used by our code and dependencies.
include_directories("${CMAKE_SOURCE_DIR}/XPSDK301/CHeaders/Widgets")
include_directories("${CMAKE_SOURCE_DIR}/XPSDK301/CHeaders/Wrappers")
include_directories("${CMAKE_SOURCE_DIR}/XPSDK301/CHeaders/XPLM")
include_directories("${CMAKE_SOURCE_DIR}/include64")
include_directories("${CMAKE_SOURCE_DIR}/hidapi")
include_directories("${CMAKE_SOURCE_DIR}/.")
include_directories("${CMAKE_SOURCE_DIR}/FloatingWindows")
include_directories("${CMAKE_SOURCE_DIR}/imgui")

# Specify library search locations.
if (WIN32)
    list(APPEND CMAKE_LIBRARY_PATH "${CMAKE_SOURCE_DIR}/include64")
    list(APPEND CMAKE_LIBRARY_PATH "${CMAKE_SOURCE_DIR}/XPSDK301/Libraries/Win")
elseif (APPLE)
    list(APPEND CMAKE_FRAMEWORK_PATH "${CMAKE_SOURCE_DIR}/XPSDK301/Libraries/Mac")
    list(APPEND CMAKE_LIBRARY_PATH "${CMAKE_SOURCE_DIR}/mac_libs")
elseif (UNIX)

endif ()


# Enable all X-Plane SDK APIs up to the newest version.
add_definitions(-DXPLM200=1 -DXPLM210=1 -DXPLM300=1 -DXPLM301=1)
# Define platform macros.
add_definitions(-DAPL=$<BOOL:${APPLE}> -DIBM=$<BOOL:${WIN32}> -DLIN=$<AND:$<BOOL:${UNIX}>,$<NOT:$<BOOL:${APPLE}>>>)

# Force-enable exception support. This is most likely redundant, although for C
# code the default is the opposite. Since we are mixing C++ and C libraries,
# safer to set it on?
add_compile_options(-fexceptions)
# On UNIX systems this makes symbols non-exported by default. On Windows this
# option is simply ignored, since symbol visibility works differently there.
add_compile_options(-fvisibility=hidden)

# Enable stricter warnings and then disable some we are not interested in.
add_compile_options(-Wall -Wpedantic -Wshadow -Wfloat-equal -Wextra)
add_compile_options(-Wno-unused)

# Always use position-independent code and highest optimization level (FPS!).
add_compile_options(-O3 -fPIC)

# X-Plane plugin
# FIXME: Split this into individual targets.
list(APPEND OPENSCENERYX_SRCS OpenSceneryX.cpp)
#list(APPEND OPENSCENERYX_SRCS FloatingWindows/FLWIntegration.cpp FloatingWindows/ImGUIIntegration.cpp FloatingWindows/FloatingWindow.cpp)
#list(APPEND OPENSCENERYX_SRCS imgui/imgui.cpp imgui/imgui_demo.cpp imgui/imgui_draw.cpp imgui/imgui_lua_bindings.cpp)
#if (WIN32)
#    list(APPEND OPENSCENERYX_SRCS hidapi/windows/hid.c)
#elseif (APPLE)
#    list(APPEND OPENSCENERYX_SRCS hidapi/mac/hid.c)
#elseif (UNIX)
#    list(APPEND OPENSCENERYX_SRCS hidapi/linux/hid.c)
#endif ()

add_library(OpenSceneryX SHARED ${OPENSCENERYX_SRCS})

target_compile_features(OpenSceneryX PUBLIC cxx_std_11)

if (APPLE)
    # X-Plane supports OS X 10.10+, so this should ensure OpenSceneryX can run on
    # all supported versions.
    target_compile_options(OpenSceneryX PUBLIC -mmacosx-version-min=10.10)
    target_link_libraries(OpenSceneryX -mmacosx-version-min=10.10)
endif ()

# Link X-Plane plugin system libraries. They are only provided for OS X and Windows.
if (WIN32 OR APPLE)
    find_library(XPLM_LIBRARY NAMES XPLM XPLM_64.lib)
    find_library(XPWIDGETS_LIBRARY NAMES XPWidgets XPWidgets_64.lib)
    target_link_libraries(OpenSceneryX ${XPLM_LIBRARY} ${XPWIDGETS_LIBRARY})
endif ()

# Link OS-specific libraries HidApi depends on. Only supported for Windows and Linux.
if ((WIN32 OR UNIX) AND NOT APPLE)
    find_library(HIDAPIDEPS_LIBRARY NAMES setupapi udev)
    target_link_libraries(OpenSceneryX ${HIDAPIDEPS_LIBRARY})
endif ()

# Link library for dynamic loading of shared objects on UNIX systems.
if (UNIX)
    find_library(DL_LIBRARY dl)
    target_link_libraries(OpenSceneryX ${DL_LIBRARY})
endif ()

# Link OS X core system libraries.
if (APPLE)
    find_library(CORE_FOUNDATION_LIBRARY CoreFoundation)
    find_library(IOKIT_LIBRARY IOKit)
    target_link_libraries(OpenSceneryX ${IOKIT_LIBRARY} ${CORE_FOUNDATION_LIBRARY})
endif ()

if (WIN32)
    # Unlike OS X and Linux we build standard libraries statically since X-Plane does not provide them.
    target_link_libraries(OpenSceneryX -static-libgcc -static-libstdc++)
    # MSYS2 for some reason always links against winpthread, so we have to work around it by statically linking the
    # entire plugin. This allows building the plugin nativaly on Windows.
    target_link_libraries(OpenSceneryX -static)
elseif (APPLE)
    # Restrict set of symbols exported from the plugin. This reduces changes of
    # conflict with other plugins
    target_link_libraries(OpenSceneryX "-exported_symbols_list ${CMAKE_SOURCE_DIR}/OpenSceneryX.sym_mac")
elseif (UNIX)
    # Specify additional runtime search laths for dynamically-linked libraries.
    target_link_libraries(OpenSceneryX -Wl,-rpath=./Resources/plugins/OpenSceneryX/64)
    target_link_libraries(OpenSceneryX -Wl,-rpath=./Resources/plugins/OpenSceneryX/Modules)
    # Restrict set of symbols exported from the plugin. This reduces changes of
    # conflict with other plugins
    target_link_libraries(OpenSceneryX -Wl,--version-script -Wl,${CMAKE_SOURCE_DIR}/OpenSceneryX.sym)
endif ()

set_target_properties(OpenSceneryX PROPERTIES PREFIX "")
if (WIN32)
    set_target_properties(OpenSceneryX PROPERTIES OUTPUT_NAME "win")
elseif (APPLE)
    set_target_properties(OpenSceneryX PROPERTIES OUTPUT_NAME "mac")
elseif (UNIX)
    set_target_properties(OpenSceneryX PROPERTIES OUTPUT_NAME "lin")
endif ()
set_target_properties(OpenSceneryX PROPERTIES SUFFIX ".xpl")
