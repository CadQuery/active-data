//-----------------------------------------------------------------------------
// Created on: June 2012
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

#ifndef ActData_CAFConversionAsset_HeaderFile
#define ActData_CAFConversionAsset_HeaderFile

// Active Data includes
#include <ActData_BaseModel.h>
#include <ActData_Common.h>
#include <ActData_ParameterFactory.h>

//! \ingroup AD_DF
//!
//! Utility class providing a set useful routines performing atomic
//! conversion modifications. This class is intended to assist you in
//! your custom backward compatibility conversion routines.
class ActData_CAFConversionAsset
{
public:

  ActData_EXPORT
    ActData_CAFConversionAsset(const Handle(ActAPI_IModel)& theModel);

// Verifications:
public:

  ActData_EXPORT Standard_Boolean
    HasBadFormedNodes() const;

  ActData_EXPORT Standard_Boolean
    HasUnMTimedParams(Handle(ActAPI_HParameterList)& theParams) const;

// Conversions:
public:

  ActData_EXPORT void
    ActualizeVersions();

  ActData_EXPORT void
    ModifyParams();

  ActData_EXPORT Handle(ActAPI_IUserParameter)
    ChangeParameterType(const Handle(ActAPI_INode)& theNode,
                        const Standard_Integer thePID,
                        const ActAPI_ParameterType theNewType);

private:

  Handle(ActAPI_IUserParameter)
    expandParam(const Handle(ActAPI_INode)& theNode,
                const Standard_Integer thePID,
                const ActAPI_ParameterType theType) const;

  Handle(ActAPI_IUserParameter)
    settleParam(const Handle(ActAPI_INode)& theNode,
                const Standard_Integer thePID) const;

  TDF_Label
    uScopePRoot(const Handle(ActAPI_INode)& theNode,
                const Standard_Integer thePID,
                const Standard_Boolean toCreate) const;

  void
    accessUnMTimedParams(const TDF_Label& theNodeLab,
                         Handle(ActAPI_HParameterList)& theParams) const;

  Handle(ActAPI_HParameterList)
    accessUnMTimedParamsBySection(const TDF_Label& theSectionLab) const;

private:

  //! Data Model being modified.
  Handle(ActData_BaseModel) m_modelBase;

};

#endif
