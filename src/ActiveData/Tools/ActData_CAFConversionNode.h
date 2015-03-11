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

#ifndef ActData_CAFConversionNode_HeaderFile
#define ActData_CAFConversionNode_HeaderFile

// Active Data includes
#include <ActData_CAFConversionParameter.h>

DEFINE_STANDARD_HANDLE(ActData_CAFConversionNode, Standard_Transient)

//! \ingroup AD_DF
//!
//! Element of Conversion Model representing conversion data in scope
//! of a single Data Node.
class ActData_CAFConversionNode : public Standard_Transient
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActData_CAFConversionNode, Standard_Transient)

public:

  //! Iterator for Sampler.
  class Iterator
  {
  public:

    //! Default constructor.
    Iterator()
    {
    }

    //! Complete constructor.
    //! \param theModel [in] Conversion Node to iterate over.
    Iterator(const Handle(ActData_CAFConversionNode)& theNode)
    {
      this->Init(theNode);
    }

    //! Initializes iterator.
    //! \param theModel [in] Conversion Node to iterate over.
    void Init(const Handle(ActData_CAFConversionNode)& theNode)
    {
      m_iter.Init(theNode->m_params);
    }

    //! Returns true if there is something to iterate still.
    //! \return true/false.
    Standard_Boolean More() const
    {
      return m_iter.More();
    }

    //! Mover iteration pointer to the next item.
    void Next()
    {
      m_iter.Next();
    }

    //! Returns currently iterated value.
    //! \return current value.
    const Handle(ActData_CAFConversionParameter)& Value() const
    {
      return m_iter.Value();
    }

  private:

    //! Internal iterator.
    NCollection_Sequence<Handle(ActData_CAFConversionParameter)>::Iterator m_iter;

  };

public:

  ActData_EXPORT
    ActData_CAFConversionNode();

public:

  ActData_EXPORT void
    AddOrigin(const Handle(ActData_ParameterDTO)& theDTO);

  ActData_EXPORT ActAPI_DataObjectId
    NID() const;

  ActData_EXPORT Handle(ActData_CAFConversionParameter)
    ParamByOrigin(const Standard_Integer theOriPID) const;

  ActData_EXPORT Standard_Boolean
    Insert(const Handle(ActData_ParameterDTO)& theDTO,
           const ActAPI_ParameterGID& theGIDBefore);

  ActData_EXPORT Standard_Boolean
    Update(const ActAPI_ParameterGID& theGID,
           const Handle(ActData_ParameterDTO)& theDTO);

  ActData_EXPORT Standard_Boolean
    Remove(const ActAPI_ParameterGID& theGID);

  ActData_EXPORT void
    NormalizePIDs();

private:

  Standard_Integer
    posParameter(const ActAPI_ParameterGID& theGID) const;

private:

  //! Parameters.
  NCollection_Sequence<Handle(ActData_CAFConversionParameter)> m_params;

  //! Minimal original PID.
  Standard_Integer m_iMinPID;

};

#endif
