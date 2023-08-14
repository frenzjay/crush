#include <windows.h>
#include <tchar.h>
#include <string>
#include <random>

HWND hwndButtonYes, hwndButtonNo, hwndText;
bool isEpilepsyMode = false;
std::default_random_engine randomGenerator;

void ShowEpilepsyMode() {
    isEpilepsyMode = true;
    ::ShowWindow(hwndButtonYes, SW_HIDE);
    ::ShowWindow(hwndButtonNo, SW_HIDE);
    ::SetWindowText(hwndText, _T("I love you"));

    RECT rect;
    ::GetClientRect(GetDesktopWindow(), &rect);
    while (isEpilepsyMode) {
        COLORREF color = RGB(rand() % 256, rand() % 256, rand() % 256);
        HDC hdc = ::GetDC(NULL);
        ::FillRect(hdc, &rect, CreateSolidBrush(color));
        ::ReleaseDC(NULL, hdc);
        Sleep(100);
    }
}

void ShowLovePopup() {
    MessageBox(NULL, _T("I love you"), _T("Yieeeee"), MB_OK);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_COMMAND:
            if (reinterpret_cast<HWND>(lParam) == hwndButtonYes) {
                ShowEpilepsyMode();
            } else if (reinterpret_cast<HWND>(lParam) == hwndButtonNo) {
                ShowLovePopup();
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc = {sizeof(WNDCLASSEX), CS_CLASSDC, WindowProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("MyWinAPIApp"), NULL};
    ::RegisterClassEx(&wc);

    HWND hwnd = ::CreateWindow(wc.lpszClassName, _T("frenzgwapo"), WS_OVERLAPPEDWINDOW, 100, 100, 400, 200, NULL, NULL, wc.hInstance, NULL);

    hwndButtonNo = ::CreateWindow(_T("BUTTON"), _T("Yes"), WS_VISIBLE | WS_CHILD, 20, 100, 80, 30, hwnd, NULL, wc.hInstance, NULL);
    hwndButtonYes = ::CreateWindow(_T("BUTTON"), _T("No"), WS_VISIBLE | WS_CHILD, 120, 100, 80, 30, hwnd, NULL, wc.hInstance, NULL);

    hwndText = ::CreateWindow(_T("STATIC"), _T("Crush moba ako"), WS_VISIBLE | WS_CHILD | SS_CENTER, 0, 20, 400, 50, hwnd, NULL, wc.hInstance, NULL);
    ::SendMessage(hwndText, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);

    randomGenerator.seed(GetTickCount());

    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    MSG msg;
    while (::GetMessage(&msg, NULL, 0, 0)) {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    return 0;
}
