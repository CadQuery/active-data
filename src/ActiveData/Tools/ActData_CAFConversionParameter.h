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

#ifndef ActData_CAFConversionParameter_HeaderFile
#define ActData_CAFConversionParameter_HeaderFile

// Active Data includes
#include <ActData_Common.h>
#include <ActData_ParameterDTO.h>

DEFINE_STANDARD_HANDLE(ActData_CAFConversionParameter, Standard_Transient)

//! \ingroup AD_DF
//!
//! Element of Conversion Node.
class ActData_CAFConversionParameter : public Standard_Transient
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActData_CAFConversionParameter, Standard_Transient)

public:

  static const Standard_Integer TempPID = -1; //!< Temporary PID.

  //! Evolution mark.
  enum EvolutionType
  {
    Evolution_None    = 0x00001, //!< Not affected.
    Evolution_Updated = 0x00002, //!< Data updated.
    Evolution_New     = 0x00004, //!< New Parameter.
    Evolution_Deleted = 0x00008, //!< Removed Parameter.
    Evolution_Moved   = 0x00010  //!< Parameter moved as a whole.
  };

  //! Conversion history associated with Parameter.
  struct History
  {
    Standard_Integer Evolution; //!< Evolution.
    Standard_Integer OriginPID; //!< Original PID.

    //! Constructor.
    //! \param theOriginPID [in] original PID to set.
    //! \param theEvolution [in] evolution mark.
    History(const Standard_Integer theOriginPID,
            const EvolutionType theEvolution = Evolution_None) : OriginPID(theOriginPID),
                                                                 Evolution(theEvolution) {}
  };

public:

  ActData_EXPORT
    ActData_CAFConversionParameter(const Handle(ActData_ParameterDTO)& theDTO,
                                   const Standard_Integer theOriginPID = -1);

public:

  //! Accessor for the underlying data.
  //! \return underlying Parameter DTO.
  inline const Handle(ActData_ParameterDTO)& GetData() const
  {
    return m_data;
  }

  //! Accessor for the underlying data.
  //! \return underlying Parameter DTO.
  inline Handle(ActData_ParameterDTO)& ChangeData()
  {
    return m_data;
  }

  //! Accessor for history.
  //! \return convertion history associated with this Parameter.
  inline const History& GetHistory() const
  {
    return m_history;
  }

  //! Accessor for history.
  //! \return convertion history associated with this Parameter.
  inline History& ChangeHistory()
  {
    return m_history;
  }

private:

  //! Actual data in form of Parameter DTO.
  Handle(ActData_ParameterDTO) m_data;

  //! Conversion history.
  History m_history;

};

#endif
