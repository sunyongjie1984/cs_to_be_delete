//+-----------------------------------------------------------------------------
//
//  Copyright (c) Microsoft Corporation.  All rights reserved.
//
//  $Description:
//      Sample DirectWrite Application
//
//  $ENDTAG
//
//------------------------------------------------------------------------------

#include "stdafx.h"

/******************************************************************
*                                                                 *
*  WinMain                                                        *
*                                                                 *
*  Application entrypoint                                         *
*                                                                 *
******************************************************************/

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    HRESULT hr;
    if (SUCCEEDED(CoInitialize(NULL)))
    {
        {
            DemoApp app;

            if (SUCCEEDED(hr = app.Initialize()))
            {
                app.RunMessageLoop();
            }
        }
        CoUninitialize();
    }

    return SUCCEEDED(hr) ? EXIT_SUCCESS : EXIT_FAILURE;
}

/******************************************************************
*                                                                 *
*  DemoApp::DemoApp constructor                                   *
*                                                                 *
*  Initialize member data                                         *
*                                                                 *
******************************************************************/

DemoApp::DemoApp() :
    m_hwnd(NULL),
    m_wszHelloWorld(NULL),
    m_cHelloWorldLength(0)
{
}

/******************************************************************
*                                                                 *
*  DemoApp::~DemoApp destructor                                   *
*                                                                 *
*  Tear down resources                                            *
*                                                                 *
******************************************************************/

DemoApp::~DemoApp()
{
}

/******************************************************************
*                                                                 *
*  DemoApp::Initialize                                            *
*                                                                 *
*  Create application window and device-independent resources     *
*                                                                 *
******************************************************************/

