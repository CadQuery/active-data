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

#ifndef Mesh_ElementsIterator_HeaderFile
#define Mesh_ElementsIterator_HeaderFile

// Mesh includes
#include <Mesh_Element.h>

//! The Iterator objet to iterate on all faces of a mesh
class Mesh_ElementsIterator 
{
public:

  //! Empty constructor
  Mesh_ElementsIterator();

  //! Constructor
  ActData_EXPORT Mesh_ElementsIterator(const Handle(ActData_Mesh)& theMesh, const Mesh_ElementType theType);

  //! Reset the Iterator on the faces of mesh <M>.
  //! This method allows to add another type to iterate,
  //! e.g., Face + Edge. The default value (Node) does not
  //! change the previously installed iterated type
  ActData_EXPORT void Initialize (const Handle(ActData_Mesh)& aMesh, const Mesh_ElementType anAddType = Mesh_ET_Node);

  //! Returns True if there is a current mesh element.
  Standard_Boolean More() const;

  //! Moves to the next face.
  void Next();

  //! Query the current value of the iterator
  const Handle(Mesh_Element)& GetValue() const;

  //! Destructor
  virtual void Destroy();
  virtual ~Mesh_ElementsIterator() { Destroy(); }

protected:

  
  //! If the current value of myIter is not relevant, perform
  //! internal search of the next relevant value.
  ActData_EXPORT virtual void findNext();

  Standard_Integer myType;
  Mesh_VectorOfElements::Iterator myIter;
  Handle(ActData_Mesh) myMesh;

};


//=======================================================================
//function : Mesh_ElementsIterator
//purpose  : Empty constructor
//=======================================================================

inline Mesh_ElementsIterator::Mesh_ElementsIterator ()
{}

//=======================================================================
//function : More
//purpose  : 
//=======================================================================

inline Standard_Boolean Mesh_ElementsIterator::More () const
{
  return myIter.More();
}

//=======================================================================
//function : Next
//purpose  : 
//=======================================================================

inline void Mesh_ElementsIterator::Next()
{
  myIter.Next();
  findNext();
}

//=======================================================================
//function : GetValue
//purpose  : 
//=======================================================================

inline const Handle(Mesh_Element)& Mesh_ElementsIterator::GetValue () const
{
  return myIter.Value();
}

//=======================================================================
//function : Destroy
//purpose  : 
//=======================================================================

inline void Mesh_ElementsIterator::Destroy ()
{
}

#endif
