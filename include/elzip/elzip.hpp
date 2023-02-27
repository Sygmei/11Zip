#pragma once

#include <string>
#include <vector>

#include <fswrapper.hpp>

namespace elz
{
    class zip_exception : public std::runtime_error
    {
    public:
        zip_exception(const std::string& error);
        ~zip_exception() override = default;
    };

    inline zip_exception::zip_exception(const std::string& error) : std::runtime_error(error)
    {
    }

    using path = std::filesystem::path;

    void extractZip(const path& archive, const path& target = ".", const std::string& password = "");
    void extractFile(const path& archive, const path& fileInArchive, const path& target = ".", std::string outFilename = "", const std::string& password = "");
    void zipFolder(const path& folder, path archivePath = "");
    void zipFiles(const std::vector<path>& files, path archivePath = "archive.zip");
}  // namespace elz
