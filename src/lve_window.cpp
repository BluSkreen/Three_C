#include "lve_window.h"

/* SDL_Texture *playerTexture; */
/* SDL_FRect srcR, destR; */

LveWindow::LveWindow() {}
LveWindow::~LveWindow() {}

void LveWindow::init(const char *titile, int xpos, int ypos, int windowWidth,
                int windowHeight, bool fullscreen) {
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

  window = SDL_CreateWindow("Hello SDL Vulkan", windowWidth, windowHeight, sdlWindowFlags);
  if (!window) {
    SDL_Log("SDL_CreateWindow failed (%s)", SDL_GetError());
    isRunning = false;
    return;
  }
  std::cout << "window created!" << std::endl;

  /* renderer = SDL_CreateRenderer(window, "vkrenderer"); */
  /* if (!renderer) { */
  /*   SDL_Log("SDL_CreateRenderer failed (%s)", SDL_GetError()); */
  /*   isRunning = false; */
  /*   return; */
  /* } */
  /* std::cout << "renderer created!" << std::endl; */

  //*************
  // in some init function...

  Uint32 count_instance_extensions;
  const char * const *instance_extensions = SDL_Vulkan_GetInstanceExtensions(&count_instance_extensions);

  if (instance_extensions == NULL) {
    SDL_Log("SDL_Vulkan_GetInstanceExtensions failed (%s)", SDL_GetError());
    isRunning = false;
    return;
  }
  std::cout << "created instance extensions" << std::endl;
  /* std::cout << instance_extensions << std::endl; */
  /* std::cout << count_instance_extensions << std::endl; */
  // This extension isn't supported by MoltenVK and
  // idk how to remove it but this works
  // VK_KHR_portability_enumeration
  /* int count_extensions = count_instance_extensions + 1; */
  int count_extensions = count_instance_extensions;
  const char **extensions = (const char **)SDL_malloc(count_extensions * sizeof(const char *));
  extensions[0] = VK_EXT_DEBUG_REPORT_EXTENSION_NAME;
  SDL_memcpy(&extensions[1], instance_extensions, count_instance_extensions * sizeof(const char*));
  std::cout << "malloc extensions" << std::endl;
  std::cout << *extensions << std::endl;
  std::cout << *(extensions+1) << std::endl;
  std::cout << *(extensions+2) << std::endl;
  std::cout << *(extensions+3) << std::endl;
  /* // std::cout << *(extensions+4) << std::endl; */
  std::cout << count_extensions << std::endl;

  /* VkApplicationInfo appInfo{}; */
  VkApplicationInfo appInfo{};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pNext = NULL;
  appInfo.pApplicationName = "Hello Vulkan App";
  appInfo.applicationVersion = VK_MAKE_VERSION(1,0,0);
  appInfo.pEngineName = "helloVK",
  appInfo.engineVersion = VK_MAKE_VERSION(1,0,0),
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

void LveWindow::handleEvents() {
  SDL_Event event;
  SDL_PollEvent(&event);
  if (event.type == SDL_EVENT_QUIT) {
    isRunning = false;
  }
};

void LveWindow::update() {
  /* cnt++; */
  /* destR.h = 32; */
  /* destR.w = 32; */
  /* destR.x = cnt; */
  std::cout << "cnt: " << cnt << std::endl;
};

void LveWindow::render() {
  /* SDL_SetRenderDrawColor(renderer, 80, 80, 80, SDL_ALPHA_OPAQUE); */
  /* SDL_RenderClear(renderer); */
  /* SDL_RenderTexture(renderer, playerTexture, NULL, &destR); */
  /* SDL_RenderPresent(renderer); */
};

void LveWindow::clean() {
  /* SDL_DestroyRenderer(renderer); */
  SDL_DestroyWindow(window);
  SDL_Quit();
  std::cout << "Game Cleaned" << std::endl;
};
