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

// Own include
#include <ActDraw_DummyModel.h>

// Active Data Draw includes
#include <ActDraw_CoordNode.h>
#include <ActDraw_StubANode.h>

// Active Data includes
#include <ActData_CAFConverter.h>
#include <ActData_NodeFactory.h>
#include <ActData_Utils.h>

//-----------------------------------------------------------------------------
// Register involved Node types
//-----------------------------------------------------------------------------

REGISTER_NODE_TYPE(ActDraw_CoordNode)
REGISTER_NODE_TYPE(ActDraw_StubANode)

//-----------------------------------------------------------------------------
// Implementation of Data Model for testing purposes
//-----------------------------------------------------------------------------

//! Default constructor.
ActDraw_DummyModel::ActDraw_DummyModel()
{}

//! Registers user's Partitions in the Data Model. We use smart macro here
//! to make thing simpler.
void ActDraw_DummyModel::initPartitions()
{
  // Partition Type <-> Partition internal ID
  REGISTER_PARTITION(ActDraw_CoordPartition, Partition_Coord);
  REGISTER_PARTITION(ActDraw_StubAPartition, Partition_A);
}

//! Registers user's Tree Functions in the Data Model. You're free to omit
//! Tree Functions at all if you dislike the concept of active Data Model.
//! Anyway, you state the latter fact by keeping this method empty.
void ActDraw_DummyModel::initFunctionDrivers()
{
  // No functions
}

//! Performs initial population of the Data Model. This method will be
//! executed just after NewEmpty() invocation ensuring that even just
//! created Models do have the application-consistent structure. If you
//! do not need to perform any initializations of Nodal structure, just
//! keep the implementation empty.
//! \return true in case of success, false -- otherwise. Notice, that
//!         resulting value will be returned by NewEmpty basic method
//!         as well, so returning FALSE will be processed as Model
//!         creation failure.
Standard_Boolean ActDraw_DummyModel::populate()
{
  return Standard_True;
}

//! Returns a dedicated Partition for Nodal Variables.
//! \param theVarType [in] Variable type to return the dedicated
//!        Partition for.
//! \return Variable Partition.
Handle(ActAPI_IPartition)
  ActDraw_DummyModel::getVariablePartition(const VariableType& ActData_NotUsed(theVarType)) const
{
  return NULL;
}

//! Accessor for the root Data Node of the Model's hierarchy.
//! \return root Data Node.
Handle(ActAPI_INode) ActDraw_DummyModel::getRootNode() const
{
  ActDraw_StubAPartition::Iterator anIt( this->Partition(Partition_A) );
  return ( anIt.More() ? anIt.Value() : NULL );
}

//! Populates the passed collections of references to pass out-scope filtering
//! in Copy/Paste operation.
//! \param FuncGUIDs [in/out] Function GUIDs to pass.
//! \param Refs [in/out] Reference Parameters to pass.
void ActDraw_DummyModel::invariantCopyRefs(ActAPI_FuncGUIDStream& ActData_NotUsed(FuncGUIDs),
                                           ActAPI_ParameterLocatorStream& ActData_NotUsed(Refs)) const
{
}

//! Returns the version of your custom Data Model. This version number will
//! be stored in the persistent form of your Data Model and retrieved by
//! Load functionality. It allows you to implement your versioning
//! mechanism, i.e. compatibility conversions, etc.
//! \return the current version you define for your Data Model.
Standard_Integer ActDraw_DummyModel::actualVersionApp()
{
  return 0;
}

//! Allows you to perform conversion from the older version of Data Model
//! to the actual one. If you are not planning to have any kind of
//! backward compatibility for your Data Model, you should return NULL.
//! \return properly initialized CAF converter or NULL.
Handle(ActData_CAFConverter) ActDraw_DummyModel::converterApp()
{
  return NULL;
}
