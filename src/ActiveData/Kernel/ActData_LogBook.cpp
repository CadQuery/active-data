//-----------------------------------------------------------------------------
// Created on: June 2012
//-----------------------------------------------------------------------------
// Copyright (c) 2017, OPEN CASCADE SAS
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. All advertising materials mentioning features or use of this software
//    must display the following acknowledgement:
//    This product includes software developed by the OPEN CASCADE SAS.
// 4. Neither the name of the OPEN CASCADE SAS nor the
//    names of its contributors may be used to endorse or promote products
//    derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY OPEN CASCADE SAS ''AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL OPEN CASCADE SAS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Web: http://dev.opencascade.org
//-----------------------------------------------------------------------------

// Own include
#include <ActData_LogBook.h>

// Active Data includes
#include <ActData_BaseModel.h>
#include <ActData_ParameterFactory.h>
#include <ActData_Utils.h>

// OCCT includes
#include <TDF_ChildIterator.hxx>
#include <TDF_ListIteratorOfLabelList.hxx>
#include <TDF_Tool.hxx>

#undef COUT_DEBUG

//! Removes all occurrences of the passed Label from the given list.
//! \param theList [in] reference list to remove Label occurrences from.
//! \param theLabel [in] Label reference to remove.
static void RemoveAllOccurrences(const Handle(TDataStd_ReferenceList)& theList,
                                 const TDF_Label& theLabel)
{
  Standard_Boolean isDone;
  do
  {
    isDone = ( !theList.IsNull() && theList->Remove(theLabel) );
  }
  while ( isDone );
}

//-----------------------------------------------------------------------------
// Services
//-----------------------------------------------------------------------------

//! Checks whether the passed Data Cursor has TOUCHED or IMPACTED root Label.
//! \param theDC [in] Data Cursor to check.
//! \return true/false.
Standard_Boolean
  ActData_LogBook::IsModifiedCursor(const Handle(ActAPI_IDataCursor)& theDC)
{
  TDF_Label aLogBookSection =
    theDC->RootLabel().Root().FindChild(ActData_BaseModel::StructureTag_LogBook);

  ActData_LogBook LogBook(aLogBookSection);
  return LogBook.IsModified( theDC->RootLabel() );
}

//! Checks whether the passed Data Cursor is registered in HEAVY DEPLOYMENT
//! record.
//! \param theDC [in] Data Cursor to check.
//! \return true/false.
Standard_Boolean
  ActData_LogBook::IsPendingCursor(const Handle(ActAPI_IDataCursor)& theDC)
{
  TDF_Label aLogBookSection =
    theDC->RootLabel().Root().FindChild(ActData_BaseModel::StructureTag_LogBook);

  ActData_LogBook LogBook(aLogBookSection);
  return LogBook.IsHeavyDeployment( theDC->RootLabel() );
}

//-----------------------------------------------------------------------------
// Construction methods
//-----------------------------------------------------------------------------

//! Constructor accepting root Label of LogBook section.
//! \param theRootLab [in] root Label to set.
ActData_LogBook::ActData_LogBook(const TDF_Label& theRootLab)
{
  m_root = theRootLab;
}

//-----------------------------------------------------------------------------
// Common methods
//-----------------------------------------------------------------------------

