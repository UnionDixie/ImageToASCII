#include "DragAndDrop.h"

std::queue<std::string> imageToConvert;
LONG_PTR sfmlCallBack = 0x0;

LRESULT CALLBACK dragDropCallback(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == WM_DROPFILES)
    {
        HDROP hDrop = reinterpret_cast<HDROP>(wParam);
        //https://docs.microsoft.com/en-us/windows/win32/api/shellapi/nf-shellapi-dragqueryfilea
        const UINT  iFile = 0xFFFFFFFF;
        const UINT filescount = DragQueryFile(hDrop, iFile, nullptr, 0);
        for (UINT i = 0; i < filescount; ++i)
        {
            const UINT bufsize = DragQueryFile(hDrop, i, NULL, 0);
            std::wstring getPath;
            getPath.resize(bufsize + 1);
            if (DragQueryFile(hDrop, i, &getPath[0], bufsize + 1))
            {
                std::string currentPath;
                sf::Utf8::fromWide(getPath.begin(), getPath.end(), std::back_inserter(currentPath));
                std::cout << currentPath << std::endl;
                imageToConvert.push(currentPath);
            }
        }
        DragFinish(hDrop);
        std::cout << "-------------" << std::endl;
    }
    return CallWindowProcW(reinterpret_cast<WNDPROC>(sfmlCallBack), handle, message, wParam, lParam);
}



void DragAndDrop::SetHandle(HWND appHwnd)
{
    DragAcceptFiles(appHwnd, true);
    sfmlCallBack = SetWindowLongPtrW(appHwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(dragDropCallback));
}

bool DragAndDrop::haveImages() const
{
    return imageToConvert.empty();
}

std::queue<std::string>& DragAndDrop::getImageToConvert()
{
    return imageToConvert;
}
