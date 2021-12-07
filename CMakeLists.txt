cmake_minimum_required(VERSION 3.20)
project(PostrgreeTest)

set(CMAKE_CXX_STANDARD 17)

# Need to set your specific version
# see https://github.com/actions/virtual-environments/issues/4243
# and https://github.com/taocpp/taopq/commit/ae5171f75a4254f3d5ff6cf8bf7cd724442b258b
set(PostgreSQL_ADDITIONAL_VERSIONS 14)
find_package(PostgreSQL REQUIRED)

add_subdirectory(deps/libpqxx)

add_executable(PostrgreeTest library.cpp)

target_link_libraries(PostrgreeTest PRIVATE pqxx)
                      #PostgreSQL::PostgreSQL)
