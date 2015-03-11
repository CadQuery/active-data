//-----------------------------------------------------------------------------
// Created on: January 2012
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

#ifndef ActDraw_Common_HeaderFile
#define ActDraw_Common_HeaderFile

// Windows API
#include <windows.h>

// Active Data (API) includes
#include <ActAPI_IModel.h>

// Active Data (Draw plug-in) includes
#include <ActDraw_Commands.h>
#include <ActDraw_DrawTestSuite.h>

// Mesh includes
#include <Mesh.h>
#include <Mesh_Element.h>
#include <Mesh_Group.h>

// Short-cut for function pointer on Windows API window procedures
#define WINPROC_PARAM(P) LRESULT (__stdcall *P) (HWND, UINT, WPARAM, LPARAM)

//! \ingroup AD_DRAW
//!
//! Auxillary data types and functions for any test suite.
namespace ActDraw_Common
{
  ActDraw_EXPORT TCollection_AsciiString
    AddrToString(const TopoDS_Shape& theShape);

  ActDraw_EXPORT Standard_Boolean
    SaveBinaryCAF(const TCollection_AsciiString& theFilename,
                  const Handle(ActAPI_IModel)& theModel);

  ActDraw_EXPORT Standard_Boolean
    OpenBinaryCAF(const TCollection_AsciiString& theFilename,
                  const Handle(ActAPI_IModel)& theModel);

  ActDraw_EXPORT TopoDS_Shape
    RandomShape();

  ActDraw_EXPORT Standard_Boolean
    RandomBoolean();

};

#endif
