# Copyright (c) 2023, Oracle and/or its affiliates. All rights reserved.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License, version 2.0, as
# published by the Free Software Foundation.
#
# This program is also distributed with certain software (including
# but not limited to OpenSSL) that is licensed under separate terms,
# as designated in a particular file or component or in included license
# documentation.  The authors of MySQL hereby grant you an
# additional permission to link the program and your derivative works
# with the separately licensed software that they have included with
# MySQL.
#
# Without limiting anything contained in the foregoing, this file,
# which is part of MySQL Connector/C++, is also subject to the
# Universal FOSS Exception, version 1.0, a copy of which can be found at
# http://oss.oracle.com/licenses/universal-foss-exception.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU General Public License, version 2.0, for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin St, Fifth Floor, Boston, MA 02110-1301  USA

#
# Cmake configuration file for MySQL Connector/C++ package `mysql-concpp`
# =======================================================================
#
# See also: https://cmake.org/cmake/help/latest/manual/cmake-packages.7.html
#
# The following import targets are created by the package. All these targets
# are in the `mysql::` namespace.
#
# - concpp-xdevapi, concpp    -- the XDevAPI variant of the library
# - concpp-xdevapi-static, concpp-static -- static variant of the above
# - concpp-jdbc               -- the JDBC variant of the library
# - concpp-jdbc-static        -- static variant of the above
#
# Targets `mysql::concpp` and `mysql::concpp-static` are aliases for
# `mysql::concpp-xdevapi` and `mysql::concpp-xdevapi-static`, respectively.
#
# Also, the following variables are set:
#
# - Xxx_FOUND
# - Xxx_DEBUG_FOUND, Xxx_debug_FOUND -- (1)
# - Xxx_VERSION, Xxx_VERSION_CC
# - Xxx_ROOT_DIR -- (2)
# - Xxx_RUNTIME_LIBRARY_DIRS, Xxx_RUNTIME_LIBRARY_DIR -- (2,3)
# - Xxx_PLUGIN_DIR -- (4)
#
# In these variable names Xxx is either `MYSQL_CONCPP` or `mysql-concpp`,
# CC is version component: one of `MAJOR`, `MINOR` or `PATCH`.
#
# Note (1): These are set to true if debug libraries are available
# (see below).
#
# Note (2): Set only in case of a monolithic install (TGZ, ZIP, MSI).
#
# Note (3): Application that links to shared connector libraries must find
# these libraries at runtime. Depending on the platform this is achieved by
# configuring RPATH in the executable, editing environment variables
# or copying shared libraries to the location of the executable. In either
# case the _RUNTIME_LIBRARY_DIR(S) variable gives the location where shared
# connector libraries can be found.
#
# Note (4): The JDBC connector might require loading of authentication plugins
# at connection time (depending on authentication mechaism being used). These
# plugins are in the location given by _PLUGIN_DIR variable. Depending on
# the installation type it might be necessary to specify this location
# with connection configuration options for plugins to be correctly found
# at runtime (see: https://dev.mysql.com/doc/connector-cpp/8.2/en/connector-cpp-authentication.html)
#
# Note: The variables are put in the cache but if Xxx_FOUND is not set or
# is false then the module will be re-loaded and the other variables in
# the cache will be overwritten with newly detected values.
#
# Note: If mysql-concpp_FIND_VERBOSE is true when loading package diagnostic
# messages will be printed by this script.
#
# OpenSSL dependency
# ------------------
#
# Connector/C++ requires OpenSSL libraires. Depending on the platform and
# the installation type it is either expected that OpenSSL will be installed
# on the system or these libraries are bundled in the connector package.
# Connector library targets are configured to use OpenSSL from appropriate
# locations. This can be overriden by user -- if `mysql::openssl` target
# is defined prior to loading `mysql-concpp` package then this target is used
# to resolve dependency on OpenSSL library.
#
# Debug libraries
# ---------------
#
# When linking with static Connector/C++ library on Windows and building
# in debug mode the library built in debug mode is needed. Such debug builds
# of Connector/C++ are distributed as a separate package to be installed
# on top of the regular one. If debug libraries are available this script
# will detect them and configure mysql:: import targets so that they use
# debug variants of the library for builds in debug mode. The presence
# of debug libraries is indicated by setting _DEBUG_FOUND variable to true.
# It is also possible to request "debug" component using `REQUIRE debug`
# clause of `find_package()` command. If this is done then `find_package()`
# will fail if debug libraries were not found.
#
# Note: Debug libraries are needed and used only on Windows. For Linux
# separate packages with debug symbols are available that can be used
# to debug connector libraries but only release builds of these libararies
# are distributed.
#

