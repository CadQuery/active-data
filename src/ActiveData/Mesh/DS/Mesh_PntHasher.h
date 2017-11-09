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

#ifndef Mesh_PntHasher_HeaderFile
#define Mesh_PntHasher_HeaderFile

// OCCT includes
#include <gp_Pnt.hxx>

class Mesh_PntHasher 
{
public:

  //! Returns a HasCode value  for  the  Key <K>  in the
  //! range 0..Upper.
  static int HashCode(const gp_Pnt& Point, const int Upper);

  //! Returns True  when the two  keys are the same. Two
  //! same  keys  must   have  the  same  hashcode,  the
  //! contrary is not necessary.
  static unsigned IsEqual(const gp_Pnt& Point1, const gp_Pnt& Point2);
};


//=======================================================================
//function : HashCode
//purpose  : 
//=======================================================================

inline int Mesh_PntHasher::HashCode(const gp_Pnt& point, const int Upper)
{
  union 
  {
    double R[3];
    int    I[6];
  } U;

  point.Coord(U.R[0],U.R[1],U.R[2]);

  return ::HashCode(U.I[0]/23+U.I[1]/19+U.I[2]/17+U.I[3]/13+U.I[4]/11+U.I[5]/7,Upper);
}

//=======================================================================
//function : IsEqual
//purpose  : 
//=======================================================================

inline unsigned Mesh_PntHasher::IsEqual(const gp_Pnt& point1, const gp_Pnt& point2)
{
  Standard_Real tab1[3], tab2[3];
  point1.Coord(tab1[0],tab1[1],tab1[2]);
  point2.Coord(tab2[0],tab2[1],tab2[2]);
  return (memcmp(tab1,tab2,sizeof(tab1)) == 0);
}

#endif
