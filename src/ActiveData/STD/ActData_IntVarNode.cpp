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
#include <ActData_IntVarNode.h>

// Active Data includes
#include <ActData_ParameterFactory.h>

//! Constructs new Data Node in a heap.
//! \return Node instance.
Handle(ActAPI_INode) ActData_IntVarNode::Instance()
{
  return new ActData_IntVarNode();
}

//! Default constructor performing registering of the underlying
//! Parameters.
ActData_IntVarNode::ActData_IntVarNode() : ActData_BaseVarNode()
{
  REGISTER_PARAMETER_EXPR(Int, Param_Value);
}

//! Initializes the basic set of Nodal Parameters.
//! \param theName [in] variable name.
//! \param theValue [in] value to set.
void ActData_IntVarNode::Init(const TCollection_AsciiString& theName,
                              const Standard_Integer theValue)
{
  this->SetVariableName(theName);
  this->SetValue(theValue);
}

//! Setter for the value.
//! \param theValue [in] value to set.
void ActData_IntVarNode::SetValue(const Standard_Integer theValue)
{
  ActData_ParameterFactory::AsInt( this->Parameter(Param_Value) )->SetValue(theValue);
}

//! Getter for the value.
//! \return stored value.
Standard_Integer ActData_IntVarNode::GetValue() const
{
  return ActData_ParameterFactory::AsInt( this->Parameter(Param_Value) )->GetValue();
}
