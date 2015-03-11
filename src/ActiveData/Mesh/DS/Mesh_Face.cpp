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

// Mesh includes
#include <Mesh_Face.h>

//=======================================================================
//function : GetFaceDefinedByNodes
//purpose  : 
//=======================================================================
void Mesh_Face::GetFaceDefinedByNodes(const Standard_Integer /*rank*/, 
                                           const Standard_Address idnode,
                                           Standard_Integer& nb) const
{
  nb = myNbNodes;
  Standard_Integer *ptr = (Standard_Integer *)idnode;
  const Standard_Integer *ptrFrom = (const Standard_Integer *)GetConnections();
  for (Standard_Integer i=0; i < nb; ++i)
    ptr[i] = ptrFrom[i];
}

//=======================================================================
//function : Print
//purpose  : 
//=======================================================================

void Mesh_Face::Print(Standard_OStream& OS) const
{
  OS << "face < " << myID <<" > : ( ";
  for (Standard_Integer i=1; i<myNbNodes; ++i)
    OS << GetConnection(i) << " , ";
  OS << GetConnection(myNbNodes) << " )" << endl;
}