//! Removes all references to the given Label from the LogBook.
//! \param theLab [in] Label to remove the references for.
void ActData_LogBook::ClearReferencesFor(const TDF_Label& theLab)
{
  TDF_Label aLogTScope = m_root.FindChild(StructureTag_Touched),
            aLogIScope = m_root.FindChild(StructureTag_Impacted),
            aLogFScope = m_root.FindChild(StructureTag_Forced),
            aLogHScope = m_root.FindChild(StructureTag_HeavyDeploy);

  Handle(TDataStd_ReferenceList) aRefTList = TDataStd_ReferenceList::Set(aLogTScope),
                                 aRefIList = TDataStd_ReferenceList::Set(aLogIScope),
                                 aRefFList = TDataStd_ReferenceList::Set(aLogFScope),
                                 aRefHList = TDataStd_ReferenceList::Set(aLogHScope);

#if defined COUT_DEBUG
  TCollection_AsciiString RefEntry;
  TDF_Tool::Entry(theLab, RefEntry);
  cout << "TO DELETE: " << RefEntry.ToCString() << endl;
  if ( !aRefTList.IsNull() )
  {
    cout << "----------------------------------"  << endl;
    cout << "---> TOUCHED: "                      << endl;
    const TDF_LabelList& aLabListT = aRefTList->List();
    for ( TDF_ListIteratorOfLabelList it(aLabListT); it.More(); it.Next() )
    {
      TCollection_AsciiString Entry;
      TDF_Tool::Entry(it.Value(), Entry);
      cout << "--->>> " << Entry.ToCString() << endl;
    }
  }
  if ( !aRefIList.IsNull() )
  {
    cout << "----------------------------------" << endl;
    cout << "---> IMPACTED: "                    << endl;
    const TDF_LabelList& aLabListI = aRefIList->List();
    for ( TDF_ListIteratorOfLabelList it(aLabListI); it.More(); it.Next() )
    {
      TCollection_AsciiString Entry;
      TDF_Tool::Entry(it.Value(), Entry);
      cout << "--->>> " << Entry.ToCString() << endl;
    }
  }
  if ( !aRefFList.IsNull() )
  {
    cout << "----------------------------------" << endl;
    cout << "---> FORCED: "                      << endl;
    const TDF_LabelList& aLabListF = aRefFList->List();
    for ( TDF_ListIteratorOfLabelList it(aLabListF); it.More(); it.Next() )
    {
      TCollection_AsciiString Entry;
      TDF_Tool::Entry(it.Value(), Entry);
      cout << "--->>> " << Entry.ToCString() << endl;
    }
  }
  if ( !aRefHList.IsNull() )
  {
    cout << "----------------------------------" << endl;
    cout << "---> HEAVY DEPLOYMENT: "            << endl;
    const TDF_LabelList& aLabListH = aRefHList->List();
    for ( TDF_ListIteratorOfLabelList it(aLabListH); it.More(); it.Next() )
    {
      TCollection_AsciiString Entry;
      TDF_Tool::Entry(it.Value(), Entry);
      cout << "--->>> " << Entry.ToCString() << endl;
    }
    cout << "----------------------------------" << endl;
  }
#endif

  this->clearReferences(theLab, StructureTag_Touched);
  this->clearReferences(theLab, StructureTag_Impacted);
  this->clearReferences(theLab, StructureTag_Forced);
  this->clearReferences(theLab, StructureTag_HeavyDeploy);
}

//-----------------------------------------------------------------------------
// MODIFIED records
//-----------------------------------------------------------------------------

//! Marks the passed CAF Label as TOUCHED.
//! \param theParam [in] Parameter to set TOUCHED.
void ActData_LogBook::Touch(const TDF_Label& theLab)
{
  this->addToReferenceList(theLab, StructureTag_Touched);
}

//! Marks the passed Data Parameter as TOUCHED.
//! \param theParam [in] Parameter to set TOUCHED.
void ActData_LogBook::Touch(const Handle(ActAPI_IUserParameter)& theParam)
{
  this->Touch( theParam->RootLabel() );
}

//! Checks whether the given Label is marked as TOUCHED or not.
//! \param theLab [in] CAF Label to check.
//! \return true/false.
Standard_Boolean
  ActData_LogBook::IsTouched(const TDF_Label& theLab) const
{
  return this->isReferenced(theLab, StructureTag_Touched);
}

//! Checks whether the given Parameter is marked as TOUCHED or not.
//! \param theParam [in] Nodal Parameter to check.
//! \return true/false.
Standard_Boolean
  ActData_LogBook::IsTouched(const Handle(ActAPI_IUserParameter)& theParam) const
{
  return this->IsTouched( theParam->RootLabel() );
}

//! Marks the passed CAF Label as IMPACTED.
//! \param theParam [in] Parameter to set IMPACTED.
void ActData_LogBook::Impact(const TDF_Label& theLab)
{
  this->addToReferenceList(theLab, StructureTag_Impacted);
}

