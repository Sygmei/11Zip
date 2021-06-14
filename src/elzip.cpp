#include <fstream>
#include <iostream>

#include <elzip.hpp>
#include <fswrapper.hpp>
#include <unzipper.hpp>
#include <zipper.hpp>

namespace elz
{
    void extractZip(std::string zipname, std::string target)
    {
        ziputils::unzipper zipFile;
        zipFile.open(zipname.c_str());
        for (std::string filename : zipFile.getFilenames())
        {
            std::filesystem::path cDir(target + ((std::filesystem::path(filename).parent_path().string() == "") ? "" : "/") + std::filesystem::path(filename).parent_path().string());
            std::filesystem::path cFile(target + "/" + filename);
            std::filesystem::path fillPath;
            for (std::filesystem::path pathPart : cDir)
            {
                fillPath /= pathPart;
                if (!exists(fillPath))
                {
                    create_directory(fillPath);
                }
            }
            std::cout << "Opening file : " << filename << std::endl;
            zipFile.openEntry(filename.c_str());
            std::ofstream wFile;
            wFile.open(cFile.string(), std::ios_base::binary | std::ios_base::out);
            std::string dumped = zipFile.dump();
            wFile.write(dumped.c_str(), dumped.size());
            wFile.close();
        }
    }

    void extractFile(std::string zipname, std::string filename, std::string target)
    {
        ziputils::unzipper zipFile;
        zipFile.open(zipname.c_str());
        zipFile.openEntry(filename.c_str());
        std::ofstream wFile;
        wFile.open(target, std::ios_base::binary | std::ios_base::out);
        std::string dumped = zipFile.dump();
        wFile.write(dumped.c_str(), dumped.size());
        wFile.close();
    }

    void zipFolder(std::string folderName, std::string zipTarget)
    {
        if (!std::filesystem::is_directory(std::filesystem::path(folderName)))
        {
            throw std::runtime_error("'" + folderName + "' is not a valid directory");
        }
        if (folderName.back() != '/' || folderName.back() != std::filesystem::path::preferred_separator)
        {
            folderName += std::filesystem::path::preferred_separator;
        }
        if (zipTarget.empty())
        {
            const auto lastPathElement = std::filesystem::path(folderName).parent_path().filename();
            zipTarget = lastPathElement.string() + ".zip";
        }
        ziputils::zipper zipper;
        zipper.open(zipTarget.c_str());
        for (const auto& path : std::filesystem::recursive_directory_iterator(folderName))
        {
            auto absolutePath = path.path().string();
            auto relativePath = std::filesystem::relative(path.path(), folderName);
            auto pathStr = relativePath.string();
            zipper.addEntry(pathStr.c_str());

            std::ifstream fileContent;
            fileContent.open(absolutePath, std::ifstream::in | std::ifstream::binary);

            zipper << fileContent;

            zipper.closeEntry();
        }
        zipper.close();
    }
}