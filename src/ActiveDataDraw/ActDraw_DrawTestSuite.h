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

#ifndef ActDraw_DrawTestSuite_HeaderFile
#define ActDraw_DrawTestSuite_HeaderFile

// OCCT includes
#pragma warning(push, 0)
#include <BRepTools.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <BRep_Builder.hxx>
#include <DrawTrSurf.hxx>
#include <Draw_Color.hxx>
#include <Draw_MarkerShape.hxx>
#include <DBRep.hxx>
#include <Geom_Curve.hxx>
#include <Geom_Line.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <Geom_Surface.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <GCE2d_MakeLine.hxx>
#include <gce_MakeLin.hxx>
#include <OSD_Timer.hxx>
#include <Precision.hxx>
#include <TopoDS_Shape.hxx>
#include <TCollection_AsciiString.hxx>
#include <TopoDS_Edge.hxx>
#pragma warning(pop)

/************************************************************************
                           INLINE RENDERING
 ************************************************************************/

//! For any entity which we are going to visualize we need to generate some
//! unique name to be used as a name of the corresponding DRAW variable.
//! The applied approach consists in reserving some big amount of indices
//! presuming that we cannot have e.g. more than 1 million points to render.
//! If it is not the case, just increase the SHIFT_INDEX value
#define SHIFT_INDEX 1000000

//! Initializes a scope of DRAW variables to store any type of entities
#define DRAW_INITGROUP(P_BASENAME) \
  static Standard_Integer P_BASENAME ## _count = 1;

//! Initializes a scope of DRAW variables to store any type of entities.
//! Unlike DRAW_INITGROUP, it does not use static memory
#define DRAW_INITLOCALGROUP(P_BASENAME) \
  Standard_Integer P_BASENAME ## _count = 1;

