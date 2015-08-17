cmake_minimum_required(VERSION 2.8)

#Project
set(prject_name test1)

project(${prject_name})

#Library
file(
  GLOB_RECURSE sources
  *.cpp *.h
)

add_EXECUTABLE(
  ${prject_name}
  ${sources}
)

include_directories(../../core/include)

#Linking
target_link_libraries(
  ${prject_name}
  Core
)
