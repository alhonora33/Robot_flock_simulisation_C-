# Include testing cmake module
include(CTest) 

# Find GTest
find_package(GTest REQUIRED)

# create the testing file and list of tests
set (TestToRun
  testmain.cpp
)

# create the testing file and list of tests
create_test_sourcelist (Tests Tests.cpp ${TestToRun})

# add the executable
add_executable (Tests ${Tests})

# Link GTest and pthread (required for GTest)
target_link_libraries (Tests GTest::GTest GTest::Main pthread)

# add the tests
add_test (NAME test_main COMMAND Tests testmain)