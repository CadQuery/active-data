//-----------------------------------------------------------------------------
// Created on: April 2014
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

#ifndef ActData_RealArrayOwnerAPI_HeaderFile
#define ActData_RealArrayOwnerAPI_HeaderFile

// Active Data includes
#include <ActData_BaseNode.h>
#include <ActData_ParameterFactory.h>
#include <ActData_Utils.h>

//! \ingroup AD_DF
//!
//! Base class for Data Nodes manipulating arrays of real scalars. The
//! indexation starts with 0.
class ActData_RealArrayOwnerAPI
{
// Working with reference lists:
public:

  ActData_EXPORT void
    AddElement(const Standard_Integer theArrPID,
               const Standard_Real theVal);

  ActData_EXPORT void
    PrependElement(const Standard_Integer theArrPID,
                   const Standard_Real theVal);

  ActData_EXPORT Standard_Boolean
    RemoveElement(const Standard_Integer theArrPID,
                  const Standard_Integer theIndex);

  ActData_EXPORT void
    InsertElementAfter(const Standard_Integer theArrPID,
                       const Standard_Integer theIndex,
                       const Standard_Real theVal);

  ActData_EXPORT Standard_Real
    GetElement(const Standard_Integer theArrPID,
               const Standard_Integer theIndex) const;

  ActData_EXPORT void
    SetElement(const Standard_Integer theArrPID,
               const Standard_Integer theIndex,
               const Standard_Real theVal) const;

  ActData_EXPORT Standard_Integer
    NbElements(const Standard_Integer theArrPID) const;

public:

  virtual Handle(ActAPI_INode) RealArraySource() const = 0;

// Internal methods:
protected:

  Handle(ActData_RealArrayParameter) arrParam(const Standard_Integer thePID) const;

protected:

  //! Allocation is allowed only via Instance method.
  ActData_RealArrayOwnerAPI() {};

};

#endif
