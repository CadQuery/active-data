//-----------------------------------------------------------------------------
// Created on: March 2012
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
#include <ActData_BoolVarNode.h>

// Active Data includes
#include <ActData_ParameterFactory.h>

//! Constructs new Data Node in a heap.
//! \return Node instance.
Handle(ActAPI_INode) ActData_BoolVarNode::Instance()
{
  return new ActData_BoolVarNode();
}

//! Default constructor performing registering of the underlying
//! Parameters.
ActData_BoolVarNode::ActData_BoolVarNode() : ActData_BaseVarNode()
{
  REGISTER_PARAMETER_EXPR(Bool, Param_Value);
}

//! Initializes the basic set of Nodal Parameters.
//! \param theName [in] variable name.
//! \param theValue [in] value to set.
void ActData_BoolVarNode::Init(const TCollection_AsciiString& theName,
                               const Standard_Boolean theValue)
{
  this->SetVariableName(theName);
  this->SetValue(theValue);
}

//! Setter for the value.
//! \param theValue [in] value to set.
void ActData_BoolVarNode::SetValue(const Standard_Boolean theValue)
{
  ActData_ParameterFactory::AsBool( this->Parameter(Param_Value) )->SetValue(theValue);
}

//! Getter for the value.
//! \return stored value.
Standard_Boolean ActData_BoolVarNode::GetValue() const
{
  return ActData_ParameterFactory::AsBool( this->Parameter(Param_Value) )->GetValue();
}
