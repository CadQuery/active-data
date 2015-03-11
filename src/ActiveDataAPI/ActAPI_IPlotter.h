//-----------------------------------------------------------------------------
// Created on: April 2016
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

#ifndef ActAPI_IPlotter_HeaderFile
#define ActAPI_IPlotter_HeaderFile

// Active Data (API) includes
#include <ActAPI_Common.h>

// OCCT includes
#include <Quantity_Color.hxx>

// Forward declarations
class Geom_Curve;
class Geom_Plane;
class Geom_Surface;
class Poly_Triangulation;

//-----------------------------------------------------------------------------

#define Color_Red     Quantity_Color(Quantity_NOC_RED)
#define Color_Green   Quantity_Color(Quantity_NOC_GREEN)
#define Color_Blue    Quantity_Color(Quantity_NOC_BLUE1)
#define Color_Yellow  Quantity_Color(Quantity_NOC_YELLOW)
#define Color_White   Quantity_Color(Quantity_NOC_WHITE)
#define Color_Black   Quantity_Color(Quantity_NOC_BLACK)
#define Color_Violet  Quantity_Color(Quantity_NOC_VIOLET)
#define Color_Magenta Quantity_Color(Quantity_NOC_MAGENTA1)

//-----------------------------------------------------------------------------

DEFINE_STANDARD_HANDLE(ActAPI_IPlotter, Standard_Transient)

//! \ingroup AD_API
//!
//! Interface for Imperative Viewer. A particular algorithm may benefit
//! from immediate plotting of its geometric variables in a unified way
//! thanks to this abstract class.
class ActAPI_IPlotter : public Standard_Transient
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActAPI_IPlotter, Standard_Transient)

public:

  ActAPI_EXPORT static Quantity_NameOfColor
    Color_Sparse(const int index);

public:

  ActAPI_EXPORT virtual
    ~ActAPI_IPlotter();

// COMMON:
public:

  virtual void
    CLEAN() = 0;

// GEOMETRY:
public:

  virtual void
    DRAW_POINT(const gp_XY&,
               const Quantity_Color&,
               const TCollection_AsciiString&) = 0;

  virtual void
    DRAW_POINT(const gp_Pnt2d&,
               const Quantity_Color&,
               const TCollection_AsciiString&) = 0;

  virtual void
    DRAW_POINT(const gp_XYZ&,
               const Quantity_Color&,
               const TCollection_AsciiString&) = 0;

  virtual void
    DRAW_POINT(const gp_Pnt&,
               const Quantity_Color&,
               const TCollection_AsciiString&) = 0;

  virtual void
    DRAW_POINTS(const Handle(HRealArray)&,
                const Quantity_Color&,
                const TCollection_AsciiString&) = 0;

  virtual void
    DRAW_LINK(const gp_Pnt&,
              const gp_Pnt&,
              const Quantity_Color&,
              const TCollection_AsciiString&) = 0;

  virtual void
    DRAW_VECTOR_AT(const gp_Pnt&,
                   const gp_Vec&,
                   const Quantity_Color&,
                   const TCollection_AsciiString&) = 0;

  virtual void
    DRAW_CURVE(const Handle(Geom_Curve)&,
               const Quantity_Color&,
               const TCollection_AsciiString&) = 0;

  virtual void
    DRAW_SURFACE(const Handle(Geom_Surface)&,
                 const Quantity_Color&,
                 const TCollection_AsciiString&) = 0;

  virtual void
    DRAW_SURFACE(const Handle(Geom_Surface)&,
                 const Quantity_Color&,
                 const double, // opacity
                 const TCollection_AsciiString&) = 0;

  virtual void
    DRAW_SURFACE(const Handle(Geom_Surface)&,
                 const double, // U limit
                 const double, // V limit
                 const Quantity_Color&,
                 const TCollection_AsciiString&) = 0;

  virtual void
    DRAW_SURFACE(const Handle(Geom_Surface)&,
                 const double, // U limit
                 const double, // V limit
                 const Quantity_Color&,
                 const double, // opacity
                 const TCollection_AsciiString&) = 0;

