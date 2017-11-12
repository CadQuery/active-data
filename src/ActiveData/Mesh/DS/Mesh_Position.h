//-----------------------------------------------------------------------------
// Created on: June 2016
//-----------------------------------------------------------------------------
// Copyright (c) 2017, OPEN CASCADE SAS
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright
//      notice, this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//    * Neither the name of OPEN CASCADE SAS nor the
//      names of all contributors may be used to endorse or promote products
//      derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Web: http://dev.opencascade.org
//-----------------------------------------------------------------------------

#ifndef Mesh_Position_HeaderFile
#define Mesh_Position_HeaderFile

// Active Data includes
#include <ActData.h>

// Mesh includes
#include <Mesh_TypeOfPosition.h>

// OCCT includes
#include <gp_Pnt.hxx>

DEFINE_STANDARD_HANDLE(Mesh_Position, Standard_Transient)

//! Abstract class to define the different positions of a node
//! related to the underlying geometry (CAD model).
class Mesh_Position : public Standard_Transient
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(Mesh_Position, Standard_Transient)

public:

  //! returns the resulting 3d point to be set
  //! in the MeshNode instance
  //! must be redefined by inherited classes
  ActData_EXPORT virtual const gp_Pnt& Coords() const;

  //! returns the type of position
  ActData_EXPORT virtual Mesh_TypeOfPosition GetTypeOfPosition() const = 0;

  //! Sets the ShapeId of the position
  void SetShapeId (const Standard_Integer aShapeId);

  //! Returns the ShapeId of the position
  Standard_Integer GetShapeId() const;

protected:

  Mesh_Position();
  Mesh_Position(const Standard_Integer aShapeId);

private:

  Standard_Integer myShapeId;

};


inline Mesh_Position::Mesh_Position()
  : myShapeId(0)
{
}

//=======================================================================
//function : Mesh_Position
//purpose  : 
//=======================================================================

inline Mesh_Position::Mesh_Position(const Standard_Integer aShapeId)
  : myShapeId(aShapeId)
{
}

//=======================================================================
//function : SetShapeId
//purpose  : 
//=======================================================================

inline void Mesh_Position::SetShapeId(const Standard_Integer aShapeId)
{
  myShapeId = aShapeId;
}

//=======================================================================
//function : GetShapeId
//purpose  : 
//=======================================================================

inline Standard_Integer Mesh_Position::GetShapeId() const
{
  return myShapeId;
}

#endif
