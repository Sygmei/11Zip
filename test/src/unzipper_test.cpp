#include <gtest/gtest.h>

#include "elzip/elzip.hpp"

static const std::filesystem::path locAssetDir{ASSETS_DIR "_Live"};

class GithubTestFixture : public ::testing::Test {
protected:
	void SetUp() override {
		std::filesystem::copy(
			ASSETS_DIR,
			locAssetDir,
			std::filesystem::copy_options::overwrite_existing
				| std::filesystem::copy_options::recursive);
	}

	void TearDown() override {
		if (HasFailure()) {
			std::cout << "===== ===== assetContent ===== =====\n";
			for (const auto& it : std::filesystem::recursive_directory_iterator(
					 std::filesystem::path(locAssetDir))) {
				std::cout << " > " << it.path().u8string() << '\n';
#if also_prints_content_of_binary_files
				if (it.is_regular_file()) {
					auto file = std::ifstream(it.path());
					std::cout << std::string(
						(std::istreambuf_iterator<char>(file)),
						(std::istreambuf_iterator<char>()))
							  << '\n';
					file.close();
				}
#endif
			}
		}
		std::filesystem::remove_all(locAssetDir);
	}
};

TEST(UnzipFile, can_unzip_an_archive_which_contains_binary_files) // NOLINT
{
    EXPECT_EXIT({
        elz::extractZip(locAssetDir / "patch.zip", locAssetDir / "patch");
        exit(0);
        },
        ::testing::ExitedWithCode(0),
        "");
}