# message(STATUS "mysql-concpp module config (${MYSQL_CONCPP_FOUND}, ${mysql-concpp_FOUND})")

if(mysql-concpp_FOUND)
  return()
endif()

function(message_info)
  if(NOT mysql-concpp_FIND_VERBOSE OR mysql-concpp_FIND_QUIETLY)
    return()
  endif()
  message(STATUS ${ARGV})
endfunction()


macro(main)

  # Set paths to look for headers and libraries either relative to this file
  # or in system-wide locations.
  #
  # FIXME: lib64/ or lib/ as appropriate for the platform

  if(EXISTS "include/mysqlx/xdevapi.h")

    set(MYSQL_CONCPP_ROOT_DIR ".")
    message_info("mysql-conccp module at: ${MYSQL_CONCPP_ROOT_DIR}")
    set(LIB_PATH "${MYSQL_CONCPP_ROOT_DIR}/lib64")
    set(INCLUDE_PATH "${MYSQL_CONCPP_ROOT_DIR}/include")

  else()

    # These are paths for RPM layout
    set(LIB_PATH "/usr/lib64")
    set(INCLUDE_PATH "/usr/include/mysql-cppconn-8")

  endif()


  # Headers must always be found first.

  find_includes()

  if(fail_message_includes)
    set_not_found(
      "Could NOT find MySQL Connector/C++ headers (${fail_message_includes})."
    )
    # Note: Error out early.
    message(FATAL_ERROR ${mysql-concpp_NOT_FOUND_MESSAGE})
  endif()

  message_info("mysql-concpp includes: ${MYSQL_CONCPP_INCLUDE_DIR}")

  # Note: On windows we look for the import library, not the DLL. This import
  # library normally is in a ./vsNN subfolder of the library path.

  set(import_suffix)
  if(WIN32)
    set(import_suffix PATH_SUFFIXES vs14)
  endif()

  # Find required dependencies. Currtently this looks for OpenSSL and defines
  # `mysql::openssl` interface library for it if found.

  find_deps()

  # Find connector libraries and define interface targets for the ones that
  # were found.

  find_connector(XDevAPI)
  find_connector(JDBC)

  # Aliases for -xdevapi* targets.

  foreach(suffix "" "-static" "-debug" "-static-debug")

    if(TARGET mysql::concpp-xdevapi${suffix})
      set(MYSQL_CONCPP_FOUND 1)
      add_library(mysql::concpp${suffix} ALIAS mysql::concpp-xdevapi${suffix})
    endif()

  endforeach()


  # Build the NOT_FOUND message.
  # Note: The different find_xxx() functions set the specific part
  # of the message, such as ${fail_message_devapi}, in case of failure.

  set(fail_message "Could NOT find MySQL Connector/C++.")

  if(fail_message_devapi) # AND MYSQL_CONCPP_FIND_REQUIRED_devapi)
    list(APPEND fail_message ${fail_message_devapi})
  elseif(fail_message_jdbc) # AND MYSQL_CONCPP_FIND_REQUIRED_jdbc)
    list(APPEND fail_message ${fail_message_jdbc})
  endif()

  set_not_found(${fail_message})

  include(FindPackageHandleStandardArgs)

  find_package_handle_standard_args(mysql-concpp
    REQUIRED_VARS
      mysql-concpp_VERSION
      MYSQL_CONCPP_FOUND
      MYSQL_CONCPP_INCLUDE_DIR
    VERSION_VAR mysql-concpp_VERSION
  #  HANDLE_COMPONENTS
    FAIL_MESSAGE "${mysql-concpp_NOT_FOUND_MESSAGE}"
  )

  # Set alternative variables

  foreach(var
    ROOT_DIR PLUGIN_DIR RUNTIME_LIBRARY_DIR RUNTIME_LIBRARY_DIRS DEBUG_FOUND
  )

    if(NOT DEFINED MYSQL_CONCPP_${var})
      continue()
    endif()

    set(mysql-concpp_${var} ${MYSQL_CONCPP_${var}} CACHE INTERNAL "mysql-concpp module config variable" FORCE)
    set(MYSQL_CONCPP_${var} ${MYSQL_CONCPP_${var}} CACHE INTERNAL "mysql-concpp module config variable" FORCE)

    if(var STREQUAL "RUNTIME_LIBRARY_DIR")
      set(MYSQL_CONCPP_RUNTIME_LIBRARY_DIRS
        "${MYSQL_CONCPP_RUNTIME_LIBRARY_DIR}"
      )
    endif()

  endforeach(var)

  foreach(ver "" _MAJOR _MINOR _PATCH _TWEAK _COUNT)

    if(NOT DEFINED mysql-concpp_VERSION${ver})
      continue()
    endif()

    set(mysql-concpp_VERSION${ver} ${mysql-concpp_VERSION${ver}} CACHE INTERNAL "mysql-concpp module config variable" FORCE)
    set(MYSQL_CONCPP_VERSION${ver} ${mysql-concpp_VERSION${ver}} CACHE INTERNAL "mysql-concpp module config variable" FORCE)

  endforeach(ver)

