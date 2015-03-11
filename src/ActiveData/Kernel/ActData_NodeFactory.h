//-----------------------------------------------------------------------------
// Created on: May 2012
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

#ifndef ActData_NodeFactory_HeaderFile
#define ActData_NodeFactory_HeaderFile

// Let the static registry of RTTI fill itself
#include <Standard_Type.hxx>

// Active Data includes
#include <ActData_BaseNode.h>
#include <ActData_Common.h>

// Active Data (API) includes
#include <ActAPI_INode.h>

// OCCT includes
#include <NCollection_DataMap.hxx>
#include <TDF_Label.hxx>

//! Pointer to Node allocation routine.
typedef Handle(ActAPI_INode) (*ActData_NodeAllocator)();

#define DEFINE_NODE_FACTORY(C, AllocFunction) \
  class Registrator \
  { \
  public: \
    Registrator() \
    { \
      ActData_NodeFactory::RegisterNodeType(C::get_type_name(), \
                                            AllocFunction); \
    } \
  }; \
  static Registrator m_typeRegistrator;

#define REGISTER_NODE_TYPE(C) \
  C::Registrator C::m_typeRegistrator;

#define REGISTER_PARAMETER_COMMON(Class, Id, IsExpressible) \
  this->registerParameter(Id, ActData_##Class##Parameter::Instance(), IsExpressible)

#define REGISTER_PARAMETER(Class, Id) \
  REGISTER_PARAMETER_COMMON(Class, Id, Standard_False)

#define REGISTER_PARAMETER_EXPR(Class, Id) \
  REGISTER_PARAMETER_COMMON(Class, Id, Standard_True)

//! \ingroup AD_DF
//!
//! Factory for Data Nodes.
class ActData_NodeFactory
{
public:

  //! Mapping between Node types and allocation routines.
  typedef NCollection_DataMap<TCollection_AsciiString, ActData_NodeAllocator> NodeAllocMap;

// Node factory:
public:

  ActData_EXPORT static const NodeAllocMap&
    RegisterNodeType(const TCollection_AsciiString& theType,
                     const ActData_NodeAllocator&   theAllocFunc);

  ActData_EXPORT static const NodeAllocMap&
    GetAllocMap();

  ActData_EXPORT static Standard_Boolean
    IsNode(const TDF_Label&         theLab,
           TCollection_AsciiString& theNodeType);

  ActData_EXPORT static Standard_Boolean
    IsNode(const TDF_Label& theLab);

  ActData_EXPORT static Handle(ActAPI_INode)
    NodeInstanceByType(const TCollection_AsciiString& theNodeType);

  ActData_EXPORT static Standard_Boolean
    CanSettleNode(const TDF_Label& theLab);

  ActData_EXPORT static Handle(ActAPI_INode)
    NodeSettle(const TDF_Label& theLab);

  ActData_EXPORT static void
    NodeSettle(const Handle(ActData_BaseNode)& theNode,
               const TDF_Label&                theLab);

  ActData_EXPORT static Handle(ActAPI_INode)
    NodeByParamSettle(const TDF_Label& theParamLabel);

  ActData_EXPORT static Handle(ActAPI_INode)
    NodeByParamSettle(const Handle(ActAPI_IUserParameter)& theParam);

private:

  static NodeAllocMap m_allocMap;

};

#endif