HRESULT DemoApp::Initialize()
{
    WNDCLASSEX wcex;
    HRESULT hr;
    ATOM atom;

    // Register window class
    wcex.cbSize        = sizeof(WNDCLASSEX);
    wcex.style         = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc   = DemoApp::WndProc;
    wcex.cbClsExtra    = 0;
    wcex.cbWndExtra    = sizeof(LONG_PTR);
    wcex.hInstance     = HINST_THISCOMPONENT;
    wcex.hbrBackground = NULL;
    wcex.lpszMenuName  = NULL;
    wcex.hIcon         = LoadIcon(
                            NULL,
                            IDI_APPLICATION);
    wcex.hCursor       = LoadCursor(
                            NULL,
                            IDC_ARROW);
    wcex.lpszClassName = TEXT("D2DDemoApp");
    wcex.hIconSm       = LoadIcon(
                            NULL,
                            IDI_APPLICATION
                            );

    atom = RegisterClassEx(
        &wcex
        );

    IFR(atom ? S_OK : E_FAIL);

    // Create window
    m_hwnd = CreateWindow(
        TEXT("D2DDemoApp"),
        TEXT("D2D Demo App"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        640,
        480,
        NULL,
        NULL,
        HINST_THISCOMPONENT,
        this
        );

    IFR(m_hwnd ? S_OK : E_FAIL);

    IFR(CreateDeviceIndependentResources(
        ));

    ShowWindow(
        m_hwnd,
        SW_SHOWNORMAL
        );

    UpdateWindow(
        m_hwnd
        );

    return hr;
}

/******************************************************************
*                                                                 *
*  DemoApp::CreateDeviceIndependentResources                      *
*                                                                 *
*  This method is used to create resources which are not bound    *
*  to any device. Their lifetime effectively extends for the      *
*  duration of the app. These resources include the Direct2D and  *
*  DirectWrite factories; and a DirectWrite Text Format object    *
*  (used for identifying particular font characteristics) and     *
*  a Direct2D geometry.                                           *
*                                                                 *
******************************************************************/

HRESULT DemoApp::CreateDeviceIndependentResources()
{
    HRESULT hr = S_OK;

    // Create WIC factory
    IFR(CoCreateInstance(
        CLSID_WICImagingFactory,
        NULL,
        CLSCTX_INPROC_SERVER,
        IID_IWICImagingFactory,
        reinterpret_cast<void **>(&m_spWICFactory)
        ));

    // Create Direct2D factory
    IFR(D2D1CreateFactory(
        D2D1_FACTORY_TYPE_SINGLE_THREADED,
        &m_spD2DFactory
        ));

    // Exercise 1, Step 1
    // Create a shared DirectWrite factory
    //IFR(DWriteCreateFactory(
    //    DWRITE_FACTORY_TYPE_SHARED,
    //    __uuidof(IDWriteFactory),
    //    reinterpret_cast<IUnknown**>(&m_spDWriteFactory)
    //    ));

    // Exercise 1, Step 2a
    // The string to display
    //m_wszHelloWorld = L"Hello World using DirectWrite!";
    //m_cHelloWorldLength = wcslen(m_wszHelloWorld);

    // Exercise 1, Step 2b
    // Create a text format using Gabriola with a font size of 72
    // we use this to set the default font, weight, stretch, style, and locale
    //IFR(m_spDWriteFactory->CreateTextFormat(
    //    L"Gabriola", //font family name
    //    NULL, //font collection (NULL sets it to use the system font collection)
    //    DWRITE_FONT_WEIGHT_REGULAR,
    //    DWRITE_FONT_STYLE_NORMAL,
    //    DWRITE_FONT_STRETCH_NORMAL,
    //    72.0f,
    //    L"en-us",
    //    &m_spTextFormat
    //    ));

    // Exercise 1, Step 2c
    // Center align (horizontally) the text
    //IFR(m_spTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER));
    // Center align (vertically) the text
    //IFR(m_spTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER));

    // Exercise 2, Step 1
    // Create a text layout using the text format
    //IFR(m_spDWriteFactory->CreateTextLayout(
    //    m_wszHelloWorld,
    //    m_cHelloWorldLength,
    //    m_spTextFormat,
    //    640.0f,
    //    480.0f,
    //    &m_spTextLayout
    //    ));

    // Exercise 2, Step 2a
    // Format the "DirectWrite" substring to be of font size 100
    //{
    //    DWRITE_TEXT_RANGE textRange = {18, /* start index where "DirectWrite" appears */
    //                                    2 /* length of the substring "Di" in "DirectWrite" */};
    //    IFR(m_spTextLayout->SetFontSize(100.0f, textRange));
    //}

    // Exercise 2, Step 2b
    // Format the word "DWrite" to be underlined and bold
    //{
    //    DWRITE_TEXT_RANGE textRange = {18, /* start index where "DirectWrite" appears */
    //                                   11 /* length of the substring "DirectWrite" */};
    //    IFR(m_spTextLayout->SetUnderline(TRUE, textRange));
    //    IFR(m_spTextLayout->SetFontWeight(DWRITE_FONT_WEIGHT_BOLD, textRange));
    //}

    // Exercise 2, Step 3a
    // Create an typography object
    //IDWriteTypographyPtr spTypography;
    //IFR(m_spDWriteFactory->CreateTypography(&spTypography));

    // Exercise 2, Step 3b
    // Set the stylistic set
    //DWRITE_FONT_FEATURE fontFeature = {DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_7,
    //                                   1};
    //IFR(spTypography->AddFontFeature(fontFeature));

    // Exercise 2, Step 3c
    // Format the entire string with the stylistic set
    //{
    //    DWRITE_TEXT_RANGE textRange = {0,
    //                                   m_cHelloWorldLength};
    //    IFR(m_spTextLayout->SetTypography(spTypography, textRange));
    //}

    return hr;
}

/******************************************************************
*                                                                 *
*  DemoApp::CreateDeviceResources                                 *
*                                                                 *
*  This method creates resources which are bound to a particular  *
*  D3D device. It's all centralized here, in case the resources   *
*  need to be recreated in case of D3D device loss (eg. display   *
*  change, remoting, removal of video card, etc).                 *
*                                                                 *
******************************************************************/

HRESULT DemoApp::CreateDeviceResources()
{
    HRESULT hr = S_OK;

    RECT rc;
    GetClientRect(
        m_hwnd,
        &rc
        );

    D2D1_SIZE_U size = D2D1::SizeU(
        rc.right - rc.left,
        rc.bottom - rc.top
    );

    if (!m_spRT)
    {
        // Create a Direct2D render target
        IFR(m_spD2DFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(
                m_hwnd,
                size
                ),
            &m_spRT
            ));

        // Create a black brush
        IFR(m_spRT->CreateSolidColorBrush(
            D2D1::ColorF(
                D2D1::ColorF::Black
                ),
            &m_spBlackBrush));

        // Create the bitmap to be used by the bitmap brush
        ID2D1BitmapPtr spBitmap;
        IFR(LoadResourceBitmap(
            m_spRT,
            m_spWICFactory,
            L"Tulip",
            L"Image",
            &spBitmap
            ));

        // Create the bitmap brush
        D2D1_BITMAP_BRUSH_PROPERTIES properties = { D2D1_EXTEND_MODE_WRAP, D2D1_EXTEND_MODE_WRAP, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR };
        IFR(m_spRT->CreateBitmapBrush(
            spBitmap,
            properties,
            &m_spBitmapBrush));

        // Exercise 3, Step 8a
        // Create the text renderer
        //m_spTextRenderer = new CustomTextRenderer(
        //    m_spD2DFactory,
        //    m_spRT,
        //    m_spBlackBrush,
        //    m_spBitmapBrush
        //    );
    }

    return hr;
}

