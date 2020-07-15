#include <windows.h>

/* Function Prototypes */
LRESULT __stdcall MainWindowCallBack(HWND hwnd, UINT uMsg, WPARAM uwParam, LPARAM lParam);

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
            OutputDebugString("WM_SIZE\n");
            break;
        }
        case WM_DESTROY:
        {
            OutputDebugString("WM_DESTROY\n");
            break;
        }
        case WM_CLOSE:
        {
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
