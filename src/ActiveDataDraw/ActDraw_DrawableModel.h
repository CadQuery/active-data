//-----------------------------------------------------------------------------
// Created on: January 2016
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

#ifndef ActDraw_DrawableModel_HeaderFile
#define ActDraw_DrawableModel_HeaderFile

// Active Data Draw includes
#include <ActDraw_Common.h>
#include <ActDraw_DummyModel.h>

// OCCT includes
#include <Draw_Drawable3D.hxx>

DEFINE_STANDARD_HANDLE(ActDraw_DrawableModel, Draw_Drawable3D)

//! \ingroup AD_DRAW
//!
//! Drawable for Data Model.
class ActDraw_DrawableModel : public Draw_Drawable3D
{
public:

  // OCCT RTTI
  DEFINE_STANDARD_RTTI_INLINE(ActDraw_DrawableModel, Draw_Drawable3D)

public:

  ActDraw_EXPORT
    ActDraw_DrawableModel(const Handle(ActDraw_DummyModel)& M);

public:

  //! Sets Data Model.
  //! \param M [in] Model to set.
  inline void SetModel(const Handle(ActDraw_DummyModel)& M)
  {
    m_model = M;
  }

  //! Accessor for the underlying Data Model.
  //! \return Data Model.
  inline Handle(ActDraw_DummyModel) Model() const
  {
    return m_model;
  }

public:

  ActDraw_EXPORT virtual void
    DrawOn(Draw_Display& D) const;

private:

  Handle(ActDraw_DummyModel) m_model; //!< Wrapped Data Model instance.

};

#endif
