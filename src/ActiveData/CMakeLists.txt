project(ActiveData)

#------------------------------------------------------------------------------
# Common
#------------------------------------------------------------------------------

set (H_FILES
  ActData.h
  ActData_Common.h
  ActData_Plugin.h
)

set (CPP_FILES
  ActData_Plugin.cpp
)

#------------------------------------------------------------------------------
# OCAF drivers for binary file format
#------------------------------------------------------------------------------

set (drivers_H_FILES
  BinDrivers/ActData_BinDrivers.h
  BinDrivers/ActData_BinRetrievalDriver.h
  BinDrivers/ActData_BinStorageDriver.h
  BinDrivers/ActData_MeshDriver.h
)
set (drivers_CPP_FILES 
  BinDrivers/ActData_BinDrivers.cpp
  BinDrivers/ActData_BinRetrievalDriver.cpp
  BinDrivers/ActData_BinStorageDriver.cpp
  BinDrivers/ActData_MeshDriver.cpp
)

#------------------------------------------------------------------------------
# Kernel
#------------------------------------------------------------------------------

set (kernel_H_FILES
  Kernel/ActData_Application.h
  Kernel/ActData_AsciiStringParameter.h
  Kernel/ActData_BaseModel.h
  Kernel/ActData_BaseNode.h
  Kernel/ActData_BasePartition.h
  Kernel/ActData_BaseTreeFunction.h
  Kernel/ActData_BoolArrayParameter.h
  Kernel/ActData_BoolParameter.h
  Kernel/ActData_ComplexArrayParameter.h
  Kernel/ActData_CopyPasteEngine.h
  Kernel/ActData_DependencyAnalyzer.h
  Kernel/ActData_DependencyGraph.h
  Kernel/ActData_DependencyGraphIterator.h
  Kernel/ActData_ExtTransactionEngine.h
  Kernel/ActData_FuncExecutionCtx.h
  Kernel/ActData_FuncExecutionTask.h
  Kernel/ActData_GraphFrozenException.h
  Kernel/ActData_GroupParameter.h
  Kernel/ActData_IntArrayParameter.h
  Kernel/ActData_IntParameter.h
  Kernel/ActData_LogBook.h
  Kernel/ActData_MeshParameter.h
  Kernel/ActData_MetaParameter.h
  Kernel/ActData_NameParameter.h
  Kernel/ActData_NodeFactory.h
  Kernel/ActData_ParameterDTO.h
  Kernel/ActData_ParameterFactory.h
  Kernel/ActData_RealArrayParameter.h
  Kernel/ActData_RealParameter.h
  Kernel/ActData_RefClassifier.h
  Kernel/ActData_ReferenceListParameter.h
  Kernel/ActData_ReferenceParameter.h
  Kernel/ActData_SamplerTreeNode.h
  Kernel/ActData_SelectionParameter.h
  Kernel/ActData_SequentialFuncIterator.h
  Kernel/ActData_ShapeParameter.h
  Kernel/ActData_StringArrayParameter.h
  Kernel/ActData_TimeStampParameter.h
  Kernel/ActData_TransactionEngine.h
  Kernel/ActData_TreeFunctionParameter.h
  Kernel/ActData_TreeFunctionPriority.h
  Kernel/ActData_TreeNodeParameter.h
  Kernel/ActData_TriangulationParameter.h
  Kernel/ActData_UserParameter.h
  Kernel/ActData_Utils.h
)
set (kernel_CPP_FILES 
  Kernel/ActData_Application.cpp
  Kernel/ActData_AsciiStringParameter.cpp
  Kernel/ActData_BaseModel.cpp
  Kernel/ActData_BaseNode.cpp
  Kernel/ActData_BasePartition.cpp
  Kernel/ActData_BaseTreeFunction.cpp
  Kernel/ActData_BoolArrayParameter.cpp
  Kernel/ActData_BoolParameter.cpp
  Kernel/ActData_ComplexArrayParameter.cpp
  Kernel/ActData_CopyPasteEngine.cpp
  Kernel/ActData_DependencyAnalyzer.cpp
  Kernel/ActData_DependencyGraph.cpp
  Kernel/ActData_DependencyGraphIterator.cpp
  Kernel/ActData_ExtTransactionEngine.cpp
  Kernel/ActData_FuncExecutionCtx.cpp
  Kernel/ActData_FuncExecutionTask.cpp
  Kernel/ActData_GroupParameter.cpp
  Kernel/ActData_IntArrayParameter.cpp
  Kernel/ActData_IntParameter.cpp
  Kernel/ActData_LogBook.cpp
  Kernel/ActData_MeshParameter.cpp
  Kernel/ActData_MetaParameter.cpp
  Kernel/ActData_NameParameter.cpp
  Kernel/ActData_NodeFactory.cpp
  Kernel/ActData_ParameterDTO.cpp
  Kernel/ActData_ParameterFactory.cpp
  Kernel/ActData_RealArrayParameter.cpp
  Kernel/ActData_RealParameter.cpp
  Kernel/ActData_RefClassifier.cpp
  Kernel/ActData_ReferenceListParameter.cpp
  Kernel/ActData_ReferenceParameter.cpp
  Kernel/ActData_SamplerTreeNode.cpp
  Kernel/ActData_SelectionParameter.cpp
  Kernel/ActData_SequentialFuncIterator.cpp
  Kernel/ActData_ShapeParameter.cpp
  Kernel/ActData_StringArrayParameter.cpp
  Kernel/ActData_TimeStampParameter.cpp
  Kernel/ActData_TransactionEngine.cpp
  Kernel/ActData_TreeFunctionParameter.cpp
  Kernel/ActData_TreeNodeParameter.cpp
  Kernel/ActData_TriangulationParameter.cpp
  Kernel/ActData_UserParameter.cpp
  Kernel/ActData_Utils.cpp
)

