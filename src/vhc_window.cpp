#include "vhc_window.hpp"
#include <algorithm>
#include <iterator>

/* SDL_Texture *playerTexture; */
/* SDL_FRect srcR, destR; */

namespace vhc {

VhcWindow::VhcWindow(const char *title, int width, int height, int xpos, int ypos, bool fullscreen)
    : title{title}, width{width}, height{height} {
  initWindow(xpos, ypos, fullscreen);
}
VhcWindow::~VhcWindow() {
  SDL_DestroyWindow(window);
  SDL_Quit();
  std::cout << "Game Cleaned" << std::endl;
}

void VhcWindow::initWindow(int xpos, int ypos, bool fullscreen) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("SDL_Init failed (%s)", SDL_GetError());
    isRunning = false;
    return;
  }

  SDL_WindowFlags sdlWindowFlags{0};
  sdlWindowFlags = SDL_WINDOW_VULKAN;
  if (fullscreen) {
    sdlWindowFlags = sdlWindowFlags | SDL_WINDOW_FULLSCREEN;
  }

  window = SDL_CreateWindow(title, width, height,
                            sdlWindowFlags);
  if (!window) {
    SDL_Log("SDL_CreateWindow failed (%s)", SDL_GetError());
    isRunning = false;
    return;
  }
  std::cout << "window created!" << std::endl;

  //*************
  // Vulkan
  Uint32 count_instance_extensions;
  const char *const *instance_extensions =
      SDL_Vulkan_GetInstanceExtensions(&count_instance_extensions);

  if (instance_extensions == NULL) {
    SDL_Log("SDL_Vulkan_GetInstanceExtensions failed (%s)", SDL_GetError());
    isRunning = false;
    return;
  }
  std::cout << "created instance extensions" << std::endl;

  int count_extensions = count_instance_extensions + 1;
  // This extension isn't supported by MoltenVK and
  // idk how to remove it but this works
  // VK_KHR_portability_enumeration
  // UPDATE: Below now filters the extension from the array of pointers/strings
  /* int count_extensions = count_instance_extensions; */

  /* MACOS FILTER FOR MOLTENVK */
  std::vector<const char *> vec_filtered_extensions;
  std::copy_if(instance_extensions,
               instance_extensions + count_instance_extensions,
               std::back_inserter(vec_filtered_extensions),
               [&count_extensions](const char *str) {
                 if (strcmp(str, "VK_KHR_portability_enumeration") != 0) {
                   return true;
                 } else {
                   count_extensions--;
                   return false;
                 }
               });
  // Create an array of pointers to const char
  const char **filtered_extensions =
      new const char *[vec_filtered_extensions.size() + 1];
  // Copy pointers from the vector to the array
  for (size_t i = 0; i < vec_filtered_extensions.size(); ++i) {
    filtered_extensions[i] = vec_filtered_extensions[i];
  }
  // Add a null terminator
  filtered_extensions[vec_filtered_extensions.size()] = nullptr;
  /* END OF FILTER FOR MOLTENVK */

  const char **extensions =
      (const char **)SDL_malloc(count_extensions * sizeof(const char *));
  extensions[0] = VK_EXT_DEBUG_REPORT_EXTENSION_NAME;
  SDL_memcpy(&extensions[1], filtered_extensions,
             count_instance_extensions * sizeof(const char *));

  std::cout << "malloc extensions" << std::endl;
  std::cout << count_extensions << std::endl;
  std::cout << *extensions << std::endl;
  std::cout << *(extensions + 1) << std::endl;
  std::cout << *(extensions + 2) << std::endl;
  /* std::cout << *(extensions + 3) << std::endl; */
  /* // std::cout << *(extensions+4) << std::endl; */

  /* VkApplicationInfo appInfo{}; */
  VkApplicationInfo appInfo{};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pNext = NULL;
  appInfo.pApplicationName = "Hello Vulkan App";
  appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.pEngineName = "helloVK",
  appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0),
  appInfo.apiVersion = VK_API_VERSION_1_0;

  std::vector<const char *> layerNames{};
  // uncomment below if you want to use validation layers
  // layerNames.push_back("VK_LAYER_LUNARG_standard_validation");

  VkInstanceCreateInfo info{};
  info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  info.pApplicationInfo = &appInfo;
  info.enabledLayerCount = layerNames.size();
  info.ppEnabledLayerNames = layerNames.data();
  info.enabledExtensionCount = count_extensions;
  info.ppEnabledExtensionNames = extensions;

  VkResult res;
  VkInstance instance;
  res = vkCreateInstance(&info, NULL, &instance);
  if (res != VK_SUCCESS) {
    // do some error checking
    SDL_Log("vkCreateInstance failed (%s)", SDL_GetError());
    /* std::cout << "failed to create a vulkan instance!" << std::endl; */
    isRunning = false;
    return;
  }
  SDL_free(extensions);
  std::cout << "created instance" << std::endl;

  VkSurfaceKHR surface;
  /* VkAllocationCallbacks allocator; */
  if (!SDL_Vulkan_CreateSurface(window, instance, NULL, &surface)) {
    // failed to create a surface!
    std::cout << "failed to create a surface!" << std::endl;
    isRunning = false;
    return;
  }
  std::cout << "created surface" << std::endl;
  //*************

  /* openGLContext = SDL_GL_CreateContext(&window); */

  /* SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); */
  isRunning = true;

  /* SDL_Surface *tmpSurface = IMG_Load("assets/Sprite-0001.png"); */
  /* playerTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface); */
  /* SDL_DestroySurface(tmpSurface); */
};

void VhcWindow::handleEvents() {
  SDL_Event event;
  SDL_PollEvent(&event);
  if (event.type == SDL_EVENT_QUIT) {
    isRunning = false;
  }
};

/* void VhcWindow::update() { */
/*   /1* cnt++; *1/ */
/*   /1* destR.h = 32; *1/ */
/*   /1* destR.w = 32; *1/ */
/*   /1* destR.x = cnt; *1/ */
/*   /1* std::cout << "cnt: " << cnt << std::endl; *1/ */
/* }; */

/* void VhcWindow::render() { */
/*   /1* SDL_SetRenderDrawColor(renderer, 80, 80, 80, SDL_ALPHA_OPAQUE); *1/ */
/*   /1* SDL_RenderClear(renderer); *1/ */
/*   /1* SDL_RenderTexture(renderer, playerTexture, NULL, &destR); *1/ */
/*   /1* SDL_RenderPresent(renderer); *1/ */
/* }; */

/* void VhcWindow::clean() { */
/*   /1* SDL_DestroyRenderer(renderer); *1/ */
/*   /1* SDL_DestroyWindow(window); *1/ */
/*   /1* SDL_Quit(); *1/ */
/*   /1* std::cout << "Game Cleaned" << std::endl; *1/ */
/* }; */

}
