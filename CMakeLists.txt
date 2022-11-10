cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(bulk VERSION ${PROJECT_VERSION})


set(INSTALL_GTEST OFF)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/GTEST_LINUX" 
"googletest")

include(GNUInstallDirs)

add_library(async SHARED async.cpp State_machine.cpp)
add_executable(bulk_server main.cpp)
add_executable(lib_test tests/tests.cpp)




set_target_properties(bulk_server async  lib_test PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    PUBLIC_HEADER async.h
)


target_link_libraries(bulk_server PRIVATE  
    async
)


target_include_directories(
    lib_test PRIVATE
   ${GTEST_INCLUDE_DIRS}
   ${CMAKE_CURRENT_SOURCE_DIR}

)

target_include_directories(
    bulk_server PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(lib_test PRIVATE
    gtest gtest_main
    async
)


if (MSVC)

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    target_compile_options(bulk_server PRIVATE
        /W3
    )

    target_compile_options(lib_test PRIVATE
        /W3
    )
else ()
    target_compile_options(bulk_server PRIVATE
        -Wall -Wextra -pedantic 
    )

    target_compile_options(lib_test PRIVATE
        -Wall -Wextra -pedantic 
    )
endif()

install(TARGETS bulk_server RUNTIME DESTINATION bin)

install(TARGETS async
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

add_test(lib_test lib_test)

