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
