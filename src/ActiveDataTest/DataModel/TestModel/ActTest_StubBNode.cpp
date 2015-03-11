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
#include <ActTest_StubBNode.h>

// Active Data includes
#include <ActData_ParameterFactory.h>

//-----------------------------------------------------------------------------
// Implementation of Data Node for testing purposes
//-----------------------------------------------------------------------------

//! Default constructor.
ActTest_StubBNode::ActTest_StubBNode()
{
  REGISTER_PARAMETER(Name,          PID_Name);
  REGISTER_PARAMETER(Int,           PID_Int);
  REGISTER_PARAMETER(Real,          PID_Real);
  REGISTER_PARAMETER(TreeFunction,  PID_TFunc);
  REGISTER_PARAMETER(Reference,     PID_Ref);
  REGISTER_PARAMETER(ReferenceList, PID_RefList);
}

//! This method will be called by Nodal Factory in order to allocate
//! Nodes automatically by request (e.g. in Model::FindNode routine).
//! \return new instance of our Dummy Node allocated in heap.
Handle(ActAPI_INode) ActTest_StubBNode::Instance()
{
  return new ActTest_StubBNode();
}

//! Accessor for the Node's name.
//! \return name of the Node.
TCollection_ExtendedString ActTest_StubBNode::GetName()
{
  return ActData_ParameterFactory::AsName( this->Parameter(PID_Name) )->GetValue();
}

//! Sets name for the Node.
//! \param theName [in] name to set.
void ActTest_StubBNode::SetName(const TCollection_ExtendedString& theName)
{
  ActData_ParameterFactory::AsName( this->Parameter(PID_Name) )->SetValue(theName);
}

//! Initializes the basic set of Nodal Parameters.
//! \param theIntVal [in] integer value to set.
//! \param theRealVal [in] real value to set.
void ActTest_StubBNode::Init(const Standard_Integer theIntVal,
                             const Standard_Real    theRealVal)
{
  ActData_ParameterFactory::AsInt ( this->Parameter(PID_Int) )->SetValue(theIntVal);
  ActData_ParameterFactory::AsReal( this->Parameter(PID_Real)    )->SetValue(theRealVal);
}

//! Accessor for the integer value.
//! \return requested value.
Standard_Integer ActTest_StubBNode::GetIntValue() const
{
  return ActData_ParameterFactory::AsInt( this->Parameter(PID_Int) )->GetValue();
}

//! Accessor for the real value.
//! \return requested value.
Standard_Real ActTest_StubBNode::GetRealValue() const
{
  return ActData_ParameterFactory::AsReal( this->Parameter(PID_Real) )->GetValue();
}
