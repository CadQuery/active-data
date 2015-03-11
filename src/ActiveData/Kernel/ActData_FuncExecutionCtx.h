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

#ifndef ActData_FuncExecutionCtx_HeaderFile
#define ActData_FuncExecutionCtx_HeaderFile

// Active Data includes
#include <ActData_Common.h>
#include <ActData_TreeFunctionParameter.h>

// Active Data (API) includes
#include <ActAPI_IProgressNotifier.h>
#include <ActAPI_TxData.h>

// OCCT includes
#include <NCollection_DataMap.hxx>
#include <NCollection_Handle.hxx>
#include <NCollection_Map.hxx>
#include <NCollection_List.hxx>
#include <TFunction_GraphNode.hxx>

// Active Data forward declarations
class ActData_BaseModel;
class ActData_TreeFunctionParameter;

DEFINE_STANDARD_HANDLE(ActData_FuncExecutionCtx, Standard_Transient)

//! \ingroup AD_DF
//!
//! Class representing execution context for Tree Function mechanism.
class ActData_FuncExecutionCtx : public Standard_Transient
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActData_FuncExecutionCtx, Standard_Transient)

public:

  //! Custom data associated with each function type. Tree Function concept
  //! presumes that the internal workflow uses input and output Parameters
  //! to perform a dedicated algorithm. It means that the arguments for the
  //! algorithm are always data chunks coming from data model. However, in
  //! many cases algorithm might need some service-layer stuff to proceed, e.g.
  //! progress indicators & collectors, etc. Such data is passed to
  //! Tree Functions by means of a specialized data map. Note that unlike
  //! input & output Parameters, this kind of data is always optional and
  //! exists in a single instance for each type of Tree Function.
  typedef NCollection_DataMap<Standard_GUID, Handle(Standard_Transient)> FunctionDataMap;
  typedef NCollection_Shared<FunctionDataMap>                            HFunctionDataMap;

// Construction:
public:

  ActData_EXPORT
    ActData_FuncExecutionCtx();

// User data:
public:

  ActData_EXPORT void
    BindUserData(const Standard_GUID& theFuncGUID,
                 const Handle(Standard_Transient)& theUserData);

  ActData_EXPORT void
    UnBindUserData(const Standard_GUID& theFuncGUID);

  ActData_EXPORT Handle(Standard_Transient)
    AccessUserData(const Standard_GUID& theFuncGUID);

  ActData_EXPORT void
    ReleaseUserData();

// Transaction data:
public:

  ActData_EXPORT void
    SetTxData(const ActAPI_TxData& theData);

  ActData_EXPORT const ActAPI_TxData&
    AccessTxData() const;

  ActData_EXPORT void
    ReleaseTxData();

// Managing dependency graph:
public:

  ActData_EXPORT static void
    UpdateDependencies(const Handle(ActData_BaseModel)& theModel);

  ActData_EXPORT static Standard_Integer
    CheckDependencyGraph(const Handle(ActData_BaseModel)& theModel);

  ActData_EXPORT static Standard_Integer
    CheckDependencyGraph(const Handle(ActData_BaseModel)& theModel,
                         Handle(ActAPI_HParameterList)& theFaultyParams);

// Progress notification:
public:

  ActData_EXPORT void
    SetProgressNotifier(const Handle(ActAPI_IProgressNotifier)& thePNotifier);

  ActData_EXPORT Handle(ActAPI_IProgressNotifier)
    ProgressNotifier() const;

  ActData_EXPORT Standard_Boolean
    IsProgressNotifierOn() const;

  ActData_EXPORT void
    ProgressNotifierOn();

  ActData_EXPORT void
    ProgressNotifierOff();

  ActData_EXPORT void
    FreezeGraph();

  ActData_EXPORT Standard_Boolean
    IsGraphFrozen() const;

  ActData_EXPORT void
    UnFreezeGraph();

// Forced execution:
public:

  ActData_EXPORT void
    Force(const Handle(ActData_TreeFunctionParameter)& theParam);

// Heavy deployment:
public:

  ActData_EXPORT void
    Deploy(const Handle(ActData_TreeFunctionParameter)& theParam);

// Services:
public:

  ActData_EXPORT void
    ForceDeployPropagation(const Handle(ActData_BaseModel)& theModel,
                           ActAPI_ProgressEntry PEntry);

public:

  //! Sets a collection of Tree Function Parameters requiring "heavy"
  //! execution.
  //! \param theRoots [in] list to set.
  inline void SetFunctions2Deploy(const Handle(ActAPI_HParameterList)& theRoots)
  {
    m_functions2Deploy = theRoots;
  }

  //! Cleans up the collection of Tree Function Parameters registered for
  //! "heavy" execution.
  inline void CleanFunctions2Deploy()
  {
    m_functions2Deploy.Nullify();
  }

// Transient data:
private:

  //! Data map of user-specific data associated with Tree Functions.
  Handle(HFunctionDataMap) m_funcDataMap;

  //! Global Progress Notifier for all Tree Functions.
  Handle(ActAPI_IProgressNotifier) m_PNotifier;

  //! Indicates whether Progress Notification is enabled or not.
  Standard_Boolean m_bProgressNotifierOn;

  //! Indicates whether Execution Graph is frozen or not.
  Standard_Boolean m_bIsGraphFrozen;

  //! Transaction user data.
  ActAPI_TxData m_txData;

  //! List of Tree Function Parameters to deploy for "heavy" execution.
  Handle(ActAPI_HParameterList) m_functions2Deploy;

};

#endif
