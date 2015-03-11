//-----------------------------------------------------------------------------
// Created on: April 2012
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

#ifndef ActAPI_IDataCursor_HeaderFile
#define ActAPI_IDataCursor_HeaderFile

// Active Data (API) includes
#include <ActAPI.h>

// OCCT includes
#include <NCollection_Map.hxx>
#include <NCollection_Sequence.hxx>
#include <NCollection_Shared.hxx>
#include <Standard_Transient.hxx>
#include <Standard_Type.hxx>
#include <TCollection_AsciiString.hxx>
#include <TDF_Label.hxx>

//! \ingroup AD_API
//!
//! ID in form of CAF entry, e.g. "0:1:1".
typedef TCollection_AsciiString ActAPI_DataObjectId;

//! \ingroup AD_API
//!
//! Short-cuts for collection of Data Object IDs.
typedef NCollection_Sequence<ActAPI_DataObjectId>   ActAPI_DataObjectIdList;
typedef NCollection_Shared<ActAPI_DataObjectIdList> ActAPI_HDataObjectIdList;

//-----------------------------------------------------------------------------
// Data Cursor
//-----------------------------------------------------------------------------

//! \ingroup AD_API
//!
//! Interface for Data Cursors. Defines common public methods for consulting
//! the underlying Data Object and its verification against the rules defined
//! by actual derived Cursor classes.
class ActAPI_IDataCursor : public Standard_Transient
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActAPI_IDataCursor, Standard_Transient)

public:

  ActAPI_EXPORT virtual
    ~ActAPI_IDataCursor();

public:

  //! Hasher for maps.
  struct Hasher
  {
    //! HashCode() function for Data Cursor to be used in OCCT Data Maps.
    //! \param theDC [in] Data Cursor to calculate a hash code for.
    //! \param theUpper [in] upper index.
    //! \return hash code.
    static inline Standard_Integer HashCode(const Handle(ActAPI_IDataCursor)& theDC,
                                            const Standard_Integer theUpper)
    {
      if ( theDC.IsNull() )
        return 0;

      ActAPI_DataObjectId anObjectId = theDC->GetId();
      return ::HashCode(anObjectId, theUpper);
    }

    //! IsEqual() function for Data Cursors to be used in OCCT Data Maps.
    //! \param theDC1 [in] first Data Cursor.
    //! \param theDC2 [in] second Data Cursor.
    //! \return true in case of equality, false -- otherwise.
    static inline Standard_Boolean IsEqual(const Handle(ActAPI_IDataCursor)& theDC1,
                                           const Handle(ActAPI_IDataCursor)& theDC2)
    {
      if ( theDC1.IsNull() || theDC2.IsNull() )
        return Standard_False;

      ActAPI_DataObjectId anObject1Id = theDC1->GetId();
      ActAPI_DataObjectId anObject2Id = theDC2->GetId();
      return ::IsEqual(anObject1Id, anObject2Id);
    }
  };

  //! HashCode() function for Data Cursor to be used in OCCT Data Maps.
  //! \param theDC [in] Data Cursor to calculate a hash code for.
  //! \param theUpper [in] upper index.
  //! \return hash code.
  static inline Standard_Integer HashCode(const Handle(ActAPI_IDataCursor)& theDC,
                                          const Standard_Integer theUpper)
  {
    return Hasher::HashCode(theDC, theUpper);
  }

  //! IsEqual() function for Data Cursors to be used in OCCT Data Maps.
  //! \param theDC1 [in] first Data Cursor.
  //! \param theDC2 [in] second Data Cursor.
  //! \return true in case of equality, false -- otherwise.
  static inline Standard_Boolean IsEqual(const Handle(ActAPI_IDataCursor)& theDC1,
                                         const Handle(ActAPI_IDataCursor)& theDC2)
  {
    return Hasher::IsEqual(theDC1, theDC2);
  }

public:

  virtual Standard_Boolean
    IsAttached() = 0;

  virtual Standard_Boolean
    IsDetached() = 0;

  virtual Standard_Boolean
    IsWellFormed() = 0;

  virtual Standard_Boolean
    IsValidData() = 0;

  virtual Standard_Boolean
    IsPendingData() = 0;

  virtual ActAPI_DataObjectId
    GetId() const = 0;

public:

  virtual TDF_Label
    RootLabel() const = 0;

// Notice that methods for moving the Data Cursor from one entity to another
// are declared in private section as this functionality is used by Data
// Framework only (more abstract mechanisms are available for client code)
private:

  //! Expanding routine. Given a particular TDF Label, it attempts to
  //! produce an expected structure of underlying TDF Labels for subsequent
  //! charging of Data Cursor. Used properly, it normally produces an ATTACHED
  //! and BAD-FORMED Data Cursor as underlying CAF data normally requires
  //! additional initialization.
  //! \param theLabel [in] TDF Label to expand the domain-specific data chunks.
  virtual void
    expandOn(const TDF_Label& theLabel) = 0;

  //! Settling routine. Given a particular TDF Label, it presumes that it
  //! already has an expected internal sub-hierarchy and does not attempt
  //! to create any TDF Label in addendum. This method should be normally used
  //! just to move the Data Cursor from one well-formed Data Object to another.
  //! Used properly, it produces an ATTACHED and WELL-FORMED Data Cursor.
  //! \param theLabel [in] TDF Label to move the Cursor to.
  virtual void
    settleOn(const TDF_Label& theLabel) = 0;

};

//! \ingroup AD_API
//!
//! Short-cuts for collection of Data Cursors.
typedef NCollection_Sequence<Handle(ActAPI_IDataCursor)> ActAPI_DataCursorList;
typedef NCollection_Shared<ActAPI_DataCursorList>        ActAPI_HDataCursorList;

#endif
