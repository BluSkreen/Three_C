#pragma once

/* #include <vulkan/vulkan.hpp> */
#include <SDL3/SDL.h>
/* #include <SDL3/SDL_init.h> */
/* #include <SDL3/SDL_video.h> */
/* #include <SDL3/SDL_render.h> */
/* #include <SDL3_image/SDL_image.h> */
/* #include <SDL3/SDL_oldnames.h> */
/* #include <SDL3/SDL_rect.h> */
#include <SDL3/SDL_vulkan.h>
#include <vulkan/vulkan.h>
/* #include <vulkan/vulkan_core.h> */
#include <iostream>

class LveWindow {

public:
  LveWindow();
  ~LveWindow();

  void init(const char *titile, int xpos, int ypos, int windowWidth, int windowHeight,
            bool fullscreen);

  void handleEvents();
  void update();
  bool running() { return isRunning; }
  void render();
  void clean();

private:
  bool isRunning;
  int cnt = 0;
  SDL_Window *window;
  /* SDL_Renderer *renderer; */
};
