// Launcher.cpp : Defines the entry point for the application.
//

#define _CRT_SECURE_NO_WARNINGS


#include "framework.h"
#include <shellapi.h>
#include <algorithm>
#include <cwctype>
#include <string>

int APIENTRY wWinMain(_In_    HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_     LPWSTR    lpCmdLine,
                     _In_     int       nCmdShow)
{
  UNREFERENCED_PARAMETER  (hInstance);
  UNREFERENCED_PARAMETER  (hPrevInstance);
  UNREFERENCED_PARAMETER  (nCmdShow);

  std::wstring cmdLine = std::wstring (lpCmdLine);

  if (! cmdLine.empty())
  {
    const std::wstring delimiter = L".exe"; // split cmdLine at the .exe

    // First position is a quotation mark -- we need to strip those
    if (cmdLine.find(L"\"") == 0)
      cmdLine = cmdLine.substr(1, cmdLine.find(L"\"", 1) - 1) + cmdLine.substr(cmdLine.find(L"\"", 1) + 1, std::wstring::npos);

    // Transform to lowercase
    std::wstring cmdLineLower = cmdLine;
    std::transform (cmdLineLower.begin(), cmdLineLower.end(), cmdLineLower.begin(), [](wchar_t c) { return std::towlower(c); });

    // Extract the target path and any proxied command line arguments
    std::wstring path = cmdLine.substr(0, cmdLineLower.find(delimiter) + delimiter.length());                        // path
    std::wstring args = cmdLine.substr(   cmdLineLower.find(delimiter) + delimiter.length(), cmdLineLower.length()); // proxied command line

    // Trim spaces
    path.erase (path.begin(), std::find_if (path.begin(), path.end(), [](wchar_t ch) { return !std::iswspace(ch); }));
    args.erase (args.begin(), std::find_if (args.begin(), args.end(), [](wchar_t ch) { return !std::iswspace(ch); }));
    path.erase (std::find_if(path.rbegin(), path.rend(), [](wchar_t ch) { return !std::iswspace(ch); }).base(), path.end());
    args.erase (std::find_if(args.rbegin(), args.rend(), [](wchar_t ch) { return !std::iswspace(ch); }).base(), args.end());

#ifdef _DEBUG
    OutputDebugString(L"Path: ");
    OutputDebugString(path.c_str());
    OutputDebugString(L"\n");

    OutputDebugString(L"Args: ");
    OutputDebugString(args.c_str());
    OutputDebugString(L"\n");
#endif

    SHELLEXECUTEINFOW
    sexi              = { };
    sexi.cbSize       = sizeof (SHELLEXECUTEINFOW);
    sexi.lpVerb       = L"OPEN";
    sexi.lpFile       = path.c_str();
    sexi.lpParameters = args.c_str();
    sexi.lpDirectory  = NULL;
    sexi.nShow        = SW_SHOW;
    sexi.fMask        = SEE_MASK_FLAG_NO_UI |
                        SEE_MASK_NOASYNC    | SEE_MASK_NOZONECHECKS;

    // Launch executable
    ShellExecuteExW (&sexi);

    return 0;
  }

  return 1;
}