//! Marks the passed Data Parameter as IMPACTED.
//! \param theParam [in] Parameter to set IMPACTED.
void ActData_LogBook::Impact(const Handle(ActAPI_IUserParameter)& theParam)
{
  this->Impact( theParam->RootLabel() );
}

//! Checks whether the given Label is marked as IMPACTED or not.
//! \param theLab [in] CAF Label to check.
//! \return true/false.
Standard_Boolean
  ActData_LogBook::IsImpacted(const TDF_Label& theLab) const
{
  return this->isReferenced(theLab, StructureTag_Impacted);
}

//! Checks whether the given Parameter is marked as IMPACTED or not.
//! \param theParam [in] Nodal Parameter to check.
//! \return true/false.
Standard_Boolean
  ActData_LogBook::IsImpacted(const Handle(ActAPI_IUserParameter)& theParam) const
{
  return this->IsImpacted( theParam->RootLabel() );
}

//! Checks whether the given Label is marked as TOUCHED or IMPACTED.
//! \param theLab [in] CAF Label to check.
//! \return true/false.
Standard_Boolean
  ActData_LogBook::IsModified(const TDF_Label& theLab) const
{
  return this->IsTouched(theLab) || this->IsImpacted(theLab);
}

//! Checks whether the given Parameter is marked as TOUCHED or IMPACTED.
//! \param theParam [in] Nodal Parameter to check.
//! \return true/false.
Standard_Boolean
  ActData_LogBook::IsModified(const Handle(ActAPI_IUserParameter)& theParam) const
{
  return this->IsTouched(theParam) || this->IsImpacted(theParam);
}

//! Cleans up the collection of Labels marked as TOUCHED or IMPACTED.
void ActData_LogBook::ReleaseModified()
{
  this->clearReferences(StructureTag_Touched);
  this->clearReferences(StructureTag_Impacted);
}

//-----------------------------------------------------------------------------
// Forced execution support
//-----------------------------------------------------------------------------

//! Marks the passed Tree Function Parameter as requesting FORCED execution.
//! Such items normally participate in the graph execution flow regardless
//! of whether some data is actually modified or not.
//! \param theParam [in] Parameter requesting forced execution.
void ActData_LogBook::Force(const Handle(ActData_TreeFunctionParameter)& theFuncParam)
{
  this->addToReferenceList(theFuncParam->RootLabel(), StructureTag_Forced);
}

//! Checks whether the passed CAF Label is marked as requesting
//! forced execution.
//! \param theLab [in] Label to check.
//! \return true/false.
Standard_Boolean
  ActData_LogBook::IsForced(const TDF_Label& theLab) const
{
  return this->isReferenced(theLab, StructureTag_Forced);
}

//! Checks whether the passed Nodal Parameter is marked as requesting
//! forced execution.
//! \param theParam [in] Parameter to check.
//! \return true/false.
Standard_Boolean
  ActData_LogBook::IsForced(const Handle(ActAPI_IUserParameter)& theParam) const
{
  return this->IsForced( theParam->RootLabel() );
}

//! Cleans up the collection of items requesting forced execution.
void ActData_LogBook::ReleaseForced()
{
  this->clearReferences(StructureTag_Forced);
}

//-----------------------------------------------------------------------------
// Heavy deployment
//-----------------------------------------------------------------------------

//! Puts HEAVY DEPLOYMENT record for the passed Tree Function Parameter.
//! \param theParam [in] Tree Function Parameter.
void ActData_LogBook::HeavyDeploy(const Handle(ActData_TreeFunctionParameter)& theFuncParam)
{
  this->addToReferenceList(theFuncParam->RootLabel(), StructureTag_HeavyDeploy);
}

//! Checks whether the passed OCAF Label is referenced in HEAVY DEPLOYMENT
//! section.
//! \param theLab [in] Label to check.
//! \return true/false.
Standard_Boolean
  ActData_LogBook::IsHeavyDeployment(const TDF_Label& theLab) const
{
  return this->isReferenced(theLab, StructureTag_HeavyDeploy);
}

