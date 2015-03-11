//-----------------------------------------------------------------------------
// Created on: June 2012
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
#include <ActTest_StubCNode.h>

// Active Data includes
#include <ActData_ParameterFactory.h>

// Active Data (auxiliary) includes
#include <ActAux_TimeStamp.h>

//-----------------------------------------------------------------------------
// Implementation of Data Node for testing purposes
//-----------------------------------------------------------------------------

//! Default constructor.
ActTest_StubCNode::ActTest_StubCNode()
{
  REGISTER_PARAMETER(Int,           PID_Int);
  REGISTER_PARAMETER(Real,          PID_Real);
  REGISTER_PARAMETER(Bool,          PID_Bool);
  REGISTER_PARAMETER(Shape,         PID_Shape);
  REGISTER_PARAMETER(RealArray,     PID_RealArray);
  REGISTER_PARAMETER(TreeFunction,  PID_TFunc);
  REGISTER_PARAMETER(AsciiString,   PID_AStr);
  REGISTER_PARAMETER(Name,          PID_UStr);
  REGISTER_PARAMETER(BoolArray,     PID_BoolArray);
  REGISTER_PARAMETER(StringArray,   PID_StrArray);
  REGISTER_PARAMETER(ComplexArray,  PID_ComplexArray);
  REGISTER_PARAMETER(IntArray,      PID_IntArray);
  REGISTER_PARAMETER(ReferenceList, PID_RefList);
  REGISTER_PARAMETER(Group,         PID_Group);
  REGISTER_PARAMETER(Mesh,          PID_Mesh);
  REGISTER_PARAMETER(Reference,     PID_Ref);
  REGISTER_PARAMETER(Selection,     PID_Selection);
  REGISTER_PARAMETER(TimeStamp,     PID_TimeStamp);
}

//! This method will be called by Nodal Factory in order to allocate
//! Nodes automatically by request (e.g. in Model::FindNode routine).
//! \return new instance of our Dummy Node allocated in heap.
Handle(ActAPI_INode) ActTest_StubCNode::Instance()
{
  return new ActTest_StubCNode();
}

//! Accessor for the Node's name.
//! \return name of the Node.
TCollection_ExtendedString ActTest_StubCNode::GetName()
{
  return TCollection_ExtendedString();
}

//! Sets name for the Node.
//! \param theName [in] name to set.
void ActTest_StubCNode::SetName(const TCollection_ExtendedString& ActData_NotUsed(theName))
{
  // Do nothing...
}

//! Initializes Nodal Parameters with default values.
void ActTest_StubCNode::Init()
{
  ActParamTool::AsInt          ( this->Parameter(PID_Int) )         ->SetValue ( 0 );
  ActParamTool::AsReal         ( this->Parameter(PID_Real) )        ->SetValue ( 0.0 );
  ActParamTool::AsBool         ( this->Parameter(PID_Bool) )        ->SetValue ( Standard_False );
  ActParamTool::AsShape        ( this->Parameter(PID_Shape) )       ->SetShape ( TopoDS_Shape() );
  ActParamTool::AsRealArray    ( this->Parameter(PID_RealArray) )   ->SetArray ( NULL );
  ActParamTool::AsAsciiString  ( this->Parameter(PID_AStr) )        ->SetValue ( TCollection_AsciiString() );
  ActParamTool::AsName         ( this->Parameter(PID_UStr) )        ->SetValue ( TCollection_ExtendedString() );
  ActParamTool::AsBoolArray    ( this->Parameter(PID_BoolArray) )   ->SetArray ( NULL );
  ActParamTool::AsStringArray  ( this->Parameter(PID_StrArray) )    ->SetArray ( NULL );
  ActParamTool::AsComplexArray ( this->Parameter(PID_ComplexArray) )->SetArray ( NULL );
  ActParamTool::AsIntArray     ( this->Parameter(PID_IntArray) )    ->SetArray ( NULL );
  ActParamTool::AsMesh         ( this->Parameter(PID_Mesh) )        ->SetMesh  ( new ActData_Mesh );
  ActParamTool::AsSelection    ( this->Parameter(PID_Selection) )   ->SetMask  ( new TColStd_HPackedMapOfInteger );
  ActParamTool::AsTimeStamp    ( this->Parameter(PID_TimeStamp) )   ->SetValue ( new ActAux_TimeStamp );
}
