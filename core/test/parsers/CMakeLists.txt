cmake_minimum_required(VERSION 3.0)
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${CMAKE_BINARY_DIR}/include)

include_directories(../lib/libledger-test/)

add_executable(ledger-core-parser-tests
        main.cpp
        tx_parser.cpp
        websocket_notification_parser_tests.cpp)

target_link_libraries(ledger-core-parser-tests gtest gtest_main)
target_link_libraries(ledger-core-parser-tests ledger-core-static)
target_link_libraries(ledger-core-parser-tests ledger-test)
target_include_directories(ledger-core-parser-tests PUBLIC ../../../core/src)

include(CopyAndInstallImportedTargets)
if (SYS_OPENSSL)
    find_package(OpenSSL)
    if(WIN32)
        target_link_libraries( ledger-core-parser-tests crypt32 ws2_32)
    endif()
    copy_install_imported_targets(ledger-core-parser-tests OpenSSL::Crypto)
else()
    copy_install_imported_targets(ledger-core-parser-tests crypto)
endif()

include(GoogleTest)
gtest_discover_tests(ledger-core-parser-tests PROPERTIES "LABELS;unit")