file(GLOB_RECURSE CPPS  ./*.cpp )

# CMakeLists.txt for HALCON C++ examples
# Copyright (c) 2022-2023 by MVTec Software GmbH
cmake_minimum_required(VERSION 3.7.1)

# If policy CMP0091 is available, set it to NEW to enable use of the
# CMAKE_MSVC_RUNTIME_LIBRARY variable.
if(POLICY CMP0091)
  cmake_policy(SET CMP0091 NEW)
endif()

project(HalconCppExamples CXX)

# Append HALCON's cmake directory to the module path. This requires the
# HALCONEXAMPLES environment variable to be set.
file(TO_CMAKE_PATH "$ENV{HALCONEXAMPLES}" HALCONEXAMPLES)
list(APPEND CMAKE_MODULE_PATH "${HALCONEXAMPLES}/cmake")

# Option for using HALCON XL.
option(HALCON_XL "Use HALCON XL" OFF)

# Include common settings for HALCON projects
include(UseHALCON)

add_executable(show3d ${CPPS})
target_link_libraries(show3d HALCON::CppInt)

