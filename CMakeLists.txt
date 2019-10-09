cmake_minimum_required(VERSION 3.9)
project(aabbcc
  VERSION 0.1.0
  LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include(GNUInstallDirs) # Define CMAKE_INSTALL_xxx: LIBDIR, INCLUDEDIR

option(AABBCC_BUILD_DEMOS "Build demos" OFF)
mark_as_advanced(AABBCC_BUILD_DEMOS)
option(AABBCC_WRAP_PYTHON "Create python wrapping (with pybind11)" OFF)
mark_as_advanced(AABBCC_WRAP_PYTHON)

add_library(aabbcc src/AABB.cc)
set_property(TARGET aabbcc PROPERTY POSITION_INDEPENDENT_CODE ON) #-fPIC
set(aabbcc_include_dir src)
set(aabbcc_export_file "${PROJECT_BINARY_DIR}/aabbccTargets.cmake")

target_include_directories(aabbcc PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${aabbcc_include_dir}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

install(TARGETS aabbcc
        EXPORT aabbccTargets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        )

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/${aabbcc_include_dir}/AABB.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/aabbcc)

# export to the build tree
export( TARGETS aabbcc
  NAMESPACE aabbcc::
  APPEND FILE ${aabbcc_export_file})

if(AABBCC_BUILD_DEMOS)
    add_subdirectory(demos)
endif()
if(AABBCC_WRAP_PYTHON)
  # Fetch pybind11
  include(FetchContent)
  FetchContent_Declare(
    pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11
    GIT_TAG v2.3
    )
  FetchContent_GetProperties(pybind11)
  if(NOT pybind11_POPULATED)
    FetchContent_Populate(pybind11)
    add_subdirectory(${pybind11_SOURCE_DIR} ${pybind11_BINARY_DIR})
  endif()

  set(CMAKE_INSTALL_PYTHONLIBDIR aabbcc) # Install folder for python libs
  set(CMAKE_BUILD_PYTHONLIBDIR ${PROJECT_BINARY_DIR}/aabbcc) # copy python libs at build time
  add_subdirectory(python)
endif()

# Install targets and config files
set(install_cmake_dir "${CMAKE_INSTALL_LIBDIR}/cmake/aabbcc")
install (EXPORT aabbccTargets
  NAMESPACE aabbcc::
  DESTINATION ${install_cmake_dir} )

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/cmake/aabbccConfig.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/aabbccConfigVersion.cmake
              DESTINATION ${install_cmake_dir} )

include(CMakePackageConfigHelpers)
write_basic_package_version_file(aabbccConfigVersion.cmake
  VERSION ${aabbcc_VERSION}
  COMPATIBILITY SameMajorVersion)

# Build tree
set(aabbcc_TARGETS_FILE ${aabbcc_export_file})
configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/aabbccConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/aabbccConfig.cmake
  INSTALL_DESTINATION ${install_cmake_dir}
  PATH_VARS aabbcc_TARGETS_FILE
  NO_CHECK_REQUIRED_COMPONENTS_MACRO # aabbcc does not provide components
  INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR}
  )

# Install tree
set(aabbcc_TARGETS_FILE ${CMAKE_INSTALL_PREFIX}/${install_cmake_dir}/aabbccTargets.cmake)
configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/aabbccConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/cmake/aabbccConfig.cmake
  INSTALL_DESTINATION ${install_cmake_dir}
  PATH_VARS aabbcc_TARGETS_FILE
  NO_CHECK_REQUIRED_COMPONENTS_MACRO # aabbcc does not provide components
  )

