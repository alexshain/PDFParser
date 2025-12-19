cmake_minimum_required(VERSION 3.29)

project(pdf_parser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories("include")

find_package(PoDoFo REQUIRED)
message(STATUS "Found PoDoFo: ${PoDoFo_VERSION}")

add_executable(pdf_parser 
			src/main.cpp
			src/PDFParser.cpp
			src/AnsysReport/AnsysReport.cpp
			src/Composite/Component.cpp
			src/Composite/ReportComposite.cpp
			src/Composite/SettingsDataTable.cpp
			src/ParsingStrategy/ParsingContext.cpp
			src/ParsingStrategy/ParsingNestedTable.cpp
			src/ParsingStrategy/ParsingOrdinaryTable.cpp
			src/ParsingStrategy/ParsingStrategy.cpp)

target_link_libraries(pdf_parser podofo::podofo)