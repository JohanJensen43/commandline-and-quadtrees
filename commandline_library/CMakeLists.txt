project(commandline_library)

set( CMAKE_BUILD_TYPE Release)
set(CMAKE_C_FLAGS "-Wno-unused-result")
#set( CMAKE_BUILD_TYPE Debug)
#set(CMAKE_C_COMPILER /usr/bin/gcc)
#set(CMAKE_CXX_COMPILER /usr/bin/g++)

cmake_minimum_required(VERSION 2.6)


add_executable(main 
  main.c
  books.c
  librarian.c
  student.c
  bookStructure.h
  studentStructure.h
)