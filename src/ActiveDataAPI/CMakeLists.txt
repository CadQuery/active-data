project(ActiveDataAPI)

#------------------------------------------------------------------------------
# Common
#------------------------------------------------------------------------------

set (H_FILES
  ActAPI.h
  ActAPI_Common.h
  ActAPI_IAlgorithm.h
  ActAPI_IDataCursor.h
  ActAPI_ILogger.h
  ActAPI_IModel.h
  ActAPI_INode.h
  ActAPI_IParameter.h
  ActAPI_IPartition.h
  ActAPI_IPlotter.h
  ActAPI_IProgressNotifier.h
  ActAPI_ITreeFunction.h
  ActAPI_TxData.h
  ActAPI_Variables.h
  ActAPI_Version.h
)

set (CPP_FILES
  ActAPI_IAlgorithm.cpp
  ActAPI_IDataCursor.cpp
  ActAPI_ILogger.cpp
  ActAPI_IModel.cpp
  ActAPI_INode.cpp
  ActAPI_IParameter.cpp
  ActAPI_IPartition.cpp
  ActAPI_IPlotter.cpp
  ActAPI_IProgressNotifier.cpp
  ActAPI_ITreeFunction.cpp
  ActAPI_Variables.cpp
)

#------------------------------------------------------------------------------
# OpenCascade libraries
#------------------------------------------------------------------------------

set (OCCT_LIB_FILES
  TKernel
  TKMath
)

#------------------------------------------------------------------------------
# TBB libraries
#------------------------------------------------------------------------------

if (USE_TBB)
  set (TBB_LIB_FILES
    tbb
  )
endif()

#------------------------------------------------------------------------------
# Add sources
#------------------------------------------------------------------------------

foreach (FILE ${H_FILES})
  set (src_files ${src_files} ${FILE})
  source_group ("Header Files" FILES "${FILE}")
endforeach (FILE)

foreach (FILE ${CPP_FILES})
  set (src_files ${src_files} ${FILE})
  source_group ("Source Files" FILES "${FILE}")
endforeach (FILE)

#------------------------------------------------------------------------------
# Configure includes
#------------------------------------------------------------------------------

# Create include variable
set (ActiveDataAPI_include_dir_loc "${CMAKE_CURRENT_SOURCE_DIR};")
#
set (ActiveDataAPI_include_dir ${ActiveDataAPI_include_dir_loc} PARENT_SCOPE)

include_directories ( ${ActiveDataAPI_include_dir_loc}
                      ${3RDPARTY_OCCT_INCLUDE_DIR} )

if (USE_TBB)
  include_directories ( ${3RDPARTY_tbb_INCLUDE_DIR} )
endif()

#------------------------------------------------------------------------------
# Create library
#------------------------------------------------------------------------------

add_library (ActiveDataAPI SHARED
  ${H_FILES} ${CPP_FILES}
)

#------------------------------------------------------------------------------
# Dependencies
#------------------------------------------------------------------------------

if (USE_TBB)
  if (3RDPARTY_tbb_LIBRARY_DIR_DEBUG)
    link_directories(${3RDPARTY_tbb_LIBRARY_DIR_DEBUG})
  else()
    link_directories(${3RDPARTY_tbb_LIBRARY_DIR})
  endif()
endif()

foreach (LIB_FILE ${OCCT_LIB_FILES})
  if (WIN32)
    set (LIB_FILENAME "${LIB_FILE}${CMAKE_STATIC_LIBRARY_SUFFIX}")
  else()
    set (LIB_FILENAME "lib${LIB_FILE}${CMAKE_SHARED_LIBRARY_SUFFIX}")
  endif()

  if (3RDPARTY_OCCT_LIBRARY_DIR_DEBUG AND EXISTS "${3RDPARTY_OCCT_LIBRARY_DIR_DEBUG}/${LIB_FILENAME}")
    target_link_libraries (ActiveDataAPI debug ${3RDPARTY_OCCT_LIBRARY_DIR_DEBUG}/${LIB_FILENAME})
    target_link_libraries (ActiveDataAPI optimized ${3RDPARTY_OCCT_LIBRARY_DIR}/${LIB_FILENAME})
  else()
    target_link_libraries (ActiveDataAPI ${3RDPARTY_OCCT_LIBRARY_DIR}/${LIB_FILENAME})
  endif()
endforeach()

if (USE_TBB)
  foreach (LIB_FILE ${TBB_LIB_FILES})
    if (WIN32)
      set (LIB_FILENAME "${LIB_FILE}${CMAKE_STATIC_LIBRARY_SUFFIX}")
      set (LIB_FILENAME_DEBUG "${LIB_FILE}_debug${CMAKE_STATIC_LIBRARY_SUFFIX}")
    else()
      set (LIB_FILENAME "lib${LIB_FILE}${CMAKE_SHARED_LIBRARY_SUFFIX}")
      set (LIB_FILENAME_DEBUG "lib${LIB_FILE}_debug${CMAKE_SHARED_LIBRARY_SUFFIX}")
    endif()

    target_link_libraries (ActiveDataAPI debug ${3RDPARTY_tbb_LIBRARY_DIR}/${LIB_FILENAME_DEBUG})
    target_link_libraries (ActiveDataAPI optimized ${3RDPARTY_tbb_LIBRARY_DIR}/${LIB_FILENAME})
  endforeach()
endif()

#------------------------------------------------------------------------------
# Installation
#------------------------------------------------------------------------------

install (TARGETS ActiveDataAPI
         RUNTIME DESTINATION bin COMPONENT Runtime
         CONFIGURATIONS Release
         ARCHIVE DESTINATION lib COMPONENT Library
         CONFIGURATIONS Release)

install (TARGETS ActiveDataAPI
         RUNTIME DESTINATION bind COMPONENT Runtime
         CONFIGURATIONS Debug
         ARCHIVE DESTINATION libd COMPONENT Library
         CONFIGURATIONS Debug)

install (FILES ${PROJECT_BINARY_DIR}/../../${PLATFORM}${COMPILER_BITNESS}/${COMPILER}/bind/ActiveDataAPI.pdb DESTINATION bind CONFIGURATIONS Debug)

install (FILES ${H_FILES} DESTINATION include)
