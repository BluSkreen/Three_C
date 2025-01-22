#include "first_app.hpp"

namespace vhc {

void FirstApp::run() {
  while (vhcWindow.running()) {
    vhcWindow.handleEvents();
    /* vhcWindow->update(); */
    /* vhcWindow->render(); */
  }
  /*   SDL_Event event; */
  /*   SDL_PollEvent(&event); */
  /*   if (event.type == SDL_EVENT_QUIT) { */
  /*     isRunning = false; */
  /*   } */

}
}
