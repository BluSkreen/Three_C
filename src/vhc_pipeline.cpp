#include "vhc_pipeline.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>

VhcPipeline::VhcPipeline(const std::string& vertFilepath, const std::string& fragFilepath) {
  createGraphicsPipeline(vertFilepath, fragFilepath);
}

std::vector<char> VhcPipeline::readFile(const std::string &filepath) {
  std::ifstream file{filepath, std::ios::ate | std::ios::binary};

  if (!file.is_open()) {
    throw std::runtime_error("failed to open file: " + filepath);
  }

  // ate bit flag puts us at the end of the file
  size_t fileSize = static_cast<size_t>(file.tellg());
  // tellg with then give us the last position wich is the size
  std::vector<char> buffer(fileSize);

  // seek the start of the file to read data
  file.seekg(0);
  file.read(buffer.data(), fileSize);

  file.close();
  return buffer;
}

void VhcPipeline::createGraphicsPipeline(const std::string &vertFilepath,
                            const std::string &fragFilepath) {
  auto vertCode = readFile(vertFilepath);
  auto fragCode = readFile(fragFilepath);

  std::cout << "Vertex Shader Code Size: " << vertCode.size() << '\n';
  std::cout << "Fragment Shader Code Size: " << fragCode.size() << '\n';
}
