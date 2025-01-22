#pragma once

#include <SDL3/SDL.h>
/* #include <SDL3_image/SDL_image.h> */
#include "vhc_pipeline.hpp"
#include <SDL3/SDL_vulkan.h>
#include <iostream>
#include <vector>
#include <vulkan/vulkan.h>

namespace vhc {

class VhcWindow {

public:
  VhcWindow(const char *title, int width, int height, int xpos, int ypos, bool fullscreen);
  ~VhcWindow();

  // Delete copy contructors
  VhcWindow(const VhcWindow &) = delete;
  VhcWindow &operator=(const VhcWindow &) = delete;
  /* void init(const char *title, int xpos, int ypos, int windowWidth, */
  /*           int windowHeight, bool fullscreen); */

  void handleEvents();
  /* void update(); */
  bool running() { return isRunning; }
  /* void render(); */
  /* void clean(); */

private:
  void initWindow(int xpos, int ypos, bool fullscreen);

  const char *title;
  const int width;
  const int height;

  std::string windowName;
  SDL_Window *window;

  /* VhcPipeline lvePipeline{"src/shaders/simple_shader.vert.spv", */
  /*                         "src/shaders/simple_shader.frag.spv"}; */

  bool isRunning;
  /* int cnt = 0; */
  /* SDL_Renderer *renderer; */
};

}
