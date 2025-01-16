#include "lve_window.h"

LveWindow *game = nullptr;

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    game = new LveWindow();

    game->init("SDL issue", 0, 0, 640, 480, false);

    while (game->running()) {
      game->handleEvents();
      game->update();
      game->render();
    }

    game->clean();

    return 0;
}

