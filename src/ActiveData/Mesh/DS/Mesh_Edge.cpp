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
#include <Mesh_Edge.h>

//=======================================================================
//function : GetKey
//purpose  : 
//=======================================================================
Standard_Integer Mesh_Edge::GetKey() const
{
  Standard_Integer aKey = myNodes[0] + myNodes[1];
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
void Mesh_Edge::SetConnections(const Standard_Integer idnode1, 
                                    const Standard_Integer idnode2)
{
  if (idnode1 < idnode2) {
    myNodes[0] = idnode1;
    myNodes[1] = idnode2;
  } else {
    myNodes[0] = idnode2;
    myNodes[1] = idnode1;
  }
}

//=======================================================================
//function : Print
//purpose  : 
//=======================================================================

void Mesh_Edge::Print(Standard_OStream& OS) const
{
  OS << "edge < " << myID <<" > : ( " << myNodes[0] << " , " << myNodes[1] << " )" << endl;
}
