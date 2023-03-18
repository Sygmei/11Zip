#include "elzip/elzip.hpp"

#include <iostream>
#include <cassert>

int main()
{
    const elz::path archive{"test_zip.zip"};
    const elz::path target{"output"};

    try
    {
        elz::extractZip(archive, target);
        std::cout << "Extracting " << archive << " to " << target << " succeeded!" << std::endl;
        return 0;
    }
    catch (const elz::zip_exception& e)
    {
        std::cerr << "Error extracting " << archive << " to " << target << ": " << e.what() << std::endl;
        return 1;
    }
}
