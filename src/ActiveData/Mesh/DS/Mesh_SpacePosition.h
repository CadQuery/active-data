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

#ifndef Mesh_SpacePosition_HeaderFile
#define Mesh_SpacePosition_HeaderFile

// Mesh includes
#include <Mesh_Position.h>
#include <Mesh_TypeOfPosition.h>

// OCCT includes
#include <gp_Pnt.hxx>

DEFINE_STANDARD_HANDLE(Mesh_SpacePosition, Mesh_Position)

//! used to characterize a MeshNode with a 3D point
//! in space not related to any underlying geometry (CAD)
class Mesh_SpacePosition : public Mesh_Position
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(Mesh_SpacePosition, Mesh_Position)

public:

  //! Default constructor
  Mesh_SpacePosition();

  Mesh_SpacePosition(const Standard_Real x, const Standard_Real y, const Standard_Real z);

  Mesh_SpacePosition(const gp_Pnt& aCoords);

  //! returns the resulting 3d point to be set in the MeshNode instance
  virtual const gp_Pnt& Coords() const Standard_OVERRIDE;

  //! returns the type of position
  virtual Mesh_TypeOfPosition GetTypeOfPosition() const Standard_OVERRIDE;

  void SetCoords (const Standard_Real x, const Standard_Real y, const Standard_Real z);

  void SetCoords (const gp_Pnt& aCoords);

private:

  gp_Pnt myCoords;

};


//=======================================================================
//function : Mesh_SpacePosition
//purpose  : 
//=======================================================================

inline Mesh_SpacePosition::Mesh_SpacePosition()
  : Mesh_Position(),myCoords(0.,0.,0.)
{
}

//=======================================================================
//function : Mesh_SpacePosition
//purpose  : 
//=======================================================================

inline Mesh_SpacePosition::Mesh_SpacePosition(const Standard_Real x,
                                                const Standard_Real y,
                                                const Standard_Real z)
  : Mesh_Position(),myCoords(x,y,z)
{
}

//=======================================================================
//function : Mesh_SpacePosition
//purpose  : 
//=======================================================================

inline Mesh_SpacePosition::Mesh_SpacePosition(const gp_Pnt& aCoords)
  : Mesh_Position(),myCoords(aCoords)
{
}

//=======================================================================
//function : Coords
//purpose  : 
//=======================================================================

inline const gp_Pnt& Mesh_SpacePosition::Coords() const
{
  return myCoords;
}

//=======================================================================
//function : GetTypeOfPosition
//purpose  : 
//=======================================================================

inline Mesh_TypeOfPosition Mesh_SpacePosition::GetTypeOfPosition() const
{
  return Mesh_TOP_3DSPACE;
}

//=======================================================================
//function : SetCoords
//purpose  : 
//=======================================================================

inline void Mesh_SpacePosition::SetCoords(const Standard_Real x,
                                           const Standard_Real y,
                                           const Standard_Real z)
{
  myCoords.SetCoord(x,y,z);
}

//=======================================================================
//function : SetCoords
//purpose  : 
//=======================================================================

inline void Mesh_SpacePosition::SetCoords(const gp_Pnt& aCoords)
{
  myCoords = aCoords;
}

#endif // _ActData_SpacePosition_HeaderFile
