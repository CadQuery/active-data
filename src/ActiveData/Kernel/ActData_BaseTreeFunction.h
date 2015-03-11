//-----------------------------------------------------------------------------
// Created on: February 2012
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

#ifndef ActData_BaseTreeFunction_HeaderFile
#define ActData_BaseTreeFunction_HeaderFile

// Active Data includes
#include <ActData_Common.h>

// Active Data (API) includes
#include <ActAPI_IProgressNotifier.h>
#include <ActAPI_ITreeFunction.h>

// OCCT includes
#include <TFunction_Driver.hxx>
#include <TFunction_Logbook.hxx>

DEFINE_STANDARD_HANDLE(ActData_BaseTreeFunction, ActAPI_ITreeFunction)
DEFINE_STANDARD_HANDLE(ActData_TreeFunctionDriver, TFunction_Driver)

//! \ingroup AD_DF
//!
//! Base class for Tree Functions. Conceptually, Tree Function is a wrapper
//! under some algorithm allowing its execution against the dependency graph
//! defined by the user of Active Data.
class ActData_BaseTreeFunction : public ActAPI_ITreeFunction
{
friend class ActData_BaseModel;
friend class ActData_TreeFunctionDriver;

public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActData_BaseTreeFunction, ActAPI_ITreeFunction)

public:

  ActData_EXPORT virtual Standard_CString
    GetName() const;

  ActData_EXPORT virtual Standard_Integer
    Execute(const Handle(ActAPI_HParameterList)& theArgsIN,
            const Handle(ActAPI_HParameterList)& theArgsOUT) const;

  ActData_EXPORT virtual Standard_Boolean
    MustExecuteIntact(const Handle(ActAPI_HParameterList)& theArgsIN) const;

  ActData_EXPORT virtual Standard_Boolean
    NoPropagation() const;

  ActData_EXPORT virtual Standard_Integer
    Priority() const;

  ActData_EXPORT virtual void
    AutoConnect(const Handle(ActAPI_INode)& theOwnerNode) const;

public:

  //! Initializes shared user data.
  //! \param theUserData [in] user data container to set.
  inline void SetUserData(const Handle(Standard_Transient)& theUserData)
  {
    m_UserData = theUserData;
  }

  //! Accessor for the shared user data.
  //! \return requested container.
  inline const Handle(Standard_Transient)& GetUserData() const
  {
    return m_UserData;
  }

  //! Initializes shared Progress Notifier.
  //! \param thePCol [in] Progress Notifier instance to set.
  inline void SetProgressNotifier(const Handle(ActAPI_IProgressNotifier)& thePNotifier)
  {
    m_PEntry = thePNotifier;
  }

  //! Accessor for the shared Progress Notifier.
  //! \return requested Progress Notifier instance.
  inline Handle(ActAPI_IProgressNotifier) GetProgressNotifier() const
  {
    return m_PEntry.Access();
  }

  //! Returns Tree Function Driver.
  //! \return Function Driver.
  inline const Handle(ActData_TreeFunctionDriver)& GetDriver() const
  {
    return m_driver;
  }

protected:

  ActData_EXPORT
    ActData_BaseTreeFunction();

protected:

  ActData_EXPORT virtual Standard_Boolean
    validate(const Handle(ActAPI_HParameterList)& theArgsIN,
             const Handle(ActAPI_HParameterList)& theArgsOUT) const;

  ActData_EXPORT virtual Standard_Boolean
    validateInput(const Handle(ActAPI_HParameterList)& theArgsIN) const;

  ActData_EXPORT virtual Standard_Boolean
    validateOutput(const Handle(ActAPI_HParameterList)& theArgsOUT) const;

private:

  virtual Standard_Integer
    execute(const Handle(ActAPI_HParameterList)& theArgsIN,
            const Handle(ActAPI_HParameterList)& theArgsOUT,
            const Handle(Standard_Transient)& theUserData = NULL,
            ActAPI_ProgressEntry PEntry = NULL) const = 0;

  virtual ActAPI_ParameterTypeStream
    inputSignature() const = 0;

  virtual ActAPI_ParameterTypeStream
    outputSignature() const = 0;

protected:

  ActData_EXPORT Standard_Boolean
    validateBySignature(const Handle(ActAPI_HParameterList)& theArgs,
                        const ActAPI_ParameterTypeStream& theSignature) const;

  ActData_EXPORT Standard_Boolean
    hasUnrecoverableParameters(const Handle(ActAPI_HParameterList)& theArgsIN,
                               const Handle(ActAPI_HParameterList)& theArgsOUT,
                               const Standard_Integer theCheckType) const;

  ActData_EXPORT void
    propagateInvalid(const Handle(ActAPI_HParameterList)& theArgs) const;

  ActData_EXPORT void
    propagatePending(const Handle(ActAPI_HParameterList)& theArgs) const;

private:

  //! Internal OCCT TFunction Driver.
  Handle(ActData_TreeFunctionDriver) m_driver;

  //! Shared user data.
  Handle(Standard_Transient) m_UserData;

  //! Shared Progress Notifier.
  ActAPI_ProgressEntry m_PEntry;

};

//! \ingroup AD_DF
//!
//! Function Driver implementing necessary OCCT TFunction Driver mechanism
//! with respect to Active Data concepts. This class describes a kernel
//! object which is used by OCCT TFunction engine in order to build a
//! dependency graph. Besides that, this class provides an entry point to
//! execution routine which delegates the actual execution of the particular
//! algorithm to the domain-specific Tree Function.
class ActData_TreeFunctionDriver : public TFunction_Driver
{
friend class ActData_BaseModel;
friend class ActData_BaseTreeFunction;
friend class ActData_FuncExecutionCtx;

public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActData_TreeFunctionDriver, TFunction_Driver)

public:

  ActData_EXPORT ActData_TreeFunctionDriver();

  //! Accessor for the corresponding domain-specific Tree Function.
  //! \return the corresponding Tree Function.
  inline const Handle(ActAPI_ITreeFunction)& GetFunction() const
  {
    return m_func;
  }

private:

  ActData_EXPORT virtual Standard_Boolean
    MustExecute(const Handle(TFunction_Logbook)&) const;

  ActData_EXPORT virtual Standard_Integer
    Execute(Handle(TFunction_Logbook)&) const;

  ActData_EXPORT virtual void
    Arguments(TDF_LabelList& theArguments) const;

  ActData_EXPORT virtual void
    Results(TDF_LabelList& theResults) const;

private:

  Handle(ActAPI_HParameterList)
    parametersByLabels(const TDF_LabelList& theLabels) const;

  void
    initFunction(const Handle(ActAPI_ITreeFunction)& theFunc);

private:

  //! Domain-specific Tree Function associated with the TFunction Driver.
  Handle(ActAPI_ITreeFunction) m_func;

};

#endif
