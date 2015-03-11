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

// Own include
#include <ActData_ParameterFactory.h>

// OCCT includes
#include <Standard_ProgramError.hxx>
#include <TDataStd_Integer.hxx>
#include <TDF_ListIteratorOfLabelList.hxx>

//! Default constructor.
ActData_ParameterFactory::ActData_ParameterFactory()
{}

//! Factory method performing actual allocation of DETACHED Parameter instance
//! of the given type.
//! \param theParamType [in] requested Parameter type.
//! \return new DETACHED Parameter instance.
Handle(ActAPI_IUserParameter)
  ActData_ParameterFactory::NewParameterDetached(const Standard_Integer theParamType)
{
  Handle(ActAPI_IUserParameter) aResult;

  ActAPI_ParameterType aParamType = static_cast<ActAPI_ParameterType>(theParamType);
  switch ( aParamType )
  {
    case Parameter_Bool:
      aResult = ActData_BoolParameter::Instance();
      break;

    case Parameter_BoolArray:
      aResult = ActData_BoolArrayParameter::Instance();
      break;

    case Parameter_Int:
      aResult = ActData_IntParameter::Instance();
      break;

    case Parameter_Real:
      aResult = ActData_RealParameter::Instance();
      break;

    case Parameter_RealArray:
      aResult = ActData_RealArrayParameter::Instance();
      break;

    case Parameter_Shape:
      aResult = ActData_ShapeParameter::Instance();
      break;

    case Parameter_TreeFunction:
      aResult = ActData_TreeFunctionParameter::Instance();
      break;

    case Parameter_TreeNode:
      aResult = ActData_TreeNodeParameter::Instance();
      break;

    case Parameter_AsciiString:
      aResult = ActData_AsciiStringParameter::Instance();
      break;

    case Parameter_ComplexArray:
      aResult = ActData_ComplexArrayParameter::Instance();
      break;

    case Parameter_IntArray:
      aResult = ActData_IntArrayParameter::Instance();
      break;

    case Parameter_Name:
      aResult = ActData_NameParameter::Instance();
      break;

    case Parameter_StringArray:
      aResult = ActData_StringArrayParameter::Instance();
      break;

    case Parameter_ReferenceList:
      aResult = ActData_ReferenceListParameter::Instance();
      break;

    case Parameter_Group:
      aResult = ActData_GroupParameter::Instance();
      break;

    case Parameter_Mesh:
      aResult = ActData_MeshParameter::Instance();
      break;

    case Parameter_Reference:
      aResult = ActData_ReferenceParameter::Instance();
      break;

    case Parameter_Selection:
      aResult = ActData_SelectionParameter::Instance();
      break;

    case Parameter_TimeStamp:
      aResult = ActData_TimeStampParameter::Instance();
      break;

    default: break;
  }

  return aResult;
}

//! Checks whether the given Label represents Parameter data or not.
//! \param theLabel [in] raw Label to check.
//! \return true/false.
Standard_Boolean
  ActData_ParameterFactory::IsParameter(const TDF_Label& theLabel)
{
  /* =====================================
   *  Check if TYPE Attribute is in place
   * ===================================== */

  if ( theLabel.IsNull() )
    return Standard_False;

  TDF_Label aParamTypeLab =
    theLabel.FindChild(ActData_UserParameter::DS_ParamType, Standard_False);

  if ( aParamTypeLab.IsNull() )
    return Standard_False;

  Handle(TDataStd_Integer) aParamTypeAttr;
  if ( !aParamTypeLab.FindAttribute(TDataStd_Integer::GetID(), aParamTypeAttr) )
    return Standard_False;

  /* =========================================
   *  Check if IS_VALID Attribute is in place
   * ========================================= */

  TDF_Label aParamValidityLab =
    theLabel.FindChild(ActData_UserParameter::DS_IsValid, Standard_False);

  if ( aParamValidityLab.IsNull() )
    return Standard_False;

  Handle(TDataStd_Integer) aParamValidityAttr;
  if ( !aParamValidityLab.FindAttribute(TDataStd_Integer::GetID(), aParamValidityAttr) )
    return Standard_False;

  return Standard_True;
}

//! READ-ONLY method settling down the Parameter Data Cursor of the given type
//! to the given CAF Label.
//! \param theParamType [in] type of the Parameter to settle.
//! \param theLabel     [in] target Label to get data access to.
//! \return new Parameter instance.
Handle(ActAPI_IUserParameter)
  ActData_ParameterFactory::NewParameterSettle(const Standard_Integer theParamType,
                                               const TDF_Label&       theLabel)
{
  Handle(ActData_UserParameter) aResult =
    Handle(ActData_UserParameter)::DownCast( NewParameterDetached(theParamType) );

  if ( !aResult.IsNull() )
    aResult->settleOn(theLabel);

  return aResult;
}

//! Method EXPANDING the Parameter Data Cursor of the given type on the given
//! CAF Label.
//! \param theParamType [in] type of the Parameter to expand.
//! \param theLabel     [in] target Label.
//! \return new Parameter instance.
Handle(ActAPI_IUserParameter)
  ActData_ParameterFactory::NewParameterExpand(const Standard_Integer theParamType,
                                               const TDF_Label&       theLabel)
{
  Handle(ActData_UserParameter) aResult =
    Handle(ActData_UserParameter)::DownCast( NewParameterDetached(theParamType) );

  aResult->expandOn(theLabel);

  return aResult;
}

//! READ-ONLY method settling down the Parameter Data Cursor to the given
//! CAF Label.
//! \param theLabel [in] target Label to get data access to.
//! \return new Parameter instance.
Handle(ActAPI_IUserParameter)
  ActData_ParameterFactory::NewParameterSettle(const TDF_Label& theLabel)
{
  TDF_Label aTypeLab = theLabel.FindChild(ActData_UserParameter::DS_ParamType, Standard_False);

  if ( aTypeLab.IsNull() )
    Standard_ProgramError::Raise("Inconsistent Type Label");

  Handle(TDataStd_Integer) aTypeAttr;
  if ( !aTypeLab.FindAttribute(TDataStd_Integer::GetID(), aTypeAttr) )
    return NULL; // Type Attribute not found

  return NewParameterSettle(aTypeAttr->Get(), theLabel);
}

//! Constructs a list of Parameters by the list of the corresponding
//! TDF Labels.
//! \param theLabels [in] list of TDF Labels to pack.
//! \return high-level list of Parameters.
Handle(ActAPI_HParameterList)
  ActData_ParameterFactory::ParamsByLabelsSettle(const TDF_LabelList& theLabels)
{
  ActAPI_ParameterStream aPStream;
  TDF_ListIteratorOfLabelList aLabelIt(theLabels);
  for ( ; aLabelIt.More(); aLabelIt.Next() )
  {
    TDF_Label aLab = aLabelIt.Value();
    aPStream << ActData_ParameterFactory::NewParameterSettle(aLab);
  }

  return aPStream;
}

//! Attempts to find a Parameter instance owning the passed Label as one
//! of its children (any level is allowed).
//! \param theLabel [in] Label to recover a Parameter for.
//! \return Parameter instance or NULL if nothing appropriate was found.
Handle(ActAPI_IUserParameter)
  ActData_ParameterFactory::ParamByChildLabelSettle(const TDF_Label& theLabel)
{
  if ( IsParameter(theLabel) )
    return NewParameterSettle(theLabel);

  TDF_Label aFather = theLabel.Father();
  if ( aFather.IsNull() )
    return NULL;

  return ParamByChildLabelSettle(aFather);
}
