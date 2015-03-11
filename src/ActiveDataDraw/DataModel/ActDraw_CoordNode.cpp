//-----------------------------------------------------------------------------
// Created on: January 2016
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
#include <ActDraw_CoordNode.h>

// Active Data includes
#include <ActData_ParameterFactory.h>

//-----------------------------------------------------------------------------
// Implementation of Data Node for testing purposes
//-----------------------------------------------------------------------------

//! Default constructor.
ActDraw_CoordNode::ActDraw_CoordNode()
{
  REGISTER_PARAMETER(Name, PID_Name);
  REGISTER_PARAMETER(Real, PID_X);
  REGISTER_PARAMETER(Real, PID_Y);
  REGISTER_PARAMETER(Real, PID_Z);
}

//! This method will be called by Nodal Factory in order to allocate
//! Nodes automatically by request (e.g. in Model::FindNode routine).
//! \return new instance of our Node allocated in heap.
Handle(ActAPI_INode) ActDraw_CoordNode::Instance()
{
  return new ActDraw_CoordNode();
}

//! Accessor for the Node's name.
//! \return name of the Node.
TCollection_ExtendedString ActDraw_CoordNode::GetName()
{
  return ActData_ParameterFactory::AsName( this->Parameter(PID_Name) )->GetValue();
}

//! Sets name for the Node.
//! \param name [in] name to set.
void ActDraw_CoordNode::SetName(const TCollection_ExtendedString& name)
{
  ActData_ParameterFactory::AsName( this->Parameter(PID_Name) )->SetValue(name);
}

//! Initializes the basic set of Nodal Parameters.
//! \param x [in] X coordinate to set.
//! \param y [in] Y coordinate to set.
//! \param z [in] Z coordinate to set.
void ActDraw_CoordNode::Init(const Standard_Real x,
                             const Standard_Real y,
                             const Standard_Real z)
{
  ActParamTool::AsReal( this->Parameter(PID_X) )->SetValue(x);
  ActParamTool::AsReal( this->Parameter(PID_Y) )->SetValue(y);
  ActParamTool::AsReal( this->Parameter(PID_Z) )->SetValue(z);
}