#------------------------------------------------------------------------------
# Mesh
#------------------------------------------------------------------------------

set (mesh_H_FILES
  Mesh/ActData_MeshAttr.h
  Mesh/ActData_MeshDeltaEntities.h
  Mesh/ActData_MeshMDelta.h
)

set (mesh_CPP_FILES 
  Mesh/ActData_MeshAttr.cpp
  Mesh/ActData_MeshDeltaEntities.cpp
  Mesh/ActData_MeshMDelta.cpp
)

#------------------------------------------------------------------------------
# Mesh data structures
#------------------------------------------------------------------------------

set (meshds_H_FILES
  Mesh/DS/Mesh.h
  Mesh/DS/Mesh_Direction.h
  Mesh/DS/Mesh_Edge.h
  Mesh/DS/Mesh_EdgesIterator.h
  Mesh/DS/Mesh_Element.h
  Mesh/DS/Mesh_ElementsIterator.h
  Mesh/DS/Mesh_ElementType.h
  Mesh/DS/Mesh_Face.h
  Mesh/DS/Mesh_FacesIterator.h
  Mesh/DS/Mesh_Group.h
  Mesh/DS/Mesh_IDFactory.h
  Mesh/DS/Mesh_MapOfMeshElement.h
  Mesh/DS/Mesh_MapOfMeshOrientedElement.h
  Mesh/DS/Mesh_Node.h
  Mesh/DS/Mesh_NodesIterator.h
  Mesh/DS/Mesh_Object.h
  Mesh/DS/Mesh_PntHasher.h
  Mesh/DS/Mesh_Position.h
  Mesh/DS/Mesh_Quadrangle.h
  Mesh/DS/Mesh_SpacePosition.h
  Mesh/DS/Mesh_State.h
  Mesh/DS/Mesh_Triangle.h
  Mesh/DS/Mesh_TypeOfPosition.h
)

set (meshds_CPP_FILES 
  Mesh/DS/Mesh.cpp
  Mesh/DS/Mesh_Direction.cpp
  Mesh/DS/Mesh_Edge.cpp
  Mesh/DS/Mesh_Element.cpp
  Mesh/DS/Mesh_ElementsIterator.cpp
  Mesh/DS/Mesh_Face.cpp
  Mesh/DS/Mesh_Group.cpp
  Mesh/DS/Mesh_IDFactory.cpp
  Mesh/DS/Mesh_MapOfMeshElement.cpp
  Mesh/DS/Mesh_MapOfMeshOrientedElement.cpp
  Mesh/DS/Mesh_Node.cpp
  Mesh/DS/Mesh_Position.cpp
  Mesh/DS/Mesh_Quadrangle.cpp
  Mesh/DS/Mesh_Triangle.cpp
)

#------------------------------------------------------------------------------
# Programming patterns
#------------------------------------------------------------------------------

set (patterns_H_FILES
  Patterns/ActData_RealArrayOwnerAPI.h
  Patterns/ActData_RecordCollectionOwnerAPI.h
)

set (patterns_CPP_FILES 
  Patterns/ActData_RealArrayOwnerAPI.cpp
  Patterns/ActData_RecordCollectionOwnerAPI.cpp
)

#------------------------------------------------------------------------------
# Standard implementations
#------------------------------------------------------------------------------

set (std_H_FILES
  STD/ActData_BaseVarNode.h
  STD/ActData_BoolVarNode.h
  STD/ActData_BoolVarPartition.h
  STD/ActData_IntVarNode.h
  STD/ActData_IntVarPartition.h
  STD/ActData_RealEvaluatorFunc.h
  STD/ActData_RealVarNode.h
  STD/ActData_RealVarPartition.h
)

