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

// Own include
#include <Mesh_IDFactory.h>

// Mesh includes
#include <Mesh_Element.h>

// OCCT includes
#include <TColStd_MapIteratorOfPackedMapOfInteger.hxx>

//-----------------------------------------------------------------------------

Mesh_IDFactory::Mesh_IDFactory() : myMaxID(0)
{}

//-----------------------------------------------------------------------------

Standard_Integer Mesh_IDFactory::GetFreeID()
{
  TColStd_MapIteratorOfPackedMapOfInteger it(myPoolOfID);
  while (it.More()) {
    const Standard_Integer anID = it.Key();
    it.Next();
    myPoolOfID.Remove(anID);
    // We have to check that the ID is really free because it could be
    // already allocated by a direct call Mesh::AddElementWithID
    if (myElements(anID).IsNull())
      return anID;
  }
  return ++myMaxID;
}

//-----------------------------------------------------------------------------

void Mesh_IDFactory::ReleaseID(const Standard_Integer theID)
{
  myElements.ChangeValue(theID).Nullify();
  if (theID == myMaxID)
    --myMaxID;
  else
    myPoolOfID.Add(theID);
}

//-----------------------------------------------------------------------------

Standard_Boolean Mesh_IDFactory::BindID
                                (const Standard_Integer          ID,
                                 const Handle(Mesh_Element)& theElem)
{
  Standard_Boolean aResult (Standard_False);
  if (ID > 0) {
    if (ID < myElements.Length()) {
      Handle(Mesh_Element)& aTarget = myElements.ChangeValue(ID);
      if (aTarget.IsNull()) {
        aResult = Standard_True;
        aTarget = theElem;
      }
    } else {
      if (ID > myMaxID) {       // if ID has not been obtained via GetFreeID
        //MSV 8.11.06 for OCC13810: too much memory is allocated to
        // store free IDs. We reduce memory usage at the sacrifice 
        // of availability of these free IDs.
        //for (Standard_Integer id = myMaxID+1; id < ID; id++)
        //  myPoolOfID.Add (id);
        myMaxID = ID;
      }
      aResult = Standard_True;
      myElements.SetValue (ID, theElem);
    }
  }
  return aResult;
}

//-----------------------------------------------------------------------------

Handle(Mesh_Element) Mesh_IDFactory::MeshElement
                                        (const Standard_Integer ID) const
{
  if (ID > 0 && ID < myElements.Length())
    return myElements.Value (ID);
  return 0L;
}

//-----------------------------------------------------------------------------

NCollection_Vector<Handle(Mesh_Element)>::Iterator Mesh_IDFactory::Iterator() const
{
  return NCollection_Vector<Handle(Mesh_Element)>::Iterator(myElements);
}
