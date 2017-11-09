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