set (std_CPP_FILES 
  STD/ActData_BaseVarNode.cpp
  STD/ActData_BoolVarNode.cpp
  STD/ActData_BoolVarPartition.cpp
  STD/ActData_IntVarNode.cpp
  STD/ActData_IntVarPartition.cpp
  STD/ActData_RealEvaluatorFunc.cpp
  STD/ActData_RealVarNode.cpp
  STD/ActData_RealVarPartition.cpp
)

#------------------------------------------------------------------------------
# Tools
#------------------------------------------------------------------------------

set (tools_H_FILES
  Tools/ActData_CAFConversionAsset.h
  Tools/ActData_CAFConversionCtx.h
  Tools/ActData_CAFConversionModel.h
  Tools/ActData_CAFConversionNode.h
  Tools/ActData_CAFConversionParameter.h
  Tools/ActData_CAFConverter.h
  Tools/ActData_CAFConverterBase.h
  Tools/ActData_CAFConverterFw.h
  Tools/ActData_CAFDumper.h
  Tools/ActData_CAFLoader.h
  Tools/ActData_GraphToDot.h
  Tools/ActData_UniqueNodeName.h
)

set (tools_CPP_FILES 
  Tools/ActData_CAFConversionAsset.cpp
  Tools/ActData_CAFConversionCtx.cpp
  Tools/ActData_CAFConversionModel.cpp
  Tools/ActData_CAFConversionNode.cpp
  Tools/ActData_CAFConversionParameter.cpp
  Tools/ActData_CAFConverter.cpp
  Tools/ActData_CAFConverterFw.cpp
  Tools/ActData_CAFDumper.cpp
  Tools/ActData_CAFLoader.cpp
  Tools/ActData_GraphToDot.cpp
  Tools/ActData_UniqueNodeName.cpp
)

#------------------------------------------------------------------------------
# OpenCascade libraries
#------------------------------------------------------------------------------

set (OCCT_LIB_FILES
  TKernel
  TKMath
  TKBinL
  TKBin
  TKLCAF
  TKCAF
  TKCDF
)

#------------------------------------------------------------------------------
# TBB libraries
#------------------------------------------------------------------------------

set (TBB_LIB_FILES
  tbb
)

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

foreach (FILE ${drivers_H_FILES})
  set (src_files ${src_files} ${FILE})
  source_group ("Header Files\\Drivers" FILES "${FILE}")
endforeach (FILE)

foreach (FILE ${drivers_CPP_FILES})
  set (src_files ${src_files} ${FILE})
  source_group ("Source Files\\Drivers" FILES "${FILE}")
endforeach (FILE)

foreach (FILE ${kernel_H_FILES})
  set (src_files ${src_files} ${FILE})
  source_group ("Header Files\\Kernel" FILES "${FILE}")
endforeach (FILE)

foreach (FILE ${kernel_CPP_FILES})
  set (src_files ${src_files} ${FILE})
  source_group ("Source Files\\Kernel" FILES "${FILE}")
endforeach (FILE)

foreach (FILE ${mesh_H_FILES})
  set (src_files ${src_files} ${FILE})
  source_group ("Header Files\\Mesh" FILES "${FILE}")
endforeach (FILE)

foreach (FILE ${mesh_CPP_FILES})
  set (src_files ${src_files} ${FILE})
  source_group ("Source Files\\Mesh" FILES "${FILE}")
endforeach (FILE)

foreach (FILE ${meshds_H_FILES})
  set (src_files ${src_files} ${FILE})
  source_group ("Header Files\\Mesh\\DS" FILES "${FILE}")
endforeach (FILE)

foreach (FILE ${meshds_CPP_FILES})
  set (src_files ${src_files} ${FILE})
  source_group ("Source Files\\Mesh\\DS" FILES "${FILE}")
endforeach (FILE)

foreach (FILE ${patterns_H_FILES})
  set (src_files ${src_files} ${FILE})
  source_group ("Header Files\\Patterns" FILES "${FILE}")
endforeach (FILE)

foreach (FILE ${patterns_CPP_FILES})
  set (src_files ${src_files} ${FILE})
  source_group ("Source Files\\Patterns" FILES "${FILE}")
endforeach (FILE)

foreach (FILE ${std_H_FILES})
  set (src_files ${src_files} ${FILE})
  source_group ("Header Files\\STD" FILES "${FILE}")
endforeach (FILE)

foreach (FILE ${std_CPP_FILES})
  set (src_files ${src_files} ${FILE})
  source_group ("Source Files\\STD" FILES "${FILE}")
endforeach (FILE)

foreach (FILE ${tools_H_FILES})
  set (src_files ${src_files} ${FILE})
  source_group ("Header Files\\Tools" FILES "${FILE}")
endforeach (FILE)

foreach (FILE ${tools_CPP_FILES})
  set (src_files ${src_files} ${FILE})
  source_group ("Source Files\\Tools" FILES "${FILE}")
