#include <glDemo/utils/FileUtils.hpp>

#include <fstream>
#include <sstream>

using namespace OGLUtils;

std::string FileUtils::readFile(const std::string& path) {
    std::ifstream fileStream(path);
    std::stringstream buffer;
    buffer << fileStream.rdbuf();
    return buffer.str();
}
