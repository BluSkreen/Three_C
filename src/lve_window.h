#pragma once

#include <SDL3/SDL.h>
/* #include <SDL3_image/SDL_image.h> */
#include "lve_pipeline.h"
#include <SDL3/SDL_vulkan.h>
#include <iostream>
#include <vector>
#include <vulkan/vulkan.h>

class LveWindow {

public:
  LveWindow();
  ~LveWindow();

  void init(const char *titile, int xpos, int ypos, int windowWidth,
            int windowHeight, bool fullscreen);

  void handleEvents();
  void update();
  bool running() { return isRunning; }
  void render();
  void clean();

private:
  bool isRunning;
  int cnt = 0;
  SDL_Window *window;
  LvePipeline lvePipeline{"src/shaders/simple_shader.vert.spv",
                          "src/shaders/simple_shader.frag.spv"};
  /* SDL_Renderer *renderer; */
};
