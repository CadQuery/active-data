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

#ifndef ActAPI_Variables_HeaderFile
#define ActAPI_Variables_HeaderFile

// Active Data (API) includes
#include <ActAPI_Common.h>

// OCCT includes
#include <TCollection_AsciiString.hxx>

// TBB includes
#include <concurrent_vector.h>

//-----------------------------------------------------------------------------
// Base class
//-----------------------------------------------------------------------------

DEFINE_STANDARD_HANDLE(ActAPI_VariableBase, Standard_Transient)

//! \ingroup AD_API
//!
//! Base class for Variables.
class ActAPI_VariableBase : public Standard_Transient
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActAPI_VariableBase, Standard_Transient)

public:

  //! Variable name.
  TCollection_AsciiString Name;

protected:

  //! Default constructor
  ActAPI_VariableBase() : Standard_Transient()
  {}

};

//-----------------------------------------------------------------------------
// Integer
//-----------------------------------------------------------------------------

DEFINE_STANDARD_HANDLE(ActAPI_VariableInt, ActAPI_VariableBase)

//! \ingroup AD_API
//!
//! Integer variable.
class ActAPI_VariableInt : public ActAPI_VariableBase
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActAPI_VariableInt, ActAPI_VariableBase)

public:

  //! Factory method ensuring allocation of Variable instance in a heap.
  //! \param theName [in] variable name.
  //! \param theValue [in] variable value.
  //! \return variable instance.
  ActAPI_EXPORT static Handle(ActAPI_VariableInt)
    Instance(const TCollection_AsciiString& theName,
             const Standard_Integer         theValue)
  {
    return new ActAPI_VariableInt(theName, theValue);
  }

public:

  //! Variable value.
  Standard_Integer Value;

public:

  //! Default constructor.
  ActAPI_VariableInt() : ActAPI_VariableBase()
  {}

  //! Constructor accepting variable value as an argument. The variable will
  //! have no name (empty name member).
  //! \param theValue [in] variable value.
  ActAPI_VariableInt(const Standard_Integer theValue) : ActAPI_VariableBase()
  {
    Value = theValue;
  }

  //! Constructor accepting the name and the value of the variable.
  //! \param theName [in] variable name.
  //! \param theValue [in] variable value.
  ActAPI_VariableInt(const TCollection_AsciiString& theName,
                     const Standard_Integer         theValue) : ActAPI_VariableBase()
  {
    Name = theName;
    Value = theValue;
  }

};

//-----------------------------------------------------------------------------
// Real
//-----------------------------------------------------------------------------

DEFINE_STANDARD_HANDLE(ActAPI_VariableReal, ActAPI_VariableBase)

//! \ingroup AD_API
//!
//! Real variable.
class ActAPI_VariableReal : public ActAPI_VariableBase
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActAPI_VariableReal, ActAPI_VariableBase)

public:

  //! Factory method ensuring allocation of Variable instance in a heap.
  //! \param theName [in] variable name.
  //! \param theValue [in] variable value.
  //! \return variable instance.
  ActAPI_EXPORT static Handle(ActAPI_VariableReal)
    Instance(const TCollection_AsciiString& theName,
             const Standard_Real            theValue)
  {
    return new ActAPI_VariableReal(theName, theValue);
  }

public:

  //! Variable value.
  Standard_Real Value;

public:

  //! Default constructor.
  ActAPI_VariableReal() : ActAPI_VariableBase()
  {}

  //! Constructor accepting variable value as an argument. The variable will
  //! have no name (empty name member).
  //! \param theValue [in] variable value.
  ActAPI_VariableReal(const Standard_Real theValue) : ActAPI_VariableBase()
  {
    Value = theValue;
  }

  //! Constructor accepting variable name and value as arguments.
  //! \param theName [in] variable name.
  //! \param theValue [in] variable value.
  ActAPI_VariableReal(const TCollection_AsciiString& theName,
                      const Standard_Real            theValue) : ActAPI_VariableBase()
  {
    Name = theName;
    Value = theValue;
  }

};

//-----------------------------------------------------------------------------
// Real array
//-----------------------------------------------------------------------------

DEFINE_STANDARD_HANDLE(ActAPI_VariableRealArray, ActAPI_VariableBase)

//! \ingroup AD_API
//!
//! Real array variable.
class ActAPI_VariableRealArray : public ActAPI_VariableBase
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActAPI_VariableRealArray, ActAPI_VariableBase)

public:

  //! Factory method ensuring allocation of Variable instance in a heap.
  //! \param theName [in] variable name.
  //! \param theValue [in] variable value.
  //! \return variable instance.
  ActAPI_EXPORT static Handle(ActAPI_VariableRealArray)
    Instance(const TCollection_AsciiString& theName,
             const Handle(HRealArray)&      theValue)
  {
    return new ActAPI_VariableRealArray(theName, theValue);
  }

public:

  //! Variable value.
  Handle(HRealArray) Value;

public:

  //! Default constructor.
  ActAPI_VariableRealArray() : ActAPI_VariableBase()
  {}

  //! Constructor accepting variable value as an argument. The variable will
  //! have no name (empty name member).
  //! \param theValue [in] variable value.
  ActAPI_VariableRealArray(const Handle(HRealArray)& theValue) : ActAPI_VariableBase()
  {
    Value = theValue;
  }

  //! Constructor accepting variable name and value as arguments.
  //! \param theName [in] variable name.
  //! \param theValue [in] variable value.
  ActAPI_VariableRealArray(const TCollection_AsciiString& theName,
                           const Handle(HRealArray)&      theValue) : ActAPI_VariableBase()
  {
    Name = theName;
    Value = theValue;
  }

};

