cmake_minimum_required (VERSION 2.6)


project (swighandles)


find_package(PythonInterp)
find_package(PythonLibs)
find_package(SWIG REQUIRED)


include(${SWIG_USE_FILE})

include_directories(${PYTHON_INCLUDE_PATH})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})

add_library(standard STATIC a.cpp Standard_Transient.cpp a.h Standard_Transient.h )

set_source_files_properties(standard.i PROPERTIES CPLUSPLUS ON)

swig_add_module(standard python "standard.i" )
swig_link_libraries(standard ${PYTHON_LIBRARIES} standard)

