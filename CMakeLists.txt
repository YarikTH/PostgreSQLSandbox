cmake_minimum_required(VERSION 3.20)
project(PostrgreeTest)

set(CMAKE_CXX_STANDARD 17)

if(MSVC)
    set(MSVC_WARNING_OPTIONS)

    list(APPEND MSVC_WARNING_OPTIONS /W3)
    list(APPEND MSVC_WARNING_OPTIONS -wd5051) # disable "attribute '[un]likely' requires at least '/std:c++20'" warnings

    # Convert cmake list to string
    string(REPLACE ";" " " MSVC_WARNING_OPTIONS "${MSVC_WARNING_OPTIONS}")

    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${MSVC_WARNING_OPTIONS}")
endif()

# Need to set your specific version
# see https://github.com/actions/virtual-environments/issues/4243
# and https://github.com/taocpp/taopq/commit/ae5171f75a4254f3d5ff6cf8bf7cd724442b258b
set(PostgreSQL_ADDITIONAL_VERSIONS 14)
find_package(PostgreSQL REQUIRED)

function(get_postgre_sql_bin result_var_name)
    get_target_property(postgre_sql_include_directories PostgreSQL::PostgreSQL INTERFACE_INCLUDE_DIRECTORIES)
    
    list(GET postgre_sql_include_directories 0 postgre_sql_first_include_dir)
    
    cmake_path(GET postgre_sql_first_include_dir PARENT_PATH postgre_sql_root)
    
    cmake_path(APPEND postgre_sql_root bin OUTPUT_VARIABLE POSTGRE_SQL_BIN)
    
    set(${result_var_name} "${POSTGRE_SQL_BIN}" PARENT_SCOPE)
endfunction()

get_postgre_sql_bin(POSTGRE_SQL_BIN)

# Fetch and setup libpqxx dependency
    include(FetchContent)
    
    FetchContent_Declare(
        libpqxx
        GIT_REPOSITORY https://github.com/jtv/libpqxx.git
        GIT_TAG 7.6.0
    )
    
    FetchContent_GetProperties(libpqxx)
    if(NOT libpqxx_POPULATED)
        FetchContent_Populate(libpqxx)
        add_subdirectory(${libpqxx_SOURCE_DIR} ${libpqxx_BINARY_DIR} EXCLUDE_FROM_ALL)
    endif()

add_executable(PostrgreeTest library.cpp)

target_link_libraries(PostrgreeTest PRIVATE pqxx)
                      #PostgreSQL::PostgreSQL)
