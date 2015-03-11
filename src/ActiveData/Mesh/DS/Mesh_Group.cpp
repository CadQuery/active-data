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
#include <Mesh_Group.h>

// OCCT includes
#include <Standard_TypeMismatch.hxx>

//=======================================================================
//function : AddSubGroup
//purpose  : 
//=======================================================================
Handle(Mesh_Group) Mesh_Group::AddSubGroup()
{
  Handle(Mesh_Group) subgroup = new Mesh_Group(this);
  if (!subgroup.IsNull())
    myChildren.Append(subgroup);
  return subgroup;
}

//=======================================================================
//function : RemoveSubGroup
//purpose  : 
//=======================================================================

Standard_Boolean Mesh_Group::RemoveSubGroup(const Handle(Mesh_Group)& aGroup)
{
  Mesh_ListOfGroups::Iterator itgroup(myChildren);
  for (; itgroup.More(); itgroup.Next()) {
    Handle(Mesh_Group) subgroup = itgroup.Value();
    if (subgroup == aGroup) {
      myChildren.Remove(itgroup);
      return Standard_True;
    }
  }
  return Standard_False;
}

//=======================================================================
//function : RemoveFromParent
//purpose  : 
//=======================================================================

Standard_Boolean Mesh_Group::RemoveFromParent()
{
  if (myParent.IsNull())
    return Standard_False;

  return (myParent->RemoveSubGroup(this));
}

//=======================================================================
//function : Add
//purpose  : 
//=======================================================================

void Mesh_Group::Add(const Handle(Mesh_Element)& ME)
{
  // the type of the group is determined by the first element added
  if (myElements.IsEmpty())
    myType = ME->GetType();
  else if (ME->GetType() != myType)
    Standard_TypeMismatch::Raise("Mesh_Group::Add");
  myElements.Add(ME);
}

//=======================================================================
//function : Remove
//purpose  : 
//=======================================================================

void Mesh_Group::Remove(const Handle(Mesh_Element)& ME)
{
  myElements.Remove(ME);
  if (myElements.IsEmpty())
    myType = Mesh_ET_All;
}
