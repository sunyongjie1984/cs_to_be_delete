//+-----------------------------------------------------------------------------
//
//  Copyright (c) Microsoft Corporation.  All rights reserved.
//
//  $Description:
//      Sample DirectWrite Application header file
//
//  $ENDTAG
//
//------------------------------------------------------------------------------
//
#pragma once

/******************************************************************
*                                                                 *
*  Macros                                                         *
*                                                                 *
******************************************************************/

#ifndef Assert
#if defined( DEBUG ) || defined( _DEBUG )
#define Assert(b) do {if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}} while(0)
#else
#define Assert(b)
#endif //DEBUG || _DEBUG
#endif

#ifndef IFR
#define IFR(expr) do {{hr = (expr); Assert(SUCCEEDED(hr)); if (FAILED(hr)) return(hr);}} while(0)
#endif

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))
#endif

/******************************************************************
*                                                                 *
*  Smart Pointer Typedefs                                         *
*                                                                 *
******************************************************************/

_COM_SMARTPTR_TYPEDEF(ID2D1Factory, __uuidof(ID2D1Factory));
_COM_SMARTPTR_TYPEDEF(IWICImagingFactory, __uuidof(IWICImagingFactory));
_COM_SMARTPTR_TYPEDEF(IDWriteFactory, __uuidof(IDWriteFactory));
_COM_SMARTPTR_TYPEDEF(ID2D1HwndRenderTarget, __uuidof(ID2D1HwndRenderTarget));
_COM_SMARTPTR_TYPEDEF(ID2D1DCRenderTarget, __uuidof(ID2D1DCRenderTarget));
_COM_SMARTPTR_TYPEDEF(ID2D1SolidColorBrush, __uuidof(ID2D1SolidColorBrush));
_COM_SMARTPTR_TYPEDEF(ID2D1LinearGradientBrush, __uuidof(ID2D1LinearGradientBrush));
_COM_SMARTPTR_TYPEDEF(ID2D1RenderTarget, __uuidof(ID2D1RenderTarget));
_COM_SMARTPTR_TYPEDEF(ID2D1LinearGradientBrush, __uuidof(ID2D1LinearGradientBrush));
_COM_SMARTPTR_TYPEDEF(ID2D1SolidColorBrush, __uuidof(ID2D1SolidColorBrush));
_COM_SMARTPTR_TYPEDEF(ID2D1Bitmap, __uuidof(ID2D1Bitmap));
_COM_SMARTPTR_TYPEDEF(ID2D1BitmapBrush, __uuidof(ID2D1BitmapBrush));
_COM_SMARTPTR_TYPEDEF(ID2D1GradientStopCollection, __uuidof(ID2D1GradientStopCollection));
_COM_SMARTPTR_TYPEDEF(IDWriteTextFormat, __uuidof(IDWriteTextFormat));
_COM_SMARTPTR_TYPEDEF(IDWriteTextLayout, __uuidof(IDWriteTextLayout));
_COM_SMARTPTR_TYPEDEF(IDWriteTypography, __uuidof(IDWriteTypography));
_COM_SMARTPTR_TYPEDEF(IDWriteTextRenderer, __uuidof(IDWriteTextRenderer));
_COM_SMARTPTR_TYPEDEF(ID2D1PathGeometry, __uuidof(ID2D1PathGeometry));
_COM_SMARTPTR_TYPEDEF(ID2D1TransformedGeometry, __uuidof(ID2D1TransformedGeometry));
_COM_SMARTPTR_TYPEDEF(ID2D1RectangleGeometry, __uuidof(ID2D1RectangleGeometry));
_COM_SMARTPTR_TYPEDEF(ID2D1GeometrySink, __uuidof(ID2D1GeometrySink));
_COM_SMARTPTR_TYPEDEF(ID2D1GradientStopCollection, __uuidof(ID2D1GradientStopCollection));
_COM_SMARTPTR_TYPEDEF(IWICBitmapDecoder, __uuidof(IWICBitmapDecoder));
_COM_SMARTPTR_TYPEDEF(IWICBitmapFrameDecode, __uuidof(IWICBitmapFrameDecode));
_COM_SMARTPTR_TYPEDEF(IWICStream, __uuidof(IWICStream));
_COM_SMARTPTR_TYPEDEF(IWICFormatConverter, __uuidof(IWICFormatConverter));

/******************************************************************
*                                                                 *
*  DemoApp                                                        *
*                                                                 *
******************************************************************/

class DemoApp
{
public:
    DemoApp();
    ~DemoApp();

    HRESULT Initialize();

    void RunMessageLoop();

private:
    HRESULT CreateDeviceIndependentResources(
        );

    void DiscardDeviceIndependentResources(
        );

    HRESULT CreateDeviceResources(
        );

    void DiscardDeviceResources(
        );

    HRESULT OnRender(
        const PAINTSTRUCT &ps
        );

    HRESULT DrawD2DContent(
        const PAINTSTRUCT &ps
        );

    HRESULT LoadResourceBitmap(
        ID2D1RenderTarget *pRT,
        IWICImagingFactory *pIWICFactory,
        PCWSTR resourceName,
        PCWSTR resourceType,
        __deref_out ID2D1Bitmap **ppBitmap
    );

    void DrawText(
        );

    void DrawTextLayout(
        );

    HRESULT DrawTextLayoutUsingGeometries(
        );

    void OnResize(
        UINT width,
        UINT height
        );

    static LRESULT CALLBACK WndProc(
        HWND hWnd,
        UINT message,
        WPARAM wParam,
        LPARAM lParam
        );

private:
    HWND m_hwnd;

    // WIC
    IWICImagingFactoryPtr m_spWICFactory;

    // From Direct2D HOL
    ID2D1FactoryPtr m_spD2DFactory;
    ID2D1HwndRenderTargetPtr m_spRT;
    ID2D1SolidColorBrushPtr m_spBlackBrush;
    ID2D1BitmapBrushPtr m_spBitmapBrush;

    // DWrite
    const wchar_t* m_wszHelloWorld;
    UINT32 m_cHelloWorldLength;
    IDWriteFactoryPtr m_spDWriteFactory;
    IDWriteTextFormatPtr m_spTextFormat;
    IDWriteTextLayoutPtr m_spTextLayout;
    IDWriteTextRendererPtr m_spTextRenderer;
};