//! Checks whether the passed Tree Function Parameter is referenced in
//! HEAVY DEPLOYMENT section.
//! \param theParam [in] Tree Function Parameter to check.
//! \return true/false.
Standard_Boolean ActData_LogBook::IsHeavyDeployment(const Handle(ActAPI_IUserParameter)& theParam) const
{
  return this->IsHeavyDeployment( theParam->RootLabel() );
}

//! Cleans up HEAVY DEPLOYMENT section.
void ActData_LogBook::ReleaseHeavyDeployment()
{
  this->clearReferences(StructureTag_HeavyDeploy);
}

//-----------------------------------------------------------------------------
// Internals
//-----------------------------------------------------------------------------

//! Establishes a reference to the given CAF Label in a logging sub-section
//! defined by the second argument.
//! \param theLab [in] CAF Label to register.
//! \param theTag [in] tag determining the LogBook's destination scope.
void ActData_LogBook::addToReferenceList(const TDF_Label& theLab,
                                         const StructureTags theTag)
{
  TDF_Label aLogScope = m_root.FindChild(theTag);
  Handle(TDataStd_ReferenceList) aRefList = TDataStd_ReferenceList::Set(aLogScope);
  aRefList->Append(theLab);
}

//! Establishes a reference to the given Parameter in a logging sub-section
//! defined by the second argument.
//! \param theParam [in] Parameter to register.
//! \param theTag [in] tag determining the LogBook's destination scope.
void ActData_LogBook::addToReferenceList(const Handle(ActAPI_IUserParameter)& theParam,
                                         const StructureTags theTag)
{
  this->addToReferenceList( theParam->RootLabel(), theTag);
}

//! Checks whether the given Label is registered in the LogBook's section
//! defined by the second argument.
//! \param theLab [in] CAF Label to check.
//! \param theTag [in] tag determining the LogBook's destination scope.
//! \return true if the Label being tested is referenced by the LogBook.
Standard_Boolean ActData_LogBook::isReferenced(const TDF_Label& theLab,
                                               const StructureTags theTag) const
{
  TDF_Label aLogScope = m_root.FindChild(theTag);
  Handle(TDataStd_ReferenceList) aRefList = TDataStd_ReferenceList::Set(aLogScope);
  for ( TDF_ListIteratorOfLabelList it( aRefList->List() ); it.More(); it.Next() )
  {
    if ( theLab.IsEqual( it.Value() ) )
      return Standard_True;
  }

  return Standard_False;
}

//! Checks whether the given Parameter is registered in the LogBook's section
//! defined by the second argument.
//! \param theParam [in] Nodal Parameter to check.
//! \param theTag [in] tag determining the LogBook's destination scope.
Standard_Boolean ActData_LogBook::isReferenced(const Handle(ActAPI_IUserParameter)& theParam,
                                               const StructureTags theTag) const
{
  return this->isReferenced(theParam->RootLabel(), theTag);
}

//! Cleans up all references in the given section of the LogBook.
//! \param theTag [in] tag determining the LogBook's destination scope.
void ActData_LogBook::clearReferences(const StructureTags theTag)
{
  TDF_Label aLogScope = m_root.FindChild(theTag);
  Handle(TDataStd_ReferenceList) aRefList = TDataStd_ReferenceList::Set(aLogScope);
  aRefList->Clear();
}

//! Cleans up all references of the given Label in the given section of
//! the LogBook.
//! \param theLabel [in] Label to remove references for. All child Labels
//!        are also involved.
//! \param theTag [in] tag determining the LogBook's destination scope.
void ActData_LogBook::clearReferences(const TDF_Label& theLabel,
                                      const StructureTags theTag)
{
  TDF_Label aLogScope = m_root.FindChild(theTag);
  Handle(TDataStd_ReferenceList) aRefList = TDataStd_ReferenceList::Set(aLogScope);

  RemoveAllOccurrences(aRefList, theLabel);
  for ( TDF_ChildIterator it(theLabel, Standard_True); it.More(); it.Next() )
    RemoveAllOccurrences( aRefList, it.Value() );
}
