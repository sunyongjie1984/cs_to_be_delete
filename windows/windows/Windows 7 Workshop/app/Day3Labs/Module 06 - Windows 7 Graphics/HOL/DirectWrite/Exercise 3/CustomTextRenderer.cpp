//+-----------------------------------------------------------------------------
//
//  Copyright (c) Microsoft Corporation.  All rights reserved.
//
//  $Description:
//      Custom DirectWrite Text Renderer implementation
//
//  $ENDTAG
//
//------------------------------------------------------------------------------

#include "stdafx.h"

/******************************************************************
*                                                                 *
*  CustomTextRenderer::CustomTextRenderer                         *
*                                                                 *
*  The constructor stores the Direct2D factory, the render        *
*  target, and the outline and fill brushes used for drawing the  *
*  glyphs, underlines, and strikethroughs.                        *
*                                                                 *
******************************************************************/

CustomTextRenderer::CustomTextRenderer(
    ID2D1Factory* pD2DFactory, 
    ID2D1HwndRenderTarget* pRT, 
    ID2D1SolidColorBrush* pOutlineBrush, 
    ID2D1BitmapBrush* pFillBrush
    )
:
m_cRefCount(0), 
m_spD2DFactory(pD2DFactory), 
m_spRT(pRT), 
m_spOutlineBrush(pOutlineBrush), 
m_spFillBrush(pFillBrush)
{
}

/******************************************************************
*                                                                 *
*  CustomTextRenderer::DrawGlyphRun                               *
*                                                                 *
*  Gets GlyphRun outlines via IDWriteFontFace::GetGlyphRunOutline *
*  and then draws and fills them using Direct2D path geometries   *
*                                                                 *
******************************************************************/

STDMETHODIMP CustomTextRenderer::DrawGlyphRun(
    __maybenull void* clientDrawingContext,
    FLOAT baselineOriginX,
    FLOAT baselineOriginY,
    DWRITE_TEXT_MEASURING_METHOD measuringMethod,
    __in DWRITE_GLYPH_RUN const* glyphRun,
    __in DWRITE_GLYPH_RUN_DESCRIPTION const* glyphRunDescription,
    IUnknown* clientDrawingEffect
    )
{
    HRESULT hr = S_OK;

    // Exercise 3, Step 1
    // Create the path geometry.
    ID2D1PathGeometryPtr pPathGeometry;
    IFR(m_spD2DFactory->CreatePathGeometry(
        &pPathGeometry
        ));

    // Exercise 3, Step 2
    // Write to the path geometry using the geometry sink.
    ID2D1GeometrySinkPtr pSink;
    IFR(pPathGeometry->Open(
        &pSink
        ));

    // Exercise 3, Step 3
    // Get the glyph run outline geometries back from DirectWrite and place thew within the
    // geometry sink
    IFR(glyphRun->fontFace->GetGlyphRunOutline(
        glyphRun->fontEmSize,
        glyphRun->glyphIndices,
        glyphRun->glyphAdvances,
        glyphRun->glyphOffsets,
        glyphRun->glyphCount,
        glyphRun->isSideways,
        glyphRun->bidiLevel%2,
        pSink
        ));


    // Exercise 3, Step 4
    // Close the geometry sink
    IFR(pSink->Close());

    // Exercise 3, Step 5
    // Initialize a matrix to translate the origin of the glyph run.
    D2D1::Matrix3x2F const matrix = D2D1::Matrix3x2F(
        1.0f, 0.0f,
        0.0f, 1.0f,
        baselineOriginX, baselineOriginY
        );

    // Exercise 3, Step 6
    // Create the transformed geometry
    ID2D1TransformedGeometryPtr pTransformedGeometry;
    IFR(m_spD2DFactory->CreateTransformedGeometry(
        pPathGeometry,
        &matrix,
        &pTransformedGeometry
        ));

    // Exercise 3, Step 7
    // Draw the outline of the glyph run
    m_spRT->DrawGeometry(
        pTransformedGeometry,
        m_spOutlineBrush
        );

    // Exercise 3, Step 8
    // Fill in the glyph run
    m_spRT->FillGeometry(
        pTransformedGeometry,
        m_spFillBrush
        );

    return hr;
}

/******************************************************************
*                                                                 *
*  CustomTextRenderer::DrawUnderline                              *
*                                                                 *
*  Draws underlines below the text using a Direct2D recatangle    *
*  geometry                                                       *
*                                                                 *
******************************************************************/

STDMETHODIMP CustomTextRenderer::DrawUnderline(
    __maybenull void* clientDrawingContext,
    FLOAT baselineOriginX,
    FLOAT baselineOriginY,
    __in DWRITE_UNDERLINE const* underline,
    IUnknown* clientDrawingEffect
    )
{
    HRESULT hr;

    D2D1_RECT_F rect = D2D1::RectF(
        0,
        underline->offset,
        underline->width,
        underline->offset + underline->thickness
        );

    ID2D1RectangleGeometryPtr pRectangleGeometry;
    IFR(m_spD2DFactory->CreateRectangleGeometry(
        &rect, 
        &pRectangleGeometry
        ));

    // Initialize a matrix to translate the origin of the underline
    D2D1::Matrix3x2F const matrix = D2D1::Matrix3x2F(
        1.0f, 0.0f,
        0.0f, 1.0f,
        baselineOriginX, baselineOriginY
        );

    ID2D1TransformedGeometryPtr pTransformedGeometry;
    IFR(m_spD2DFactory->CreateTransformedGeometry(
        pRectangleGeometry,
        &matrix,
        &pTransformedGeometry
        ));

    // Draw the outline of the rectangle
    m_spRT->DrawGeometry(
        pTransformedGeometry,
        m_spOutlineBrush
        );

    // Fill in the rectangle
    m_spRT->FillGeometry(
        pTransformedGeometry,
        m_spFillBrush
        );

    return S_OK;
}

