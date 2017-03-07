//+-----------------------------------------------------------------------------
//
//  Copyright (c) Microsoft Corporation.  All rights reserved.
//
//  $Description:
//      Custom DirectWrite Text Renderer
//
//  $ENDTAG
//
//------------------------------------------------------------------------------

#pragma once

/******************************************************************
*                                                                 *
*  CustomTextRenderer                                             *
*                                                                 *
*  The IDWriteTextRenderer interface is an input parameter to     *
*  IDWriteTextLayout::Draw.  This interfaces defines a number of  *
*  callback functions that the client application implements for  *
*  custom text rendering.  This sample renderer implementation    *
*  renders text using text outlines and Direct2D.                 *
*  A more sophisticated client would also support bitmap          *
*  renderings.                                                    *
*                                                                 *
******************************************************************/

class CustomTextRenderer : public IDWriteTextRenderer
{
public:
    CustomTextRenderer(
        ID2D1Factory* pD2DFactory, 
        ID2D1HwndRenderTarget* pRT, 
        ID2D1SolidColorBrush* pOutlineBrush, 
        ID2D1BitmapBrush* pFillBrush
        );

    STDMETHOD(IsPixelSnappingDisabled)(
        __maybenull void* clientDrawingContext,
        __out BOOL* isDisabled
        );

    STDMETHOD(GetCurrentTransform)(
        __maybenull void* clientDrawingContext,
        __out DWRITE_MATRIX* transform
        );

    STDMETHOD(GetPixelsPerDip)(
        __maybenull void* clientDrawingContext,
        __out FLOAT* pixelsPerDip
        );

    STDMETHOD(DrawGlyphRun)(
        __maybenull void* clientDrawingContext,
        FLOAT baselineOriginX,
        FLOAT baselineOriginY,
        DWRITE_TEXT_MEASURING_METHOD measuringMethod,
        __in DWRITE_GLYPH_RUN const* glyphRun,
        __in DWRITE_GLYPH_RUN_DESCRIPTION const* glyphRunDescription,
        IUnknown* clientDrawingEffect
        );

    STDMETHOD(DrawUnderline)(
        __maybenull void* clientDrawingContext,
        FLOAT baselineOriginX,
        FLOAT baselineOriginY,
        __in DWRITE_UNDERLINE const* underline,
        IUnknown* clientDrawingEffect
        );

    STDMETHOD(DrawStrikethrough)(
        __maybenull void* clientDrawingContext,
        FLOAT baselineOriginX,
        FLOAT baselineOriginY,
        __in DWRITE_STRIKETHROUGH const* strikethrough,
        IUnknown* clientDrawingEffect
        );

    STDMETHOD(DrawInlineObject)(
        __maybenull void* clientDrawingContext,
        FLOAT originX,
        FLOAT originY,
        IDWriteInlineObject* inlineObject,
        BOOL isSideways,
        BOOL isRightToLeft,
        IUnknown* clientDrawingEffect
        );

public:
    unsigned long STDMETHODCALLTYPE AddRef();
    unsigned long STDMETHODCALLTYPE Release();
    HRESULT STDMETHODCALLTYPE QueryInterface(
        IID const& riid,
        void** ppvObject
    );

private:
    unsigned long m_cRefCount;
    ID2D1FactoryPtr m_spD2DFactory;
    ID2D1HwndRenderTargetPtr m_spRT;
    ID2D1SolidColorBrushPtr m_spOutlineBrush;
    ID2D1BitmapBrushPtr m_spFillBrush;
};
