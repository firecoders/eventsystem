# Make sure gtest is installed
find_package ( GTest REQUIRED )
include_directories ( ${GTEST_INCLUDE_DIRS} )

# Use files from tests
file ( GLOB_RECURSE TEST_SRCS ${CMAKE_CURRENT_LIST_DIR} *.cpp )
include_directories ( ${CMAKE_CURRENT_LIST_DIR} )

# Create test executable
add_executable ( test_executable ${TEST_SRCS} )
target_link_libraries ( test_executable ${GTEST_BOTH_LIBRARIES} pthread )
