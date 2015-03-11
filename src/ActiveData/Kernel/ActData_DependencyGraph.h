//-----------------------------------------------------------------------------
// Created on: November 2012
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

#ifndef ActData_DependencyGraph_HeaderFile
#define ActData_DependencyGraph_HeaderFile

// Active Data includes
#include <ActData_BaseModel.h>
#include <ActData_BaseTreeFunction.h>
#include <ActData_Common.h>
#include <ActData_ParameterFactory.h>

// OCCT includes
#include <TDF_LabelMapHasher.hxx>
#include <TFunction_DoubleMapIteratorOfDoubleMapOfIntegerLabel.hxx>
#include <TFunction_DoubleMapOfIntegerLabel.hxx>
#include <TFunction_Driver.hxx>

//-----------------------------------------------------------------------------
// Common definitions
//-----------------------------------------------------------------------------

//! Convenient type short-cut for OCCT TFunction kernel collection
//! representing dependency graph.
typedef TFunction_DoubleMapOfIntegerLabel ActData_Graph;

//! Type short-cut for upper-level graph iterator. This iterator allows
//! traversing the entire collection of existing graph nodes, however,
//! it does not follow any associativity order. Thus, it is necessary
//! to use OCCT TFunction_GraphNode relations later on in order to iterate
//! graph's topological web.
typedef TFunction_DoubleMapIteratorOfDoubleMapOfIntegerLabel ActData_TFuncGraphIterator;

//-----------------------------------------------------------------------------
// Dependency Graph
//-----------------------------------------------------------------------------

DEFINE_STANDARD_HANDLE(ActData_DependencyGraph, Standard_Transient)

//! \ingroup AD_DF
//!
//! Class representing actual model of Dependency Graph. Being built from
//! OCAF-specific graph of Tree Functions, the instance of this class provides
//! convenient accessors to its topology.
//!
//! IMPORTANT: the nodes of the resulting graph are Tree Function Parameters,
//!            not Tree Functions. This class builds a graph of instances,
//!            rather than pure model graph of logical connections. That is
//!            why the constructed Graph can consist of several disconnected
//!            sub-graphs. The latter fact should be taken into account in
//!            iterating routines.
class ActData_DependencyGraph : public Standard_Transient
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActData_DependencyGraph, Standard_Transient)

public:

  //! Structure representing oriented graph edge.
  struct OriEdge
  {
    Standard_Integer V1; //!< First (source) vertex.
    Standard_Integer V2; //!< Second (target) vertex.

    //! Default constructor.
    OriEdge() : V1(-1), V2(-1)
    {}

    //! Complete constructor.
    //! \param theV1 [in] first vertex.
    //! \param theV2 [in] second vertex.
    OriEdge(const Standard_Integer theV1,
            const Standard_Integer theV2)
      : V1(theV1), V2(theV2)
    {}

    //! Hashing tool.
    struct Hasher
    {
      //! Returns Hash Code for the given link.
      //! \param theLink [in] oriented link to compute hash code for.
      //! \param theNbBuckets [in] number of buckets.
      //! \return calculated hash code.
      static Standard_Integer HashCode(const OriEdge& theLink,
                                       const Standard_Integer theNbBuckets = 100)
      {
        Standard_Integer aKey = theLink.V1 + theLink.V2;
        aKey += (aKey << 10);
        aKey ^= (aKey >> 6);
        aKey += (aKey << 3);
        aKey ^= (aKey >> 11);
        return (aKey & 0x7fffffff) % theNbBuckets;
      }

      //! Checks whether two oriented links are the same.
      //! \param theLink1 [in] first link.
      //! \param theLink2 [in] second link.
      //! \return true in case of equality, false -- otherwise.
      static Standard_Boolean
        IsEqual(const OriEdge& theLink1,
                const OriEdge& theLink2)
      {
        return theLink1.V1 == theLink2.V1 && theLink1.V2 == theLink2.V2;
      }
    };
  };

  //! Additional data associated with each graph vertex.
  struct VertexData
  {
    Handle(ActAPI_ITreeFunction) TreeFunction; //!< Tree Function instance.
    Handle(ActAPI_IUserParameter)    Parameter;    //!< Tree Function Parameter.

    //! Default constructor.
    VertexData() {}

    //! Complete constructor.
    //! \param theTFunc [in] Tree Function to set.
    //! \param theParam [in] Tree Function Parameter.
    VertexData(const Handle(ActAPI_ITreeFunction)& theTFunc,
               const Handle(ActAPI_IUserParameter)& theParam)
    : TreeFunction(theTFunc),
      Parameter(theParam) {}

    //! Complete constructor.
    //! \param theTFuncDrv [in] Tree Function Driver to access Tree Function.
    VertexData(const Handle(TFunction_Driver)& theTFuncDrv)
    {
      Handle(ActData_TreeFunctionDriver) aDrv = Handle(ActData_TreeFunctionDriver)::DownCast(theTFuncDrv);
      TreeFunction = aDrv->GetFunction();
      Parameter = ActParamTool::NewParameterSettle( aDrv->Label() );
    }
  };

  //! Type short-cut for correspondence between OCAF Labels & vertices.
  typedef NCollection_DataMap<TDF_Label, Standard_Integer, TDF_LabelMapHasher> LabelVertexMap;

  //! Type short-cut for the involved graph vertices.
  typedef NCollection_DataMap<Standard_Integer, VertexData> VertexDataMap;

  //! Type short-cut for the involved graph edges (oriented links).
  typedef NCollection_Map<OriEdge, OriEdge::Hasher> EdgeMap;

public:

  ActData_EXPORT ActData_DependencyGraph();
  ActData_EXPORT ActData_DependencyGraph(const Handle(ActData_BaseModel)& theModel);

public:

  ActData_EXPORT void
    Build(const Handle(ActData_BaseModel)& theModel);

  ActData_EXPORT Handle(ActData_TreeFunctionParameter)
    FunctionByVertex(const Standard_Integer theVertexID) const;

  ActData_EXPORT Standard_Integer
    VertexByLabel(const TDF_Label& theLab) const;

  ActData_EXPORT Standard_Integer
    VertexByFunction(const Handle(ActData_TreeFunctionParameter)& theParam) const;

  ActData_EXPORT VertexData
    DataByVertex(const Standard_Integer theVertexID) const;

// Accessors:
public:

  //! Returns the collection of graph vertices.
  //! \return collection of vertices.
  inline const VertexDataMap& Vertices() const
  {
    return m_vertices;
  }

  //! Returns the collection of graph edges.
  //! \return collection of edges.
  inline const EdgeMap& Edges() const
  {
    return m_edges;
  }

  //! Returns Data Model instance the Graph entity is initialized with.
  //! \return Data Model instance.
  inline const Handle(ActData_BaseModel)& Model() const
  {
    return m_model;
  }

private:

  void buildFrom(const TDF_Label& theLNode,
                 const Standard_Integer theID);

  void registerVertex(const Standard_Integer theID,
                      const VertexData& theVData,
                      const TDF_Label& theFuncRoot);

private:

  //! Data Model instance to access dependency graph and other data related
  //! to the Tree Function mechanism.
  Handle(ActData_BaseModel) m_model;

  //! Mapping between OCAF Labels and graph vertices.
  LabelVertexMap m_labelVerts;

  //! Graph vertices.
  VertexDataMap m_vertices;

  //! Graph edges.
  EdgeMap m_edges;

};

#endif
