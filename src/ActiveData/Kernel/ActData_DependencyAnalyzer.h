//-----------------------------------------------------------------------------
// Created on: May 2012
//-----------------------------------------------------------------------------
// Copyright (c) 2017 Sergey Slyadnev
// Code covered by the MIT License
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//
// Web: http://dev.opencascade.org
//-----------------------------------------------------------------------------

#ifndef ActData_DependencyAnalyzer_HeaderFile
#define ActData_DependencyAnalyzer_HeaderFile

// Active Data includes
#include <ActData_BaseModel.h>
#include <ActData_Common.h>
#include <ActData_DependencyGraph.h>

// OCCT includes
#include <NCollection_Handle.hxx>
#include <NCollection_Sequence.hxx>
#include <NCollection_List.hxx>

DEFINE_STANDARD_HANDLE(ActData_DependencyAnalyzer, Standard_Transient)

//! \ingroup AD_DF
//!
//! Auxiliary tool performing different kinds of analysis on Tree
//! Function dependency graphs.
class ActData_DependencyAnalyzer : public Standard_Transient
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActData_DependencyAnalyzer, Standard_Transient)

public:

  //! Stack of internal function IDs utilized by OCCT TFunction kernel.
  typedef NCollection_List<Standard_Integer> FuncIDStack;

  //! Collection of function ID stacks.
  typedef NCollection_Sequence<FuncIDStack> FuncIDStackList;

  //! Specifies algorithms applicable for searching Strongly Connected
  //! Components (SCC) in the dependency graph being analyzed.
  enum LoopStrategy
  {
    //! Depth-First Search algorithm. This is the simplest NP-hard algorithm
    //! performing full traversal of the dependency graph and finding all
    //! loops in all combinations. The computational complexity of this
    //! algorithm is equivalent to N^N, where N is the number of graph nodes.
    LoopStrategy_AD_DFS = 1,

    // TODO: NYI
    LoopStrategy_Tarjan
  };

  //! States of dependency graph representing analysis results.
  enum GraphState
  {
    GraphState_Undefined = 0x00001,
    GraphState_Ok        = 0x00002,
    GraphState_HasLoops  = 0x00004,
    GraphState_NoGraph   = 0x00008
  };

// Construction:
public:

  ActData_EXPORT ActData_DependencyAnalyzer(const Handle(ActData_BaseModel)& theModel);

// Analysis of dependency graph:
public:

  ActData_EXPORT void
    DetectLoops(const LoopStrategy = LoopStrategy_AD_DFS);

// Accessors to the results of analysis:
public:

  ActData_EXPORT Standard_Integer
    GetResultStatus() const;

  ActData_EXPORT Handle(ActAPI_HParameterList)
    CyclicParameters(const Standard_Boolean isEnriched = Standard_True) const;

  ActData_EXPORT Standard_Boolean
    IsInitialized() const;

  ActData_EXPORT Standard_Boolean
    IsDone() const;

  ActData_EXPORT Standard_Boolean
    IsOk() const;

  ActData_EXPORT Standard_Boolean
    HasLoops() const;

// Dependency graph validation internals:
private:

  void performAD_DFS(const ActData_Graph& theGraph);

  void performTarjan(const ActData_Graph& theGraph);

  void checkLoopRecursiveAD_DFS(const Handle(TFunction_GraphNode)& theNode,
                             FuncIDStack& theStack,
                             FuncIDStackList& theLoopSeq) const;

  void cumulateChildParameters(const Standard_Integer theRootID,
                               TColStd_PackedMapOfInteger& theChildIDs) const;

// Prerequisite members:
private:

  //! Data Model instance to access dependency graph and other data related
  //! to the Tree Function mechanism.
  Handle(ActData_BaseModel) m_model;

// Resulting members:
private:

  //! Cumulative collection comprised of Parameter IDs forming up cyclical
  //! chains in the dependency graph being analyzed.
  TColStd_PackedMapOfInteger m_cyclicParamIDs;

  //! Result of analysis.
  Standard_Integer m_resultState;

};

#endif
