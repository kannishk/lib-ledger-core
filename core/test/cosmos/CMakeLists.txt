set( COSMOS_TESTS_NAME "ledger-core-cosmos-tests" )

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${CMAKE_BINARY_DIR}/include)

file(GLOB ledger-core-fixtures-srcs
        "../fixtures/*.cpp"
        "../fixtures/*.h"
        )

add_executable(${COSMOS_TESTS_NAME}
  main.cpp
  Fixtures.cpp
  address_test.cpp
  db_test.cpp
  transactions_test.cpp
  AccountTests.cpp
  parsers_test.cpp
  ${ledger-core-fixtures-srcs}
  ../integration/BaseFixture.cpp
  ../integration/IntegrationEnvironment.cpp
  )
target_link_libraries(${COSMOS_TESTS_NAME} gtest gtest_main)
target_link_libraries(${COSMOS_TESTS_NAME} ledger-core-static)
target_link_libraries(${COSMOS_TESTS_NAME} ledger-test)
target_include_directories(${COSMOS_TESTS_NAME} PUBLIC ../../../qt-host)
target_include_directories(${COSMOS_TESTS_NAME} PUBLIC ../../../core/src)
target_include_directories(${COSMOS_TESTS_NAME} PUBLIC ../lib/libledger-test)

include(CopyAndInstallImportedTargets)
if (SYS_OPENSSL)
    find_package(OpenSSL)
    if(WIN32)
        target_link_libraries( ${COSMOS_TESTS_NAME} ws2_32 crypt32 )
    endif()	
    copy_install_imported_targets(${COSMOS_TESTS_NAME} OpenSSL::Crypto)
else()
    copy_install_imported_targets(${COSMOS_TESTS_NAME} crypto)
endif()

if (SYS_LIBUV)
    copy_install_imported_targets(${COSMOS_TESTS_NAME} PkgConfig::UV)
else()
    copy_install_imported_targets(${COSMOS_TESTS_NAME} uv)
endif()

include(GoogleTest)
gtest_discover_tests(ledger-core-cosmos-tests PROPERTIES "LABELS;unit")
