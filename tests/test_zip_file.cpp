#include "elzip/elzip.hpp"

#include <iostream>
#include <cassert>

int main()
{
    const elz::path archive{"test_zip.zip"};
    const elz::path file{"files/test.txt"};

    try
    {
        elz::zipFiles({file}, archive);
        std::cout << "Zipping " << file << " to " << archive << " succeeded!" << std::endl;
        return 0;
    }
    catch (const elz::zip_exception& e)
    {
        std::cerr << "Error zipping " << file << " to " << archive << ": " << e.what() << std::endl;
        return 1;
    }
}
