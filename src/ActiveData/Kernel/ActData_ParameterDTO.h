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

#ifndef ActData_ParameterDTO_HeaderFile
#define ActData_ParameterDTO_HeaderFile

// Active Data includes
#include <ActData_Common.h>

// Active Data (API) includes
#include <ActAPI_IParameter.h>

DEFINE_STANDARD_HANDLE(ActData_ParameterDTO, Standard_Transient)

//! Data Transfer Object for Nodal Parameter. Unlike Parameter class itself,
//! this one is designed for usage in OCAF-disconnected state.
class ActData_ParameterDTO : public Standard_Transient
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActData_ParameterDTO, Standard_Transient)

public:

  //! Accessor for Parameter's GID.
  //! \return Parameter's GID.
  inline const ActAPI_ParameterGID& GID() const
  {
    return m_GID;
  }

  //! Accessor for Parameter's GID.
  //! \return Parameter's GID.
  inline ActAPI_ParameterGID& ChangeGID()
  {
    return m_GID;
  }

  //! Accessor for Parameter type.
  //! \return Parameter type.
  inline ActAPI_ParameterType ParamType() const
  {
    return m_type;
  }

  //! Accessor for name.
  //! \return name.
  inline const TCollection_ExtendedString& Name() const
  {
    return m_name;
  }

  //! Accessor for name.
  //! \return name.
  inline TCollection_ExtendedString& ChangeName()
  {
    return m_name;
  }

  //! Accessor for semantic ID.
  //! \return semantic ID.
  inline const TCollection_AsciiString& SID() const
  {
    return m_SID;
  }

  //! Accessor for semantic ID.
  //! \return semantic ID.
  inline TCollection_AsciiString& ChangeSID()
  {
    return m_SID;
  }

  //! Accessor for evaluation string.
  //! \return evaluation string.
  inline const TCollection_AsciiString& EvalStr() const
  {
    return m_evalStr;
  }

  //! Accessor for evaluation string.
  //! \return evaluation string.
  inline TCollection_AsciiString& ChangeEvalStr()
  {
    return m_evalStr;
  }

  //! Accessor for validity flag.
  //! \return validity flag.
  inline Standard_Boolean IsValid() const
  {
    return m_bIsValid;
  }

  //! Accessor for validity flag.
  //! \return validity flag.
  inline Standard_Boolean& ChangeIsValid()
  {
    return m_bIsValid;
  }

  //! Accessor for user flags.
  //! \return user flags.
  inline Standard_Integer UFlags() const
  {
    return m_iUFlags;
  }

  //! Accessor for user flags.
  //! \return user flags.
  inline Standard_Integer& ChangeUFlags()
  {
    return m_iUFlags;
  }

  //! Accessor for pending flag.
  //! \return pending flag.
  inline Standard_Boolean IsPending() const
  {
    return m_bIsPending;
  }

  //! Accessor for pending flag.
  //! \return pending flag.
  inline Standard_Boolean& ChangeIsPending()
  {
    return m_bIsPending;
  }

public:

  ActData_EXPORT
    ActData_ParameterDTO(const ActAPI_ParameterGID& theGID,
                         const ActAPI_ParameterType theParamType);

  ActData_EXPORT
    ActData_ParameterDTO(const ActAPI_ParameterGID& theGID,
                         const ActAPI_ParameterType theParamType,
                         const TCollection_ExtendedString& theName);

  ActData_EXPORT
    ActData_ParameterDTO(const ActAPI_ParameterGID& theGID,
                         const ActAPI_ParameterType theParamType,
                         const TCollection_AsciiString& theSID);

  ActData_EXPORT
    ActData_ParameterDTO(const ActAPI_ParameterGID& theGID,
                         const ActAPI_ParameterType theParamType,
                         const TCollection_ExtendedString& theName,
                         const TCollection_AsciiString& theSID);

  ActData_EXPORT
    ActData_ParameterDTO(const ActAPI_ParameterGID& theGID,
                         const ActAPI_ParameterType theParamType,
                         const TCollection_ExtendedString& theName,
                         const TCollection_AsciiString& theSID,
                         const TCollection_AsciiString& theEvalStr);

  ActData_EXPORT
    ActData_ParameterDTO(const ActAPI_ParameterGID& theGID,
                         const ActAPI_ParameterType theParamType,
                         const Standard_Integer theUFlags);

  ActData_EXPORT
    ActData_ParameterDTO(const ActAPI_ParameterGID& theGID,
                         const ActAPI_ParameterType theParamType,
                         const TCollection_ExtendedString& theName,
                         const TCollection_AsciiString& theSID,
                         const TCollection_AsciiString& theEvalStr,
                         const Standard_Integer theUFlags);

  ActData_EXPORT void
    Init(const ActAPI_ParameterGID&        theGID,
         const ActAPI_ParameterType        theParamType,
         const TCollection_ExtendedString& theName,
         const TCollection_AsciiString&    theSID,
         const TCollection_AsciiString&    theEvalStr,
         const Standard_Boolean            isValid,
         const Standard_Integer            theUFlags,
         const Standard_Boolean            isPending);

public:

  //! Hasher tool for data maps.
  struct Hasher
  {
    //! Returns hash code for the given Parameter DTO.
    //! \param theParamDTO [in] Parameter DTO to calculate hash code for.
    //! \param theNbBuckets [in] number of buckets.
    //! \return calculated hash code.
    static Standard_Integer HashCode(const Handle(ActData_ParameterDTO)& theParamDTO,
                                     const Standard_Integer              theNbBuckets = 100)
    {
      return ActAPI_ParameterGID::Hasher::HashCode(theParamDTO->GID(), theNbBuckets);
    }

    //! Checks whether two Parameter DTO instances are the same.
    //! \param theParamDTO1 [in] first Parameter DTO.
    //! \param theParamDTO2 [in] second Parameter DTO.
    //! \return true in case of equality, false -- otherwise.
    static Standard_Boolean IsEqual(const Handle(ActData_ParameterDTO)& theParamDTO1,
                                    const Handle(ActData_ParameterDTO)& theParamDTO2)
    {
      return ActAPI_ParameterGID::Hasher::IsEqual( theParamDTO1->GID(),
                                                   theParamDTO2->GID() );
    }
  };

protected:

  ActAPI_ParameterGID        m_GID;        //!< Parameter's global ID.
  ActAPI_ParameterType       m_type;       //!< Parameter's type.
  TCollection_ExtendedString m_name;       //!< Parameter's name.
  TCollection_AsciiString    m_SID;        //!< Semantic key.
  TCollection_AsciiString    m_evalStr;    //!< Evaluation string.
  Standard_Boolean           m_bIsValid;   //!< Validity flag.
  Standard_Integer           m_iUFlags;    //!< User flags.
  Standard_Boolean           m_bIsPending; //!< Pending flag.

};

#endif
