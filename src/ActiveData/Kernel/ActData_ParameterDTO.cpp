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

#include <ActData_ParameterDTO.h>

#define NIL ""

//! Constructor.
//! \param theGID [in] global ID of the Parameter.
//! \param theParamType [in] Parameter type.
ActData_ParameterDTO::ActData_ParameterDTO(const ActAPI_ParameterGID& theGID,
                                           const ActAPI_ParameterType theParamType)
: Standard_Transient()
{
  this->Init(theGID, theParamType,
             NIL, NIL, NIL,
             Standard_True, 0, Standard_False);
}

//! Constructor.
//! \param theGID [in] global ID of the Parameter.
//! \param theParamType [in] Parameter type.
//! \param theName [in] name.
ActData_ParameterDTO::ActData_ParameterDTO(const ActAPI_ParameterGID& theGID,
                                           const ActAPI_ParameterType theParamType,
                                           const TCollection_ExtendedString& theName)
: Standard_Transient()
{
  this->Init(theGID, theParamType,
             theName, NIL, NIL,
             Standard_True, 0, Standard_False);
}

//! Constructor.
//! \param theGID [in] global ID of the Parameter.
//! \param theParamType [in] Parameter type.
//! \param theSID [in] semantic ID.
ActData_ParameterDTO::ActData_ParameterDTO(const ActAPI_ParameterGID& theGID,
                                           const ActAPI_ParameterType theParamType,
                                           const TCollection_AsciiString& theSID)
: Standard_Transient()
{
  this->Init(theGID, theParamType,
             NIL, theSID, NIL,
             Standard_True, 0, Standard_False);
}

//! Constructor.
//! \param theGID [in] global ID of the Parameter.
//! \param theParamType [in] Parameter type.
//! \param theName [in] name.
//! \param theSID [in] semantic ID.
ActData_ParameterDTO::ActData_ParameterDTO(const ActAPI_ParameterGID& theGID,
                                           const ActAPI_ParameterType theParamType,
                                           const TCollection_ExtendedString& theName,
                                           const TCollection_AsciiString& theSID)
: Standard_Transient()
{
  this->Init(theGID, theParamType,
             theName, theSID, NIL,
             Standard_True, 0, Standard_False);
}

//! Constructor.
//! \param theGID [in] global ID of the Parameter.
//! \param theParamType [in] Parameter type.
//! \param theName [in] name.
//! \param theSID [in] semantic ID.
//! \param theEvalStr [in] evaluation string.
ActData_ParameterDTO::ActData_ParameterDTO(const ActAPI_ParameterGID& theGID,
                                           const ActAPI_ParameterType theParamType,
                                           const TCollection_ExtendedString& theName,
                                           const TCollection_AsciiString& theSID,
                                           const TCollection_AsciiString& theEvalStr)
: Standard_Transient()
{
  this->Init(theGID, theParamType,
             theName, theSID, theEvalStr,
             Standard_True, 0, Standard_False);
}

//! Constructor.
//! \param theGID [in] global ID of the Parameter.
//! \param theParamType [in] Parameter type.
//! \param theUFlags [in] user flags.
ActData_ParameterDTO::ActData_ParameterDTO(const ActAPI_ParameterGID& theGID,
                                           const ActAPI_ParameterType theParamType,
                                           const Standard_Integer theUFlags)
: Standard_Transient()
{
  this->Init(theGID, theParamType,
             NIL, NIL, NIL,
             Standard_True, theUFlags, Standard_False);
}

//! Constructor.
//! \param theGID [in] global ID of the Parameter.
//! \param theParamType [in] Parameter type.
//! \param theName [in] name.
//! \param theSID [in] semantic ID.
//! \param theEvalStr [in] evaluation string.
//! \param theUFlags [in] user flags.
ActData_ParameterDTO::ActData_ParameterDTO(const ActAPI_ParameterGID& theGID,
                                           const ActAPI_ParameterType theParamType,
                                           const TCollection_ExtendedString& theName,
                                           const TCollection_AsciiString& theSID,
                                           const TCollection_AsciiString& theEvalStr,
                                           const Standard_Integer theUFlags)
: Standard_Transient()
{
  this->Init(theGID, theParamType,
             theName, theSID, theEvalStr,
             Standard_True, theUFlags, Standard_False);
}

//! Initialization routine.
//! \param theGID [in] global ID of the Parameter.
//! \param theParamType [in] Parameter type.
//! \param theName [in] name.
//! \param theSID [in] semantic ID.
//! \param theEvalStr [in] evaluation string.
//! \param isValid [in] validity flag.
//! \param theUFlags [in] user flags.
//! \param isPending [in] pending flag.
void ActData_ParameterDTO::Init(const ActAPI_ParameterGID& theGID,
                                const ActAPI_ParameterType theParamType,
                                const TCollection_ExtendedString& theName,
                                const TCollection_AsciiString& theSID,
                                const TCollection_AsciiString& theEvalStr,
                                const Standard_Boolean isValid,
                                const Standard_Integer theUFlags,
                                const Standard_Boolean isPending)
{
  m_GID        = theGID;
  m_type       = theParamType;
  m_name       = theName;
  m_SID        = theSID;
  m_evalStr    = theEvalStr;
  m_bIsValid   = isValid;
  m_iUFlags    = theUFlags;
  m_bIsPending = isPending;
}
