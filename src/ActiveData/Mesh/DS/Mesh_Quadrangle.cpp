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
#include <Mesh_Quadrangle.h>

//=======================================================================
//function : GetKey
//purpose  : compute the Key of the face based on the ids of its bounding nodes
//=======================================================================
Standard_Integer Mesh_Quadrangle::GetKey() const
{
  Standard_Integer aKey = myNodes[0];
  aKey += (aKey << 10);
  aKey ^= (aKey >> 6);
  aKey += (myNodes[1] + myNodes[3]);
  aKey += (aKey << 10);
  aKey ^= (aKey >> 6);
  aKey += myNodes[2];
  aKey += (aKey << 10);
  aKey ^= (aKey >> 6);
  aKey += (aKey << 3);
  aKey ^= (aKey >> 11);
//    return aKey + (aKey << 15);
  return aKey & 0x7fffffff;
}

//=======================================================================
//function : SetConnections
//purpose  : 
//=======================================================================

void Mesh_Quadrangle::SetConnections(const Standard_Integer idnode1, 
                                          const Standard_Integer idnode2,
                                          const Standard_Integer idnode3,
                                          const Standard_Integer idnode4)
{
  Standard_Integer idmin = (idnode1 < idnode2 ? idnode1 : idnode2);
  idmin = (idmin < idnode3 ? idmin : idnode3);
  idmin = (idmin < idnode4 ? idmin : idnode4);
  
  myNodes[0] = idmin;
  if (idmin == idnode1) {
    myNodes[1] = idnode2;
    myNodes[2] = idnode3;
    myNodes[3] = idnode4;
  } else if (idmin == idnode2) {
    myNodes[1] = idnode3;
    myNodes[2] = idnode4;
    myNodes[3] = idnode1;
  } else if (idmin == idnode3) {
    myNodes[1] = idnode4;
    myNodes[2] = idnode1;
    myNodes[3] = idnode2;
  } else {
    myNodes[1] = idnode1;
    myNodes[2] = idnode2;
    myNodes[3] = idnode3;
  }
}