/******************************************************************
*                                                                 *
*  CustomTextRenderer::DrawStrikethrough                          *
*                                                                 *
*  Draws strikethroughs below the text using a Direct2D           *
*  recatangle geometry                                            *
*                                                                 *
******************************************************************/

STDMETHODIMP CustomTextRenderer::DrawStrikethrough(
    __maybenull void* clientDrawingContext,
    FLOAT baselineOriginX,
    FLOAT baselineOriginY,
    __in DWRITE_STRIKETHROUGH const* strikethrough,
    IUnknown* clientDrawingEffect
    )
{
    HRESULT hr;

    D2D1_RECT_F rect = D2D1::RectF(
        0,
        strikethrough->offset,
        strikethrough->width,
        strikethrough->offset + strikethrough->thickness
        );

    ID2D1RectangleGeometryPtr pRectangleGeometry;
    IFR(m_spD2DFactory->CreateRectangleGeometry(
        &rect, 
        &pRectangleGeometry
        ));

    // Initialize a matrix to translate the origin of the strikethrough
    D2D1::Matrix3x2F const matrix = D2D1::Matrix3x2F(
        1.0f, 0.0f,
        0.0f, 1.0f,
        baselineOriginX, baselineOriginY
        );

    ID2D1TransformedGeometryPtr pTransformedGeometry;
    IFR(m_spD2DFactory->CreateTransformedGeometry(
        pRectangleGeometry,
        &matrix,
        &pTransformedGeometry
        ));

    // Draw the outline of the rectangle
    m_spRT->DrawGeometry(
        pTransformedGeometry,
        m_spOutlineBrush
        );

    // Fill in the rectangle
    m_spRT->FillGeometry(
        pTransformedGeometry,
        m_spFillBrush
        );

    return S_OK;
}

/******************************************************************
*                                                                 *
*  CustomTextRenderer::DrawInlineObject                           *
*                                                                 *
*  This function is not implemented for the purposes of this lab. *
*                                                                 *
******************************************************************/

STDMETHODIMP CustomTextRenderer::DrawInlineObject(
    __maybenull void* clientDrawingContext,
    FLOAT originX,
    FLOAT originY,
    IDWriteInlineObject* inlineObject,
    BOOL isSideways,
    BOOL isRightToLeft,
    IUnknown* clientDrawingEffect
    )
{
    // Not implemented
    return E_NOTIMPL;
}

/******************************************************************
*                                                                 *
*  CustomTextRenderer::AddRef                                     *
*                                                                 *
*  Increments the ref count                                       *
*                                                                 *
******************************************************************/

STDMETHODIMP_(unsigned long) CustomTextRenderer::AddRef()
{
    return InterlockedIncrement(&m_cRefCount);
}

/******************************************************************
*                                                                 *
*  CustomTextRenderer::Release                                    *
*                                                                 *
*  Decrements the ref count and deletes the instance if the ref   *
*  count becomes 0                                                *
*                                                                 *
******************************************************************/

STDMETHODIMP_(unsigned long) CustomTextRenderer::Release()
{
    if (InterlockedDecrement(&m_cRefCount) == 0)
    {
        delete this;
        return 0;
    }

    return m_cRefCount;
}

/******************************************************************
*                                                                 *
*  CustomTextRenderer::IsPixelSnappingDisabled                    *
*                                                                 *
*  Determines whether pixel snapping is disabled. The recommended *
*  default is FALSE, unless doing animation that requires         *
*  subpixel vertical placement.                                   *
*                                                                 *
******************************************************************/

STDMETHODIMP CustomTextRenderer::IsPixelSnappingDisabled(
    __maybenull void* clientDrawingContext,
    __out BOOL* isDisabled
    )
{
    *isDisabled = FALSE;
    return S_OK;
}

/******************************************************************
*                                                                 *
*  CustomTextRenderer::GetCurrentTransform                        *
*                                                                 *
*  Returns the current transform applied to the render target..   *
*                                                                 *
******************************************************************/

STDMETHODIMP CustomTextRenderer::GetCurrentTransform(
    __maybenull void* clientDrawingContext,
    __out DWRITE_MATRIX* transform
    )
{
    //forward the render target's transform
    m_spRT->GetTransform(reinterpret_cast<D2D1_MATRIX_3X2_F*>(transform));
    return S_OK;
}

/******************************************************************
*                                                                 *
*  CustomTextRenderer::GetPixelsPerDip                            *
*                                                                 *
*  This returns the number of pixels per DIP.                     *
*                                                                 *
******************************************************************/

STDMETHODIMP CustomTextRenderer::GetPixelsPerDip(
    __maybenull void* clientDrawingContext,
    __out FLOAT* pixelsPerDip
    )
{
    *pixelsPerDip = 1.0f;
    return S_OK;
}

/******************************************************************
*                                                                 *
*  CustomTextRenderer::QueryInterface                             *
*                                                                 *
*  Query interface implementation                                 *
*                                                                 *
******************************************************************/

STDMETHODIMP CustomTextRenderer::QueryInterface(
    IID const& riid,
    void** ppvObject
    )
{
    if (__uuidof(IDWriteTextRenderer) == riid)
    {
        *ppvObject = dynamic_cast<IDWriteTextRenderer*>(this);
    }
    else if (__uuidof(IDWritePixelSnapping) == riid)
    {
        *ppvObject = dynamic_cast<IDWritePixelSnapping*>(this);
    }
    else if (__uuidof(IUnknown) == riid)
    {
        *ppvObject = dynamic_cast<IUnknown*>(this);
    }
    else
    {
        *ppvObject = NULL;
        return E_FAIL;
    }

    return S_OK;
}