/******************************************************************
*                                                                 *
*  DemoApp::DiscardDeviceResources                                *
*                                                                 *
*  Discard device-specific resources which need to be recreated   *
*  when a D3D device is lost                                      *
*                                                                 *
******************************************************************/

void DemoApp::DiscardDeviceResources()
{
    m_spRT.Release();
    m_spBlackBrush.Release();
    m_spBitmapBrush.Release();
    m_spTextRenderer.Release();
}

/******************************************************************
*                                                                 *
*  DemoApp::RunMessageLoop                                        *
*                                                                 *
*  Main window message loop                                       *
*                                                                 *
******************************************************************/

void DemoApp::RunMessageLoop()
{
    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

/******************************************************************
*                                                                 *
*  DemoApp::DrawText                                              *
*                                                                 *
*  This method will draw text using the IDWriteTextFormat         *
*                                                                 *
******************************************************************/

void DemoApp::DrawText()
{
    RECT rc;

    GetClientRect(
        m_hwnd,
        &rc
        );

    // Exercise 1, Step 3a
    //D2D1_RECT_F layoutRect = D2D1::RectF(
    //    static_cast<FLOAT>(rc.top),
    //    static_cast<FLOAT>(rc.left),
    //    static_cast<FLOAT>(rc.right - rc.left),
    //    static_cast<FLOAT>(rc.bottom - rc.top)
    //    );

    // Exercise 1, Step 3b
    //m_spRT->DrawText(
    //    m_wszHelloWorld, //the string to render
    //    m_cHelloWorldLength, //the string's length
    //    m_spTextFormat, //the text format
    //    layoutRect, //the region of the window where the text will be rendered
    //    m_spBlackBrush //the brush used to draw the text
    //    );
}

/******************************************************************
*                                                                 *
*  DemoApp::DrawTextLayout                                        *
*                                                                 *
*  This method will draw text using the IDWriteTextLayout and the *
*  via the Direct2D render target                                 *
*                                                                 *
******************************************************************/

void DemoApp::DrawTextLayout()
{
    RECT rc;

    GetClientRect(
        m_hwnd,
        &rc
        );

    // Exercise 2, Step 5a
    //D2D1_POINT_2F origin = D2D1::Point2F(
    //    static_cast<FLOAT>(rc.top),
    //    static_cast<FLOAT>(rc.left)
    //    );

    // Exercise 2, Step 5b
    //m_spRT->DrawTextLayout(
    //    origin,
    //    m_spTextLayout,
    //    m_spBlackBrush
    //    );
}

/******************************************************************
*                                                                 *
*  DemoApp::DrawTextLayoutUsingGeometries                         *
*                                                                 *
*  This method will draw text using the IDWriteTextLayout's Draw  *
*  method and a custom IDWriteTextRenderer                        *
*                                                                 *
******************************************************************/

HRESULT DemoApp::DrawTextLayoutUsingGeometries()
{
    HRESULT hr = S_OK;

    RECT rc;

    GetClientRect(
        m_hwnd,
        &rc);

    // Exercise 3, Step 8b
    //D2D1_POINT_2F origin = D2D1::Point2F(
    //    static_cast<FLOAT>(rc.top),
    //    static_cast<FLOAT>(rc.left)
    //    );

    // Draw the text layout using DirectWrite
    //IFR(m_spTextLayout->Draw(
    //    NULL,
    //    m_spTextRenderer,
    //    origin.x,
    //    origin.y
    //    ));

    return hr;
}

/******************************************************************
*                                                                 *
*  DemoApp::OnRender                                              *
*                                                                 *
*  Called whenever the application needs to display the client    *
*  window. This method draws a bitmap a couple times, draws some  *
*  geometry, and writes "Hello World"                             *
*                                                                 *
*  Note that this function will not render anything if the window *
*  is occluded (eg. obscured by other windows or off monitor).    *
*  Also, this function will automatically discard device-specific *
*  resources if the D3D device disappears during execution, and   *
*  will recreate the resources the next time it's invoked.        *
*                                                                 *
******************************************************************/

HRESULT DemoApp::OnRender(const PAINTSTRUCT &ps)
{
    HRESULT hr;

    IFR(DrawD2DContent(ps));

    return hr;
}

/******************************************************************
*                                                                 *
*  DemoApp::DrawD2DContent                                        *
*                                                                 *
*  This method draws a bitmap a couple times, draws some          *
*  geometry, and writes "Hello World"                             *
*                                                                 *
*  Note that this function will not render anything if the window *
*  is occluded (eg. obscured by other windows or off monitor).    *
*  Also, this function will automatically discard device-specific *
*  resources if the D3D device disappears during execution, and   *
*  will recreate the resources the next time it's invoked.        *
*                                                                 *
******************************************************************/

HRESULT DemoApp::DrawD2DContent(const PAINTSTRUCT &ps)
{
    HRESULT hr;

    IFR(CreateDeviceResources());

    if (!(m_spRT->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
    {
        m_spRT->BeginDraw();

        m_spRT->SetTransform(
            D2D1::Matrix3x2F::Identity(
                )
            );

        m_spRT->Clear(D2D1::ColorF(D2D1::ColorF::White));

        // Exercise 1, Step 4
        //DrawText();

        // Exercise 2, Step 5
        //DrawTextLayout();

        // Exercise 3, Step 8c
        //IFR(DrawTextLayoutUsingGeometries());

        hr = m_spRT->EndDraw(
            );
    }

    if (hr == D2DERR_RECREATE_TARGET)
    {
        DiscardDeviceResources();
    }

    return S_OK;
}


/******************************************************************
*                                                                 *
*  DemoApp::OnResize                                              *
*                                                                 *
*  If the application receives a WM_SIZE message, this method     *
*  resize the render target appropriately.                        *
*                                                                 *
******************************************************************/

void DemoApp::OnResize(UINT width, UINT height)
{
    if (m_spRT)
    {
        D2D1_SIZE_U size;
        size.width = width;
        size.height = height;
        m_spRT->Resize(size);

        // Exercise 2, Step 4
        //m_spTextLayout->SetMaxWidth(static_cast<FLOAT>(width));
        //m_spTextLayout->SetMaxHeight(static_cast<FLOAT>(height));
    }
}

/******************************************************************
*                                                                 *
*  DemoApp::WndProc                                               *
*                                                                 *
*  Window message handler                                         *
*                                                                 *
******************************************************************/

LRESULT CALLBACK DemoApp::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == WM_CREATE)
    {
        LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
        DemoApp *pDemoApp = (DemoApp *)pcs->lpCreateParams;

        ::SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            PtrToUlong(pDemoApp));

        return 1;
    }

    DemoApp *pDemoApp = reinterpret_cast<DemoApp *>(static_cast<LONG_PTR>(
                ::GetWindowLongPtrW(hwnd, GWLP_USERDATA)));

    if (pDemoApp)
    {
        switch(message)
        {
        case WM_SIZE:
            {
                UINT width = LOWORD(lParam);
                UINT height = HIWORD(lParam);
                pDemoApp->OnResize(width, height);
            }
            return 0;

        case WM_PAINT:
        case WM_DISPLAYCHANGE:
            {
                PAINTSTRUCT ps;
                BeginPaint(hwnd, &ps);
                pDemoApp->OnRender(
                    ps
                    );
                EndPaint(
                    hwnd,
                    &ps
                    );
            }
            return 0;

        case WM_DESTROY:
            {
                PostQuitMessage(0);
            }
            return 1;
        }
    }
    return DefWindowProc(
        hwnd,
        message,
        wParam,
        lParam
        );
}

