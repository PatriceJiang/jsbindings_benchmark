#!/bin/bash
set -x

cmake -Bbuild-android \
 -DCMAKE_TOOLCHAIN_FILE="$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake"  \
 -DANDROID_PLATFORM=android-21 \
 -GNinja \
 -DCMAKE_BUILD_TYPE=Debug \
 -DANDROID_ABI=arm64-v8a
