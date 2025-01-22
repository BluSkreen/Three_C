#pragma once

#include "vhc_window.hpp"

// GET THE REFRACTORED CODE FROM NOBARA
// AND CHANGE THE WINDOW.HPP

namespace vhc {
class FirstApp {
public:
  static constexpr int WIDTH = 800;
  static constexpr int HEIGHT = 600;

  void run();

private:
  VhcWindow vhcWindow{"Hello Vulkan!", WIDTH, HEIGHT, 0, 0, false};
};
} // namespace vhc
