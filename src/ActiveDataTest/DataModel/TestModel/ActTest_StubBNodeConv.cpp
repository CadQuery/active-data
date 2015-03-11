//-----------------------------------------------------------------------------
// Created on: March 2013
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
#include <ActTest_StubBNodeConv.h>

// Active Data includes
#include <ActData_ParameterFactory.h>

//-----------------------------------------------------------------------------
// Implementation of Data Node for testing purposes
//-----------------------------------------------------------------------------

//! Default constructor.
ActTest_StubBNodeConv::ActTest_StubBNodeConv()
{
  REGISTER_PARAMETER(Name,          PID_Name);
  REGISTER_PARAMETER(Int,           PID_Int);
  REGISTER_PARAMETER(Int,           PID_NEWInt1);
  REGISTER_PARAMETER(Real,          PID_Real);
  REGISTER_PARAMETER(TreeFunction,  PID_TFunc);
  REGISTER_PARAMETER(Int,           PID_NEWInt2);
  REGISTER_PARAMETER(ReferenceList, PID_RefList);
}

//! This method will be called by Nodal Factory in order to allocate
//! Nodes automatically by request (e.g. in Model::FindNode routine).
//! \return new instance of our Dummy Node allocated in heap.
Handle(ActAPI_INode) ActTest_StubBNodeConv::Instance()
{
  return new ActTest_StubBNodeConv();
}

//! Accessor for the Node's name.
//! \return name of the Node.
TCollection_ExtendedString ActTest_StubBNodeConv::GetName()
{
  return ActData_ParameterFactory::AsName( this->Parameter(PID_Name) )->GetValue();
}

//! Sets name for the Node.
//! \param theName [in] name to set.
void ActTest_StubBNodeConv::SetName(const TCollection_ExtendedString& theName)
{
  ActData_ParameterFactory::AsName( this->Parameter(PID_Name) )->SetValue(theName);
}


//! Intializes the basic set of Nodal Parameters.
void ActTest_StubBNodeConv::Init()
{
  ActData_ParameterFactory::AsInt ( this->Parameter(PID_Int) )    ->SetValue(0);
  ActData_ParameterFactory::AsInt ( this->Parameter(PID_NEWInt1) )->SetValue(0);
  ActData_ParameterFactory::AsReal( this->Parameter(PID_Real)    )->SetValue(0.0);
  ActData_ParameterFactory::AsInt ( this->Parameter(PID_NEWInt2) )->SetValue(0);
}
