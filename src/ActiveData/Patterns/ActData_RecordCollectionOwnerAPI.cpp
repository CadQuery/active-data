//-----------------------------------------------------------------------------
// Created on: April 2014
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
#include <ActData_RecordCollectionOwnerAPI.h>

//! Appends the passed data to the end of the stored list of data records.
//! \param theRefPID [in] ID of the Reference List Parameter containing
//!        actual data.
//! \param theTarget [in] data to add.
void ActData_RecordCollectionOwnerAPI::AddRecord(const Standard_Integer theRefPID,
                                                 const Handle(ActAPI_INode)& theTarget)
{
  this->RecordSource()->ConnectReferenceToList( theRefPID, theTarget, this->NbRecords(theRefPID) );
}

//! Prepends the passed data to the beginning of the stored list of records.
//! \param theRefPID [in] ID of the Reference List Parameter containing
//!        actual data.
//! \param theTarget [in] data to prepend.
void ActData_RecordCollectionOwnerAPI::PrependRecord(const Standard_Integer theRefPID,
                                                     const Handle(ActAPI_INode)& theTarget)
{
  this->RecordSource()->ConnectReferenceToList(theRefPID, theTarget, 0);
}

//! Removes the data record referred to by the given index.
//! \param theRefPID [in] ID of the Reference List Parameter containing
//!        actual data.
//! \param theIndex [in] index of the data record in the internal collection.
//! \return true in case of success, false -- otherwise.
Standard_Boolean
  ActData_RecordCollectionOwnerAPI::RemoveRecord(const Standard_Integer theRefPID,
                                                 const Standard_Integer theIndex)
{
  return this->RecordSource()->DisconnectReferenceFromList(theRefPID, theIndex);
}

//! Inserts the given data after another item referred to by the passed index.
//! \param theRefPID [in] ID of the Reference List Parameter containing
//!        actual data.
//! \param theIndex [in] index of the data record to insert the new one after.
//! \param theTarget [in] data to insert.
void ActData_RecordCollectionOwnerAPI::InsertRecordAfter(const Standard_Integer theRefPID,
                                                         const Standard_Integer theIndex,
                                                         const Handle(ActAPI_INode)& theTarget)
{
  this->RecordSource()->ConnectReferenceToList(theRefPID, theTarget, theIndex);
}

//! Accessor for the data record referred to by the passed index.
//! \param theRefPID [in] ID of the Reference List Parameter containing
//!        actual data.
//! \param theIndex [in] index of the data record to access.
//! \return requested data.
Handle(ActAPI_INode)
  ActData_RecordCollectionOwnerAPI::GetRecord(const Standard_Integer theRefPID,
                                              const Standard_Integer theIndex) const
{
  Standard_Integer aNbRecords = this->NbRecords(theRefPID);

  if ( theIndex > aNbRecords || theIndex < 1 )
    return NULL;

  Handle(ActAPI_IDataCursor)
    aTargetDC = this->refsParam(theRefPID)->GetTarget(theIndex);

  return Handle(ActAPI_INode)::DownCast(aTargetDC);
}

//! Swap the records with the given indexes.
//! Does nothing if indexes are not valid.
//! \param theRefPID [in] ID of the Reference List Parameter containing
//!        actual data.
//! \param theFirstIndex [in] the index of the first record.
//! \param theSecondIndex [in] the index of the second record.
//! \return true in case of success, false -- otherwise.
Standard_Boolean ActData_RecordCollectionOwnerAPI::SwapRecords(const Standard_Integer theRefPID,
                                                               const Standard_Integer theFirstIndex,
                                                               const Standard_Integer theSecondIndex)
{
  Standard_Integer aNbRecords = this->NbRecords(theRefPID);

  // Indexes are valid?
  if ( theFirstIndex == theSecondIndex)
    return Standard_False;

  if ( theFirstIndex > aNbRecords || theFirstIndex < 1 )
    return Standard_False;

  if ( theSecondIndex > aNbRecords || theSecondIndex < 1 )
    return Standard_False;

  // Do swap on ReferenceListParameter
  return this->refsParam(theRefPID)->SwapTargets(theFirstIndex,theSecondIndex);
}

//! Returns the number of stored data records.
//! \param theRefPID [in] ID of the Reference List Parameter containing
//!        actual data.
//! \return number of data records.
Standard_Integer
  ActData_RecordCollectionOwnerAPI::NbRecords(const Standard_Integer theRefPID) const
{
  return this->refsParam(theRefPID)->NbTargets();
}

//! Checks whether the passed target is referenced by the Reference List
//! Parameter identified by the given ID.
//! \param theRefPID [in] ID of the Reference List Parameter to access.
//! \param theTarget [in] Data Cursor to check.
//! \return index of the target or 0 if nothing was found.
Standard_Integer 
  ActData_RecordCollectionOwnerAPI::HasTarget(const Standard_Integer theRefPID,
                                              const Handle(ActAPI_INode)& theTarget) const
{
  return this->refsParam(theRefPID)->HasTarget(theTarget);
}

//! Convenient accessor for the Reference List Parameter identified by
//! the given ID.
//! \param theRefPID [in] ID of the Reference List Parameter to access.
//! \return requested Parameter.
Handle(ActData_ReferenceListParameter)
  ActData_RecordCollectionOwnerAPI::refsParam(const Standard_Integer theRefPID) const
{
  return ActParamTool::AsReferenceList( this->RecordSource()->Parameter(theRefPID) );
}
