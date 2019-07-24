project(ActiveDataAux)

#------------------------------------------------------------------------------
# Common
#------------------------------------------------------------------------------

set (H_FILES
  ActAux.h
  ActAux_ArrayUtils.h
  ActAux_Common.h
  ActAux_Env.h
  ActAux_ExprCalculator.h
  ActAux_FileDumper.h
  ActAux_ShapeFactory.h
  ActAux_SpyLog.h
  ActAux_TimeStamp.h
  ActAux_Timing.h
  ActAux_Utils.h
)

set (CPP_FILES
  ActAux_ArrayUtils.cpp
  ActAux_ExprCalculator.cpp
  ActAux_FileDumper.cpp
  ActAux_ShapeFactory.cpp
  ActAux_SpyLog.cpp
  ActAux_TimeStamp.cpp
  ActAux_Utils.cpp
)

#------------------------------------------------------------------------------
# OpenCascade libraries
#------------------------------------------------------------------------------

set (OCCT_LIB_FILES
  TKernel
  TKMath
  TKBRep
  TKTopAlgo
  TKPrim
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
set (ActiveDataAux_include_dir_loc "${CMAKE_CURRENT_SOURCE_DIR};")
#
set (ActiveDataAux_include_dir ${ActiveDataAux_include_dir_loc} PARENT_SCOPE)

include_directories ( ${ActiveDataAux_include_dir_loc}
                      ${ActiveDataAPI_include_dir}
                      ${3RDPARTY_OCCT_INCLUDE_DIR} )

if (USE_TBB)
  include_directories ( ${3RDPARTY_tbb_INCLUDE_DIR} )
endif()

#------------------------------------------------------------------------------
# Create library
#------------------------------------------------------------------------------

add_library (ActiveDataAux SHARED
  ${H_FILES} ${CPP_FILES}
)

#------------------------------------------------------------------------------
# Dependencies
#------------------------------------------------------------------------------

target_link_libraries(ActiveDataAux ActiveDataAPI)

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
    target_link_libraries (ActiveDataAux debug ${3RDPARTY_OCCT_LIBRARY_DIR_DEBUG}/${LIB_FILENAME})
    target_link_libraries (ActiveDataAux optimized ${3RDPARTY_OCCT_LIBRARY_DIR}/${LIB_FILENAME})
  else()
    target_link_libraries (ActiveDataAux ${3RDPARTY_OCCT_LIBRARY_DIR}/${LIB_FILENAME})
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

    target_link_libraries (ActiveDataAux debug ${3RDPARTY_tbb_LIBRARY_DIR}/${LIB_FILENAME_DEBUG})
    target_link_libraries (ActiveDataAux optimized ${3RDPARTY_tbb_LIBRARY_DIR}/${LIB_FILENAME})
  endforeach()
endif()

#------------------------------------------------------------------------------
# Installation
#------------------------------------------------------------------------------

install (TARGETS ActiveDataAux
         RUNTIME DESTINATION bin COMPONENT Runtime
         CONFIGURATIONS Release
         ARCHIVE DESTINATION lib LIBRARY DESTINATION lib COMPONENT Library
         CONFIGURATIONS Release)

install (TARGETS ActiveDataAux
         RUNTIME DESTINATION bini COMPONENT Runtime
         CONFIGURATIONS RelWithDebInfo
         ARCHIVE DESTINATION libi COMPONENT Library
         CONFIGURATIONS RelWithDebInfo)

install (TARGETS ActiveDataAux
         RUNTIME DESTINATION bind COMPONENT Runtime
         CONFIGURATIONS Debug
         ARCHIVE DESTINATION libd LIBRARY DESTINATION libd COMPONENT Library
         CONFIGURATIONS Debug)

install (FILES ${PROJECT_BINARY_DIR}/../../${PLATFORM}${COMPILER_BITNESS}/${COMPILER}/bind/ActiveDataAux.pdb DESTINATION bind CONFIGURATIONS Debug)

install (FILES ${H_FILES} DESTINATION include)
