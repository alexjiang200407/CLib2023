# CMakeList.txt : CMake project for POOEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)


set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project("MyCLib")


add_executable(
	"${PROJECT_NAME}"
)
set_target_properties(MyCLib PROPERTIES LINKER_LANGUAGE C)

include(cmake/headerlist.cmake)
include(cmake/sourcelist.cmake)

target_sources(${PROJECT_NAME} PRIVATE ${HEADER_FILES})
target_sources(${PROJECT_NAME} PRIVATE ${SOURCE_FILES})


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MyCLib PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
