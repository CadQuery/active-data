project(ActiveDataTest)

#------------------------------------------------------------------------------
# Common
#------------------------------------------------------------------------------

set (H_FILES
  ActTest.h
  ActTest_CaseIDs.h
  ActTest_DataFramework.h
)

set (CPP_FILES
  ActTest_DataFramework.cpp
  ActTest_Main.cpp
)

#------------------------------------------------------------------------------
# Data Model
#------------------------------------------------------------------------------

set (datamodel_H_FILES
  DataModel/ActTest_AsciiStringParameter.h
  DataModel/ActTest_BaseModel.h
  DataModel/ActTest_BoolArrayParameter.h
  DataModel/ActTest_BoolParameter.h
  DataModel/ActTest_CAFConversionCtx.h
  DataModel/ActTest_ComplexArrayParameter.h
  DataModel/ActTest_CopyPasteEngine.h
  DataModel/ActTest_ExtTransactionEngine.h
  DataModel/ActTest_GroupParameter.h
  DataModel/ActTest_IntArrayParameter.h
  DataModel/ActTest_IntParameter.h
  DataModel/ActTest_MeshAttr.h
  DataModel/ActTest_MeshParameter.h
  DataModel/ActTest_NameParameter.h
  DataModel/ActTest_RealArrayParameter.h
  DataModel/ActTest_RealParameter.h
  DataModel/ActTest_ReferenceListParameter.h
  DataModel/ActTest_ReferenceParameter.h
  DataModel/ActTest_SelectionParameter.h
  DataModel/ActTest_ShapeParameter.h
  DataModel/ActTest_StringArrayParameter.h
  DataModel/ActTest_TimeStamp.h
  DataModel/ActTest_TimeStampParameter.h
  DataModel/ActTest_TreeFunctionParameter.h
  DataModel/ActTest_TreeNodeParameter.h
  DataModel/ActTest_TriangulationParameter.h
)

set (datamodel_CPP_FILES 
  DataModel/ActTest_AsciiStringParameter.cpp
  DataModel/ActTest_BaseModel.cpp
  DataModel/ActTest_BoolArrayParameter.cpp
  DataModel/ActTest_BoolParameter.cpp
  DataModel/ActTest_CAFConversionCtx.cpp
  DataModel/ActTest_ComplexArrayParameter.cpp
  DataModel/ActTest_CopyPasteEngine.cpp
  DataModel/ActTest_ExtTransactionEngine.cpp
  DataModel/ActTest_GroupParameter.cpp
  DataModel/ActTest_IntArrayParameter.cpp
  DataModel/ActTest_IntParameter.cpp
  DataModel/ActTest_MeshAttr.cpp
  DataModel/ActTest_MeshParameter.cpp
  DataModel/ActTest_NameParameter.cpp
  DataModel/ActTest_RealArrayParameter.cpp
  DataModel/ActTest_RealParameter.cpp
  DataModel/ActTest_ReferenceListParameter.cpp
  DataModel/ActTest_ReferenceParameter.cpp
  DataModel/ActTest_SelectionParameter.cpp
  DataModel/ActTest_ShapeParameter.cpp
  DataModel/ActTest_StringArrayParameter.cpp
  DataModel/ActTest_TimeStamp.cpp
  DataModel/ActTest_TimeStampParameter.cpp
  DataModel/ActTest_TreeFunctionParameter.cpp
  DataModel/ActTest_TreeNodeParameter.cpp
  DataModel/ActTest_TriangulationParameter.cpp
)

#------------------------------------------------------------------------------
# Test Data Model
#------------------------------------------------------------------------------

