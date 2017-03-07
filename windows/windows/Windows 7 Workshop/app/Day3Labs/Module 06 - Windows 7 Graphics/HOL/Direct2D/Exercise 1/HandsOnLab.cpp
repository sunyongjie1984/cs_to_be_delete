//+-----------------------------------------------------------------------------
//
//  Copyright (c) Microsoft Corporation.  All rights reserved.
//
//  $Description:
//      Sample Direct2D Application
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
    int nCmdShow
    )
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

    return SUCCEEDED(hr);
}

/******************************************************************
*                                                                 *
*  DemoApp::DemoApp constructor                                   *
*                                                                 *
*  Initialize member data                                         *
*                                                                 *
******************************************************************/

DemoApp::DemoApp() :
    m_hwnd(NULL)
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
        IDI_APPLICATION
        );
    wcex.hCursor       = LoadCursor(
        NULL,
        IDC_ARROW
        );
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

    //IFR(CreateDeviceIndependentResources());

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
*  duration of the app. These resources include the D2D and       *
*  DWrite factories; and a DWrite Text Format object              *
*  (used for identifying particular font characteristics) and     *
*  a D2D geometry.                                                *
*                                                                 *
******************************************************************/

HRESULT DemoApp::CreateDeviceIndependentResources()
{
    ID2D1GeometrySinkPtr spSink;
    HRESULT hr = S_OK;

    // Create D2D factory
    //IFR(D2D1CreateFactory(
    //    D2D1_FACTORY_TYPE_SINGLE_THREADED,
    //    &m_spD2DFactory
    //    ));

    // Create the path geometry
    //IFR(m_spD2DFactory->CreatePathGeometry(
    //    &m_spPathGeometry
    //    ));

    // Write to the path geometry using the geometry sink. We are going to create an
    // hour glass.
    //IFR(m_spPathGeometry->Open(
    //    &spSink
    //    ));

    //spSink->SetFillMode(
    //    D2D1_FILL_MODE_ALTERNATE
    //    );

    //spSink->BeginFigure(
    //    D2D1::Point2F(0, 0),
    //    D2D1_FIGURE_BEGIN_FILLED
    //    );

    //spSink->AddLine(
    //    D2D1::Point2F(200, 0)
    //    );

    //spSink->AddBezier(
    //    D2D1::BezierSegment(
    //        D2D1::Point2F(150, 50),
    //        D2D1::Point2F(150, 150),
    //        D2D1::Point2F(200, 200)
    //    ));

    //spSink->AddLine(
    //    D2D1::Point2F(0, 200)
    //    );

    //spSink->AddBezier(
    //    D2D1::BezierSegment(
    //        D2D1::Point2F(50, 150),
    //        D2D1::Point2F(50, 50),
    //        D2D1::Point2F(0, 0)
    //    ));

    //spSink->EndFigure(
    //    D2D1_FIGURE_END_CLOSED
    //    );

    //IFR(spSink->Close());

    // Create a transformed geometry which is tilted at an angle to the previous geometry
    //IFR(m_spD2DFactory->CreateTransformedGeometry(
    //    m_spPathGeometry,
    //    D2D1::Matrix3x2F::Rotation(
    //        45.0f,
    //        D2D1::Point2F(100, 100)
    //        ),
    //    &m_spTransformedGeometry
    //    ));

    // Create another path geometry that will contain the result of geometry boolean operations
    //IFR(m_spD2DFactory->CreatePathGeometry(
    //    &m_spCombinedPathGeometry
    //    ));

    // Write to the path geometry using the geometry sink. We are going to combine
    // hour glass with an hour glass rotated at an angle of 45 degrees.
    //IFR(m_spCombinedPathGeometry->Open(
    //    &spSink
    //    ));

    //spSink->SetFillMode(
    //    D2D1_FILL_MODE_ALTERNATE
    //    );

    //m_spPathGeometry->CombineWithGeometry(
    //    m_spTransformedGeometry,
    //    D2D1_COMBINE_MODE_UNION,
    //    D2D1::Matrix3x2F::Identity(),
    //    0.25f,
    //    spSink
    //    );

    //IFR(spSink->Close());

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
    ID2D1GradientStopCollectionPtr spGradientStops;

    if (!m_spRT)
    {
        //RECT rc;
        //GetClientRect(
        //    m_hwnd,
        //    &rc
        //    );
        //D2D1_SIZE_U size = D2D1::SizeU(
        //    rc.right - rc.left,
        //    rc.bottom - rc.top
        //    );

        // Create a D2D render target
        //IFR(m_spD2DFactory->CreateHwndRenderTarget(
        //    D2D1::RenderTargetProperties(),
        //    D2D1::HwndRenderTargetProperties(
        //        m_hwnd,
        //        size
        //        ),
        //    &m_spRT
        //    ));

        // Create a green brush
        //IFR(m_spRT->CreateSolidColorBrush(
        //    D2D1::ColorF(D2D1::ColorF::Green),
        //    &m_spGreenBrush
        //    ));

        // Create an orange brush
        //IFR(m_spRT->CreateSolidColorBrush(
        //    D2D1::ColorF(D2D1::ColorF::Orange),
        //    &m_spOrangeBrush
        //    ));

        // Create a linear gradient brush
        //static const D2D1_GRADIENT_STOP stops[] =
        //{
        //    { 0.f,  { 0.f, 1.f, 1.f, 1.f }  },
        //    { 1.f,  { 0.f, 0.f, 1.f, 1.f }  },
        //};

        //IFR(m_spRT->CreateGradientStopCollection(
        //    stops,
        //    ARRAY_SIZE(stops),
        //    &spGradientStops
        //    ));

        //IFR(m_spRT->CreateLinearGradientBrush(
        //    D2D1::LinearGradientBrushProperties(
        //        D2D1::Point2F(100, 0),
        //        D2D1::Point2F(100, 200)
        //        ),
        //    D2D1::BrushProperties(),
        //    spGradientStops,
        //    &m_spLGBrush
        //    ));
    }

    if (!m_spDCRT)
    {
        // Create a DC render target
        //D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
        //    D2D1_RENDER_TARGET_USAGE_GDI_COMPATIBLE,
        //    D2D1::PixelFormat(
        //        DXGI_FORMAT_B8G8R8A8_UNORM,
        //        D2D1_ALPHA_MODE_IGNORE
        //        )
        //    );

        //IFR(m_spD2DFactory->CreateDCRenderTarget(
        //    &props,
        //    &m_spDCRT
        //    ));

        // Create a black brush
        //IFR(m_spDCRT->CreateSolidColorBrush(
        //    D2D1::ColorF(D2D1::ColorF::Black),
        //    &m_spBlackBrush
        //    ));
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
    m_spDCRT.Release();
    m_spBlackBrush.Release();
    m_spLGBrush.Release();
    m_spGreenBrush.Release();
    m_spOrangeBrush.Release();
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
*  DemoApp::D2DRectangle                                          *
*                                                                 *
*  This method will draw a fill and outline rectangle             *
*                                                                 *
******************************************************************/

void DemoApp::DrawD2DRectangle()
{
    //RECT rc;

    //GetClientRect(
    //    m_hwnd,
    //    &rc
    //    );

    //D2D1_SIZE_U size = D2D1::SizeU(
    //    rc.right - rc.left,
    //    rc.bottom - rc.top
    //    );

    //D2D1_RECT_F rectangle1 = D2D1::RectF(
    //    size.width/2 - 50.0f,
    //    size.height/2 - 50.0f,
    //    size.width/2 + 50.0f,
    //    size.height/2 + 50.0f
    //    );

    //D2D1_RECT_F rectangle2 = D2D1::RectF(
    //    size.width/2 - 100.0f,
    //    size.height/2 - 100.0f,
    //    size.width/2 + 100.0f,
    //    size.height/2 + 100.0f
    //    );

    // Draw a filled rectangle
    //m_spRT->FillRectangle(
    //    &rectangle1,
    //    m_spGreenBrush
    //    );

    // Draw an outline rectangle
    //m_spRT->DrawRectangle(
    //    &rectangle2,
    //    m_spOrangeBrush
    //    );
}

/******************************************************************
*                                                                 *
*  DemoApp::D2DGeometry                                           *
*                                                                 *
*  This method demonstrates D2D geometries, Boolean operations    *
*  on geometries and linear gradient brushes                      *
*                                                                 *
******************************************************************/

HRESULT DemoApp::DrawD2DGeometry()
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

    // Draw the hour glass geometry at the top left corner of the client area
    //m_spRT->DrawGeometry(
    //    m_spPathGeometry,
    //    m_spGreenBrush
    //    );

    // Perform a translation about both X and Y axis
    //m_spRT->SetTransform(
    //    D2D1::Matrix3x2F::Translation(
    //        size.width/2-100.0f,
    //        size.height/2-100.0f
    //        )
    //    );

    //m_spRT->FillGeometry(
    //    m_spPathGeometry,
    //    m_spLGBrush
    //    );

    // Draw the combined geometry
    //m_spRT->DrawGeometry(
    //    m_spCombinedPathGeometry,
    //    m_spOrangeBrush
    //    );

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
    HRESULT hr = S_OK;

    //IFR(DrawD2DContent(ps));

    //IFR(DrawDCInterop(ps));

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
    HRESULT hr = S_OK;

    //IFR(CreateDeviceResources());

    if (!(m_spRT->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
    {
        //m_spRT->BeginDraw();

        //m_spRT->SetTransform(
        //    D2D1::Matrix3x2F::Identity()
        //    );

        //m_spRT->Clear(
        //    D2D1::ColorF(D2D1::ColorF::White)
        //    );

        // Exercise 1
        //DrawD2DRectangle();

        // Exercise 2
        //DrawD2DGeometry();

        //hr = m_spRT->EndDraw();
    }

    if (hr == D2DERR_RECREATE_TARGET)
    {
        DiscardDeviceResources();
    }

    return hr;
}


/******************************************************************
*                                                                 *
*  DemoApp::DrawDCInterop                                         *
*                                                                 *
*  This method will draw using D2D to a GDI HDC                   *
*                                                                 *
******************************************************************/

HRESULT DemoApp::DrawDCInterop(const PAINTSTRUCT &ps)
{
    HRESULT hr = S_OK;
    //RECT rc;

    // Create the DC render target
    //IFR(CreateDeviceResources());

    // Get the dimensions of the client drawing area
    //GetClientRect(
    //    m_hwnd,
    //    &rc
    //    );

    // Bind the DC to the DC render target 
    //IFR(m_spDCRT->BindDC(
    //    ps.hdc,
    //    &rc
    //    ));

    // Start drawing to the DC render target
    //m_spDCRT->BeginDraw();

    //m_spDCRT->SetTransform(
    //    D2D1::Matrix3x2F::Identity()
    //    );

    //m_spDCRT->Clear(
    //    D2D1::ColorF(D2D1::ColorF::White)
    //    );

    //m_spDCRT->DrawEllipse(
    //    D2D1::Ellipse(
    //        D2D1::Point2F(150.0f, 150.0f),
    //        100.0f,
    //        100.0f
    //        ),
    //    m_spBlackBrush,
    //    3.0
    //    );

    //m_spDCRT->DrawLine(
    //    D2D1::Point2F(150.0f, 150.0f),
    //    D2D1::Point2F(
    //        (150.0f + 100.0f * 0.15425f),
    //        (150.0f - 100.0f * 0.988f)
    //        ), 
    //    m_spBlackBrush,
    //    3.0
    //    );

    //m_spDCRT->DrawLine(
    //    D2D1::Point2F(150.0f, 150.0f),
    //    D2D1::Point2F(
    //        (150.0f + 100.0f * 0.525f),
    //        (150.0f + 100.0f * 0.8509f)
    //        ),
    //    m_spBlackBrush,
    //    3.0
    //    );

    //m_spDCRT->DrawLine(
    //    D2D1::Point2F(150.0f, 150.0f),
    //    D2D1::Point2F(
    //        (150.0f - 100.0f * 0.988f),
    //        (150.0f - 100.0f * 0.15425f)
    //        ),
    //    m_spBlackBrush,
    //    3.0
    //    );

    //hr = m_spDCRT->EndDraw();

    // Drawing the pie chart with GDI

    // Let's save the original object first
    //HGDIOBJ original = NULL;
    //original = SelectObject(
    //    ps.hdc,
    //    GetStockObject(DC_PEN)
    //    );

    //HPEN blackPen = CreatePen(PS_SOLID, 3, 0);
    //SelectObject(ps.hdc, blackPen);

    //::Ellipse(
    //    ps.hdc,
    //    300,
    //    50,
    //    500,
    //    250
    //    );

    //POINT pntArray1[2];
    //pntArray1[0].x = 400;
    //pntArray1[0].y = 150;
    //pntArray1[1].x = static_cast<LONG>(400 + 100 * 0.15425);
    //pntArray1[1].y = static_cast<LONG>(150 - 100 * 0.9885);

    //POINT pntArray2[2];
    //pntArray2[0].x = 400;
    //pntArray2[0].y = 150;
    //pntArray2[1].x = static_cast<LONG>(400 + 100 * 0.525);
    //pntArray2[1].y = static_cast<LONG>(150 + 100 * 0.8509);


    //POINT pntArray3[2];
    //pntArray3[0].x = 400;
    //pntArray3[0].y = 150;
    //pntArray3[1].x = static_cast<LONG>(400 - 100 * 0.988);
    //pntArray3[1].y = static_cast<LONG>(150 - 100 * 0.15425);

    //::Polyline(
    //    ps.hdc,
    //    pntArray1,
    //    2
    //    );

    //::Polyline(
    //    ps.hdc,
    //    pntArray2,
    //    2
    //    );

    //::Polyline(
    //    ps.hdc,
    //    pntArray3,
    //    2
    //    );
    //
    //DeleteObject(blackPen);

    // Restore the original object
    //SelectObject(ps.hdc, original);

    //if (hr == D2DERR_RECREATE_TARGET)
    //{
    //    DiscardDeviceResources();
    //}
    return hr;
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
    HRESULT hr;

    if (m_spRT)
    {
        // Try to resize the target
        D2D1_SIZE_U size;
        size.width = width;
        size.height = height;
        hr = m_spRT->Resize(size);

        // If we couldn't resize, release it and we'll recreate it
        // during the next render pass.
        if (FAILED(hr))
        {
            DiscardDeviceResources();
            InvalidateRect(m_hwnd, NULL, FALSE);
        }
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
            PtrToUlong(pDemoApp)
            );

        return 1;
    }

    DemoApp *pDemoApp = reinterpret_cast<DemoApp *>(static_cast<LONG_PTR>(
                ::GetWindowLongPtrW(hwnd, GWLP_USERDATA)
                ));

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
                pDemoApp->OnRender(ps);
                EndPaint(hwnd, &ps);
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