//! Puts a unique variable representing a point into DRAW geometric
//! context (DrawTrSurf). Thus you're able to dump any points into the
//! DRAW viewer (non-OpenGL 2D or 3D) with some custom parameters like
//! rendering marker or color. Use it in the following way:
//!
//! #if defined DRAW_INITGROUP && defined DRAW_POINT
//!   DRAW_INITGROUP(some_unique_prefix_)
//!   DRAW_POINT(aPnt, some_unique_prefix_, Draw_blanc, Draw_X)
//! #endif
//!
//! Here,
//!
//! - P_ENTITY is your gp_Pnt or gp_Pnt2d variable;
//!
//! - P_BASENAME is some unique prefix for automatically generated
//!   name of the corresponding DRAW variable for your point. Note that
//!   this name must be previously registered via DRAW_INITGROUP invocation;
//!
//! - P_POINT_COLOR is a color to render your point,
//!   e.g. Draw_blanc   -- white,
//!        Draw_rouge   -- red,
//!        Draw_vert    -- green,
//!        Draw_bleu    -- blue,
//!        Draw_cyan    -- cyan,
//!        Draw_or      -- golden,
//!        Draw_magenta -- magenta,
//!        Draw_marron  -- brown,
//!        Draw_orange  -- orange,
//!        Draw_rose    -- pink,
//!        Draw_saumon  -- salmon,
//!        Draw_violet  -- violet,
//!        Draw_jaune   -- yellow,
//!        Draw_kaki    -- dark-olive green,
//!        Draw_corail  -- coral;
//!
//! - P_POINT_MARKER is a marker to render your point,
//!   e.g. Draw_Square,
//!        Draw_Losange,
//!        Draw_X,
//!        Draw_Plus,
//!        Draw_Circle,
//!        Draw_CircleZoom;
#define DRAW_POINT(P_ENTITY, P_BASENAME, P_POINT_COLOR, P_POINT_MARKER) \
  { \
    TCollection_AsciiString __debug_draw_BaseName(#P_BASENAME); \
    TCollection_AsciiString __debug_draw_EntityName = __debug_draw_BaseName.Cat( TCollection_AsciiString(SHIFT_INDEX + (P_BASENAME ## _count)++) ); \
    Draw_Color aPrevPntColor = DrawTrSurf_PointColor(P_POINT_COLOR); \
    Draw_MarkerShape aPrevPntMarker = DrawTrSurf_PointMarker(P_POINT_MARKER); \
    DrawTrSurf::Set(__debug_draw_EntityName.ToCString(), P_ENTITY); \
    DrawTrSurf_PointColor(aPrevPntColor); \
    DrawTrSurf_PointMarker(aPrevPntMarker); \
  }

// ------------------- [BEGIN]: EXPERIMENTAL: Rendering steps of algo ---------------- //

#define DRAW_INITSTEPGROUP(P_GROUPNAME, P_STEPNUM) \
  TopoDS_Compound aGroupCompound; \
  BRep_Builder aGroupBuilder; \
  aGroupBuilder.MakeCompound(aGroupCompound); \
  TCollection_AsciiString aDrawBaseName(#P_GROUPNAME); \
  TCollection_AsciiString aDrawName = aDrawBaseName.Cat( TCollection_AsciiString(P_STEPNUM) );

#define DRAW_DUMPSTEPGROUP(P_GROUPNAME) \
  DBRep::Set(aDrawName.ToCString(), aGroupCompound);

#define DRAW_POINTGROUP(P_ENTITY, P_BASENAME, P_POINT_COLOR, P_POINT_MARKER) \
  { \
    DRAW_POINT(P_ENTITY, P_BASENAME, P_POINT_COLOR, P_POINT_MARKER) \
    aGroupBuilder.Add( BRepBuilderAPI_MakeVertex(P_ENTITY), aGroupCompound ); \
  }

// ------------------- [END]: EXPERIMENTAL: Rendering steps of algo ------------------ //

//! Hides the entire group.
//!  - P_BASENAME -- group to hide;
//!  - P_NB_ENTITIES -- number of entities in the group;
//!  - P_DI -- Draw Interpreter;
//!
//! IMPORTANT: this function is VERY (!) slow as it erases entities one-by-one via DRAW interpreter.
#define DRAW_ERASE_GROUP(P_BASENAME, P_NB_ENTITIES, P_DI) \
  { \
    TCollection_AsciiString __debug_draw_BaseName(#P_BASENAME); \
    for ( Standard_Integer anIndex = 1; anIndex <= P_NB_ENTITIES; anIndex++ ) \
    { \
      TCollection_AsciiString __debug_draw_EntityName = __debug_draw_BaseName.Cat( TCollection_AsciiString(SHIFT_INDEX + anIndex) ); \
      TCollection_AsciiString __debug_draw_EraseCommand("erase "); \
      TCollection_AsciiString __debug_draw_EraseGroupCommand = __debug_draw_EraseCommand.Cat(__debug_draw_EntityName); \
      P_DI.Eval( __debug_draw_EraseGroupCommand.ToCString() ); \
    } \
  }

//! Draws a 2D line thru the passed 2D points (P_POINT1, P_POINT2).
//! The P_BASENAME must be previously registered via DRAW_INITGROUP invocation.
//!
//! Usage example:
//!
//! #ifdef DRAW_LINE2D
//!   DRAW_INITGROUP(emesh_quad_link_)
//!   DRAW_LINE2D(aPnt2d1, aPnt2d2, emesh_quad_link_, Draw_cyan)
//! #endif
#define DRAW_LINE2D(P_POINT1, P_POINT2, P_BASENAME, P_CURVE_COLOR) \
  { \
    Standard_Real aLen = P_POINT1.Distance(P_POINT2); \
    TCollection_AsciiString __debug_draw_BaseName(#P_BASENAME); \
    TCollection_AsciiString __debug_draw_EntityName = __debug_draw_BaseName.Cat( TCollection_AsciiString(SHIFT_INDEX + (P_BASENAME ## _count)++) ); \
    Draw_Color aPrevCurveColor = DrawTrSurf_CurveColor(P_CURVE_COLOR); \
    DrawTrSurf::Set( __debug_draw_EntityName.ToCString(), \
                     new Geom2d_TrimmedCurve(GCE2d_MakeLine(P_POINT1, P_POINT2), 0.0, aLen), \
                     Standard_False ); \
    DrawTrSurf_CurveColor(aPrevCurveColor); \
  }

//! Draws a 3D line thru the passed 3D points (P_POINT1, P_POINT2).
//! The P_BASENAME must be previously registered via DRAW_INITGROUP invocation.
//!
//! Usage example:
//!
//! #ifdef DRAW_LINE3D
//!   DRAW_INITGROUP(emesh_quad_link_)
//!   DRAW_LINE3D(aPnt1, aPnt2, emesh_tri_link_, Draw_bleu)
//! #endif
#define DRAW_LINE3D(P_POINT1, P_POINT2, P_BASENAME, P_CURVE_COLOR) \
  { \
    Standard_Real aLen = P_POINT1.Distance(P_POINT2); \
    TCollection_AsciiString __debug_draw_BaseName(#P_BASENAME); \
    TCollection_AsciiString __debug_draw_EntityName = __debug_draw_BaseName.Cat( TCollection_AsciiString(SHIFT_INDEX + (P_BASENAME ## _count)++) ); \
    Draw_Color aPrevCurveColor = DrawTrSurf_CurveColor(P_CURVE_COLOR); \
    DrawTrSurf::Set( __debug_draw_EntityName.ToCString(), \
                     new Geom_TrimmedCurve(new Geom_Line(gce_MakeLin(P_POINT1, P_POINT2)), 0.0, aLen), \
                     Standard_False ); \
    DrawTrSurf_CurveColor(aPrevCurveColor); \
  }

//! Draws a 3D triangle by three points (P_POINT1, P_POINT2, P_POINT3).
//! The links will be: P_POINT1 <---> P_POINT2,
//!                    P_POINT1 <---> P_POINT3,
//!                    P_POINT2 <---> P_POINT3;
#define DRAW_TRIANGLE3D(P_POINT1, P_POINT2, P_POINT3, P_BASENAME, P_COLOR) \
  { \
    DRAW_LINE3D(P_POINT1, P_POINT2, P_BASENAME, P_COLOR) \
    DRAW_LINE3D(P_POINT1, P_POINT3, P_BASENAME, P_COLOR) \
    DRAW_LINE3D(P_POINT2, P_POINT3, P_BASENAME, P_COLOR) \
  }

//! Draws a 3D quadrangle by four points (P_POINT1, P_POINT2, P_POINT3, P_POINT4).
//! The links will be: P_POINT1 <---> P_POINT2,
//!                    P_POINT2 <---> P_POINT3,
//!                    P_POINT3 <---> P_POINT4;
//!                    P_POINT4 <---> P_POINT1;
#define DRAW_QUADRANGLE3D(P_POINT1, P_POINT2, P_POINT3, P_POINT4, P_BASENAME, P_COLOR) \
  { \
    if ( P_POINT1.Distance(P_POINT2) > Precision::Confusion() ) \
    { \
      DRAW_LINE3D(P_POINT1, P_POINT2, P_BASENAME, P_COLOR) \
    } \
    if ( P_POINT2.Distance(P_POINT3) > Precision::Confusion() ) \
    { \
      DRAW_LINE3D(P_POINT2, P_POINT3, P_BASENAME, P_COLOR) \
    } \
    if ( P_POINT3.Distance(P_POINT4) > Precision::Confusion() ) \
    { \
      DRAW_LINE3D(P_POINT3, P_POINT4, P_BASENAME, P_COLOR) \
    } \
    if ( P_POINT4.Distance(P_POINT1) > Precision::Confusion() ) \
    { \
      DRAW_LINE3D(P_POINT4, P_POINT1, P_BASENAME, P_COLOR) \
    } \
  }

//! Externals for inline drawings
Standard_IMPORT Draw_Color DrawTrSurf_CurveColor(const Draw_Color col);
Standard_IMPORT Draw_Color DrawTrSurf_PointColor(const Draw_Color col);
Standard_IMPORT Draw_MarkerShape DrawTrSurf_PointMarker(const Draw_MarkerShape marker);

#endif
