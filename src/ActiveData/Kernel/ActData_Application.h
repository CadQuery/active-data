//-----------------------------------------------------------------------------
// Created on: February 2012
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

#ifndef ActData_Application_HeaderFile
#define ActData_Application_HeaderFile

// Active Data includes
#include <ActData_Common.h>

// OCCT includes
#include <TDocStd_Application.hxx>

DEFINE_STANDARD_HANDLE(ActData_Application, TDocStd_Application)

//! \ingroup AD_DF
//!
//! Application class representing the corresponding notion in OCAF
//! architecture. The single instance of this class is used to manipulate
//! with CAF Documents which in turn contain the actual application data.
//! CAF Application is responsible for managing CAF documents, i.e. saving,
//! opening, etc.
class ActData_Application : public TDocStd_Application
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActData_Application, TDocStd_Application)

public:

  ActData_EXPORT static Handle(ActData_Application) Instance();

  ActData_EXPORT virtual void Formats(TColStd_SequenceOfExtendedString& theFormats);

  ActData_EXPORT Standard_CString ResourcesName();

private:

  ActData_Application();

};

#endif
