/* #include "vhc_window.hpp" */

/* VhcWindow *game = nullptr; */

/* int main(int argc, char *argv[]) { */
/*   (void)argc; */
/*   (void)argv; */

/*   game = new VhcWindow(); */

/*   game->init("SDL issue", 0, 0, 640, 480, false); */

/*   while (game->running()) { */
/*     game->handleEvents(); */
/*     game->update(); */
/*     game->render(); */
/*   } */

/*   game->clean(); */

/*   return 0; */
/* } */

#include "first_app.hpp"
#include <cstdlib>
#include <exception>

int main() {
  vhc::FirstApp app{};

  try {
    app.run();
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