// TOPOLOGY:
public:

  virtual void
    DRAW_SHAPE(const TopoDS_Shape&,
               const TCollection_AsciiString&) = 0;

  virtual void
    DRAW_SHAPE(const TopoDS_Shape&,
               const Quantity_Color&,
               const TCollection_AsciiString&) = 0;

  virtual void
    DRAW_SHAPE(const TopoDS_Shape&,
               const double, // opacity
               const TCollection_AsciiString&) = 0;

  virtual void
    DRAW_SHAPE(const TopoDS_Shape&,
               const Quantity_Color&,
               const double, // opacity
               const TCollection_AsciiString&) = 0;

  virtual void
    DRAW_SHAPE(const TopoDS_Shape&,
               const Quantity_Color&,
               const double, // opacity
               const bool, // is wireframe
               const TCollection_AsciiString&) = 0;

// TRIANGULATION:
public:

  virtual void
    DRAW_TRIANGULATION(const Handle(Poly_Triangulation)&,
                       const Quantity_Color&,
                       const double, // opacity
                       const TCollection_AsciiString&) = 0;

// TEXT
public:

  virtual void
    DRAW_TEXT(const TCollection_AsciiString&) = 0;

};

//-----------------------------------------------------------------------------

//! \ingroup AD_API
//!
//! Safe entry to IV.
class ActAPI_PlotterEntry
{
public:

  //! Default constructor.
  ActAPI_PlotterEntry() {}

  //! Dummy conversion constructor.
  ActAPI_PlotterEntry(Standard_Integer) {}

  //! Constructor.
  //! \param iv [in] IV to wrap.
  ActAPI_PlotterEntry(const Handle(ActAPI_IPlotter)& iv) : m_iv(iv) {}

public:

  //! \return Journal instance.
  const Handle(ActAPI_IPlotter)& Plotter() const { return m_iv; }

public:

//---------------------------------------------------------------------------//

  void
    CLEAN()
  {
    if ( m_iv.IsNull() ) return;
    //
    m_iv->CLEAN();
  }

//---------------------------------------------------------------------------//

  void
    DRAW_POINT(const gp_XY&                   coord,
               const Quantity_Color&          color,
               const TCollection_AsciiString& name = "")
  {
    if ( m_iv.IsNull() ) return;
    //
    m_iv->DRAW_POINT(coord, color, name);
  }

//---------------------------------------------------------------------------//

  void
    DRAW_POINT(const gp_Pnt2d&                point,
               const Quantity_Color&          color,
               const TCollection_AsciiString& name = "")
  {
    if ( m_iv.IsNull() ) return;
    //
    m_iv->DRAW_POINT(point, color, name);
  }

//---------------------------------------------------------------------------//

  void
    DRAW_POINT(const gp_XYZ&                  coord,
               const Quantity_Color&          color,
               const TCollection_AsciiString& name = "")
  {
    if ( m_iv.IsNull() ) return;
    //
    m_iv->DRAW_POINT(coord, color, name);
  }

//---------------------------------------------------------------------------//

  void
    DRAW_POINT(const gp_Pnt&                  point,
               const Quantity_Color&          color,
               const TCollection_AsciiString& name = "")
  {
    if ( m_iv.IsNull() ) return;
    //
    m_iv->DRAW_POINT(point, color, name);
  }

//---------------------------------------------------------------------------//

  void
    DRAW_POINTS(const Handle(HRealArray)&      coords,
                const Quantity_Color&          color,
                const TCollection_AsciiString& name = "")
  {
    if ( m_iv.IsNull() ) return;
    //
    m_iv->DRAW_POINTS(coords, color, name);
  }

//---------------------------------------------------------------------------//

  void
    DRAW_LINK(const gp_Pnt&                  p1,
              const gp_Pnt&                  p2,
              const Quantity_Color&          color,
              const TCollection_AsciiString& name = "")
  {
    if ( m_iv.IsNull() ) return;
    //
    m_iv->DRAW_LINK(p1, p2, color, name);
  }

//---------------------------------------------------------------------------//

  void
    DRAW_VECTOR_AT(const gp_Pnt&                  P,
                   const gp_Vec&                  V,
                   const Quantity_Color&          color,
                   const TCollection_AsciiString& name = "")
  {
    if ( m_iv.IsNull() ) return;
    //
    m_iv->DRAW_VECTOR_AT(P, V, color, name);
  }

//---------------------------------------------------------------------------//

