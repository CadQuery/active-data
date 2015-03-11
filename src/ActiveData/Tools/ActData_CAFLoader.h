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

#ifndef ActData_CAFLoader_HeaderFile
#define ActData_CAFLoader_HeaderFile

// Active Data includes
#include <ActData_BaseModel.h>

// OCCT includes
#include <Message_ProgressIndicator.hxx>

DEFINE_STANDARD_HANDLE(ActData_CAFLoader, Standard_Transient)

//! \ingroup AD_DF
//!
//! Loader class for Data Model instances. This class enriches default
//! loading functionality with compatibility conversion mechanism.
class ActData_CAFLoader : public Standard_Transient
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActData_CAFLoader, Standard_Transient)

public:

  ActData_EXPORT static Standard_Boolean
    LoadAndConvert(const TCollection_AsciiString& theFilename,
                   Handle(ActAPI_IModel)& theModel);

  ActData_EXPORT static Standard_Boolean
    LoadWithVersions(const TCollection_AsciiString& theFilename,
                     Handle(ActAPI_IModel)& theModel,
                     Standard_Integer& theFwVerStored,
                     Standard_Integer& theAppVerStored,
                     Standard_Integer& theFwVerActual,
                     Standard_Integer& theAppVerActual);

  ActData_EXPORT static Standard_Boolean
    Convert(Handle(ActAPI_IModel)& theModel,
            const Standard_Integer theFwVerStored,
            const Standard_Integer theAppVerStored,
            const Standard_Integer theFwVerActual,
            const Standard_Integer theAppVerActual,
            const TCollection_AsciiString& theFnBefore = TCollection_AsciiString(),
            const TCollection_AsciiString& theFnAfter = TCollection_AsciiString(),
            const Handle(Message_ProgressIndicator)& theProgress = NULL);

  ActData_EXPORT static Standard_Boolean
    CheckWellFormed(const Handle(ActAPI_IModel)& theModel);

public:

  ActData_EXPORT
    ActData_CAFLoader(const Handle(ActAPI_IModel)& theModel);

public:

  ActData_EXPORT Standard_Boolean
    Load(const TCollection_AsciiString& theFilename);

  ActData_EXPORT Standard_Boolean
    NeedsConversion() const;

  ActData_EXPORT Standard_Boolean
    Convert(const TCollection_AsciiString& theFnBefore = TCollection_AsciiString(),
            const TCollection_AsciiString& theFnAfter = TCollection_AsciiString(),
            const Handle(Message_ProgressIndicator)& theProgress = NULL);

  ActData_EXPORT Standard_Boolean
    CheckWellFormed() const;

public:

  //! Returns converted Data Model.
  //! \return converted Data Model instance.
  inline const Handle(ActAPI_IModel)& ModifiedModel() const
  {
    return m_model;
  }

  //! Returns stored version of Framework.
  //! \return requested version string.
  inline TCollection_AsciiString FwStoredVersion() const
  {
    return versionToString(m_fwVerStored);
  }

  //! Returns actual version of Framework.
  //! \return requested version string.
  inline TCollection_AsciiString FwActualVersion() const
  {
    return versionToString(m_fwVerActual);
  }

  //! Returns stored version of Application.
  //! \return requested version string.
  inline TCollection_AsciiString AppStoredVersion() const
  {
    return versionToString(m_appVerStored);
  }

  //! Returns actual version of Application.
  //! \return requested version string.
  inline TCollection_AsciiString AppActualVersion() const
  {
    return versionToString(m_appVerActual);
  }

  //! Returns filename of the currently loaded Data Model.
  //! \return requested filename.
  inline const TCollection_AsciiString& Filename() const
  {
    return m_filename;
  }

private:

  ActData_EXPORT TCollection_AsciiString
    versionToString(const Standard_Integer theVerNum) const;

private:

  ActData_CAFLoader() {}

private:

  //! Loaded and optionally converted Data Model.
  Handle(ActAPI_IModel) m_model;

  //! Loaded version of Framework.
  Standard_Integer m_fwVerStored;

  //! Loaded version of Application.
  Standard_Integer m_appVerStored;

  //! Actual version of Framework.
  Standard_Integer m_fwVerActual;

  //! Actual version of Application.
  Standard_Integer m_appVerActual;

  //! Filename of the currently loaded Data Model.
  TCollection_AsciiString m_filename;

};

#endif
