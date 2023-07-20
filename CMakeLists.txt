
cmake_minimum_required(VERSION 3.0)
project(AptosUnrealSDK, VERSION 0.1.0)

include(CTest)
enable_testing()

# Add the BCS source files to the BCS library target
add_library(BCS
    BCS/BCSDeserializer.cpp
    BCS/BCSDeserializer.h
    BCS/BCSSerializer.cpp
    BCS/BCSSerializer.h
)

# Create the executable for the unit tests
add_executable(UnitTests
    BCS/Test.cpp
)

# Link against the BCS library
target_link_libraries(UnitTests PRIVATE BCS)

# Include Catch2
target_include_directories(UnitTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# Include Catch2 header file directly in the test file
target_compile_definitions(UnitTests PRIVATE CATCH_CONFIG_MAIN)

# Add the test as a test target for ctest
add_test(NAME UnitTests COMMAND UnitTests)
