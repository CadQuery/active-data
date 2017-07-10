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

#ifndef ActData_ParameterFactory_HeaderFile
#define ActData_ParameterFactory_HeaderFile

// Active Data includes
#include <ActData_AsciiStringParameter.h>
#include <ActData_BoolArrayParameter.h>
#include <ActData_BoolParameter.h>
#include <ActData_Common.h>
#include <ActData_ComplexArrayParameter.h>
#include <ActData_GroupParameter.h>
#include <ActData_IntArrayParameter.h>
#include <ActData_IntParameter.h>
#include <ActData_MeshParameter.h>
#include <ActData_NameParameter.h>
#include <ActData_ReferenceListParameter.h>
#include <ActData_ReferenceParameter.h>
#include <ActData_RealParameter.h>
#include <ActData_RealArrayParameter.h>
#include <ActData_SelectionParameter.h>
#include <ActData_ShapeParameter.h>
#include <ActData_StringArrayParameter.h>
#include <ActData_TimeStampParameter.h>
#include <ActData_TreeFunctionParameter.h>
#include <ActData_TreeNodeParameter.h>
#include <ActData_TriangulationParameter.h>

// Active Data (API) includes
#include <ActAPI_IParameter.h>

// OCCT includes
#include <TDF_Label.hxx>

#define Parameter_SafeDownCast_Macro(Type) \
  inline static Handle(ActData_##Type##Parameter) As##Type##(const Handle(ActAPI_IUserParameter)& theParam) \
  { \
    return Handle(ActData_##Type##Parameter)::DownCast(theParam); \
  }

//! Convenience short-cut which is useful to reduce the amount of code
//! to be written. E.g. ActData_ParameterFactory::AsReal(...) becomes
//! ActParamTool::AsReal(...)
#define ActParamTool ActData_ParameterFactory

DEFINE_STANDARD_HANDLE(ActData_ParameterFactory, Standard_Transient)

//! \ingroup AD_DF
//!
//! Factory class for all existing types of Active Data Parameters.
class ActData_ParameterFactory : public Standard_Transient
{
friend class ActData_TreeFunctionDriver;

public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActData_ParameterFactory, Standard_Transient)

// Settling/Expanding:
public:

  ActData_EXPORT static Handle(ActAPI_IUserParameter)
    NewParameterDetached(const Standard_Integer theParamType);

  ActData_EXPORT static Standard_Boolean
    IsParameter(const TDF_Label& theLabel);

  ActData_EXPORT static Handle(ActAPI_IUserParameter)
    NewParameterSettle(const Standard_Integer theParamType,
                       const TDF_Label&       theLabel);

  ActData_EXPORT static Handle(ActAPI_IUserParameter)
    NewParameterExpand(const Standard_Integer theParamType,
                       const TDF_Label&       theLabel);

  ActData_EXPORT static Handle(ActAPI_IUserParameter)
    NewParameterSettle(const TDF_Label& theLabel);

  ActData_EXPORT static Handle(ActAPI_HParameterList)
    ParamsByLabelsSettle(const TDF_LabelList& theLabels);

  ActData_EXPORT static Handle(ActAPI_IUserParameter)
    ParamByChildLabelSettle(const TDF_Label& theLabel);

// Safe Conversion methods:
public:

  Parameter_SafeDownCast_Macro(AsciiString)
  Parameter_SafeDownCast_Macro(BoolArray)
  Parameter_SafeDownCast_Macro(Bool)
  Parameter_SafeDownCast_Macro(ComplexArray)
  Parameter_SafeDownCast_Macro(Group)
  Parameter_SafeDownCast_Macro(IntArray)
  Parameter_SafeDownCast_Macro(Int)
  Parameter_SafeDownCast_Macro(Mesh)
  Parameter_SafeDownCast_Macro(Name)
  Parameter_SafeDownCast_Macro(RealArray)
  Parameter_SafeDownCast_Macro(Real)
  Parameter_SafeDownCast_Macro(Reference)
  Parameter_SafeDownCast_Macro(ReferenceList)
  Parameter_SafeDownCast_Macro(Selection)
  Parameter_SafeDownCast_Macro(Shape)
  Parameter_SafeDownCast_Macro(StringArray)
  Parameter_SafeDownCast_Macro(TimeStamp)
  Parameter_SafeDownCast_Macro(TreeFunction)
  Parameter_SafeDownCast_Macro(TreeNode)
  Parameter_SafeDownCast_Macro(Triangulation)

private:

  ActData_ParameterFactory();

};

#endif
