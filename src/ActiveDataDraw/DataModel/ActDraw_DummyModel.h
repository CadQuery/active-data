//-----------------------------------------------------------------------------
// Created on: March 2015
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

#ifndef ActDraw_DummyModel_HeaderFile
#define ActDraw_DummyModel_HeaderFile

// Active Data Draw includes
#include <ActDraw_CoordPartition.h>
#include <ActDraw_StubAPartition.h>

// Active Data includes
#include <ActData_BaseModel.h>

DEFINE_STANDARD_HANDLE(ActDraw_DummyModel, ActData_BaseModel)

//! \ingroup AD_DRAW
//!
//! Data Model implementation for Draw commands.
class ActDraw_DummyModel : public ActData_BaseModel
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActDraw_DummyModel, ActData_BaseModel)

public:

  ActDraw_EXPORT ActDraw_DummyModel();

public:

  //! Create a cloned instance of Data Model.
  //! \return cloned instance.
  inline virtual Handle(ActAPI_IModel) Clone() const
  {
    return ActData_BaseModel::CloneInstance<ActDraw_DummyModel>();
  }

// Accessors:
public:

  //! Accessor for the Coord Partition.
  inline Handle(ActDraw_CoordPartition) CoordPartition() const
  {
    return Handle(ActDraw_CoordPartition)::DownCast( this->Partition(Partition_Coord) );
  }

  //! Accessor for the Partition A.
  inline Handle(ActDraw_StubAPartition) StubAPartition() const
  {
    return Handle(ActDraw_StubAPartition)::DownCast( this->Partition(Partition_A) );
  }

public:

  //! Initializes a collection of Tree Function GUIDs which are going to pass
  //! out-scope Reference Filter on Copy/Paste operation. Normally, you
  //! are expected to avoid the methods like this, just because there is
  //! already invariantCopyRefs method which is called automatically. The
  //! only benefit from having such additional methods is to provide
  //! dynamic changing of Reference Filter contents. It is very specific
  //! and unlikely valuable in real-world applications. However, this is
  //! really useful in unit tests.
  //! \param theFuncGUIDs [in] Function GUIDs to pass.
  inline void LoadCopyFuncGUIDs(const ActAPI_FuncGUIDStream& theFuncGUIDs)
  {
    m_copyGUIDs = theFuncGUIDs;
  }

  //! Same as LoadCopyFuncGUIDs, however, specialized for direct References,
  //! not for Tree Functions.
  //! \param theRefs [in] References to pass.
  inline void LoadCopyRefs(const ActAPI_ParameterLocatorStream& theRefs)
  {
    m_copyRefs = theRefs;
  }

// Methods we are forced to implement in order to have complete
// mechanism for Data Model construction:
private:

  virtual void
    initPartitions();

  virtual void
    initFunctionDrivers();

  virtual Standard_Boolean
    populate();

// Methods we are forced to implement in order to have complete set of
// Model structure management services:
private:

  Handle(ActAPI_IPartition)
    getVariablePartition(const VariableType& theVarType) const;

  virtual Handle(ActAPI_INode)
    getRootNode() const;

  virtual void
    invariantCopyRefs(ActAPI_FuncGUIDStream& FuncGUIDs,
                      ActAPI_ParameterLocatorStream& Refs) const;

// Methods we are forced to implement in order to have complete set of
// Model versioning services:
private:

  virtual Standard_Integer
    actualVersionApp();

  virtual Handle(ActData_CAFConverter)
    converterApp();

private:

  //! Partition IDs.
  enum PartitionType
  {
    Partition_Coord = 1,
    Partition_A
  };

// Properties for dynamical setting of out-scope filter arguments:
private:

  //! Tree Function GUIDs to pass out-scope filtering.
  ActAPI_FuncGUIDStream m_copyGUIDs;

  //! Reference Parameters to pass out-scope filtering.
  ActAPI_ParameterLocatorStream m_copyRefs;

};

#endif
