#ifndef __FILEUTILS_H__
#define __FILEUTILS_H__

#include <string>

namespace OGLUtils {

class FileUtils {
public:
    static std::string readFile(const std::string& path);

private:
    FileUtils();
};

}

#endif // __FILEUTILS_H__