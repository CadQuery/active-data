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

#ifndef ActDraw_CoordPartition_HeaderFile
#define ActDraw_CoordPartition_HeaderFile

// Active Data Draw includes
#include <ActDraw.h>

// Active Data includes
#include <ActData_BasePartition.h>

DEFINE_STANDARD_HANDLE(ActDraw_CoordPartition, ActData_BasePartition)

//! \ingroup AD_DRAW
//!
//! Partition for XYZ points.
class ActDraw_CoordPartition : public ActData_BasePartition
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActDraw_CoordPartition, ActData_BasePartition)

public:

  //! Creates new Partition instance in a heap.
  //! \return just created instance.
  static Handle(ActDraw_CoordPartition) Instance();

public:

  virtual Handle(Standard_Type)
    GetNodeType() const;

protected:

  //! Allow allocation only via Instance method.
  ActDraw_CoordPartition();

};

#endif
