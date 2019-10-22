cmake_minimum_required (VERSION 2.6)


project (swighandles)

set(CMAKE_CXX_STANDARD 14)

find_package(PythonInterp)
find_package(PythonLibs)
find_package(SWIG REQUIRED)


include(${SWIG_USE_FILE})

include_directories(${PYTHON_INCLUDE_PATH})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})

add_library(standard STATIC
    src/a.cpp
    src/a.h
    src/Standard_Transient.cpp
    src/Standard_Transient.hxx )
set_property(TARGET standard PROPERTY POSITION_INDEPENDENT_CODE ON)

set_source_files_properties(src/standard.i PROPERTIES CPLUSPLUS ON DEPENDS src/occ_handle1.i)

include_directories(${PROJECT_SOURCE_DIR}/src)
swig_add_module(standard python src/standard.i)
swig_link_libraries(standard ${PYTHON_LIBRARIES} standard)


add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE standard)

add_custom_target(run_python_tests
    COMMAND
    ${CMAKE_COMMAND} -E env PYTHONPATH=${CMAKE_CURRENT_BINARY_DIR}
    ${PYTHON_EXECUTABLE}
    test.py
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test
)
