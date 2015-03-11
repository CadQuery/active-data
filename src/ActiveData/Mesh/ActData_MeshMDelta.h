//-----------------------------------------------------------------------------
// Created on: April 2012
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

#ifndef ActData_MeshMDelta_HeaderFile
#define ActData_MeshMDelta_HeaderFile

// Active Data includes
#include <ActData_Common.h>
#include <ActData_MeshDeltaEntities.h>

// OCCT includes
#include <Standard_OStream.hxx>
#include <TDF_DeltaOnModification.hxx>

// Active Data forward declarations
class ActData_MeshAttr;

DEFINE_STANDARD_HANDLE(ActData_MeshMDelta, TDF_DeltaOnModification)

//! \ingroup AD_DF
//!
//! Modification Delta for Mesh Attribute. Each Modification Delta manages
//! so called Modification Queue represented internally by simple OCCT
//! sequence. Modification Queue in-turn stores Modification Requests, all
//! having dual nature. E.g. Addition Request is dual for Removal Request
//! and vice versa.
//!
//! Conceptually Modification Delta represents an atomic portion of changes
//! which are to be applied on the actual Mesh DS currently stored in the
//! corresponding TDF Attribute. It can be INVERTED in order to exchange
//! the actual Modification Queue by its dual representation.
class ActData_MeshMDelta : public TDF_DeltaOnModification
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActData_MeshMDelta, TDF_DeltaOnModification)

// Construction:
public:

  ActData_EXPORT
    ActData_MeshMDelta(const Handle(ActData_MeshAttr)& ActualAttr);

// Kernel routines:
public:

  ActData_EXPORT virtual void
    Apply();

  ActData_EXPORT void
    Clean();

  ActData_EXPORT Handle(ActData_MeshMDelta)
    DeepCopy() const;

  ActData_EXPORT void
    Invert();

// Modification requests:
public:

  ActData_EXPORT void
    ReplacedMesh(const Handle(ActData_Mesh)& OldMesh,
                 const Handle(ActData_Mesh)& NewMesh);

  ActData_EXPORT void
    AddedNode(const Standard_Integer ID,
              const Standard_Real X,
              const Standard_Real Y,
              const Standard_Real Z);

  ActData_EXPORT void
    AddedTriangle(const Standard_Integer ID,
                  Standard_Address Nodes);

  ActData_EXPORT void
    AddedQuadrangle(const Standard_Integer ID,
                    Standard_Address Nodes);

  ActData_EXPORT void
    RemovedNode(const Standard_Integer ID);

  ActData_EXPORT void
    RemovedTriangle(const Standard_Integer ID);

  ActData_EXPORT void
    RemovedQuadrangle(const Standard_Integer ID);

// Debugging:
public:

  ActData_EXPORT virtual Standard_OStream&
    Dump(Standard_OStream& theOut) const;

private:

  //! Ordered collection of Modification Requests.
  ActData_DeltaMQueue m_queue;

};

#endif
