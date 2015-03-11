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

// Own include
#include <ActData_MeshDriver.h>

// OCCT includes
#include <BinObjMgt_Persistent.hxx>

#undef COUT_DEBUG

//! Constructor accepting Message Driver for the parent class.
//! \param theMsgDriver [in] Message Driver for parent.
ActData_MeshDriver::ActData_MeshDriver(const Handle(CDM_MessageDriver)& theMsgDriver)
: BinMDF_ADriver(theMsgDriver)
{
}

//! Creates an empty instance of Mesh Attribute for data transferring.
//! \return empty instance of Mesh Attribute.
Handle(TDF_Attribute) ActData_MeshDriver::NewEmpty() const
{
  return new ActData_MeshAttr();
}

//! Transfers data from PERSISTENT source of Mesh Attribute into its TRANSIENT
//! form. This method is a secondary one comparing to the dual Paste method
//! performing converse operation and defining the format rules (order and the
//! membership of the items being recorded) so.
//! \param FromPersistent [in] persistence buffer to transfer data into
//!                            transient instance of Mesh Attribute from.
//! \param ToTransient    [in] transient instance of Mesh Attribute being
//!                            assembled.
//! \param RelocTable     [in] not used (see OCAF reference manual).
//! \return true in case of success, false -- otherwise.
Standard_Boolean
  ActData_MeshDriver::Paste(const BinObjMgt_Persistent&  FromPersistent,
                            const Handle(TDF_Attribute)& ToTransient,
                            BinObjMgt_RRelocationTable&  ActData_NotUsed(RelocTable)) const
{
  Handle(ActData_MeshAttr) aMeshAttr = Handle(ActData_MeshAttr)::DownCast(ToTransient);
  if ( aMeshAttr.IsNull() )
  {
    WriteMessage("ERROR: NULL Mesh Attribute");
    return Standard_False;
  }

  // Disable accumulation of deltas
  aMeshAttr->DeltaModeOff();

  // Create new Mesh DS
  aMeshAttr->NewEmptyMesh();

  // Read from the input stream
  Read<BinObjMgt_Persistent>(FromPersistent, aMeshAttr);

  // Enable accumulation of deltas
  aMeshAttr->DeltaModeOn();

  return Standard_True;
}

//! Transfers data from transient instance of Mesh Attribute into the
//! persistence buffer for further binary storing.
//! \param FromTransient [in] transient Mesh Attribute source.
//! \param ToPersistent [in] persistence buffer to transfer data to.
//! \param RelocTable [in] not used (see OCAF reference manual).
void ActData_MeshDriver::Paste(const Handle(TDF_Attribute)& FromTransient,
                               BinObjMgt_Persistent&        ToPersistent,
                               BinObjMgt_SRelocationTable&  ActData_NotUsed(RelocTable)) const
{
  /* ====================================================
   *  Access Mesh Attribute along with contained Mesh DS
   * ==================================================== */

  Handle(ActData_MeshAttr) aMeshAttr = Handle(ActData_MeshAttr)::DownCast(FromTransient);
  if ( aMeshAttr.IsNull() )
  {
    WriteMessage("ERROR: NULL Mesh Attribute");
    return;
  }

  // Write to the output stream
  Write<BinObjMgt_Persistent>(aMeshAttr, ToPersistent);
}
