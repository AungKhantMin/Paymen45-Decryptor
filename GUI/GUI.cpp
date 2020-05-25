#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <CommCtrl.h>
#include <tlhelp32.h>
#include <array>
#include <math.h>
#include <vector>
#include <objbase.h>

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Paymen45 (.g8R4rqWIp9) Decryptor";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.
    int dpiX = 0;
    int dpiY = 0;
    HDC hdc = GetDC(NULL);
    if (hdc)
    {
        dpiX = GetDeviceCaps(hdc, LOGPIXELSX);
        dpiY = GetDeviceCaps(hdc, LOGPIXELSY);
        ReleaseDC(NULL, hdc);
    }

    HWND m_hwnd = CreateWindow(                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Paymen45 (.g8R4rqWIp9) Decryptor",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, 
        static_cast<UINT>(ceil(640.f * dpiX / 96.f)),
        static_cast<UINT>(ceil(480.f * dpiY / 96.f)),

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (m_hwnd == NULL)
    {
        return 0;
    }

    int xpos = 20;            // Horizontal position of the window.
    int ypos = 20;            // Vertical position of the window.
    int nwidth = 580;          // Width of the window
    int nheight = 200;         // Height of the window
    HWND hwndParent = m_hwnd; // Handle to the parent window

    HWND hWndComboBox = CreateWindow(WC_COMBOBOX, TEXT(""),
        CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
        xpos, ypos, nwidth, nheight, hwndParent, NULL, HINST_THISCOMPONENT,
        NULL);


    //Getting Process List

    HANDLE hProcessSnap;
    HANDLE hProcess;
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    Process32First(hProcessSnap, &pe32);
    do
    {

        WCHAR fStr[0x50];
        memset(fStr, 0, sizeof(fStr));
        wsprintfW(fStr, L"pid: %d    processName: %s", pe32.th32ProcessID, pe32.szExeFile);
        WCHAR temp[0x50];
        memset(temp, 0, sizeof(temp));
        wcscpy_s(temp, sizeof(temp) / sizeof(WCHAR), fStr);
        SendMessage(hWndComboBox, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)temp);

    } while (Process32Next(hProcessSnap, &pe32));


 
    SendMessage(hWndComboBox, CB_SETCURSEL, (WPARAM)1, (LPARAM)0);
    ShowWindow(m_hwnd, nCmdShow);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);



            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

            EndPaint(hwnd, &ps);
        }
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}