endforeach (FILE)

#------------------------------------------------------------------------------
# Configure includes
#------------------------------------------------------------------------------

# Create include variable
set (ActiveData_include_dir_loc "${CMAKE_CURRENT_SOURCE_DIR};\
  ${CMAKE_CURRENT_SOURCE_DIR}/BinDrivers;\
  ${CMAKE_CURRENT_SOURCE_DIR}/Kernel;\
  ${CMAKE_CURRENT_SOURCE_DIR}/Mesh;\
  ${CMAKE_CURRENT_SOURCE_DIR}/Mesh/DS;\
  ${CMAKE_CURRENT_SOURCE_DIR}/Patterns;\
  ${CMAKE_CURRENT_SOURCE_DIR}/STD;\
  ${CMAKE_CURRENT_SOURCE_DIR}/Tools;")
#
set (ActiveData_include_dir ${ActiveData_include_dir_loc} PARENT_SCOPE)

include_directories ( ${ActiveData_include_dir_loc}
                      ${ActiveDataAPI_include_dir}
                      ${ActiveDataAux_include_dir}
                      ${3RDPARTY_OCCT_INCLUDE_DIR}
                      ${3RDPARTY_tbb_INCLUDE_DIR} )

#------------------------------------------------------------------------------
# Create library
#------------------------------------------------------------------------------

add_library (ActiveData SHARED
  ${H_FILES}          ${CPP_FILES}
  ${drivers_H_FILES}  ${drivers_CPP_FILES}
  ${kernel_H_FILES}   ${kernel_CPP_FILES}
  ${mesh_H_FILES}     ${mesh_CPP_FILES}
  ${meshds_H_FILES}   ${meshds_CPP_FILES}
  ${patterns_H_FILES} ${patterns_CPP_FILES}
  ${std_H_FILES}      ${std_CPP_FILES}
  ${tools_H_FILES}    ${tools_CPP_FILES}
)

#------------------------------------------------------------------------------
# Dependencies
#------------------------------------------------------------------------------

target_link_libraries(ActiveData ActiveDataAux ActiveDataAPI)

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
    target_link_libraries (ActiveData debug ${3RDPARTY_OCCT_LIBRARY_DIR_DEBUG}/${LIB_FILENAME})
    target_link_libraries (ActiveData optimized ${3RDPARTY_OCCT_LIBRARY_DIR}/${LIB_FILENAME})
  else()
    target_link_libraries (ActiveData ${3RDPARTY_OCCT_LIBRARY_DIR}/${LIB_FILENAME})
  endif()
endforeach()

foreach (LIB_FILE ${TBB_LIB_FILES})
  if (WIN32)
    set (LIB_FILENAME "${LIB_FILE}${CMAKE_STATIC_LIBRARY_SUFFIX}")
    set (LIB_FILENAME_DEBUG "${LIB_FILE}_debug${CMAKE_STATIC_LIBRARY_SUFFIX}")
  else()
    set (LIB_FILENAME "lib${LIB_FILE}${CMAKE_SHARED_LIBRARY_SUFFIX}")
    set (LIB_FILENAME_DEBUG "lib${LIB_FILE}_debug${CMAKE_SHARED_LIBRARY_SUFFIX}")
  endif()

  target_link_libraries (ActiveData debug ${3RDPARTY_tbb_LIBRARY_DIR}/${LIB_FILENAME_DEBUG})
  target_link_libraries (ActiveData optimized ${3RDPARTY_tbb_LIBRARY_DIR}/${LIB_FILENAME})
endforeach()

#------------------------------------------------------------------------------
# Installation
#------------------------------------------------------------------------------

install (TARGETS ActiveData
         RUNTIME DESTINATION bin COMPONENT Runtime
         CONFIGURATIONS Release
         ARCHIVE DESTINATION lib COMPONENT Library
         CONFIGURATIONS Release)

install (TARGETS ActiveData
         RUNTIME DESTINATION bind COMPONENT Runtime
         CONFIGURATIONS Debug
         ARCHIVE DESTINATION libd COMPONENT Library
         CONFIGURATIONS Debug)

install (FILES ${PROJECT_BINARY_DIR}/../../${PLATFORM}${COMPILER_BITNESS}/${COMPILER}/bind/ActiveData.pdb DESTINATION bind CONFIGURATIONS Debug)

install (FILES ${H_FILES}          DESTINATION include)
install (FILES ${drivers_H_FILES}  DESTINATION include)
install (FILES ${kernel_H_FILES}   DESTINATION include)
install (FILES ${mesh_H_FILES}     DESTINATION include)
install (FILES ${meshds_H_FILES}   DESTINATION include)
install (FILES ${patterns_H_FILES} DESTINATION include)
install (FILES ${std_H_FILES}      DESTINATION include)
install (FILES ${tools_H_FILES}    DESTINATION include)
