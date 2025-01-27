cmake_minimum_required(VERSION 3.0)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})
include_directories(${CMAKE_BINARY_DIR}/include)

include_directories(../lib/libledger-test/)

add_executable(ledger-core-net-tests main.cpp http_client_tests.cpp websocket_client_tests.cpp)

target_link_libraries(ledger-core-net-tests gtest gtest_main)
target_link_libraries(ledger-core-net-tests gmock)
target_link_libraries(ledger-core-net-tests ledger-core-static)
target_link_libraries(ledger-core-net-tests ledger-test)

target_include_directories(ledger-core-net-tests PUBLIC ../../../core/src)

include(CopyAndInstallImportedTargets)
if (SYS_OPENSSL)
    find_package(OpenSSL)
    if(WIN32)
        target_link_libraries( ledger-core-net-tests crypt32 ws2_32)
    endif()
    copy_install_imported_targets(ledger-core-net-tests OpenSSL::Crypto)
else()
    copy_install_imported_targets(ledger-core-net-tests crypto)
endif()

include(GoogleTest)
gtest_discover_tests(ledger-core-net-tests PROPERTIES "LABELS;unit")