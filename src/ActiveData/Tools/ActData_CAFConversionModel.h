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

#ifndef ActData_CAFConversionModel_HeaderFile
#define ActData_CAFConversionModel_HeaderFile

// Active Data includes
#include <ActData_BaseModel.h>
#include <ActData_CAFConversionNode.h>
#include <ActData_Common.h>
#include <ActData_ParameterDTO.h>

DEFINE_STANDARD_HANDLE(ActData_CAFConversionModel, Standard_Transient)

//! \ingroup AD_DF
//!
//! Conversion Model (Sampler) representing transient sampler structure used
//! by Conversion Context.
class ActData_CAFConversionModel : public Standard_Transient
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActData_CAFConversionModel, Standard_Transient)

public:

  //! Relocation map.
  typedef NCollection_DataMap<ActAPI_ParameterGID,
                              ActAPI_ParameterGID,
                              ActAPI_ParameterGID::Hasher> TRelocMap;

  //! Type shortcut for map of Conversion Nodes against their original IDs.
  typedef NCollection_DataMap<ActAPI_DataObjectId,
                              Handle(ActData_CAFConversionNode)> TNodeMap;

  //! Iterator for Sampler.
  class Iterator
  {
  public:

    //! Default constructor.
    Iterator()
    {
    }

    //! Complete constructor.
    //! \param theModel [in] Conversion Sampler to iterate over.
    Iterator(const Handle(ActData_CAFConversionModel)& theModel)
    {
      this->Init(theModel);
    }

    //! Initializes iterator.
    //! \param theModel [in] Conversion Sampler to iterate over.
    void Init(const Handle(ActData_CAFConversionModel)& theModel)
    {
      m_iter.Initialize(theModel->m_nodeMap);
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

    //! Returns currently iterated key.
    //! \return current key.
    const ActAPI_DataObjectId& Key() const
    {
      return m_iter.Key();
    }

    //! Returns currently iterated value.
    //! \return current value.
    const Handle(ActData_CAFConversionNode)& Value() const
    {
      return m_iter.Value();
    }

  private:

    TNodeMap::Iterator m_iter; //!< Internal iterator.

  };

public:

  ActData_EXPORT
    ActData_CAFConversionModel();

public:

  ActData_EXPORT Standard_Boolean
    ContainsNode(const ActAPI_DataObjectId& theNID) const;

  ActData_EXPORT Standard_Boolean
    AddOriginNode(const ActAPI_DataObjectId& theNID,
                  const Handle(ActAPI_IModel)& theModel);

  ActData_EXPORT Handle(ActData_CAFConversionNode)
    GetNode(const ActAPI_DataObjectId& theNID) const;

public:

  ActData_EXPORT void
    Clear();

  ActData_EXPORT void
    BuildRelocationMap();

  ActData_EXPORT ActAPI_ParameterGID
    Converted(const ActAPI_ParameterGID& theOldGID) const;

private:

  TNodeMap  m_nodeMap;  //!< Map of Conversion Nodes.
  TRelocMap m_relocMap; //!< Conversion relocation map.

};

#endif
