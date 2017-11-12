cmake_minimum_required (VERSION 2.6)

project(echo)


FILE(GLOB_RECURSE CPP_LISTS "*.cpp")
FILE(GLOB_RECURSE C_LISTS "*.c")
FILE(GLOB_RECURSE CC_LISTS "*.cc")
FILE(GLOB_RECURSE CXX_LISTS "*.cxx")
FILE(GLOB_RECURSE OTHER_LISTS " *.inl")


SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib
	CACHE PATH "Single directory for all static libraries.")
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib
	CACHE PATH "Single directory for all dynamic libraries.")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin
    CACHE PATH "Single directory for all executable.")



SET(SRC_FILES 
    main.cc
    common.cc
    Timestamp.cc
    ttcp_blocking.cc


	)
	


FIND_LIBRARY(/usr/local/lib /usr/lib64  /lib61 NO_DEFAULT_PATH)
SET(CXX_FLAGS -g -Wall -fPIC)
ADD_DEFINITIONS(${CXX_FLAGS} -std=c++0x)

LINK_DIRECTORIES(/usr/local/lib /usr/lib64)
set(LINK_LIBRARIES  boost_program_options)
ADD_EXECUTABLE(ttcp ${SRC_FILES})

TARGET_LINK_LIBRARIES(ttcp ${LINK_LIBRARIES})

