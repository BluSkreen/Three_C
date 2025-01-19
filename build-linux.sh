#!/bin/sh

source ~/packages/vulkan/1.4.304.0/setup-env.sh

cmake -DCMAKE_PREFIX_PATH=/Users/json3b/packages/build-SDL3 -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=1

