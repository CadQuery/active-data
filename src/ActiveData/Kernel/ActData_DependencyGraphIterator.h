//-----------------------------------------------------------------------------
// Created on: January 2013
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

#ifndef ActData_DependencyGraphIterator_HeaderFile
#define ActData_DependencyGraphIterator_HeaderFile

// Active Data includes
#include <ActData_DependencyGraph.h>

// OCCT includes
#include <NCollection_Sequence.hxx>
#include <TFunction_IFunction.hxx>

//! \ingroup AD_DF
//!
//! Iterator for Dependency Graph. This class can iterate starting from a
//! single graph node in two directions: up and down. Iterating down you
//! traverse all Tree Functions scheduled for execution after yours.
//! Iterating uo you traverse all Tree Functions scheduled for execution
//! before yours. The iterator first traverses a single level:
//! only after the complete level traversal it goes deeper. The diving
//! point is not deterministic.
class ActData_DependencyGraphIterator
{
public:

  ActData_EXPORT
    ActData_DependencyGraphIterator();

  ActData_EXPORT
    ActData_DependencyGraphIterator(const Handle(ActData_DependencyGraph)& theGraph,
                                    const Standard_Integer theRootVertex,
                                    const Standard_Boolean isReverseOrder);

public:

  ActData_EXPORT void
    Init(const Handle(ActData_DependencyGraph)& theGraph,
         const Standard_Integer theRootVertex,
         const Standard_Boolean isReverseOrder);

  ActData_EXPORT Standard_Boolean
    More() const;

  ActData_EXPORT Standard_Integer
    Current() const;

  ActData_EXPORT void
    Next();

protected:

  void
    nextLevel();

  void
    nextLevel(NCollection_Map<Standard_Integer>& theLevel) const;

  NCollection_Sequence<Standard_Integer>
    successorsOrPredecessors() const;

  NCollection_Sequence<Standard_Integer>
    successorsOrPredecessors(const Standard_Integer theVertex) const;

  NCollection_Sequence<Standard_Integer>
    successors() const;

  NCollection_Sequence<Standard_Integer>
    successors(const Standard_Integer theVertex) const;

  NCollection_Sequence<Standard_Integer>
    predecessors() const;

  NCollection_Sequence<Standard_Integer>
    predecessors(const Standard_Integer theVertex) const;

  TFunction_IFunction
    settleIFunc(const Standard_Integer theVertex) const;

protected:

  Handle(ActData_DependencyGraph)   m_graph;             //!< Graph being iterated.
  Standard_Integer                  m_currentID;         //!< ID of the current vertex.
  Standard_Integer                  m_levelRoot;         //!< Root of the current level.
  NCollection_Map<Standard_Integer> m_traversedSiblings; //!< Traversed siblings for current.
  NCollection_Map<Standard_Integer> m_currentSiblings;   //!< All siblings for current.
  Standard_Boolean                  m_bReversed;         //!< Order of traverse.

};

#endif