/******************************************************************
*                                                                 *
*  DemoApp::LoadResourceBitmap                                    *
*                                                                 *
*  This method will create a Direct2D bitmap from a resource in   *
*  this DLL.                                                      *
*                                                                 *
******************************************************************/

HRESULT
DemoApp::LoadResourceBitmap(
    ID2D1RenderTarget *pRT,
    IWICImagingFactory *pIWICFactory,
    PCWSTR resourceName,
    PCWSTR resourceType,
    __deref_out ID2D1Bitmap **ppBitmap
    )
{
    HRESULT hr;

    IWICBitmapDecoderPtr spDecoder;
    IWICBitmapFrameDecodePtr spSource;
    IWICStreamPtr spStream;
    IWICFormatConverterPtr spConverter;

    HRSRC imageResHandle = NULL;
    HGLOBAL imageResDataHandle = NULL;
    void *pImageFile = NULL;
    DWORD imageFileSize = 0;

    // Locate the resource handle in our dll
    imageResHandle = FindResourceW(
        HINST_THISCOMPONENT,
        resourceName,
        resourceType
        );

    IFR(imageResHandle ? S_OK : E_FAIL);

    // Load the resource
    imageResDataHandle = LoadResource(
        HINST_THISCOMPONENT,
        imageResHandle
        );

    IFR(imageResDataHandle ? S_OK : E_FAIL);

    // Lock it to get a system memory pointer
    pImageFile = LockResource(
        imageResDataHandle
        );

    IFR(pImageFile ? S_OK : E_FAIL);

    // Calculate the size
    imageFileSize = SizeofResource(
        HINST_THISCOMPONENT,
        imageResHandle
        );

    IFR(imageFileSize ? S_OK : E_FAIL);

    // Create a WIC stream to map onto the memory
    IFR(pIWICFactory->CreateStream(&spStream));

    // Initialize the stream with the memory pointer and size
    IFR(spStream->InitializeFromMemory(
        reinterpret_cast<BYTE*>(pImageFile),
        imageFileSize
        ));

    // Create a decoder for the stream
    IFR(pIWICFactory->CreateDecoderFromStream(
        spStream,
        NULL,
        WICDecodeMetadataCacheOnLoad,
        &spDecoder
        ));

    // Create the initial frame
    IFR(spDecoder->GetFrame(
        0,
        &spSource
        ));

    // Format convert to 32bppPBGRA -- which Direct2D expects
    IFR(pIWICFactory->CreateFormatConverter(&spConverter));

    IFR(spConverter->Initialize(
        spSource,
        GUID_WICPixelFormat32bppPBGRA,
        WICBitmapDitherTypeNone,
        NULL,
        0.f,
        WICBitmapPaletteTypeMedianCut
        ));

    // Create a Direct2D bitmap from the WIC bitmap.
    IFR(pRT->CreateBitmapFromWicBitmap(
        spConverter,
        NULL,
        ppBitmap
        ));

    return hr;
}
