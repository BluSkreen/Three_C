cmake_minimum_required(VERSION 3.11)

project(Vulkan_Hand_Crank CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++20")
set(source_dir "${PROJECT_SOURCE_DIR}/src/")

find_package(SDL3 REQUIRED)

if(CMAKE_HOST_APPLE)

  find_library(MoltenVK NAMES MoltenVK)

elseif(CMAKE_HOST_UNIX)

  find_package(Vulkan REQUIRED)
  # find_package(SDL3_image REQUIRED)

elseif(CMAKE_HOST_WIN32)

endif()

file(GLOB source_files "${source_dir}/*.cpp")
add_executable(${PROJECT_NAME} ${source_files})

if(CMAKE_HOST_APPLE)

  target_include_directories(
    ${PROJECT_NAME}
    PUBLIC "/Users/json3b/packages/VulkanSDK/1.3.296.0/macOS/include")
  # include(CMakePrintHelpers) cmake_print_variables(MoltenVK)
  target_link_libraries(${PROJECT_NAME} PUBLIC ${MoltenVK})
  # COMMENT ALSO WORKS WHEN BUILDT MoltenVK
  # target_include_directories(${PROJECT_NAME} PRIVATE
  # "${PROJECT_SOURCE_DIR}/dependencies/MoltenVK/include")
  # target_link_libraries(${PROJECT_NAME} PRIVATE
  # "${PROJECT_SOURCE_DIR}/dependencies/MoltenVK/static/MoltenVK.xcframework/macos-arm64_x86_64/libMoltenVK.a")

  target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

  target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
      "-framework Metal -framework Foundation -framework QuartzCore -framework CoreGraphics -framework IOSurface -framework IOKit -framework AppKit"
  )
  # -framework Cocoa -framework CoreVideo")

  set_target_properties(${PROJECT_NAME}
                        PROPERTIES INSTALL_RPATH @executable_path/../Frameworks)

elseif(CMAKE_HOST_UNIX)

  target_link_libraries(${PROJECT_NAME} PRIVATE Vulkan::Vulkan)
  target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3
  )# SDL3_image::SDL3_image)

elseif(CMAKE_HOST_WIN32)

  message(
    "This project is not configured for windows. Or maybe it is, but before
          you go changing this file remember to hydrate you big ol doofus.")
endif()
