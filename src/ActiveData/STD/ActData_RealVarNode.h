//-----------------------------------------------------------------------------
// Created on: April 2012
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

#ifndef ActData_RealVarNode_HeaderFile
#define ActData_RealVarNode_HeaderFile

// Active Data includes
#include <ActData_BaseVarNode.h>
#include <ActData_RealParameter.h>

DEFINE_STANDARD_HANDLE(ActData_RealVarNode, ActData_BaseVarNode)

//! \ingroup AD_DF
//!
//! Simple Node defining its only Real Parameter as an expressible one.
//! This Node is shipped with Active Data to support Evaluation
//! mechanism. The idea behind this class is to represent Real Variables
//! involved in Python expressions. Anyway, you are free to use it as
//! just a plain data chunk if you want.
class ActData_RealVarNode : public ActData_BaseVarNode
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActData_RealVarNode, ActData_BaseVarNode)

  // Automatic registration of Node instance in the Nodal Factory.
  DEFINE_NODE_FACTORY(ActData_RealVarNode, Instance)

public:

  ActData_EXPORT static Handle(ActAPI_INode) Instance();

// Initialization routines:
public:

  ActData_EXPORT void Init(const TCollection_AsciiString& theName,
                           const Standard_Real theValue);

// Setters & Getters:
public:

  ActData_EXPORT void
    SetValue(const Standard_Real theValue);

  ActData_EXPORT Standard_Real
    GetValue() const;

protected:

  //! Allocation is allowed only via Instance method.
  ActData_EXPORT ActData_RealVarNode();

};

#endif
