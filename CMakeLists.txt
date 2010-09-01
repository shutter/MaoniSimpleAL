# Copyright (c) 2010 Stefan Hutter, University of Zurich

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(MaoniSimpleAL)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

find_package(Boost  REQUIRED)
find_package(GLEW   REQUIRED)
find_package(OpenGL REQUIRED)
find_package(OpenAL REQUIRED)
find_package(ALURE   REQUIRED)
find_package(Maoni  REQUIRED)

include_directories(include
  ${Boost_INCLUDE_DIRS}
  ${GLEW_INCLUDE_DIR}
  ${OpenGL_INCLUDE_DIRS}
  ${OpenAL_INCLUDE_DIR}
  ${ALURE_INCLUDE_DIR}
  ${Maoni_INCLUDE_DIRS}
  )

add_executable(MaoniSimpleAL 
  src/main.cpp
  src/sound.cpp
  )
  
target_link_libraries(MaoniSimpleAL ${Maoni_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES} ${OPENAL_LIBRARY} ${ALURE_LIBRARY})