cmake_minimum_required(VERSION 3.10)

project(harambe)

message(STATUS "==================")
message(STATUS "CONFIGURING harambe")
message(STATUS "==================")

macro(replace_flags flag newflag)
    FOREACH(flag_var CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE)
        IF(${flag_var} MATCHES ${flag})
            STRING(REGEX REPLACE "${flag}" "${newflag}" ${flag_var} "${${flag_var}}")
        ENDIF()
    ENDFOREACH(flag_var)
endmacro()

# Setup the make environment. #
################################
# Activate very verbose makefiles.
set(CMAKE_VERBOSE_MAKEFILE ON)
# Allow else() and endif() constructs (with empty parentheses)
set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true)

SET(CMAKE_BUILD_TYPE Debug CACHE STRING "default to debug" FORCE)

# Setup the cmake directory containing numerous cmake scripts and macros.
set(CMAKE_MODULE_PATH "${harambe_SOURCE_DIR}/cmake")

FIND_PACKAGE(FLEX)
FIND_PACKAGE(BISON)

# Put all source files into one variable. #
##########################################
set(SOURCES_COMMON
            main.cpp
            buildins.cpp
            AstNode.cpp
            Declaration.cpp
            FunctionDeclaration.cpp
            CodeGenContext.cpp
            VisitorSyntaxCheck.cpp
            VisitorPrettyPrint.cpp
            tokens.l
            parser.y
            GetOpt.cpp
            Array.cpp
            Range.cpp
   )

set(HEADER_COMMON
            buildins.h
            AstNode.h
            FunctionDeclaration.h
            CodeGenContext.h
            Visitor.h
            VisitorSyntaxCheck.h
            VisitorPrettyPrint.h
            GetOpt.h
   )

if(MSVC)
    source_group(Header\ Files FILES ${HEADER_COMMON})
    source_group(Source\ Files FILES ${SOURCE_COMMON})
endif()

BISON_TARGET(Parser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp)
FLEX_TARGET(Scanner tokens.l ${CMAKE_CURRENT_BINARY_DIR}/tokens.cpp )
ADD_FLEX_BISON_DEPENDENCY(Scanner Parser)

add_executable(harambe ${SOURCES_COMMON} ${HEADER_COMMON} ${BISON_Parser_OUTPUTS} ${FLEX_Scanner_OUTPUTS})

# Check for various language-stuff and compiler versions #
##########################################################

# Compiler-dependent and build-depended flags:
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(harambe PRIVATE -Wall)
elseif(MSVC)
    target_compile_definitions(harambe PRIVATE YY_NO_UNISTD_H)
    target_compile_definitions(harambe PRIVATE _SCL_SECURE_NO_WARNINGS)
    target_compile_definitions(harambe PRIVATE _CRT_SECURE_NO_WARNINGS)
    target_compile_definitions(harambe PRIVATE _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS)
    set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/tokens.cpp PROPERTIES COMPILE_DEFINITIONS __STDC_VERSION__=199901L)
endif()

# Debug or release ?
target_compile_definitions(harambe PRIVATE $<$<CONFIG:Debug>:_DEBUG>)

# Search for the different needed libs. #
#########################################

# We incorporate the CMake features provided by LLVM:
find_package(LLVM
  PATHS "${LLVM_ROOT}/lib/cmake/llvm" "$ENV{ProgramFiles}/lib/cmake/llvm")

if( LLVM_FOUND )
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${LLVM_DIR}")
else()
    message(FATAL_ERROR "LLVM installation not found. Set LLVM_ROOT to the installation root path.")
endif()

include(LLVMConfig)
message(STATUS "Found LLVM Package Version:${LLVM_PACKAGE_VERSION}")
message(STATUS "LLVM Built type : ${LLVM_BUILD_TYPE}")
string(REGEX MATCH "[0-9]+\\.[0-9]+" LLVM_VER ${LLVM_PACKAGE_VERSION} )
if(${LLVM_VER} VERSION_LESS "3.8" )
    message(FATAL_ERROR "LLVM version before 3.8 are not supported. Abort!")
endif()
if(NOT ${LLVM_VER} VERSION_EQUAL "6.0" )
    message(WARNING "LLVM version before ${LLVM_VER} is not tested.")
endif()

if(MSVC)
    if(NOT CMAKE_CL_64)
        message(FATAL_ERROR "Currently only 64bit compilation is supported!")
    endif()
endif()

# Add the compiler definitions of LLVM
if(MSVC)
    # In order to use it with target_compile_definitions we have to replace the -D
    # with a semicolon otherwise they are not correctly populated to MSVC and the
    # IntelliSense is broken (command line error).
    string(REPLACE "-D" ";" LLVM_DEFINITIONS ${LLVM_DEFINITIONS} )
endif()
target_compile_definitions(harambe PRIVATE ${LLVM_DEFINITIONS})
if( "${LLVM_BUILD_TYPE}" MATCHES  "Release|RelWithDebInfo|MinSizeRel")
  target_compile_definitions(harambe PRIVATE LLVM_NO_DUMP)
endif()

# Now set the header and library paths:
include_directories( ${LLVM_ROOT}/include )
link_directories( ${LLVM_ROOT}/lib )

# Let's suppose we want to build a JIT compiler with support for
# binary code :
llvm_map_components_to_libnames(REQ_LLVM_LIBRARIES mcjit interpreter native ipo)

if(NOT LLVM_ENABLE_RTTI)
    target_compile_definitions(harambe PRIVATE harambe_NO_RTTI)
    if(MSVC)
        target_compile_options(harambe PRIVATE /GR-)
    else()
        target_compile_options(harambe PRIVATE -fno-rtti)
    endif()
endif()

if(LLVM_ENABLE_EH AND CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(harambe PRIVATE -fexceptions)
endif()

set(VER_MAJ 0)
set(VER_MIN 2)
set(VER_REV 0)

configure_file(config.in ${harambe_SOURCE_DIR}/config.h)

# The compiling process. #
##########################

# Add additional include search directories.
target_include_directories(harambe PRIVATE ${harambe_SOURCE_DIR})
target_include_directories(harambe PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

set_property(TARGET harambe PROPERTY CXX_STANDARD 17)
set_property(TARGET harambe PROPERTY CXX_STANDARD_REQUIRED ON)

# Finally, we link the LLVM libraries to our executable:
target_link_libraries(harambe ${REQ_LLVM_LIBRARIES})
