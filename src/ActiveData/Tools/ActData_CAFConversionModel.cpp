//-----------------------------------------------------------------------------
// Created on: March 2013
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
#include <ActData_CAFConversionModel.h>

// Active Data includes
#include <ActData_ParameterFactory.h>

// OCCT includes
#include <TDF_Tool.hxx>

//! Default constructor.
ActData_CAFConversionModel::ActData_CAFConversionModel()
{
}

//! Checks whether the Model contains Conversion Node for the given
//! original NID.
//! \param theNID [in] ID of the Node in original Model.
//! \return true/false.
Standard_Boolean
  ActData_CAFConversionModel::ContainsNode(const ActAPI_DataObjectId& theNID) const
{
  return m_nodeMap.IsBound(theNID);
}

//! Adds new Node to Conversion Model populating its Conversion Parameters
//! with original data.
//! \param theNID [in] ID of the Node to add.
//! \param theModel [in] original Data Model.
//! \return true in case of success, false -- otherwise.
Standard_Boolean
  ActData_CAFConversionModel::AddOriginNode(const ActAPI_DataObjectId& theNID,
                                            const Handle(ActAPI_IModel)& theModel)
{
  Handle(ActData_CAFConversionNode) aConvNode = new ActData_CAFConversionNode;

  // NOTICE: we cannot use Data Cursors to access Nodal Parameters here as
  //         Data Cursors available in current environment are not suitable
  //         for scanning old Model versions

  Handle(ActData_BaseModel) aModelBase = Handle(ActData_BaseModel)::DownCast(theModel);

  // Get root Label of the source Node
  TDF_Label aRootLab;
  TDF_Tool::Label(aModelBase->Document()->GetData(), theNID, aRootLab, Standard_False);
  //
  if ( aRootLab.IsNull() )
    return Standard_False;

  // ...
  // Iterate over sub-Labels corresponding to USER section of the target
  // Node. Here we assume that Parameters from INTERNAL section are not
  // used in compatibility conversion carried out with help of this class.
  // Such presumption is justified as this tool is designed for
  // domain-specific compatibility conversion only
  // ...

  TDF_Label aUSectionLab = aRootLab.FindChild(ActData_BaseNode::TagUser, Standard_False);

  if ( aUSectionLab.IsNull() )
    return Standard_False;

  for ( TDF_ChildIterator lit(aUSectionLab); lit.More(); lit.Next() )
  {
    const TDF_Label aParamLab = lit.Value();

    // Now we can use Parameter Cursors as their format is immutable from
    // version to version

    Handle(ActAPI_IUserParameter) aParam = ActParamTool::NewParameterSettle(aParamLab);
    Handle(ActData_UserParameter) aParamBase = Handle(ActData_UserParameter)::DownCast(aParam);

    if ( aParamBase.IsNull() || !aParamBase->IsWellFormed() )
      return Standard_False; // FRAMEWORK data format changed?

    // Get data from Parameter in form of DTO
    Handle(ActData_ParameterDTO) aParamDTO = aParamBase->GetAsDTO();
    aConvNode->AddOrigin(aParamDTO);
  }

  // Register Node in Conversion Model
  m_nodeMap.Bind(theNID, aConvNode);
  return Standard_True;
}

//! Returns Conversion Node for the given ID.
//! \param theNID [in] ID of the Node to access.
//! \return requested Conversion Node or NULL if no such Node exists.
Handle(ActData_CAFConversionNode)
  ActData_CAFConversionModel::GetNode(const ActAPI_DataObjectId& theNID) const
{
  if ( !this->ContainsNode(theNID) )
    return NULL;

  return m_nodeMap.Find(theNID);
}

//! Cleans up the contents.
void ActData_CAFConversionModel::Clear()
{
  m_nodeMap.Clear();
  m_relocMap.Clear();
}

//! Builds relocation map corresponding to the actual state of conversion.
void ActData_CAFConversionModel::BuildRelocationMap()
{
  // Iterate over the Conversion Nodes
  for ( TNodeMap::Iterator mit(m_nodeMap); mit.More(); mit.Next() )
  {
    const Handle(ActData_CAFConversionNode)& CNode = mit.Value();
    ActAPI_DataObjectId NID = CNode->NID();

    // Iterate over the Conversion Parameters binding old GIDs to new GIDs
    for ( ActData_CAFConversionNode::Iterator nit(CNode); nit.More(); nit.Next() )
    {
      // Access Conversion Parameter with its associated data
      const Handle(ActData_CAFConversionParameter)& CParam = nit.Value();
      const ActData_CAFConversionParameter::History& CHistory = CParam->GetHistory();
      const Handle(ActData_ParameterDTO)& CData = CParam->GetData();

      // Get PIDs
      Standard_Integer OldPID = CHistory.OriginPID;
      Standard_Integer NewPID = CData->GID().PID;

      // Prepare GIDs
      ActAPI_ParameterGID OldGID(NID, OldPID), NewGID;
      if ( CHistory.Evolution != ActData_CAFConversionParameter::Evolution_Deleted )
      {
        NewGID.NID = NID;
        NewGID.PID = NewPID;
      }
      // Bind GIDs together into a single relocation map
      m_relocMap.Bind(OldGID, NewGID);
    }
  }
}

//! Returns new GID by old GID. If no new GID is recorded, returns the
//! passed old GID instead.
//! \param theOldGID [in] old GID to access new one for.
//! \return new GID.
ActAPI_ParameterGID
  ActData_CAFConversionModel::Converted(const ActAPI_ParameterGID& theOldGID) const
{
  if ( !m_relocMap.IsBound(theOldGID) )
    return theOldGID;

  return m_relocMap.Find(theOldGID);
}
