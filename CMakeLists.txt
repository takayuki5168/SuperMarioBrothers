cmake_minimum_required(VERSION 3.5)

project(SuperMarioBrothers CXX)

#Compiler
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=gnu++14" COMPILER_SUPPORTS_CXX14)
if(COMPILER_SUPPORTS_CXX14)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXXX_FLAGS} -std=gnu++14")
else()
  message(FATAL_ERROR "コンパイラはC++14に対応していません")
endif()
message("Compiler:\n\t${CMAKE_CXX_COMPILER}")

#Set default build type to Release

#Set compile flags
#set(CMAKE_CXX_FLAGS "${CMKAE_CXX_FLAGS} -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer")

#set(SuperMarioBrothers ON)

#Sources and headers
file(GLOB MAIN_SOURCES ${CMAKE_CURRENT_LIST_DIR} *.cpp)
set(MAIN_SOURCE_DIR src)
foreach(source_dir IN LISTS MAIN_SOURCE_DIR)
  file(GLOB dir_sources ${CMAKE_CURRENT_LIST_DIR} ${source_dir}/*.cpp)
  set(MAIN_SOURCES ${MAIN_SOURCES} ${dir_sources})
endforeach()
include_directories(${CMAKE_CURRENT_LIST_DIR})

# Build main
add_executable(${PROJECT_NAME} ${MAIN_SOURCES})

find_package(SDL)

include_directories(${PROJECT_NAME} ${SDL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL_LIBRARY})

# Clean
add_custom_target(cmake-clean
  COMMAND rm -rf `find ${CMAKE_BINARY_DIR} -name \"*[cC][mM]ake*\" -and -not -name \"CMakeLists.txt\"`
  COMMAND rm -rf `find ${CMAKE_BINARY_DIR} -name \"Makefile\"`)
add_custom_target(full-clean
  COMMAND make clean
  COMMAND make cmake-clean)