endmacro(main)


# Set the _NOT_FOUND message for the module from a list of strings passed
# to the function.

function(set_not_found)

  list(JOIN ARGN " " message)
  set(mysql-concpp_NOT_FOUND_MESSAGE "${message}" PARENT_SCOPE)

endfunction()


function(find_includes)

  #message(STATUS "Looking for headers at: ${INCLUDE_PATH}")

  find_path(MYSQL_CONCPP_INCLUDE_DIR
    NAMES mysqlx/xdevapi.h
    PATHS ${INCLUDE_PATH}
    NO_DEFAULT_PATH
    NO_CACHE
  )

  if(NOT MYSQL_CONCPP_INCLUDE_DIR)

    if(MYSQL_CONCPP_ROOT_DIR)
      set(fail_message_includes
        "at MYSQL_CONCPP_ROOT_DIR: ${INCLUDE_PATH}"
      )
    else()
      set(fail_message_includes "at ${INCLUDE_PATH}")
    endif()

    set_parent(fail_message_includes)
    return()

  endif()

  set_parent(MYSQL_CONCPP_INCLUDE_DIR)

endfunction()


# Find XDevAPI or JDBC connector libraries, as specified by parameter `which`
# and create interface library targets for them. Both shared and static
# variants are searched for.
#
# TODO: Currently this will fail if release libraries are not found, even
# if debug ones are present. Should this be changed?

