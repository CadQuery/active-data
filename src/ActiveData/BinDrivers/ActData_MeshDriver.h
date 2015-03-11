//-----------------------------------------------------------------------------
// Created on: May 2012
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

#ifndef ActData_MeshDriver_HeaderFile
#define ActData_MeshDriver_HeaderFile

// Active Data includes
#include <ActData_Common.h>
#include <ActData_MeshAttr.h>

// Mesh includes
#include <Mesh_ElementsIterator.h>
#include <Mesh_Node.h>
#include <Mesh_Quadrangle.h>
#include <Mesh_Triangle.h>

// OCCT includes
#include <BinMDF_ADriver.hxx>
#include <CDM_MessageDriver.hxx>

DEFINE_STANDARD_HANDLE(ActData_MeshDriver, BinMDF_ADriver)

//! \ingroup AD_DF
//!
//! Storage/Retrieval Driver for Mesh Attribute.
class ActData_MeshDriver : public BinMDF_ADriver
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActData_MeshDriver, BinMDF_ADriver)

public:

  //---------------------------------------------------------------------------

  template <typename TStream>
  static bool
    Write(const Handle(ActData_MeshAttr)& meshAttr,
          TStream&                        out)
  {
    /* ==================================
     *  Push mesh nodes to binary buffer
     * ================================== */

    const Handle(ActData_Mesh)& aMeshDS = meshAttr->GetMesh();
    if ( aMeshDS.IsNull() )
    {
      return Standard_False;
    }

    // Access data
    Standard_Integer aNbNodes = aMeshDS->NbNodes();
    Standard_Integer aNbFaces = aMeshDS->NbFaces();

    // Push data
    out << aNbNodes << aNbFaces;

    Mesh_ElementsIterator aMeshNodesIt(aMeshDS, Mesh_ET_Node);
    for ( ; aMeshNodesIt.More(); aMeshNodesIt.Next() )
    {
      // Access next node
      Handle(Mesh_Node)
        aNode = Handle(Mesh_Node)::DownCast( aMeshNodesIt.GetValue() );

      // Push data
      out << aNode->GetID();
      out << aNode->Pnt().X();
      out << aNode->Pnt().Y();
      out << aNode->Pnt().Z();
    }

    /* =====================================
     *  Push mesh elements to binary buffer
     * ===================================== */

    Mesh_ElementsIterator aMeshElemsIt(aMeshDS, Mesh_ET_Face);
    for ( ; aMeshElemsIt.More(); aMeshElemsIt.Next() )
    {
      const Handle(Mesh_Element)& anElem = aMeshElemsIt.GetValue();

      // Proceed with TRIANGLE elements
      if ( anElem->IsInstance( STANDARD_TYPE(Mesh_Triangle) ) )
      {
        // Access element data
        Handle(Mesh_Triangle) aTriElem = Handle(Mesh_Triangle)::DownCast(anElem);
        Standard_Integer aTriNodeIds[3];
        Standard_Integer aNbNodes;
        aTriElem->GetFaceDefinedByNodes(3, aTriNodeIds, aNbNodes);

        // Push data
        out << aTriElem->GetID();
        out << aNbNodes;
        for ( Standard_Integer i = 0; i < aNbNodes; i++ )
          out << aTriNodeIds[i];
      }
      // Proceed with QUADRANGLE elements
      else if ( anElem->IsInstance( STANDARD_TYPE(Mesh_Quadrangle) ) )
      {
        // Access element data
        Handle(Mesh_Quadrangle) aQuadElem = Handle(Mesh_Quadrangle)::DownCast(anElem);
        Standard_Integer aQuadNodeIds[4];
        Standard_Integer aNbNodes;
        aQuadElem->GetFaceDefinedByNodes(4, aQuadNodeIds, aNbNodes);

        // Push data
        out << aQuadElem->GetID();
        out << aNbNodes;
        for ( Standard_Integer i = 0; i < aNbNodes; i++ )
          out << aQuadNodeIds[i];
      }
    }
    return Standard_True;
  }

  //---------------------------------------------------------------------------

  template <typename TStream>
  static Standard_Boolean
    Read(const TStream&            in,
         Handle(ActData_MeshAttr)& meshAttr)
  {
    /* ==========================================================
     *  Read number of nodes and elements from the binary buffer
     * ========================================================== */

    // Read data
    Standard_Integer aNbNodes, aNbFaces;
    in >> aNbNodes >> aNbFaces;

    /* ====================
     *  Restore mesh nodes
     * ==================== */

    for ( Standard_Integer i = 1; i <= aNbNodes; i++ )
    {
      Standard_Integer aNodeID;
      Standard_Real aCoordX, aCoordY, aCoordZ;

      // Read data
      in >> aNodeID;
      in >> aCoordX;
      in >> aCoordY;
      in >> aCoordZ;

      // Create a transient node
      meshAttr->GetMesh()->AddNodeWithID(aCoordX, aCoordY, aCoordZ, aNodeID);
    }

    /* =======================
     *  Restore mesh elements
     * ======================= */

    for ( Standard_Integer i = 1; i <= aNbFaces; i++ )
    {
      Standard_Integer aFaceID, aNbNodes;
      in >> aFaceID >> aNbNodes;

      if ( aNbNodes == 3 )
      {
        Standard_Integer aTriNodeIDs[3];
        in >> aTriNodeIDs[0] >> aTriNodeIDs[1] >> aTriNodeIDs[2];

        // Create a transient element
        meshAttr->GetMesh()->AddFaceWithID(aTriNodeIDs, aNbNodes, aFaceID);
      }
      else if ( aNbNodes == 4 )
      {
        Standard_Integer aQuadNodeIDs[4];
        in >> aQuadNodeIDs[0] >> aQuadNodeIDs[1]
           >> aQuadNodeIDs[2] >> aQuadNodeIDs[3];

        // Create a transient element
        meshAttr->GetMesh()->AddFaceWithID(aQuadNodeIDs, aNbNodes, aFaceID);
      }
      else
      {
        return Standard_False;
      }
    }
    return Standard_True;
  }

  //---------------------------------------------------------------------------

// Construction:
public:

  ActData_EXPORT
    ActData_MeshDriver(const Handle(CDM_MessageDriver)& theMsgDriver);

// Kernel:
public:

  ActData_EXPORT virtual Handle(TDF_Attribute)
    NewEmpty() const;

  ActData_EXPORT virtual Standard_Boolean
    Paste(const BinObjMgt_Persistent&  FromPersistent,
          const Handle(TDF_Attribute)& ToTransient,
          BinObjMgt_RRelocationTable&  RelocTable) const;
  
  ActData_EXPORT virtual void
    Paste(const Handle(TDF_Attribute)& FromTransient,
          BinObjMgt_Persistent&        ToPersistent,
          BinObjMgt_SRelocationTable&  RelocTable) const;

};

#endif