//-----------------------------------------------------------------------------
// Boolean
//-----------------------------------------------------------------------------

DEFINE_STANDARD_HANDLE(ActAPI_VariableBool, ActAPI_VariableBase)

//! \ingroup AD_API
//!
//! Bool variable.
class ActAPI_VariableBool : public ActAPI_VariableBase
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActAPI_VariableBool, ActAPI_VariableBase)

public:

  //! Factory method ensuring allocation of Variable instance in a heap.
  //! \param theName [in] variable name.
  //! \param theValue [in] variable value.
  //! \return variable instance.
  ActAPI_EXPORT static Handle(ActAPI_VariableBool)
    Instance(const TCollection_AsciiString& theName,
             const Standard_Boolean         theValue)
  {
    return new ActAPI_VariableBool(theName, theValue);
  }

public:

  //! Variable value.
  Standard_Boolean Value;

public:

  //! Default constructor.
  ActAPI_VariableBool() : ActAPI_VariableBase()
  {}

  //! Constructor accepting variable value as an argument. The variable will
  //! have no name (empty name member).
  //! \param theValue [in] variable value.
  ActAPI_VariableBool(const Standard_Boolean theValue) : ActAPI_VariableBase()
  {
    Value = theValue;
  }

  //! Constructor accepting variable name and value as arguments.
  //! \param theName [in] variable name.
  //! \param theValue [in] variable value.
  ActAPI_VariableBool(const TCollection_AsciiString& theName,
                      const Standard_Boolean         theValue) : ActAPI_VariableBase()
  {
    Name = theName;
    Value = theValue;
  }

};

//-----------------------------------------------------------------------------
// String
//-----------------------------------------------------------------------------

DEFINE_STANDARD_HANDLE(ActAPI_VariableString, ActAPI_VariableBase)

//! \ingroup AD_API
//!
//! String variable.
class ActAPI_VariableString : public ActAPI_VariableBase
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActAPI_VariableString, ActAPI_VariableBase)

public:

  //! Factory method ensuring allocation of Variable instance in a heap.
  //! \param theName [in] variable name.
  //! \param theValue [in] variable value.
  //! \return variable instance.
  ActAPI_EXPORT static Handle(ActAPI_VariableString)
    Instance(const TCollection_AsciiString& theName,
             const TCollection_AsciiString& theValue)
  {
    return new ActAPI_VariableString(theName, theValue);
  }

public:

  //! Variable value.
  TCollection_AsciiString Value;

public:

  //! Default constructor.
  ActAPI_VariableString() : ActAPI_VariableBase()
  {}

  //! Constructor accepting variable value as an argument. The variable will
  //! have no name (empty name member).
  //! \param theValue [in] variable value.
  ActAPI_VariableString(const TCollection_AsciiString& theValue) : ActAPI_VariableBase()
  {
    Value = theValue;
  }

  //! Constructor accepting variable name and value as arguments.
  //! \param theName [in] variable name.
  //! \param theValue [in] variable value.
  ActAPI_VariableString(const TCollection_AsciiString& theName,
                        const TCollection_AsciiString& theValue) : ActAPI_VariableBase()
  {
    Name = theName;
    Value = theValue;
  }

};

//-----------------------------------------------------------------------------
// String
//-----------------------------------------------------------------------------

DEFINE_STANDARD_HANDLE(ActAPI_VariableShape, ActAPI_VariableBase)

//! \ingroup AD_API
//!
//! Variable of CAD shape type.
class ActAPI_VariableShape : public ActAPI_VariableBase
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActAPI_VariableShape, ActAPI_VariableBase)

public:

  //! Factory method ensuring allocation of Variable instance in a heap.
  //! \param theName [in] variable name.
  //! \param theValue [in] variable value.
  //! \return variable instance.
  ActAPI_EXPORT static Handle(ActAPI_VariableShape)
    Instance(const TCollection_AsciiString& theName,
             const TopoDS_Shape& theValue)
  {
    return new ActAPI_VariableShape(theName, theValue);
  }

public:

  //! Variable value.
  TopoDS_Shape Value;

public:

  //! Default constructor.
  ActAPI_VariableShape() : ActAPI_VariableBase()
  {}

  //! Constructor accepting variable value as an argument. The variable will
  //! have no name (empty name member).
  //! \param theValue [in] variable value.
  ActAPI_VariableShape(const TopoDS_Shape& theValue) : ActAPI_VariableBase()
  {
    Value = theValue;
  }

  //! Constructor accepting variable name and value as arguments.
  //! \param theName [in] variable name.
  //! \param theValue [in] variable value.
  ActAPI_VariableShape(const TCollection_AsciiString& theName,
                       const TopoDS_Shape& theValue) : ActAPI_VariableBase()
  {
    Name = theName;
    Value = theValue;
  }

};

//-----------------------------------------------------------------------------
// Auxiliary
//-----------------------------------------------------------------------------

//! \ingroup AD_API
//!
//! Collection of variables.
typedef tbb::concurrent_vector<Handle(ActAPI_VariableBase)> ActAPI_VariableList;

//! \ingroup AD_API
//!
//! Shared collection of variables (designed for manipulation by Handle).
typedef NCollection_Shared<ActAPI_VariableList> ActAPI_HVariableList;

#endif
