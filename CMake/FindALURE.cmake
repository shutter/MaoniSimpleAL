# - Try to find ALURE
# Once done this will define
#  
#  ALURE_FOUND        - system has ALURE
#  ALURE_INCLUDE_DIR  - the ALURE include directory
#  ALURE_LIBRARY      - Link these to use ALURE
#   

find_path(ALURE_INCLUDE_DIR alure.h
  PATHS
    /usr/include
    /usr/local/include
    /opt/local/include
    c:/alure/include
  PATH_SUFFIXES
    al/
    AL/
  )

find_library(ALURE_LIBRARY
  NAMES
    alure 
    libalure
  PATHS
    /usr/lib
    /usr/local/lib
    /opt/local/lib
    c:/alure/lib
  )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ALURE
  DEFAULT_MSG ALURE_LIBRARY ALURE_INCLUDE_DIR)

mark_as_advanced(ALURE_INCLUDE_DIR ALURE_LIBRARY)