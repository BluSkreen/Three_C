#!/bin/sh

source ~/packages/VulkanSDK/1.3.296.0/setup-env.sh

cmake -DCMAKE_PREFIX_PATH=/home/json/packages/SDL/build -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=DEBUG -DCMAKE_EXPORT_COMPILE_COMMANDS=1

