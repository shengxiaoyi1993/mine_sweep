#include <windows.h>
#include <stdint.h>
#include <tlhelp32.h>
#include <wingdi.h>
#include <stdio.h>
#include <iostream>
#include <vector>

typedef struct EnumHWndsArg
{
    std::vector<HWND> *vecHWnds;
    DWORD dwProcessId;
}EnumHWndsArg, *LPEnumHWndsArg;

HANDLE GetProcessHandleByID(int nID)//通过进程ID获取进程句柄
{
    return OpenProcess(PROCESS_ALL_ACCESS, FALSE, nID);
}

DWORD GetProcessIDByName(const char* pName)
{
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (INVALID_HANDLE_VALUE == hSnapshot) {
        return NULL;
    }
    PROCESSENTRY32 pe = { sizeof(pe) };
    for (BOOL ret = Process32First(hSnapshot, &pe); ret; ret = Process32Next(hSnapshot, &pe)) {
        if (strcmp(pe.szExeFile, pName) == 0) {
            CloseHandle(hSnapshot);
            printf("find target\n");
            printf("%-6d %s\n", pe.th32ProcessID, pe.szExeFile);

            return pe.th32ProcessID;
        }
        printf("%-6d %s\n", pe.th32ProcessID, pe.szExeFile);
    }
    CloseHandle(hSnapshot);
    return 0;
}

BOOL CALLBACK lpEnumFunc(HWND hwnd, LPARAM lParam)
{
    EnumHWndsArg *pArg = (LPEnumHWndsArg)lParam;
    DWORD  processId;
    GetWindowThreadProcessId(hwnd, &processId);
    if (processId == pArg->dwProcessId)
    {
        pArg->vecHWnds->push_back(hwnd);
        //printf("%p\n", hwnd);
    }
    return TRUE;
}

void GetHWndsByProcessID(DWORD processID, std::vector<HWND> &vecHWnds)
{
    EnumHWndsArg wi;
    wi.dwProcessId = processID;
    wi.vecHWnds = &vecHWnds;
    EnumWindows(lpEnumFunc, (LPARAM)&wi);
}

//将HDC数据切换程LPVOID 数据
void GetDCBits(HDC hDC, LPVOID lpBits, int nWidth, int nHeight, int nX=0, int nY=0)
{
HDC hMemDC = CreateCompatibleDC(hDC);
HBITMAP hBmpNew = CreateCompatibleBitmap(hDC, nWidth, nHeight);
HBITMAP hBmpOld = (HBITMAP)SelectObject(hMemDC, hBmpNew);
BitBlt(hMemDC, 0, 0, nWidth, nHeight, hDC, nX, nY, SRCCOPY);
LONG lLineBytes = (nWidth*24+31)/32*4;
LONG lBufferSize = lLineBytes*nHeight;
BITMAPINFOHEADER bih;
memset( &bih, 0, sizeof(bih) );
bih.biWidth = nWidth;
bih.biHeight = nHeight;
bih.biBitCount = 24;
bih.biPlanes = 1;
bih.biSize = sizeof(bih);
printf("bih.biWidth:%d\n", bih.biWidth);
printf("bih.biHeight:%d\n", bih.biHeight);

GetDIBits(hMemDC, hBmpNew, 0, nHeight, lpBits, (LPBITMAPINFO)&bih, DIB_RGB_COLORS);
printf("bih.biWidth:%d\n", bih.biWidth);
printf("bih.biHeight:%d\n", bih.biHeight);
SelectObject(hMemDC, hBmpOld);
DeleteObject(hBmpNew);
DeleteDC(hMemDC);
}

int32_t main()
{
  std::cout<<"start"<<std::endl;
    DWORD pid = GetProcessIDByName("winmine.exe");
    printf("pid = %u\n", pid);

    // BOOL GetWindowRect(HWND hWnd,LPRECT lpRect);
    if (pid != 0)
    {
        std::vector<HWND> vecHWnds;
          GetHWndsByProcessID(pid, vecHWnds);
        printf("vecHWnds.size() = %u\n", vecHWnds.size());
        for (const HWND &h : vecHWnds)
        {
            HWND parent = GetParent(h);
            RECT rect;
            LPRECT lpRect=&rect;

             GetWindowRect(h, lpRect);
             printf("left:%d,top:%d,right:%d,bottom:%d\n",lpRect->left,lpRect->top,lpRect->right,lpRect->bottom );
            if (parent == NULL)
            {
                printf("%p --->Main Wnd\n", h);
                HDC memDc_;
                HDC scrDc_;
                scrDc_ = GetWindowDC(parent);
                memDc_ = CreateCompatibleDC(scrDc_);
                // const auto ret = ::PrintWindow(h, memDc_, PW_CLIENTONLY | PW_RENDERFULLCONTENT);
                const auto ret = PrintWindow(h, memDc_, PW_CLIENTONLY);

                // LPVOID lpBits=NULL;
                char * pdate=(char *)malloc((lpRect->right-lpRect->left)*(lpRect->bottom-lpRect->top)*3);

                GetDCBits(memDc_,(LPVOID)pdate,lpRect->right-lpRect->left,lpRect->bottom-lpRect->top,0,0);


            }
            else
            {
                printf("%p %p\n", h, parent);
            }
        }
    }
    getchar();
    return S_OK;
}

// $ g++ win_proc.cpp -lgdi32
