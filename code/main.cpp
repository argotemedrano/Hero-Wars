#include <windows.h>

/* Main Macros */
#define LOCAL_PERSIST static
#define GLOBAL static
#define SINGLE_DEFINE static
#define INTERNAL_FUNCTION static

/* Globals */
// TODO: Global for now
GLOBAL bool Running;
GLOBAL BITMAPINFO BitmapInfo;
GLOBAL void* BitmapBuffer;
GLOBAL HBITMAP BitmapHandle;
GLOBAL HDC BitmapDeviceContext;

/* Function Prototypes */
LRESULT __stdcall MainWindowCallBack(HWND hwnd, UINT uMsg, WPARAM uwParam, LPARAM lParam);
INTERNAL_FUNCTION void Win32ResizeDIBSection(int width, int height);
INTERNAL_FUNCTION void Win32UpdateWindow(HDC DeviceContext, int x, int y, int width, int height);    

/*
* Entry point for WINAPI Application.
* hInstance:
* hPrevInstance:
* lpCmdLine:
* nCmdShow: 
*/
int CALLBACK WinMain(
                    _In_ HINSTANCE hInstance, 
                    _In_ HINSTANCE hPrevInstance, 
                    _In_ LPSTR lpCmdLine, 
                    _In_ int nCmdShow)
{
    WNDCLASS WindowClass = {};

    // TODO: Check if HREDRAW and VREDEAW still matter
    WindowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    WindowClass.lpfnWndProc = MainWindowCallBack; // Handles messages coming in from Windows
    WindowClass.hInstance = hInstance;
    WindowClass.lpszClassName = "HandmadeHeroWindowClass";

    if (RegisterClass(&WindowClass))
    {
        HWND WindowHandle = CreateWindowEx(
            0,
            WindowClass.lpszClassName,
            "Handmade Hero Window",
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            0,
            0,
            hInstance,
            0);

        if (WindowHandle)
        {
            MSG Message;
            // Returns non-zero value
            BOOL MessageResult;
            while ((MessageResult = GetMessage(&Message, 0, 0, 0)))
            {
                if (MessageResult > 0)
                {
                    // TODO: Log Error
                    TranslateMessage(&Message);
                    DispatchMessage(&Message);
                }
                else
                {
                    // TODO: Log Error  
                }
            }
        }
        else
        {
            // TODO: Log Error
        }
    }
    else
    {
        // TODO: Log Error
    }
    return 0;
}

// / Window, Message
/*
* HWND: Handle to the Window
* UINT uMsg: Message Windows is making us handle
*/
LRESULT __stdcall MainWindowCallBack(HWND hwnd, UINT uMsg, WPARAM uwParam, LPARAM lParam)
{
    // Return code to say what was done with the message
    LRESULT Result = 0;
    switch(uMsg)
    {
        case WM_SIZE:
        {
            RECT ClientRect;
            GetClientRect(hwnd, &ClientRect);
            int width = ClientRect.right - ClientRect.left;
            int height = ClientRect.bottom - ClientRect.top;
            Win32ResizeDIBSection(width, height);
            OutputDebugString("WM_SIZE\n");
            break;
        }
        case WM_DESTROY:
        {
            // TODO: Handle this with an error to the user? Recreate window?
            OutputDebugString("WM_DESTROY\n");
            break;
        }
        case WM_CLOSE:
        {
            // TODO: Handle this with a message to the user?
            PostQuitMessage(0);
            OutputDebugString("WM_CLOSE\n");
            break;
        }
        case WM_ACTIVATEAPP:
        {
            OutputDebugString("WM_SIZE\n");
            break;
        }
        case WM_PAINT:
        {
            PAINTSTRUCT Paint;
            HDC DeviceContext = BeginPaint(hwnd, &Paint);
            int Height = Paint.rcPaint.bottom - Paint.rcPaint.top;
            int Width = Paint.rcPaint.right - Paint.rcPaint.left;
            int X = Paint.rcPaint.left;
            int Y = Paint.rcPaint.top;
            Win32UpdateWindow(DeviceContext, X, Y, Width, Height);
            PatBlt(DeviceContext, X, Y, Width, Height, BLACKNESS);
            EndPaint(hwnd, &Paint);
            break;
        }
        default:
        {
            OutputDebugString("default\n");
            // If you don't want to handle messages
            Result = DefWindowProc(hwnd, uMsg,uwParam,lParam);
            break;
        }
    }

    return Result;
}

/*
* Resizes device independent bitmap
*/
INTERNAL_FUNCTION void Win32ResizeDIBSection(int width, int height)
{
    // TODO: Bulletproot this. Maybe do not free first, free after,
    // then free first if that fails
    // TODO: Free our DIBSection
    if (BitmapHandle)
    {
        DeleteObject(BitmapHandle);
    }
    else
    {
        BitmapDeviceContext = CreateCompatibleDC(0);
    }

    BitmapInfo.bmiHeader.biSize = sizeof(BitmapInfo.bmiHeader);
    BitmapInfo.bmiHeader.biWidth = width;
    BitmapInfo.bmiHeader.biHeight = height;
    BitmapInfo.bmiHeader.biPlanes = 1;
    BitmapInfo.bmiHeader.biBitCount = 32;
    BitmapInfo.bmiHeader.biCompression = BI_RGB;
    BitmapInfo.bmiHeader.biSizeImage = 0;
    BitmapInfo.bmiHeader.biXPelsPerMeter = 0;
    BitmapInfo.bmiHeader.biYPelsPerMeter = 0;
    BitmapInfo.bmiHeader.biClrUsed = 0;
    BitmapInfo.bmiHeader.biClrImportant = 0;

    BitmapHandle = CreateDIBSection(BitmapDeviceContext, &BitmapInfo, DIB_RGB_COLORS, &BitmapBuffer, NULL, NULL);
}

INTERNAL_FUNCTION void Win32UpdateWindow(HDC DeviceContext, int x, int y, int width, int height)    
{
    // StretchDIBits(DeviceContext, )
}