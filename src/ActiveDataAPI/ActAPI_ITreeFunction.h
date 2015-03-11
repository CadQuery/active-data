//-----------------------------------------------------------------------------
// Created on: March 2012
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

#ifndef ActAPI_ITreeFunction_HeaderFile
#define ActAPI_ITreeFunction_HeaderFile

// Active Data (API) includes
#include <ActAPI_IParameter.h>

// OCCT includes
#include <Standard_GUID.hxx>
#include <Standard_Type.hxx>

//! \ingroup AD_API
//!
//! Tree Function interface.
class ActAPI_ITreeFunction : public Standard_Transient
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActAPI_ITreeFunction, Standard_Transient)

public:

  ActAPI_EXPORT virtual ~ActAPI_ITreeFunction();

public:

  virtual Standard_Integer
    Execute(const Handle(ActAPI_HParameterList)& theArgsIN,
            const Handle(ActAPI_HParameterList)& theArgsOUT) const = 0;

  virtual Standard_CString
    GetGUID() const = 0; 

  virtual Standard_CString
    GetName() const = 0;

  virtual Standard_Boolean
    MustExecuteIntact(const Handle(ActAPI_HParameterList)& theArgsIN) const = 0;

  virtual Standard_Boolean
    IsHeavy() const = 0;

  virtual Standard_Integer
    Priority() const = 0;

};

//! Shortcuts for list of Tree Function GUIDs.
typedef NCollection_Sequence<Standard_GUID>     ActAPI_FuncGUIDList;
typedef NCollection_Shared<ActAPI_FuncGUIDList> ActAPI_HFuncGUIDList;

//-----------------------------------------------------------------------------
// Tree Function streaming
//-----------------------------------------------------------------------------

//! \ingroup AD_API
//!
//! Class providing a convenient way for assembling Tree Function GUIDs.
class ActAPI_FuncGUIDStream
{
public:

  Handle(ActAPI_HFuncGUIDList) List; //!< Actual list.

public:

  //! Default constructor.
  ActAPI_FuncGUIDStream::ActAPI_FuncGUIDStream()
  {
    List = new ActAPI_HFuncGUIDList();
  }

  //! Copy constructor. Performs SHALLOW copying.
  //! \param S [in] stream to copy.
  ActAPI_FuncGUIDStream::ActAPI_FuncGUIDStream(const ActAPI_FuncGUIDStream& S)
  {
    List = S.List;
  }

  //! Conversion operator.
  operator Handle(ActAPI_HFuncGUIDList)()
  {
    return List;
  }

  //! Pushes the passed GUID to the internal list.
  //! \param GUID [in] GUID to append to the internal list.
  //! \return this instance for further streaming.
  ActAPI_FuncGUIDStream& operator<<(const Standard_GUID& GUID)
  {
    List->Append(GUID);

    return *this;
  }
};

#endif
