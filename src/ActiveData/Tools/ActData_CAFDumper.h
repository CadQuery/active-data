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

#ifndef ActData_CAFDumper_HeaderFile
#define ActData_CAFDumper_HeaderFile

// Active Data includes
#include <ActData_BaseModel.h>
#include <ActData_BaseNode.h>
#include <ActData_BasePartition.h>
#include <ActData_Common.h>

// Active Data (API) forward declarations
#include <ActAPI_IModel.h>

// OCCT includes
#include <OSD_File.hxx>
#include <TDataStd_IntPackedMap.hxx>
#include <TDataStd_ReferenceList.hxx>
#include <TDF_Attribute.hxx>
#include <TDF_Label.hxx>

//-----------------------------------------------------------------------------
// Indentation definitions
//-----------------------------------------------------------------------------

#define DEFAULT_IDENT_LEFT 5
#define DEFAULT_ARR_LIMIT 10

//-----------------------------------------------------------------------------
// CAF Dumper Tool
//-----------------------------------------------------------------------------

//! \ingroup AD_DF
//!
//! Utility class providing functionality of dumping ACT Data Model into
//! external files.
class ActData_CAFDumper
{
// Utilized types & structures:
public:

  //! Content to dump.
  enum Content
  {
    Content_Plain = 1,
    Content_TreeNodes,
    Content_DependencyGraph // TODO: NYI Content_DependencyGraph
  };

  //! Verbosity level.
  enum Verbosity
  {
    Verbosity_StructureNodesOnly = 1,
    Verbosity_StructureOnly,
    Verbosity_DetailsSkipUnstable,
    Verbosity_Details
  };

// Kernel:
public:

  ActData_EXPORT static Standard_Boolean
    Dump(const TCollection_AsciiString& theFilename,
         const Handle(ActAPI_IModel)&   theModel,
         const Content                  theContentType = Content_Plain,
         const Verbosity                theVerbosity = Verbosity_Details);

  ActData_EXPORT static Standard_Boolean
    Dump(Standard_OStream&            theOut,
         const Handle(ActAPI_IModel)& theModel,
         const Content                theContentType = Content_Plain,
         const Verbosity              theVerbosity = Verbosity_Details);

// Internal kernel:
private:

  static void
    dumpPlainStructure(Standard_OStream&                theOut,
                       const Handle(ActData_BaseModel)& theBaseModel,
                       const Verbosity                  theVerbosity);

  static void
    dumpTreeNodeStructure(Standard_OStream&           theOut,
                          const Handle(ActAPI_INode)& theRootNode,
                          const Verbosity             theVerbosity,
                          const Standard_Integer      theNbSpacesOnTheLeft);

  static void
    dumpPartition(Standard_OStream&                    theOut,
                  const Handle(ActData_BasePartition)& thePartition,
                  const Content                        theContentType = Content_Plain,
                  const Verbosity                      theVerbosity = Verbosity_Details);

  static void
    dumpNodeHeader(Standard_OStream&           theOut,
                   const Handle(ActAPI_INode)& theNode,
                   const Verbosity             theVerbosity,
                   const Standard_Integer      theNbSpacesOnTheLeft);

  static void
    dumpBadNodeHeader(Standard_OStream&      theOut,
                      const TDF_Label&       theNodeLab,
                      const Verbosity        theVerbosity,
                      const Standard_Integer theNbSpacesOnTheLeft);

  static void
    dumpNode(Standard_OStream&               theOut,
             const Handle(ActData_BaseNode)& theNode,
             const Content                   theContentType = Content_Plain,
             const Verbosity                 theVerbosity = Verbosity_Details,
             const Standard_Integer          theNbSpacesOnTheLeft = DEFAULT_IDENT_LEFT);

  static void
    dumpLabelWithAttributes(Standard_OStream&              theOut,
                            const TDF_Label&               theLabel,
                            const Standard_Integer         theNbSpacesOnTheLeft,
                            const Standard_Boolean         doDumpChildren,
                            const Content                  theContentType = Content_Plain,
                            const Verbosity                theVerbosity = Verbosity_Details,
                            const TCollection_AsciiString& thePrefix = TCollection_AsciiString());

  static void
    dumpAttribute(Standard_OStream&              theOut,
                  const Handle(TDF_Attribute)&   theAttribute,
                  const Standard_Integer         theNbSpacesOnTheLeft,
                  const Content                  theContentType = Content_Plain,
                  const Verbosity                theVerbosity = Verbosity_Details,
                  const TCollection_AsciiString& thePrefix = TCollection_AsciiString());

// Auxiliary methods:
private:

  static TCollection_AsciiString
    emptySpaces(const Standard_Integer theNbSpaces);

  template<typename E, typename A>
  static TCollection_AsciiString
    arrayToLimitedStr(const A& theArr);

  static TCollection_AsciiString
    collectionToLimitedStr(const Handle(TDataStd_IntPackedMap)& theCol);

  static TCollection_AsciiString
    collectionToStr(const Handle(TDataStd_ReferenceList)& theCol);

  static TCollection_AsciiString
    toString(const Standard_Boolean theElem);

  static TCollection_AsciiString
    toString(const Standard_Integer theElem);

  static TCollection_AsciiString
    toString(const Standard_Real theElem);

  static TCollection_AsciiString
    toString(const TCollection_ExtendedString& theElem);

  static TCollection_AsciiString
    toString(const TopoDS_Shape& theShape);

// Construction routines:
protected:

  ActData_EXPORT ActData_CAFDumper();

};

#endif
