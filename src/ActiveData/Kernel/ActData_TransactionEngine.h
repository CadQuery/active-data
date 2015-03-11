//-----------------------------------------------------------------------------
// Created on: July 2012
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

#ifndef ActData_TransactionEngine_HeaderFile
#define ActData_TransactionEngine_HeaderFile

// Active Data includes
#include <ActData_Common.h>

// OCCT includes
#include <TDocStd_Document.hxx>

#define DEFAULT_UNDO_LIMIT 100

DEFINE_STANDARD_HANDLE(ActData_TransactionEngine, Standard_Transient)

//! \ingroup AD_DF
//!
//! Base class for auxiliary Data Model co-worker tool providing a set of
//! services for deployment and management of CAF transactional scopes. Think
//! of Transaction Engine as a wrapper under the standard OCAF transaction
//! mechanism plus additional services which can be provided by the descendant
//! classes.
//!
//! From the very general point of view, Transaction Engine is normally
//! utilized by the Data Model architectural facade in order to channel all
//! transactional stuff into one dedicated place for customization.
class ActData_TransactionEngine : public Standard_Transient
{
friend class ActData_BaseModel;

public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActData_TransactionEngine, Standard_Transient)

// Common functionality:
public:

  ActData_EXPORT
    ActData_TransactionEngine(const Handle(TDocStd_Document)& theDoc,
                              const Standard_Integer UndoLimit = DEFAULT_UNDO_LIMIT);

  ActData_EXPORT virtual void
    Release();

// Kernel functionality:
public:

  ActData_EXPORT virtual void
    DisableTransactions();

  ActData_EXPORT virtual void
    EnableTransactions();

  ActData_EXPORT virtual void
    OpenCommand();

  ActData_EXPORT virtual void
    CommitCommand();

  ActData_EXPORT virtual Standard_Boolean
    HasOpenCommand() const;

  ActData_EXPORT virtual void
    AbortCommand();

  ActData_EXPORT virtual void
    Undo(const Standard_Integer theNbUndoes = 1);

  ActData_EXPORT virtual Standard_Integer
    NbUndos() const;

  ActData_EXPORT virtual void
    Redo(const Standard_Integer theNbRedoes = 1);

  ActData_EXPORT virtual Standard_Integer
    NbRedos() const;

// Construction & initialization is hidden:
protected:

  void
    init(const Handle(TDocStd_Document)& Doc);

private:

  Handle(ActAPI_HParameterMap)
    parametersToUndo(const Standard_Integer theNbUndoes) const;

  Handle(ActAPI_HParameterMap)
    parametersToRedo(const Standard_Integer theNbRedoes) const;

  void
    touchParameters(const Handle(ActAPI_HParameterMap)& theParams);

  void
    addParametersByDelta(const Handle(TDF_Delta)& theDelta,
                         Handle(ActAPI_HParameterMap)& theMap) const;

  Standard_Boolean
    isTransactionModeOn() const;

  Standard_Boolean
    isTransactionModeOff() const;

protected:

  //! Undo Limit.
  Standard_Integer m_iUndoLimit;

  //! CAF Document instance.
  Handle(TDocStd_Document) m_doc;

  //! Indicates whether some transaction is currently active.
  Standard_Boolean m_bIsActiveTransaction;

};

#endif