  void
    DRAW_CURVE(const Handle(Geom_Curve)&      curve,
               const Quantity_Color&          color,
               const TCollection_AsciiString& name = "")
  {
    if ( m_iv.IsNull() ) return;
    //
    m_iv->DRAW_CURVE(curve, color, name);
  }

//---------------------------------------------------------------------------//

  void
    DRAW_SURFACE(const Handle(Geom_Surface)&    surface,
                 const Quantity_Color&          color,
                 const TCollection_AsciiString& name = "")
  {
    if ( m_iv.IsNull() ) return;
    //
    m_iv->DRAW_SURFACE(surface, color, name);
  }

//---------------------------------------------------------------------------//

  void
    DRAW_SURFACE(const Handle(Geom_Surface)&    surface,
                 const Quantity_Color&          color,
                 const double                   opacity,
                 const TCollection_AsciiString& name = "")
  {
    if ( m_iv.IsNull() ) return;
    //
    m_iv->DRAW_SURFACE(surface, color, opacity, name);
  }

//---------------------------------------------------------------------------//

  void
    DRAW_SURFACE(const Handle(Geom_Surface)&    surface,
                 const double                   uLimit,
                 const double                   vLimit,
                 const Quantity_Color&          color,
                 const TCollection_AsciiString& name = "")
  {
    if ( m_iv.IsNull() ) return;
    //
    m_iv->DRAW_SURFACE(surface, uLimit, vLimit, color, name);
  }

//---------------------------------------------------------------------------//

  void
    DRAW_SURFACE(const Handle(Geom_Surface)&    surface,
                 const double                   uLimit,
                 const double                   vLimit,
                 const Quantity_Color&          color,
                 const double                   opacity,
                 const TCollection_AsciiString& name = "")
  {
    if ( m_iv.IsNull() ) return;
    //
    m_iv->DRAW_SURFACE(surface, uLimit, vLimit, color, opacity, name);
  }

//---------------------------------------------------------------------------//

  void
    DRAW_SHAPE(const TopoDS_Shape&            shape,
               const TCollection_AsciiString& name = "")
  {
    if ( m_iv.IsNull() ) return;
    //
    m_iv->DRAW_SHAPE(shape, name);
  }

//---------------------------------------------------------------------------//

  void
    DRAW_SHAPE(const TopoDS_Shape&            shape,
               const Quantity_Color&          color,
               const TCollection_AsciiString& name = "")
  {
    if ( m_iv.IsNull() ) return;
    //
    m_iv->DRAW_SHAPE(shape, color, name);
  }

//---------------------------------------------------------------------------//

  void
    DRAW_SHAPE(const TopoDS_Shape&            shape,
               const double                   opacity,
               const TCollection_AsciiString& name = "")
  {
    if ( m_iv.IsNull() ) return;
    //
    m_iv->DRAW_SHAPE(shape, opacity, name);
  }

//---------------------------------------------------------------------------//

  void
    DRAW_SHAPE(const TopoDS_Shape&            shape,
               const Quantity_Color&          color,
               const double                   opacity,
               const TCollection_AsciiString& name = "")
  {
    if ( m_iv.IsNull() ) return;
    //
    m_iv->DRAW_SHAPE(shape, color, opacity, name);
  }

//---------------------------------------------------------------------------//

  void
    DRAW_SHAPE(const TopoDS_Shape&            shape,
               const Quantity_Color&          color,
               const double                   opacity,
               const bool                     isWireframe,
               const TCollection_AsciiString& name = "")
  {
    if ( m_iv.IsNull() ) return;
    //
    m_iv->DRAW_SHAPE(shape, color, opacity, isWireframe, name);
  }

//---------------------------------------------------------------------------//

  void
    DRAW_TRIANGULATION(const Handle(Poly_Triangulation)& tess,
                       const Quantity_Color&             color,
                       const double                      opacity,
                       const TCollection_AsciiString&    name = "")
  {
    if ( m_iv.IsNull() ) return;
    //
    m_iv->DRAW_TRIANGULATION(tess, color, opacity, name);
  }

//---------------------------------------------------------------------------//

  void
    DRAW_TEXT(const TCollection_AsciiString& text)
  {
    if ( m_iv.IsNull() ) return;
    //
    m_iv->DRAW_TEXT(text);
  }

//---------------------------------------------------------------------------//

private:

  Handle(ActAPI_IPlotter) m_iv; //!< IV instance.

};

#endif
