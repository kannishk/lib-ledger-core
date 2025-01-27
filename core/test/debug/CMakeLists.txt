cmake_minimum_required(VERSION 3.0)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${CMAKE_BINARY_DIR}/include)

include_directories(../lib/libledger-test/)

add_executable(ledger-core-debug-tests main.cpp logger_test.cpp)

target_link_libraries(ledger-core-debug-tests gtest gtest_main)
target_link_libraries(ledger-core-debug-tests ledger-core-static)
target_link_libraries(ledger-core-debug-tests ledger-test)

include(CopyAndInstallImportedTargets)
if (SYS_OPENSSL)
    find_package(OpenSSL)
    if(WIN32)
        target_link_libraries( ledger-core-debug-tests ws2_32 crypt32 )
    endif()
    copy_install_imported_targets(ledger-core-debug-tests OpenSSL::Crypto)
else()
    copy_install_imported_targets(ledger-core-debug-tests crypto)
endif()

include(GoogleTest)
gtest_discover_tests(ledger-core-debug-tests PROPERTIES "LABELS;unit")