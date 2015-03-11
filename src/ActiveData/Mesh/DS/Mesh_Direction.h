//-----------------------------------------------------------------------------
// Created on: June 2016
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

#ifndef Mesh_Direction_HeaderFile
#define Mesh_Direction_HeaderFile

// Active Data includes
#include <ActData.h>

// OCCT includes
#include <gp_XYZ.hxx>

//! \ingroup AD_DF
//!
//! Direction which occupies only few memory. The components are stored in
//! normalized integer numbers, so that the value 1 is stored as INT_MAX
//! and the value -1 is stored as -INT_MAX.
class Mesh_Direction
{
 public:
  // ---------- PUBLIC METHODS ----------

  /// Empty constructor
  inline Mesh_Direction ()
  { Clear(); }

  /// Constructor
  inline Mesh_Direction (const gp_XYZ& theXYZ)
  { Set (theXYZ); }

  /// Reset (empty) this data object
  inline void                           Clear   ()
  { myCoord[0] = 0; myCoord[1] = 0; myCoord[2] = 0; }

  /// Check for emptiness
  inline Standard_Boolean               IsNull  () const
  { return ((myCoord[0] | myCoord[1] | myCoord[2]) == 0); }

  ActData_EXPORT void                  Set     (const Standard_Real theX,
                                                 const Standard_Real theY,
                                                 const Standard_Real theZ);

  ActData_EXPORT void                  Set     (const gp_XYZ& theXYZ);

  ActData_EXPORT Standard_Boolean      Get     (gp_Dir& outDir) const;

 private:
  // ---------- PRIVATE FIELDS ----------
  Standard_Integer myCoord[3];
};

#endif
