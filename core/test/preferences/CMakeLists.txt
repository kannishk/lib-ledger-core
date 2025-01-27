cmake_minimum_required(VERSION 3.0)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${CMAKE_BINARY_DIR}/include)

include_directories(../lib/libledger-test/)

add_executable(ledger-core-preferences-tests main.cpp preferences_test.cpp)

target_link_libraries(ledger-core-preferences-tests gtest gtest_main)
target_link_libraries(ledger-core-preferences-tests ledger-core-static)
target_link_libraries(ledger-core-preferences-tests ledger-test)

include(CopyAndInstallImportedTargets)
if (SYS_OPENSSL)
    find_package(OpenSSL)
    if(WIN32)
        target_link_libraries( ledger-core-preferences-tests crypt32 ws2_32)
    endif()
    copy_install_imported_targets(ledger-core-preferences-tests OpenSSL::Crypto)
else()
    copy_install_imported_targets(ledger-core-preferences-tests crypto)
endif()

include(GoogleTest)
gtest_discover_tests(ledger-core-preferences-tests PROPERTIES "LABELS;unit")