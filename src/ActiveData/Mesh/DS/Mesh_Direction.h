//-----------------------------------------------------------------------------
// Created on: June 2016
//-----------------------------------------------------------------------------
// Copyright (c) 2017, OPEN CASCADE SAS
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. All advertising materials mentioning features or use of this software
//    must display the following acknowledgement:
//    This product includes software developed by the OPEN CASCADE SAS.
// 4. Neither the name of the OPEN CASCADE SAS nor the
//    names of its contributors may be used to endorse or promote products
//    derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY OPEN CASCADE SAS ''AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL OPEN CASCADE SAS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
