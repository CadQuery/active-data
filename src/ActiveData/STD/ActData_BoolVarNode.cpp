//-----------------------------------------------------------------------------
// Created on: March 2012
//-----------------------------------------------------------------------------
// Copyright (c) 2017, OPEN CASCADE SAS
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright
//      notice, this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//    * Neither the name of OPEN CASCADE SAS nor the
//      names of all contributors may be used to endorse or promote products
//      derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
