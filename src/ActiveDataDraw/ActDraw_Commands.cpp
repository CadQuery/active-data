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
#include <ActDraw_Commands.h>

// Active Data (Draw plug-in) includes
#include <ActDraw_Common.h>

// OCCT includes
#include <Draw_Interpretor.hxx>
#include <Draw_PluginMacro.hxx>
#include <OSD.hxx>
#include <Standard_Version.hxx>
#include <TCollection_AsciiString.hxx>

// OS dependent
#include <windows.h>

#pragma message ("============== Set libraries for Open CASCADE Technology " OCC_VERSION_STRING)
#pragma comment (lib, "TKBool.lib")
#pragma comment (lib, "TKBO.lib")
#pragma comment (lib, "TKBRep.lib")
#pragma comment (lib, "TKDraw.lib")
#pragma comment (lib, "TKernel.lib")
#pragma comment (lib, "TKFeat.lib")
#pragma comment (lib, "TKFillet.lib")
#pragma comment (lib, "TKG2d.lib")
#pragma comment (lib, "TKG3d.lib")
#pragma comment (lib, "TKGeomAlgo.lib")
#pragma comment (lib, "TKGeomBase.lib")
#pragma comment (lib, "TKMath.lib")
#pragma comment (lib, "TKOffset.lib")
#pragma comment (lib, "TKPrim.lib")
#pragma comment (lib, "TKTopAlgo.lib")
#pragma comment (lib, "TKTopTest.lib")
#pragma comment (lib, "TKShHealing.lib")
#pragma comment (lib, "TKXSBase.lib")
#pragma comment (lib, "TKIGES.lib")
#pragma comment (lib, "TKLCAF.lib")
#pragma comment (lib, "TKV3d.lib")
#pragma comment (lib, "TKService.lib")
#pragma comment (lib, "TKMesh.lib")

#define BUFSIZE 1000
#define ACT_TEST_DUMP "ACT_TEST_DUMP"

//! Returns the value of environment variable ACT_TEST_DUMP.
//! \return requested value in form of OCCT ASCII string.
TCollection_AsciiString ActDraw_Commands::GET_DUMP_PATH()
{
  // Get environment variable for dumping
  TCHAR chNewEnv[BUFSIZE];
  GetEnvironmentVariable(ACT_TEST_DUMP, chNewEnv, BUFSIZE);

  return TCollection_AsciiString(chNewEnv).Cat("\\");
}

//! Entry point to ACT Commands plug-in for Draw. This is a right place
//! to register commands groups and activate license keys for value-added
//! components.
//! \param theDI [in] Draw interpretor instance.
void ActDraw_Commands::Factory(Draw_Interpretor& theDI)
{
  OSD::SetSignal(Standard_True);

  // Load command suites
  CAFDumperCommands(theDI);
  MiscCommands(theDI);

#ifdef ACT_DEBUG
  theDI << "Draw Plugin: ACT Draw commands are loaded" << "\n";
#endif
}

DPLUGIN(ActDraw_Commands)
