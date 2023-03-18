#include "elzip/elzip.hpp"

#include <iostream>
#include <cassert>

int main()
{
    const elz::path archive{"test_zip.zip"};
    const elz::path folder{"files"};

    try
    {
        elz::zipFolder(folder, archive);
        std::cout << "Zipping " << folder << " to " << archive << " succeeded!" << std::endl;
        return 0;
    }
    catch (const elz::zip_exception& e)
    {
        std::cerr << "Error zipping " << folder << " to " << archive << ": " << e.what() << std::endl;
        return 1;
    }
}
