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

// Own include
#include <ActData_Application.h>

// OCCT includes
#include <TColStd_SequenceOfExtendedString.hxx>

//! Accessor for static instance of CAF Application.
//! \return instance of CAF Application.
Handle(ActData_Application) ActData_Application::Instance()
{
  static Handle(ActData_Application) anApp;
  if ( anApp.IsNull() )
    anApp = new ActData_Application();
  return anApp;
}

//! Default constructor.
ActData_Application::ActData_Application() : TDocStd_Application()
{
}

//! Enumerates the accepted formats which might be used by persistence
//! mechanism.
//! \param theFormats [out] collection of accepted formats to be populated
//!        by this method.
void ActData_Application::Formats(TColStd_SequenceOfExtendedString& theFormats) 
{
  theFormats.Append( TCollection_ExtendedString(ACTBinFormat) );
}

//! Name of the resources file containing descriptions of the accepted
//! formats.
//! \return relative filename.
Standard_CString ActData_Application::ResourcesName()
{
  return Standard_CString("Resources");
}
