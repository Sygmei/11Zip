# Add the source files
add_executable(test_extract_zip test_extract_zip.cpp)
add_executable(test_zip_file test_zip_file.cpp)
add_executable(test_zip_folder test_zip_folder.cpp)

# Link against the required libraries
target_link_libraries(test_extract_zip PRIVATE elzip)
target_link_libraries(test_zip_file PRIVATE elzip)
target_link_libraries(test_zip_folder PRIVATE elzip)

# Add the tests to CTest
enable_testing()
add_test(NAME test_extract_zip COMMAND test_extract_zip WORKING_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}")
add_test(NAME test_zip_file COMMAND test_zip_file WORKING_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}")
add_test(NAME test_zip_folder COMMAND test_zip_folder WORKING_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}")
