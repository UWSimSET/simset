cmake_minimum_required(VERSION 3.20)
project(SimSET VERSION 2.9.2 LANGUAGES C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

option(SIMSET_BUILD_SHARED "Build shared library" ON)
option(SIMSET_BUILD_STATIC "Build static library" ON)
option(SIMSET_BUILD_TOOLS "Build SimSET command-line tools" ON)

if(SIMSET_BUILD_TOOLS)
  add_executable(simset src/simset.c)
  target_link_libraries(simset PRIVATE SimSET::simset)
  target_link_libraries(simset PRIVATE SimSET::iface)
  target_compile_features(simset PRIVATE c_std_90)

  install(TARGETS simset
   RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
endif()

set(SIMSET_OS "" CACHE STRING
  "Override SimSET OS macro (e.g. DARWIN, MAC_10, LINUX, WINNT). Empty = auto.")

# ---- Collect sources ----
file(GLOB SIMSET_ALL_C CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

# Exclude entrypoint from the library (avoid main() in lib)
list(REMOVE_ITEM SIMSET_ALL_C "${CMAKE_CURRENT_SOURCE_DIR}/src/simset.c")

# ---- Decide OS macros for SimSET headers ----
set(SIMSET_DEFS "")
if(SIMSET_OS)
  list(APPEND SIMSET_DEFS "${SIMSET_OS}")
else()
  if(APPLE)
    list(APPEND SIMSET_DEFS DARWIN)
  elseif(WIN32)
    list(APPEND SIMSET_DEFS WINNT)
  elseif(UNIX)
    list(APPEND SIMSET_DEFS GEN_UNIX LINUX)
  endif()
endif()

# ---- Usage requirements for consumers (STIR) ----
add_library(simset_iface INTERFACE)
add_library(SimSET::iface ALIAS simset_iface)
set_target_properties(simset_iface PROPERTIES EXPORT_NAME iface)
target_include_directories(simset_iface INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/simset>
)
target_compile_definitions(simset_iface INTERFACE ${SIMSET_DEFS}
kSimSET_Path="${CMAKE_CURRENT_SOURCE_DIR}")

# ---- Object library (internal) ----
add_library(simset_obj OBJECT ${SIMSET_ALL_C})
target_link_libraries(simset_obj PUBLIC simset_iface)
target_compile_features(simset_obj PRIVATE c_std_90)
set_property(TARGET simset_obj PROPERTY POSITION_INDEPENDENT_CODE ON)

# ---- Static library ----
if(SIMSET_BUILD_STATIC)
  add_library(simset_static STATIC $<TARGET_OBJECTS:simset_obj>)
  add_library(SimSET::simset_static ALIAS simset_static)
  target_link_libraries(simset_static PUBLIC simset_iface)
  set_target_properties(simset_static PROPERTIES OUTPUT_NAME simset)
endif()

# ---- Shared library ----
if(SIMSET_BUILD_SHARED)
  add_library(simset_shared SHARED $<TARGET_OBJECTS:simset_obj>)
  add_library(SimSET::simset_shared ALIAS simset_shared)
  target_link_libraries(simset_shared PUBLIC simset_iface)
  set_target_properties(simset_shared PROPERTIES OUTPUT_NAME simset)
  if(APPLE)
    set_target_properties(simset_shared PROPERTIES INSTALL_NAME_DIR "@rpath")
  endif()
endif()

# ---- Choose default SimSET::simset alias ----
if(SIMSET_BUILD_SHARED)
  add_library(SimSET::simset ALIAS simset_shared)
elseif(SIMSET_BUILD_STATIC)
  add_library(SimSET::simset ALIAS simset_static)
endif()

# ---- Link libm on non-Apple UNIX ----
if(UNIX AND NOT APPLE)
  if(SIMSET_BUILD_STATIC)
    target_link_libraries(simset_static PRIVATE m)
  endif()
  if(SIMSET_BUILD_SHARED)
    target_link_libraries(simset_shared PRIVATE m)
  endif()
endif()

# ---- Install headers ----
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/"
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/simset"
  FILES_MATCHING PATTERN "*.h"
)

# ---- Install targets + export ----
install(TARGETS simset_iface EXPORT SimSETTargets)

if(SIMSET_BUILD_STATIC)
  install(TARGETS simset_static EXPORT SimSETTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )
endif()

if(SIMSET_BUILD_SHARED)
  install(TARGETS simset_shared EXPORT SimSETTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )
endif()

install(EXPORT SimSETTargets
  NAMESPACE SimSET::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SimSET
)

# ---- Package config ----
configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/SimSETConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/SimSETConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SimSET
)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/SimSETConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/SimSETConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/SimSETConfigVersion.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SimSET
)