set (testdatamodel_H_FILES
  DataModel/TestModel/ActTest_DummyModel.h
  DataModel/TestModel/ActTest_DummyTreeFunction.h
  DataModel/TestModel/ActTest_StubANode.h
  DataModel/TestModel/ActTest_StubAPartition.h
  DataModel/TestModel/ActTest_StubBNode.h
  DataModel/TestModel/ActTest_StubBNodeConv.h
  DataModel/TestModel/ActTest_StubBPartition.h
  DataModel/TestModel/ActTest_StubCNode.h
  DataModel/TestModel/ActTest_StubCNodeConv.h
  DataModel/TestModel/ActTest_StubCPartition.h
  DataModel/TestModel/ActTest_StubMeshNode.h
  DataModel/TestModel/ActTest_StubMeshPartition.h
)

set (testdatamodel_CPP_FILES 
  DataModel/TestModel/ActTest_DummyModel.cpp
  DataModel/TestModel/ActTest_DummyTreeFunction.cpp
  DataModel/TestModel/ActTest_StubANode.cpp
  DataModel/TestModel/ActTest_StubAPartition.cpp
  DataModel/TestModel/ActTest_StubBNode.cpp
  DataModel/TestModel/ActTest_StubBNodeConv.cpp
  DataModel/TestModel/ActTest_StubBPartition.cpp
  DataModel/TestModel/ActTest_StubCNode.cpp
  DataModel/TestModel/ActTest_StubCNodeConv.cpp
  DataModel/TestModel/ActTest_StubCPartition.cpp
  DataModel/TestModel/ActTest_StubMeshNode.cpp
  DataModel/TestModel/ActTest_StubMeshPartition.cpp
)

#------------------------------------------------------------------------------
# OpenCascade libraries
#------------------------------------------------------------------------------

