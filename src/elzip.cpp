#include <fstream>
#include <iostream>

#include <elzip.hpp>
#include <unzipper.hpp>
#include <zipper.hpp>

namespace elz
{
    void _extractFile(ziputils::unzipper& zipFile, path filename, path target)
    {
        zipFile.openEntry(filename.string().c_str());
        std::ofstream wFile;
        wFile.open(target.string(), std::ios_base::binary | std::ios_base::out);
        std::string dumped = zipFile.dump();
        wFile.write(dumped.c_str(), dumped.size());
        wFile.close();
    }

    void extractZip(path archive, path target)
    {
        ziputils::unzipper zipFile;
        zipFile.open(archive.string().c_str());

        for (std::string filename : zipFile.getFilenames())
        {
            std::filesystem::path currentDir = target / std::filesystem::path(filename).parent_path();
            std::filesystem::create_directories(currentDir);
            std::filesystem::path currentFile = target / filename;

            _extractFile(zipFile, filename, currentFile.string());
        }
    }

    void extractFile(path archive, path fileInArchive, path target, std::string outFilename)
    {
        ziputils::unzipper zipFile;
        zipFile.open(archive.string().c_str());
        outFilename = (outFilename.empty() ? fileInArchive.string() : outFilename);
        std::filesystem::create_directories(target);
        _extractFile(zipFile, fileInArchive.string(), target / outFilename);
    }

    void zipFolder(path directory, path archivePath)
    {
        if (!std::filesystem::is_directory(std::filesystem::path(directory)))
        {
            throw std::runtime_error("'" + directory.string() + "' is not a valid directory");
        }
        if (archivePath.empty())
        {
            archivePath = std::filesystem::path(directory).filename().string() + ".zip";
        }
        ziputils::zipper zipper;
        zipper.open(archivePath.string().c_str());
        for (const auto& path : std::filesystem::recursive_directory_iterator(directory))
        {
            auto absolutePath = path.path();
            auto relativePath = std::filesystem::relative(absolutePath, directory);
            zipper.addEntry(relativePath.string().c_str());

            std::ifstream fileContent;
            fileContent.open(absolutePath, std::ifstream::in | std::ifstream::binary);

            zipper << fileContent;

            zipper.closeEntry();
        }
        zipper.close();
    }
}