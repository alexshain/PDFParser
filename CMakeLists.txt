cmake_minimum_required(VERSION 3.29)

project(pdf_parser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories("include")

find_package(PoDoFo REQUIRED)
message(STATUS "Found PoDoFo: ${PoDoFo_VERSION}")

add_executable(pdf_parser 
			src/main.cpp)
target_link_libraries(pdf_parser podofo::podofo)