function(find_connector which)

  if(which STREQUAL "JDBC")
    set(base_name "mysqlcppconn")
    set(target_name "concpp-jdbc")
  else()
    set(base_name "mysqlcppconn8")
    set(target_name "concpp-xdevapi")
  endif()


  # Find location of shared libraries or DLLs in case of Win (if not already
  # done).

  if(NOT MYSQL_CONCPP_RUNTIME_LIBRARY_DIR)

    # TODO: Use find_file() instead to get path to DLL on Win?

    file(GLOB found
      "${LIB_PATH}/*${base_name}*"
    )

    if(NOT found)

      set(fail_message_devapi "Could not find connector libraries")

      if(MYSQL_CONCPP_ROOT_DIR)
        list(APPEND fail_message_devapi
          "(at MYSQL_CONCPP_ROOT_DIR: ${LIB_PATH})."
        )
      else()
        list(APPEND fail_message_devapi
          "(at ${LIB_PATH})."
        )
      endif()

      set_parent(fail_message_devapi)
      return()

    endif()

    list(GET found 0 path)
    get_filename_component(MYSQL_CONCPP_RUNTIME_LIBRARY_DIR "${path}" DIRECTORY)

    message_info(
      "Runtime library folder: ${MYSQL_CONCPP_RUNTIME_LIBRARY_DIR}"
    )

    set_parent(MYSQL_CONCPP_RUNTIME_LIBRARY_DIR)

    set(
      MYSQL_CONCPP_PLUGIN_DIR "${MYSQL_CONCPP_RUNTIME_LIBRARY_DIR}/plugin"
      PARENT_SCOPE
    )

  endif()

  add_connector_target(${which} ${target_name} ${base_name})
  add_connector_target(${which} ${target_name}-static ${base_name}-static)

  set_parent(MYSQL_CONCPP_DEBUG_FOUND)

  if(TARGET mysql::${target_name}-static)

    set_target_properties(mysql::${target_name}-static PROPERTIES
      IMPORTED_LINK_INTERFACE_LANGUAGES CXX
      INTERFACE_COMPILE_DEFINITIONS STATIC_CONCPP
    )

    # Handle additional dependencies required for static library.

    if(WIN32)

      target_link_libraries(mysql::${target_name}-static INTERFACE Dnsapi)

    else()

      set(libs)

      if(NOT APPLE)
        list(APPEND libs pthread)
      endif()

      # On Solaris we additionally need couple more libs.

      if(CMAKE_SYSTEM_NAME MATCHES "SunOS")
        list(APPEND libs socket nsl)
      endif()

      if(NOT CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
        list(APPEND libs resolv dl)
      endif()

      target_link_libraries(mysql::${target_name}-static INTERFACE ${libs})

    endif()

    if(TARGET mysql::openssl)

      target_link_libraries(mysql::${target_name}-static INTERFACE mysql::openssl)

    endif()

  endif()

endfunction(find_connector)


# Create connector library import target named ${tgt} and pointing at library
# with base name ${base_name}. Target is not created if the library could
# not be found. If debug variant of library is found then it is used
# for IMPORT_LOCATION_DEBUG. In this case _DEBUG_FOUND variable is set to 1.

function(add_connector_target which tgt base_name)

  set(type "SHARED")
  if(tgt MATCHES "-static")
    set(type "STATIC")
  endif()

  set(lib_path)
  find_library(lib_path
    NAMES ${base_name}
    PATHS ${MYSQL_CONCPP_RUNTIME_LIBRARY_DIR}
    ${import_suffix}
    NO_DEFAULT_PATH
    NO_CACHE
  )

  if(NOT lib_path)
    message_info("Did not find ${which} ${type} library")
    return()
  endif()

  message_info("${which} ${type} library at: ${lib_path}")
  #message(STATUS "Creating target: mysql::${tgt}")

  add_library(mysql::${tgt} ${type} IMPORTED GLOBAL)

  set_target_properties(mysql::${tgt} PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${MYSQL_CONCPP_INCLUDE_DIR}"
  )

  # TODO: On Win set IMPORTED_LOCATION to the DLL path rather than the import library...

  set_target_properties(mysql::${tgt} PROPERTIES
    IMPORTED_LOCATION "${lib_path}"
  )

  if(WIN32)
    set_target_properties(mysql::${tgt} PROPERTIES
      IMPORTED_IMPLIB "${lib_path}"
    )
  endif()

  # Look for debug variant of the library.

  set(lib_path_debug)
  find_library(lib_path_debug
    NAMES ${base_name}
    PATHS ${MYSQL_CONCPP_RUNTIME_LIBRARY_DIR}
    ${import_suffix}/debug
    NO_DEFAULT_PATH
    NO_CACHE
  )

  if(lib_path_debug)

    message_info("Found debug variant of ${which} ${type} library at: ${lib_path_debug}")

    set(MYSQL_CONCPP_DEBUG_FOUND 1 PARENT_SCOPE)

    set_target_properties(mysql::${tgt} PROPERTIES
      IMPORTED_LOCATION_DEBUG "${lib_path_debug}"
    )

    if(WIN32)
      set_target_properties(mysql::${tgt} PROPERTIES
        IMPORTED_IMPLIB_DEBUG "${lib_path_debug}"
      )
    endif()

  endif()

endfunction(add_connector_target)


function(find_deps)

  if(TARGET mysql::openssl)
    message_info(
      "Using custom mysql::openssl target to resolve dependency on OpenSSL"
    )
    return()
  endif()

  set(ssl_lib)

  if(MYSQL_CONCPP_ROOT_DIR)

    # Try to find the bundled OpenSSL

    find_library(ssl_lib
      NAMES ssl libssl
      PATHS ${LIB_PATH}
      ${import_suffix}
      NO_DEFAULT_PATH
      NO_CACHE
    )

    find_library(ssl_crypto
      NAMES crypto libcrypto
      PATHS ${LIB_PATH}
      ${import_suffix}
      NO_DEFAULT_PATH
      NO_CACHE
    )

    if(NOT ssl_lib OR NOT ssl_crypto)
      message_info("Bundled OpenSSL was not found")
      set(ssl_lib false)
    endif()

  endif()

  # Note: For some reason interface libraries can not have names with "::"

  add_library(mysql_concpp_openssl INTERFACE)

  if(NOT ssl_lib)
    message_info("Using system OpenSSL libraries")
    set(prefix)
    if(WIN32)
      set(prefix "lib")
    endif()
    set(ssl_lib "${prefix}ssl")
    set(ssl_crypto "${prefix}crypto")
  else()
    message_info("Using bundled OpenSSL")
  endif()

  target_link_libraries(mysql_concpp_openssl INTERFACE
    ${ssl_lib} ${ssl_crypto}
  )

  add_library(mysql::openssl ALIAS mysql_concpp_openssl)

endfunction(find_deps)


# Sets given variable in the parent scope to its current value in this scope.
# Optionally, if new value is given after variable name, variable's value
# is changed first.

macro(set_parent var)
  #message(STATUS "set_parent: ${var} (${ARGN})")
  if(${ARGC} GREATER 1)
    set(${var} "${ARGN}")
  endif()
  set(${var} "${${var}}" PARENT_SCOPE)
endmacro()


main()
