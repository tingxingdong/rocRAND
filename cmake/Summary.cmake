function (print_configuration_summary)
    message(STATUS "")
    message(STATUS "******** Summary ********")
    message(STATUS "General:")
    message(STATUS "  System                : ${CMAKE_SYSTEM_NAME}")
    message(STATUS "  C++ compiler          : ${CMAKE_CXX_COMPILER}")
    message(STATUS "  C++ compiler version  : ${CMAKE_CXX_COMPILER_VERSION}")
    message(STATUS "  CXX flags             : ${CMAKE_CXX_FLAGS}")
    message(STATUS "  Build type            : ${CMAKE_BUILD_TYPE}")
    get_directory_property(tmp DIRECTORY ${PROJECT_SOURCE_DIR} COMPILE_DEFINITIONS)
    message(STATUS "  Compile definitions   : ${tmp}")
    message(STATUS "")
    message(STATUS "  BUILD_SHARED_LIBS     : ${BUILD_SHARED_LIBS}")
    message(STATUS "  BUILD_TEST            : ${BUILD_TEST}")
    message(STATUS "  BUILD_BENCHMARK       : ${BUILD_BENCHMARK}")
endfunction()
