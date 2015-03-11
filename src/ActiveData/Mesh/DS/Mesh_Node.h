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

#ifndef Mesh_Node_HeaderFile
#define Mesh_Node_HeaderFile

// Mesh includes
#include <Mesh_Element.h>
#include <Mesh_Position.h>

DEFINE_STANDARD_HANDLE(Mesh_Node, Mesh_Element)

class Mesh_Node : public Mesh_Element
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(Mesh_Node, Mesh_Element)

public:

  Mesh_Node() : Mesh_Element (-1,1) {}

public:

  ActData_EXPORT Mesh_Node(const Standard_Integer ID, const Standard_Real x, const Standard_Real y, const Standard_Real z);

  ActData_EXPORT void Print (Standard_OStream& OS) const Standard_OVERRIDE;

    Standard_Integer GetKey() const Standard_OVERRIDE;

    Standard_Real X() const;

    Standard_Real Y() const;

    Standard_Real Z() const;

    const gp_Pnt& Pnt() const;

  //! Change the node location. If the last parameter is passed True,
  //! then the normals are cleared in the Node and in all its
  //! inverse elements.
  ActData_EXPORT void SetPnt (const gp_Pnt& P, const Standard_Boolean isClearNormals = Standard_False);

    void AddInverseElement (const Handle(Mesh_Element)& ME) Standard_OVERRIDE;

  ActData_EXPORT void RemoveInverseElement (const Handle(Mesh_Element)& parent);

    const Mesh_ListOfElements& InverseElements() const Standard_OVERRIDE;

    void ClearInverseElements() Standard_OVERRIDE;

    void SetPosition (const Handle(Mesh_Position)& aPos);

    const Handle(Mesh_Position)& GetPosition() const;

  //! return the mesh element type
    Mesh_ElementType GetType() const Standard_OVERRIDE;

  //! creates a copy of me
    virtual Handle(Mesh_Element) Copy (const Standard_Integer theID) const Standard_OVERRIDE;

public:

    inline Standard_Boolean operator>(const Mesh_Node& N) const
    {
      return this->GetID() > N.GetID();
    }

    inline Standard_Boolean operator==(const Mesh_Node& N) const
    {
      return this->GetID() == N.GetID();
    }

private:

  gp_Pnt                myPnt;
  Mesh_ListOfElements   myInverseElements;
  Handle(Mesh_Position) myPosition;

};


//=======================================================================
//function : GetKey
//purpose  : 
//=======================================================================

inline Standard_Integer Mesh_Node::GetKey() const
{
  return myID;
}

//=======================================================================
//function : X
//purpose  : 
//           
//=======================================================================

inline Standard_Real Mesh_Node::X() const
{
  return myPnt.X();
}

//=======================================================================
//function : Y
//purpose  : 
//           
//=======================================================================

inline Standard_Real Mesh_Node::Y() const
{
  return myPnt.Y();
}

//=======================================================================
//function : Z
//purpose  : 
//=======================================================================

inline Standard_Real Mesh_Node::Z() const
{
  return myPnt.Z();
}

//=======================================================================
//function : Pnt
//purpose  : 
//           
//=======================================================================

inline const gp_Pnt& Mesh_Node::Pnt() const
{
  return myPnt;
}

//=======================================================================
//function : AddInverseElement
//purpose  : 
//=======================================================================

inline void Mesh_Node::AddInverseElement(const Handle(Mesh_Element)& ME)
{
  myInverseElements.Append(ME);
}

//=======================================================================
//function : InverseElements
//purpose  : 
//=======================================================================

inline const Mesh_ListOfElements& Mesh_Node::InverseElements() const
{
  return myInverseElements;
}

//=======================================================================
//function : ClearInverseElements
//purpose  : 
//=======================================================================

inline void Mesh_Node::ClearInverseElements()
{
  myInverseElements.Clear();
}

//=======================================================================
//function : SetPosition
//purpose  : 
//=======================================================================

inline void Mesh_Node::SetPosition(const Handle(Mesh_Position)& aPos)
{
  myPosition = aPos;
}

//=======================================================================
//function : GetPosition
//purpose  : 
//=======================================================================

inline const Handle(Mesh_Position)& Mesh_Node::GetPosition() const
{
  return myPosition;
}

//=======================================================================
//function : GetType
//purpose  :
//=======================================================================

inline Mesh_ElementType Mesh_Node::GetType() const
{
  return Mesh_ET_Node;
}

//=======================================================================
//function : Copy
//purpose  : creates a copy of me
//=======================================================================

inline Handle(Mesh_Element) Mesh_Node::Copy(const Standard_Integer theID) const
{
  return new Mesh_Node(theID, myPnt.X(), myPnt.Y(), myPnt.Z());
}

#endif
