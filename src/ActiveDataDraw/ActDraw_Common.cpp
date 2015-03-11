//-----------------------------------------------------------------------------
// Created on: January 2012
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
#include <ActDraw_Common.h>

// Mesh includes
#pragma warning(push, 0)
#include <Mesh_ElementsIterator.h>
#include <Mesh_Node.h>
#include <Mesh_Quadrangle.h>
#include <Mesh_Triangle.h>
#pragma warning(pop)

// OCCT includes
#pragma warning(push, 0)
#include <AIS_InteractiveContext.hxx>
#include <AIS_Shape.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_Sewing.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>
#include <Draw_Interpretor.hxx>
#include <IGESControl_Reader.hxx>
#include <Message_ProgressSentry.hxx>
#include <PCDM_ReaderStatus.hxx>
#include <ShapeFix_Shape.hxx>
#include <Transfer_TransientProcess.hxx>
#include <V3d_View.hxx>
#include <V3d_Viewer.hxx>
#include <WNT_Window.hxx>
#include <XSControl_TransferReader.hxx>
#include <XSControl_WorkSession.hxx>
#pragma warning(pop)

//! Converts address of the passed shape (TShape) to string.
//! \param theShape [in] Shape to dump.
//! \return corresponding string.
TCollection_AsciiString
  ActDraw_Common::AddrToString(const TopoDS_Shape& theShape)
{
  std::string anAddrStr;
  std::ostringstream ost;
  ost << theShape.TShape().get();
  anAddrStr = ost.str();

  TCollection_AsciiString aStr =
    TCollection_AsciiString("[").Cat( anAddrStr.c_str() ).Cat("]");

  return aStr;
}

//! Saves the passed CAF document to CBF file with the given name.
//! \param theFilename [in] filename.
//! \param theApp [in] Application instance used as a tool to perform
//!        Save operation.
//! \param theDoc [in] document to save.
//! \return true in case of success, false -- otherwise.
Standard_Boolean
  ActDraw_Common::SaveBinaryCAF(const TCollection_AsciiString& theFilename,
                                const Handle(ActAPI_IModel)& theModel)
{
  cout << "\n=====================================================" << endl;
  cout << "Saving document to:"                                     << endl;
  cout << theFilename.ToCString()                                   << endl;
  cout << "=====================================================\n" << endl;

  return theModel->SaveAs(theFilename);
}

//! Restores CAF document from the given CBF file.
//! \param theFilename [in] filename.
//! \param theApp [in] Application instance used as a tool to perform
//!        Open operation.
//! \param theDoc [in] document to retrieve.
//! \return true in case of success, false -- otherwise.
Standard_Boolean
  ActDraw_Common::OpenBinaryCAF(const TCollection_AsciiString& theFilename,
                                const Handle(ActAPI_IModel)& theModel)
{
  cout << "\n=====================================================" << endl;
  cout << "Opening document from:"                                  << endl;
  cout << theFilename.ToCString()                                   << endl;
  cout << "=====================================================\n" << endl;

  return theModel->Open(theFilename);
}

TopoDS_Shape ActDraw_Common::RandomShape()
{
  Standard_Integer RAND_INDX = rand() % 10;
  TopoDS_Shape aResult;
  switch ( RAND_INDX )
  {
    case 0:
      aResult = BRepPrimAPI_MakeBox(10, 10, 10);
      break;
    case 1:
      aResult = BRepPrimAPI_MakeBox(5, 20, 40);
      break;
    case 2:
      aResult = BRepPrimAPI_MakeCone(10, 5, 10);
      break;
    case 3:
      aResult = BRepPrimAPI_MakeCone(5, 25, 20);
      break;
    case 4:
      aResult = BRepPrimAPI_MakeCylinder(10, 20);
      break;
    case 5:
      aResult = BRepPrimAPI_MakeSphere(10, 2*M_PI / 3);
      break;
    case 6:
      aResult = BRepPrimAPI_MakeSphere(10, 7*M_PI / 8);
      break;
    case 7:
      aResult = BRepPrimAPI_MakeTorus(5, 10);
      break;
    case 8:
      aResult = BRepPrimAPI_MakeTorus(10, 15, M_PI / 3);
      break;
    case 9:
      aResult = BRepPrimAPI_MakeTorus(10, 15, M_PI / 2);
      break;
  }
  return aResult;
}

Standard_Boolean ActDraw_Common::RandomBoolean()
{
  Standard_Integer RAND_INDX = rand() % 10;

  if ( RAND_INDX < 5 )
    return Standard_True;
  
  return Standard_False;
}
