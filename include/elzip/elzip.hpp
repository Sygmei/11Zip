#pragma once

#include <fswrapper.hpp>
#include <string>

namespace elz
{
    using path = std::filesystem::path;

    void extractZip(path archive, path target = ".");
    void extractFile(path archive, path fileInArchive, path target = ".", std::string outFilename = "");
    void zipFolder(path folder, path archivePath = "");
}
