project(ActiveDataTestLib)

#------------------------------------------------------------------------------
# Common
#------------------------------------------------------------------------------

set (H_FILES
  ActTestLib.h
  ActTestLib_Common.h
  ActTestLib_FileComparator.h
  ActTestLib_Launcher.h
  ActTestLib_Macro.h
  ActTestLib_TestCase.h
)

set (CPP_FILES
  ActTestLib_Common.cpp
  ActTestLib_FileComparator.cpp
  ActTestLib_Launcher.cpp
  ActTestLib_TestCase.cpp
)

#------------------------------------------------------------------------------
# Reports
#------------------------------------------------------------------------------

set (reports_H_FILES
  Reports/ActTestLib_DescriptionProc.h
  Reports/ActTestLib_ReportRenderer.h
  Reports/ActTestLib_ReportStyle.h
  Reports/ActTestLib_ReportStyleFactory.h
  Reports/ActTestLib_ReportTag.h
  Reports/ActTestLib_ReportTagFactory.h
)

set (reports_CPP_FILES 
  Reports/ActTestLib_DescriptionProc.cpp
  Reports/ActTestLib_ReportRenderer.cpp
  Reports/ActTestLib_ReportStyle.cpp
  Reports/ActTestLib_ReportStyleFactory.cpp
  Reports/ActTestLib_ReportTag.cpp
  Reports/ActTestLib_ReportTagFactory.cpp
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

foreach (FILE ${reports_H_FILES})
  set (src_files ${src_files} ${FILE})
  source_group ("Header Files\\Reports" FILES "${FILE}")
endforeach (FILE)

foreach (FILE ${reports_CPP_FILES})
  set (src_files ${src_files} ${FILE})
  source_group ("Source Files\\Reports" FILES "${FILE}")
endforeach (FILE)

#------------------------------------------------------------------------------
# Configure includes
#------------------------------------------------------------------------------

# Create include variable
set (ActiveDataTestLib_include_dir_loc "${CMAKE_CURRENT_SOURCE_DIR};\
  ${CMAKE_CURRENT_SOURCE_DIR}/Reports;")
#
set (ActiveDataTestLib_include_dir ${ActiveDataTestLib_include_dir_loc} PARENT_SCOPE)

include_directories ( ${ActiveDataTestLib_include_dir_loc}
                      ${ActiveDataAPI_include_dir}
                      ${ActiveDataAux_include_dir}
                      ${3RDPARTY_OCCT_INCLUDE_DIR} )

if (USE_TBB)
  include_directories ( ${3RDPARTY_tbb_INCLUDE_DIR} )
endif()

#------------------------------------------------------------------------------
# Create library
#------------------------------------------------------------------------------

add_library (ActiveDataTestLib SHARED
  ${H_FILES}          ${CPP_FILES}
  ${reports_H_FILES}  ${reports_CPP_FILES}
)

#------------------------------------------------------------------------------
# Dependencies
#------------------------------------------------------------------------------

target_link_libraries(ActiveDataTestLib ActiveDataAux ActiveDataAPI)

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
    target_link_libraries (ActiveDataTestLib debug ${3RDPARTY_OCCT_LIBRARY_DIR_DEBUG}/${LIB_FILENAME})
    target_link_libraries (ActiveDataTestLib optimized ${3RDPARTY_OCCT_LIBRARY_DIR}/${LIB_FILENAME})
  else()
    target_link_libraries (ActiveDataTestLib ${3RDPARTY_OCCT_LIBRARY_DIR}/${LIB_FILENAME})
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

    target_link_libraries (ActiveDataTestLib debug ${3RDPARTY_tbb_LIBRARY_DIR}/${LIB_FILENAME_DEBUG})
    target_link_libraries (ActiveDataTestLib optimized ${3RDPARTY_tbb_LIBRARY_DIR}/${LIB_FILENAME})
  endforeach()
endif()
