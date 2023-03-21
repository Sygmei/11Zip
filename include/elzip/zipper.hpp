#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <minizip/mz_compat.h>

namespace ziputils
{
    class zipper
    {
    public:
        zipper();
        ~zipper();

        bool open(const char* filename, bool append = false);
        void close();
        [[nodiscard]] bool isOpen() const;

        bool addEntry(const char* filename);
        void closeEntry();
        [[nodiscard]] bool isOpenEntry() const;

        zipper& operator<<(std::istream& is);

    private:
        void getTime(tm_zip& tmZip);

    private:
        zipFile zipFile_;
        bool entryOpen_;
    };
};
