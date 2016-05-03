CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

project(FloorDetect C CXX)

#set compile flags
if(WIN32)
  set(CMAKE_CXX_FLAGS_DEBUG "/D_DEBUG /MDd /Zi /Ob0 /Od /RTC1" CACHE STRING "extra compiler flags for debug" FORCE )
  set(CMAKE_C_FLAGS_DEBUG "/D_DEBUG /MDd /Zi /Ob0 /Od /RTC1" CACHE STRING "extra compiler flags for debug" FORCE )
else(WIN32)
  set(CMAKE_C_FLAGS_DEBUG "-pedantic " CACHE STRING "extra compiler flags for debug" FORCE )
  if(LINUX)
    set(CMAKE_C_FLAGS "-std=c++11 -fPIC -g3 -Wall -pipe -DVTK_EXCLUDE_STRSTREAM_HEADERS -Wl,--no-undefined" CACHE STRING "compiler flags always used" FORCE)
    set(CMAKE_CXX_FLAGS "-std=c++11 -fPIC -Wall -pipe -DVTK_EXCLUDE_STRSTREAM_HEADERS -Wl,--no-undefined" CACHE STRING "compiler flags always used" FORCE)
  else(LINUX)
    set(CMAKE_C_FLAGS "-std=c++11 -fPIC -g3 -Wall -pipe -DVTK_EXCLUDE_STRSTREAM_HEADERS" CACHE STRING "compiler flags always used" FORCE)
    set(CMAKE_CXX_FLAGS "-std=c++11 -fPIC -Wall -pipe -DVTK_EXCLUDE_STRSTREAM_HEADERS" CACHE STRING "compiler flags always used" FORCE)
  endif(LINUX)
  set(CMAKE_CXX_FLAGS_DEBUG "-std=c++11 -g3 " CACHE STRING "extra compiler flags for debug" FORCE )
endif(WIN32)


#Find a few packages
find_package(OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

#Detect OpenMP
FIND_PACKAGE(OpenMP)
if (OPENMP_FOUND)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
  option(USE_OPENMP "Use OpenMP for parallelization" ON)
else(OPENMP_FOUND)
  option(USE_OPENMP "Use OpenMP for parallelization" OFF)
endif (OPENMP_FOUND)

#set convenience paths
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin CACHE PATH "Single Directory for all Executables")
set(LIBRARY_OUTPUT_PATH    ${CMAKE_BINARY_DIR}/lib CACHE PATH "Single Directory for all Libraries")

#compile everything together
add_executable(FloorDetect FloorDetect.cpp)
target_link_libraries(FloorDetect ${OpenCV_LIBS} )

