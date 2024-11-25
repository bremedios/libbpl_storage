cmake_minimum_required(VERSION 3.25)

project(bpl_storage)

set(CMAKE_CXX_STANDARD 20)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
include_directories(include)

set(PUBLIC_HEADER include/bpl/storage/Json.h include/bpl/storage/Payload.h)
set(SOURCE_FILES src/Json.cpp src/Payload.cpp)

add_library(bpl_storage SHARED ${SOURCE_FILES} ${PUBLIC_HEADER} )

install(TARGETS bpl_storage DESTINATION lib)
install(FILES include/bpl/storage/Json.h DESTINATION include/bpl/storage)
install(FILES include/bpl/storage/Payload.h DESTINATION include/bpl/storage)
