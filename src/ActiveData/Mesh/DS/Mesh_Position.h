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
