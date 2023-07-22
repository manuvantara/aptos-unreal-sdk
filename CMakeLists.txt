
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

# Add the utils source files to the utils library target
add_library(Utils
    utils/hex_string.cpp
    utils/hex_string.h
)

# Add the aptos types source files to the aptos types library target
add_library(AptosTypes
    aptos_types/account_address.cpp
    aptos_types/account_address.h
)

# Create the executables for the unit tests
add_executable(BCSTests
    tests/BCSTests.cpp
)
add_executable(HexStringTests
    tests/hexStringTests.cpp
)
add_executable(AccountAddressTests
    tests/accountAddressTests.cpp
)

#Link Aptos Types to Utils
target_link_libraries(AptosTypes PRIVATE Utils)

# Link against the BCS library
target_link_libraries(BCSTests PRIVATE BCS)

# Link against the utils library
target_link_libraries(HexStringTests PRIVATE Utils)

# Link against the aptos types library
target_link_libraries(AccountAddressTests PRIVATE AptosTypes)
target_link_libraries(AccountAddressTests PRIVATE BCS)

# Include Catch2 folder
target_include_directories(BCSTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib)
target_include_directories(HexStringTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib)
target_include_directories(AccountAddressTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# Include Catch2 header file directly in the test files
target_compile_definitions(BCSTests PRIVATE CATCH_CONFIG_MAIN)
target_compile_definitions(HexStringTests PRIVATE CATCH_CONFIG_MAIN)
target_compile_definitions(AccountAddressTests PRIVATE CATCH_CONFIG_MAIN)

# Add the test as a test target for ctest
add_test(NAME BCSTests COMMAND BCSTests)
add_test(NAME HexStringTests COMMAND HexStringTests)
add_test(NAME AccountAddressTests COMMAND AccountAddressTests)