set (OCCT_LIB_FILES
  TKernel
  TKMath
  TKG3d
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

foreach (FILE ${datamodel_H_FILES})
  set (src_files ${src_files} ${FILE})
  source_group ("Header Files\\Data Model" FILES "${FILE}")
endforeach (FILE)

foreach (FILE ${datamodel_CPP_FILES})
  set (src_files ${src_files} ${FILE})
  source_group ("Source Files\\Data Model" FILES "${FILE}")
endforeach (FILE)

foreach (FILE ${testdatamodel_H_FILES})
  set (src_files ${src_files} ${FILE})
  source_group ("Header Files\\Data Model\\Test" FILES "${FILE}")
endforeach (FILE)

foreach (FILE ${testdatamodel_CPP_FILES})
  set (src_files ${src_files} ${FILE})
  source_group ("Source Files\\Data Model\\Test" FILES "${FILE}")
endforeach (FILE)

#------------------------------------------------------------------------------
# Configure includes
#------------------------------------------------------------------------------

# Create include variable
set (ActiveDataTest_include_dir_loc "${CMAKE_CURRENT_SOURCE_DIR};\
  ${CMAKE_CURRENT_SOURCE_DIR}/DataModel;\
  ${CMAKE_CURRENT_SOURCE_DIR}/DataModel/TestModel;")
#
set (ActiveDataTest_include_dir ${ActiveDataTest_include_dir_loc} PARENT_SCOPE)

include_directories ( ${ActiveDataTest_include_dir_loc}
                      ${ActiveDataAPI_include_dir}
                      ${ActiveDataAux_include_dir}
                      ${ActiveData_include_dir}
                      ${ActiveDataTestLib_include_dir}
                      ${3RDPARTY_OCCT_INCLUDE_DIR} )

if (USE_TBB)
  include_directories ( ${3RDPARTY_tbb_INCLUDE_DIR} )
endif()

#------------------------------------------------------------------------------
# Create executable and configure to run it upon compilation
#------------------------------------------------------------------------------

add_executable (ActiveDataTest
  ${H_FILES}               ${CPP_FILES}
  ${datamodel_H_FILES}     ${datamodel_CPP_FILES}
  ${testdatamodel_H_FILES} ${testdatamodel_CPP_FILES}
)

# Post build event - run tests.
add_custom_command(
        TARGET ActiveDataTest
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Running unit tests."
        COMMAND IF 1==$<CONFIG:Release> call ${ActiveDataTest_BINARY_DIR}/test_setenv_rel.bat
        COMMAND IF 1==$<CONFIG:RelWithDebInfo> call ${ActiveDataTest_BINARY_DIR}/test_setenv_rel.bat
        COMMAND IF 1==$<CONFIG:Debug> call ${ActiveDataTest_BINARY_DIR}/test_setenv_deb.bat
        COMMAND $<TARGET_FILE:ActiveDataTest>
    )

# Create directory for testing results
set (AD_TEST_DUMP ${CMAKE_BINARY_DIR}/test/dumping)
file(MAKE_DIRECTORY ${AD_TEST_DUMP})
message(STATUS "Create directory for dumping unit testing results: ${AD_TEST_DUMP}")

# Where to search for descriptions of unit tests
set (AD_TEST_DESCR ${CMAKE_SOURCE_DIR}/test/descr)

# Data files
set (AD_DATA ${CMAKE_SOURCE_DIR}/data)

set (ACTDATA_OCAF_PLUGIN_DIR "${ActiveData_SOURCE_DIR}/resources")
message (STATUS "... Info: OCAF resources are here: ${ACTDATA_OCAF_PLUGIN_DIR}")

#------------------------------------------------------------------------------
# Configure templates
#------------------------------------------------------------------------------

set (X_COMPILER_BITNESS "x${COMPILER_BITNESS}")

configure_file(${CMAKE_SOURCE_DIR}/cmake/templates/ActiveDataTest.vcxproj.user.in
               ${ActiveDataTest_BINARY_DIR}/ActiveDataTest.vcxproj.user @ONLY)

configure_file(${CMAKE_SOURCE_DIR}/cmake/templates/test_setenv_deb.bat
               ${ActiveDataTest_BINARY_DIR}/test_setenv_deb.bat @ONLY)

configure_file(${CMAKE_SOURCE_DIR}/cmake/templates/test_setenv_rel.bat
               ${ActiveDataTest_BINARY_DIR}/test_setenv_rel.bat @ONLY)

#------------------------------------------------------------------------------
# Dependencies
#------------------------------------------------------------------------------

target_link_libraries(ActiveDataTest ActiveDataTestLib ActiveData ActiveDataAux ActiveDataAPI)

if (3RDPARTY_tbb_LIBRARY_DIR_DEBUG)
  link_directories(${3RDPARTY_tbb_LIBRARY_DIR_DEBUG})
else()
  link_directories(${3RDPARTY_tbb_LIBRARY_DIR})
endif()

foreach (LIB_FILE ${OCCT_LIB_FILES})
  if (WIN32)
    set (LIB_FILENAME "${LIB_FILE}${CMAKE_STATIC_LIBRARY_SUFFIX}")
  else()
    set (LIB_FILENAME "lib${LIB_FILE}${CMAKE_SHARED_LIBRARY_SUFFIX}")
  endif()

  if (3RDPARTY_OCCT_LIBRARY_DIR_DEBUG AND EXISTS "${3RDPARTY_OCCT_LIBRARY_DIR_DEBUG}/${LIB_FILENAME}")
    target_link_libraries (ActiveDataTest debug ${3RDPARTY_OCCT_LIBRARY_DIR_DEBUG}/${LIB_FILENAME})
    target_link_libraries (ActiveDataTest optimized ${3RDPARTY_OCCT_LIBRARY_DIR}/${LIB_FILENAME})
  else()
    target_link_libraries (ActiveDataTest ${3RDPARTY_OCCT_LIBRARY_DIR}/${LIB_FILENAME})
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

    target_link_libraries (ActiveDataTest debug ${3RDPARTY_tbb_LIBRARY_DIR}/${LIB_FILENAME_DEBUG})
    target_link_libraries (ActiveDataTest optimized ${3RDPARTY_tbb_LIBRARY_DIR}/${LIB_FILENAME})
  endforeach()
endif()
