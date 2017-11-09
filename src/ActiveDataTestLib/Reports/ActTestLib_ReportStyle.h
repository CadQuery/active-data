//-----------------------------------------------------------------------------
// Created on: 26 November 2013
//-----------------------------------------------------------------------------
// Copyright (c) 2017, OPEN CASCADE SAS
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. All advertising materials mentioning features or use of this software
//    must display the following acknowledgement:
//    This product includes software developed by the OPEN CASCADE SAS.
// 4. Neither the name of the OPEN CASCADE SAS nor the
//    names of its contributors may be used to endorse or promote products
//    derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY OPEN CASCADE SAS ''AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL OPEN CASCADE SAS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Web: http://dev.opencascade.org
//-----------------------------------------------------------------------------

#ifndef ActTestLib_ReportStyle_HeaderFile
#define ActTestLib_ReportStyle_HeaderFile

// ActTestLib includes
#include <ActTestLib_ReportTag.h>

//! Structure embodying HTML styling support.
class ActTestLib_ReportStyle
{
public:

  //! Color components.
  struct Color
  {
    int R; //!< Red.
    int G; //!< Green.
    int B; //!< Blue.

    //! Default constructor.
    Color() : R(0), G(0), B(0) {}

    //! Complete constructor.
    //! \param r [in] red component in range [0;255].
    //! \param g [in] green component in range [0;255].
    //! \param b [in] blue component in range [0;255].
    Color(const int r, const int g, const int b) : R(r), G(g), B(b) {}

    //! Copy constructor.
    //! \param color [in] another color to copy data from.
    Color(const Color& color) {this->operator=(color);}

    //! Assignment operator.
    //! \param color [in] another color to copy data from.
    //! \return this.
    Color& operator=(const Color& color) {R = color.R; G = color.G; B = color.B; return *this;}
  };

public:

  //! Enumerates supported font weights.
  enum FontWeight
  {
    FW_Bold,
    FW_Normal
  };

  //! Enumerates supported font styles.
  enum FontStyle
  {
    FS_Normal,
    FS_Italic
  };

  //! Enumerates supported text alignment.
  enum TextAlign
  {
    TA_Center,
    TA_Justify,
    TA_Left,
    TA_Right
  };

  //! Enumerates supported vertical alignment.
  enum VertAlign
  {
    VA_Bottom,
    VA_Middle,
    VA_Top
  };

public:

  ActTestLib_EXPORT
    ActTestLib_ReportStyle();

  ActTestLib_EXPORT
    ActTestLib_ReportStyle(int);

  ActTestLib_EXPORT
    ActTestLib_ReportStyle(const ActTestLib_ReportStyle& copy);

  ActTestLib_EXPORT virtual
    ~ActTestLib_ReportStyle();

public:

  ActTestLib_EXPORT ActTestLib_ReportStyle&
    operator=(const ActTestLib_ReportStyle& other);

  ActTestLib_EXPORT bool
    IsNull() const;

public:

  ActTestLib_EXPORT void
    SetBorder(const int px);

  ActTestLib_EXPORT void
    SetBgColor(const Color& color);

  ActTestLib_EXPORT void
    SetColor(const Color& color);

  ActTestLib_EXPORT void
    SetFontFamily(const std::string& family);

  ActTestLib_EXPORT void
    SetFontSize(const int px);

  ActTestLib_EXPORT void
    SetFontWeight(const FontWeight weight);

  ActTestLib_EXPORT void
    SetFontStyle(const FontStyle style);

  ActTestLib_EXPORT void
    SetTextAlignment(const TextAlign align);

  ActTestLib_EXPORT void
    SetVerticalAlignment(const VertAlign align);

  ActTestLib_EXPORT void
    SetPadding(const int px);

  ActTestLib_EXPORT void
    SetWidth(const std::string& width);

public:

  ActTestLib_EXPORT virtual void
    ApplyStyles(ActTestLib_ReportTag& tag) const;

  ActTestLib_EXPORT virtual std::string
    MakeDescriptor() const;

protected:

  ActTestLib_EXPORT const char*
    getFontStyle(const FontStyle style) const;

  ActTestLib_EXPORT const char*
    getFontWeight(const FontWeight weight) const;

  ActTestLib_EXPORT const char*
    getTextAlignCSS(const TextAlign align) const;

  ActTestLib_EXPORT const char*
    getVertAlignCSS(const VertAlign align) const;

  ActTestLib_EXPORT void
    nullify(const bool release = false);

  ActTestLib_EXPORT void
    deepCopy(const ActTestLib_ReportStyle& other);

private:

  //! Style descriptor.
  struct TProps
  {
    inline bool IsBorder()     const { return (pPxBorder   != NULL); }
    inline bool IsBgColor()    const { return (pBgColor    != NULL); }
    inline bool IsColor()      const { return (pColor      != NULL); }
    inline bool IsFontFamily() const { return (pFontFamily != NULL); }
    inline bool IsFontSize()   const { return (pPxFont     != NULL); }
    inline bool IsFontWeight() const { return (pFontWeight != NULL); }
    inline bool IsFontStyle()  const { return (pFontStyle  != NULL); }
    inline bool IsTextAlign()  const { return (pTextAlign  != NULL); }
    inline bool IsVertAlign()  const { return (pVertAlign  != NULL); }
    inline bool IsPadding()    const { return (pPxPadding  != NULL); }
    inline bool IsWidth()      const { return (pWidth      != NULL); }

    //! Default constructor.
    TProps() : pPxBorder(NULL),
               pPxPadding(NULL),
               pPxFont(NULL),
               pBgColor(NULL),
               pColor(NULL),
               pFontFamily(NULL),
               pFontWeight(NULL),
               pFontStyle(NULL),
               pTextAlign(NULL),
               pVertAlign(NULL),
               pWidth(NULL) {}

    //! Returns true if all properties are nulls.
    //! \return true/false.
    bool IsNull() const
    {
      if ( !pPxBorder &&
           !pPxPadding &&
           !pPxFont &&
           !pBgColor &&
           !pColor &&
           !pFontFamily &&
           !pFontWeight &&
           !pFontStyle &&
           !pTextAlign &&
           !pVertAlign &&
           !pWidth )
        return true;

      return false;
    }

    int*         pPxBorder;
    int*         pPxPadding;
    int*         pPxFont;
    Color*       pBgColor;
    Color*       pColor;
    std::string* pFontFamily;
    FontWeight*  pFontWeight;
    FontStyle*   pFontStyle;
    TextAlign*   pTextAlign;
    VertAlign*   pVertAlign;
    std::string* pWidth;
  };

  //! Actual properties.
  TProps m_props;
};

#endif
