cmake_minimum_required(VERSION 2.6)
set(TARGET prun-leveldb)
set(CMAKE_CXX_FLAGS "-std=c++0x -Wall -Wextra -Wno-unused-parameter -Wno-long-long -pedantic -pthread -g -O3")

find_path(LevelDB_INCLUDE_PATH NAMES leveldb/db.h HINTS
   /usr/include
   /usr/local/include
   $ENV{LEVELDB}
   $ENV{LEVELDB}/include
   leveldb/include
)
find_library(LevelDB_LIBRARY NAMES libleveldb.so HINTS
   /usr/lib
   /usr/local/lib
   $ENV{LEVELDB}
   $ENV{LEVELDB}/lib
   leveldb
)

if(LevelDB_INCLUDE_PATH AND LevelDB_LIBRARY)
  set(LevelDB_FOUND TRUE)
endif(LevelDB_INCLUDE_PATH AND LevelDB_LIBRARY)

if(LevelDB_FOUND)
   include_directories ( ${LevelDB_INCLUDE_PATH} )
   set(HAVE_LEVELDB_H TRUE)
else(LevelDB_FOUND)
   message("LevelDB not found!")
endif(LevelDB_FOUND)

set(SOURCE
  ${PROJECT_SOURCE_DIR}/dblevel.cpp
)

add_library(${TARGET} SHARED ${SOURCE})
target_link_libraries( ${TARGET} ${LevelDB_LIBRARY} -lrt -rdynamic )

install(TARGETS ${TARGET}
  LIBRARY DESTINATION lib${LIB_SUFFIX}
  BUNDLE DESTINATION library)
