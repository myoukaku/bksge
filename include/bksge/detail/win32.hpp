/**
 *	@file	win32.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_DETAIL_WIN32_HPP
#define BKSGE_DETAIL_WIN32_HPP

#undef  WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#undef  NOMINMAX
#define NOMINMAX
#include <windows.h>

#undef LoadKeyboardLayout
#undef GetKeyboardLayoutName
#undef CreateDesktop
#undef CreateDesktopEx
#undef OpenDesktop
#undef EnumDesktops
#undef CreateWindowStation
#undef OpenWindowStation
#undef EnumWindowStations
#undef GetUserObjectInformation
#undef SetUserObjectInformation
#undef RegisterWindowMessage
#undef GetMessage
#undef DispatchMessage
#undef PeekMessage
#undef SendMessage
#undef SendMessageTimeout
#undef SendNotifyMessage
#undef SendMessageCallback
#undef BroadcastSystemMessageEx
#undef BroadcastSystemMessage
#undef RegisterDeviceNotification
#undef PostMessage
#undef PostThreadMessage
#undef PostAppMessage
#undef DefWindowProc
#undef CallWindowProc
#undef RegisterClass
#undef UnregisterClass
#undef GetClassInfo
#undef RegisterClassEx
#undef GetClassInfoEx
#undef CreateWindowEx
#undef CreateWindow
#undef CreateDialogParam
#undef CreateDialogIndirectParam
#undef CreateDialog
#undef CreateDialogIndirect
#undef DialogBoxParam
#undef DialogBoxIndirectParam
#undef DialogBox
#undef DialogBoxIndirect
#undef SetDlgItemText
#undef GetDlgItemText
#undef SendDlgItemMessage
#undef DefDlgProc
#undef CallMsgFilter
#undef RegisterClipboardFormat
#undef GetClipboardFormatName
#undef CharToOem
#undef OemToChar
#undef CharToOemBuff
#undef OemToCharBuff
#undef CharUpper
#undef CharUpperBuff
#undef CharLower
#undef CharLowerBuff
#undef CharNext
#undef CharPrev
#undef IsCharAlpha
#undef IsCharAlphaNumeric
#undef IsCharUpper
#undef IsCharLower
#undef GetKeyNameText
#undef VkKeyScan
#undef VkKeyScanEx
#undef MapVirtualKey
#undef MapVirtualKeyEx
#undef LoadAccelerators
#undef CreateAcceleratorTable
#undef CopyAcceleratorTable
#undef TranslateAccelerator
#undef LoadMenu
#undef LoadMenuIndirect
#undef ChangeMenu
#undef GetMenuString
#undef InsertMenu
#undef AppendMenu
#undef ModifyMenu
#undef InsertMenuItem
#undef GetMenuItemInfo
#undef SetMenuItemInfo
#undef DrawText
#undef DrawTextEx
#undef GrayString
#undef DrawState
#undef TabbedTextOut
#undef GetTabbedTextExtent
#undef SetProp
#undef GetProp
#undef RemoveProp
#undef EnumPropsEx
#undef EnumProps
#undef SetWindowText
#undef GetWindowText
#undef GetWindowTextLength
#undef MessageBox
#undef MessageBoxEx
#undef MessageBoxIndirect
#undef GetWindowLong
#undef SetWindowLong
#undef GetWindowLongPtr
#undef SetWindowLongPtr
#undef GetClassLong
#undef SetClassLong
#undef GetClassLongPtr
#undef SetClassLongPtr
#undef FindWindow
#undef FindWindowEx
#undef GetClassName
#undef SetWindowsHook
#undef SetWindowsHookEx
#undef LoadBitmap
#undef LoadCursor
#undef LoadCursorFromFile
#undef LoadIcon
#undef PrivateExtractIcons
#undef LoadImage
#undef GetIconInfoEx
#undef LoadString
#undef IsDialogMessage
#undef DlgDirList
#undef DlgDirSelectEx
#undef DlgDirListComboBox
#undef DlgDirSelectComboBoxEx
#undef DefFrameProc
#undef DefMDIChildProc
#undef CreateMDIWindow
#undef WinHelp
#undef ChangeDisplaySettings
#undef ChangeDisplaySettingsEx
#undef EnumDisplaySettings
#undef EnumDisplaySettingsEx
#undef EnumDisplayDevices
#undef SystemParametersInfo
#undef GetMonitorInfo
#undef GetWindowModuleFileName
#undef RealGetWindowClass
#undef GetAltTabInfo
#undef GetRawInputDeviceInfo
//#undef MAKEINTRESOURCE
#undef AddFontResource
#undef CopyMetaFile
#undef CreateDC
#undef CreateFontIndirect
#undef CreateFont
#undef CreateIC
#undef CreateMetaFile
#undef CreateScalableFontResource
#undef DeviceCapabilities
#undef EnumFontFamiliesEx
#undef EnumFontFamilies
#undef EnumFonts
#undef GetCharWidth
#undef GetCharWidth32
#undef GetCharWidthFloat
#undef GetCharABCWidths
#undef GetCharABCWidthsFloat
#undef GetGlyphOutline
#undef GetMetaFile
#undef GetOutlineTextMetrics
#undef GetTextExtentPoint
#undef GetTextExtentPoint32
#undef GetTextExtentExPoint
#undef GetCharacterPlacement
#undef GetGlyphIndices
#undef AddFontResourceEx
#undef RemoveFontResourceEx
#undef CreateFontIndirectEx
#undef ResetDC
#undef RemoveFontResource
#undef CopyEnhMetaFile
#undef CreateEnhMetaFile
#undef GetEnhMetaFile
#undef GetEnhMetaFileDescription
#undef GetTextMetrics
#undef StartDoc
#undef GetObject
#undef TextOut
#undef ExtTextOut
#undef PolyTextOut
#undef GetTextFace
#undef GetKerningPairs
#undef ICMENUMPROC
#undef GetLogColorSpace
#undef CreateColorSpace
#undef GetICMProfile
#undef SetICMProfile
#undef EnumICMProfiles
#undef UpdateICMRegKey
#undef wglUseFontBitmaps
#undef wglUseFontOutlines
#undef GetBinaryType
#undef GetShortPathName
#undef GetLongPathName
#undef GetLongPathNameTransacted
#undef GetEnvironmentStrings
#undef SetEnvironmentStrings
#undef FreeEnvironmentStrings
#undef SetFileShortName
#undef FormatMessage
#undef CreateMailslot
#undef EncryptFile
#undef DecryptFile
#undef FileEncryptionStatus
#undef OpenEncryptedFileRaw
#undef lstrcmp
#undef lstrcmpi
#undef lstrcpyn
#undef lstrcpy
#undef lstrcat
#undef lstrlen
#undef CreateMutex
#undef OpenMutex
#undef CreateEvent
#undef OpenEvent
#undef CreateSemaphore
#undef OpenSemaphore
#undef CreateWaitableTimer
#undef OpenWaitableTimer
#undef CreateMutexEx
#undef CreateEventEx
#undef CreateSemaphoreEx
#undef CreateWaitableTimerEx
#undef CreateFileMapping
#undef CreateFileMappingNuma
#undef OpenFileMapping
#undef GetLogicalDriveStrings
#undef LoadLibrary
#undef LoadLibraryEx
#undef GetModuleFileName
#undef GetModuleHandle
#undef PGET_MODULE_HANDLE_EX
#undef GetModuleHandleEx
#undef NeedCurrentDirectoryForExePath
#undef QueryFullProcessImageName
#undef CreateProcess
#undef FatalAppExit
#undef GetStartupInfo
#undef GetCommandLine
#undef GetEnvironmentVariable
#undef SetEnvironmentVariable
#undef ExpandEnvironmentStrings
#undef GetFirmwareEnvironmentVariable
#undef SetFirmwareEnvironmentVariable
#undef OutputDebugString
#undef FindResource
#undef FindResourceEx
#undef ENUMRESTYPEPROC
#undef ENUMRESNAMEPROC
#undef ENUMRESLANGPROC
#undef EnumResourceTypes
#undef EnumResourceNames
#undef EnumResourceLanguages
#undef EnumResourceTypesEx
#undef EnumResourceNamesEx
#undef EnumResourceLanguagesEx
#undef BeginUpdateResource
#undef UpdateResource
#undef EndUpdateResource
#undef GlobalAddAtom
#undef GlobalFindAtom
#undef GlobalGetAtomName
#undef AddAtom
#undef FindAtom
#undef GetAtomName
#undef GetProfileInt
#undef GetProfileString
#undef WriteProfileString
#undef GetProfileSection
#undef WriteProfileSection
#undef GetPrivateProfileInt
#undef GetPrivateProfileString
#undef WritePrivateProfileString
#undef GetPrivateProfileSection
#undef WritePrivateProfileSection
#undef GetPrivateProfileSectionNames
#undef GetPrivateProfileStruct
#undef WritePrivateProfileStruct
#undef GetDriveType
#undef GetSystemDirectory
#undef GetTempPath
#undef GetTempFileName
#undef GetWindowsDirectory
#undef GetSystemWindowsDirectory
#undef GetSystemWow64Directory
#undef GET_SYSTEM_WOW64_DIRECTORY_NAME_T_A
#undef GET_SYSTEM_WOW64_DIRECTORY_NAME_T_W
#undef GET_SYSTEM_WOW64_DIRECTORY_NAME_T_T
#undef SetCurrentDirectory
#undef GetCurrentDirectory
#undef SetDllDirectory
#undef GetDllDirectory
#undef GetDiskFreeSpace
#undef GetDiskFreeSpaceEx
#undef CreateDirectory
#undef CreateDirectoryEx
#undef CreateDirectoryTransacted
#undef RemoveDirectory
#undef RemoveDirectoryTransacted
#undef GetFullPathName
#undef GetFullPathNameTransacted
#undef DefineDosDevice
#undef QueryDosDevice
#undef CreateFile
#undef CreateFileTransacted
#undef SetFileAttributes
#undef GetFileAttributes
#undef SetFileAttributesTransacted
#undef GetFileAttributesTransacted
#undef GetFileAttributesEx
#undef GetCompressedFileSize
#undef GetCompressedFileSizeTransacted
#undef DeleteFile
#undef DeleteFileTransacted
#undef CheckNameLegalDOS8Dot3
#undef FindFirstFileEx
#undef FindFirstFileTransacted
#undef FindFirstFile
#undef FindNextFile
#undef SearchPath
#undef CopyFile
#undef CopyFileEx
#undef CopyFileTransacted
#undef MoveFile
#undef MoveFileEx
#undef MoveFileWithProgress
#undef MoveFileTransacted
#undef ReplaceFile
#undef CreateHardLink
#undef CreateHardLinkTransacted
#undef CreateNamedPipe
#undef GetNamedPipeHandleState
#undef CallNamedPipe
#undef WaitNamedPipe
#undef GetNamedPipeClientComputerName
#undef SetVolumeLabel
#undef GetVolumeInformation
#undef ClearEventLog
#undef BackupEventLog
#undef OpenEventLog
#undef RegisterEventSource
#undef OpenBackupEventLog
#undef ReadEventLog
#undef ReportEvent
#undef AccessCheckAndAuditAlarm
#undef AccessCheckByTypeAndAuditAlarm
#undef AccessCheckByTypeResultListAndAuditAlarm
#undef AccessCheckByTypeResultListAndAuditAlarmByHandle
#undef ObjectOpenAuditAlarm
#undef ObjectPrivilegeAuditAlarm
#undef ObjectCloseAuditAlarm
#undef ObjectDeleteAuditAlarm
#undef PrivilegedServiceAuditAlarm
#undef SetFileSecurity
#undef GetFileSecurity
#undef FindFirstChangeNotification
#undef IsBadStringPtr
#undef LookupAccountSid
#undef LookupAccountSidLocal
#undef LookupAccountName
#undef LookupAccountNameLocal
#undef LookupPrivilegeValue
#undef LookupPrivilegeName
#undef LookupPrivilegeDisplayName
#undef BuildCommDCB
#undef BuildCommDCBAndTimeouts
#undef CommConfigDialog
#undef GetDefaultCommConfig
#undef SetDefaultCommConfig
#undef GetComputerName
#undef SetComputerName
#undef GetComputerNameEx
#undef SetComputerNameEx
#undef DnsHostnameToComputerName
#undef GetUserName
#undef LogonUser
#undef LogonUserEx
#undef CreateProcessAsUser
#undef CreatePrivateNamespace
#undef OpenPrivateNamespace
#undef CreateBoundaryDescriptor
#undef GetCurrentHwProfile
#undef GetVersionEx
#undef VerifyVersionInfo
#undef CreateJobObject
#undef OpenJobObject
#undef FindFirstVolume
#undef FindNextVolume
#undef FindFirstVolumeMountPoint
#undef FindNextVolumeMountPoint
#undef SetVolumeMountPoint
#undef DeleteVolumeMountPoint
#undef GetVolumeNameForVolumeMountPoint
#undef GetVolumePathName
#undef GetVolumePathNamesForVolumeName
#undef CreateActCtx
#undef FindActCtxSectionString
#undef CreateSymbolicLink
#undef CreateSymbolicLinkTransacted
#undef GetFinalPathNameByHandle


#if 0
typedef MENUTEMPLATEW MENUTEMPLATE;
typedef LPMENUTEMPLATEW LPMENUTEMPLATE;
typedef PROPENUMPROCW        PROPENUMPROC;
typedef PROPENUMPROCEXW      PROPENUMPROCEX;
typedef EDITWORDBREAKPROCW   EDITWORDBREAKPROC;
typedef WINSTAENUMPROCW     WINSTAENUMPROC;
typedef DESKTOPENUMPROCW    DESKTOPENUMPROC;
typedef CBT_CREATEWNDW CBT_CREATEWND;
typedef LPCBT_CREATEWNDW LPCBT_CREATEWND;
typedef WNDCLASSEXW WNDCLASSEX;
typedef PWNDCLASSEXW PWNDCLASSEX;
typedef NPWNDCLASSEXW NPWNDCLASSEX;
typedef LPWNDCLASSEXW LPWNDCLASSEX;
typedef WNDCLASSW WNDCLASS;
typedef PWNDCLASSW PWNDCLASS;
typedef NPWNDCLASSW NPWNDCLASS;
typedef LPWNDCLASSW LPWNDCLASS;
typedef CREATESTRUCTW CREATESTRUCT;
typedef LPCREATESTRUCTW LPCREATESTRUCT;
typedef LPDLGTEMPLATEW LPDLGTEMPLATE;
typedef LPCDLGTEMPLATEW LPCDLGTEMPLATE;
typedef PDLGITEMTEMPLATEW PDLGITEMTEMPLATE;
typedef LPDLGITEMTEMPLATEW LPDLGITEMTEMPLATE;
typedef MENUITEMINFOW MENUITEMINFO;
typedef LPMENUITEMINFOW LPMENUITEMINFO;
typedef LPCMENUITEMINFOW LPCMENUITEMINFO;
typedef MSGBOXPARAMSW MSGBOXPARAMS;
typedef PMSGBOXPARAMSW PMSGBOXPARAMS;
typedef LPMSGBOXPARAMSW LPMSGBOXPARAMS;
typedef ICONINFOEXW ICONINFOEX;
typedef PICONINFOEXW PICONINFOEX;
typedef MDICREATESTRUCTW MDICREATESTRUCT;
typedef LPMDICREATESTRUCTW LPMDICREATESTRUCT;
typedef MULTIKEYHELPW MULTIKEYHELP;
typedef PMULTIKEYHELPW PMULTIKEYHELP;
typedef LPMULTIKEYHELPW LPMULTIKEYHELP;
typedef HELPWININFOW HELPWININFO;
typedef PHELPWININFOW PHELPWININFO;
typedef LPHELPWININFOW LPHELPWININFO;
typedef NONCLIENTMETRICSW NONCLIENTMETRICS;
typedef PNONCLIENTMETRICSW PNONCLIENTMETRICS;
typedef LPNONCLIENTMETRICSW LPNONCLIENTMETRICS;
typedef ICONMETRICSW ICONMETRICS;
typedef PICONMETRICSW PICONMETRICS;
typedef LPICONMETRICSW LPICONMETRICS;
typedef SERIALKEYSW SERIALKEYS;
typedef LPSERIALKEYSW LPSERIALKEYS;
typedef HIGHCONTRASTW HIGHCONTRAST;
typedef LPHIGHCONTRASTW LPHIGHCONTRAST;
typedef SOUNDSENTRYW SOUNDSENTRY;
typedef LPSOUNDSENTRYW LPSOUNDSENTRY;
typedef MONITORINFOEXW MONITORINFOEX;
typedef LPMONITORINFOEXW LPMONITORINFOEX;
typedef LOGCOLORSPACEW LOGCOLORSPACE;
typedef LPLOGCOLORSPACEW LPLOGCOLORSPACE;
typedef TEXTMETRICW TEXTMETRIC;
typedef PTEXTMETRICW PTEXTMETRIC;
typedef NPTEXTMETRICW NPTEXTMETRIC;
typedef LPTEXTMETRICW LPTEXTMETRIC;
typedef NEWTEXTMETRICW NEWTEXTMETRIC;
typedef PNEWTEXTMETRICW PNEWTEXTMETRIC;
typedef NPNEWTEXTMETRICW NPNEWTEXTMETRIC;
typedef LPNEWTEXTMETRICW LPNEWTEXTMETRIC;
typedef NEWTEXTMETRICEXW NEWTEXTMETRICEX;
typedef LOGFONTW LOGFONT;
typedef PLOGFONTW PLOGFONT;
typedef NPLOGFONTW NPLOGFONT;
typedef LPLOGFONTW LPLOGFONT;
typedef ENUMLOGFONTW ENUMLOGFONT;
typedef LPENUMLOGFONTW LPENUMLOGFONT;
typedef ENUMLOGFONTEXW ENUMLOGFONTEX;
typedef LPENUMLOGFONTEXW LPENUMLOGFONTEX;
typedef EXTLOGFONTW EXTLOGFONT;
typedef PEXTLOGFONTW PEXTLOGFONT;
typedef NPEXTLOGFONTW NPEXTLOGFONT;
typedef LPEXTLOGFONTW LPEXTLOGFONT;
typedef DEVMODEW DEVMODE;
typedef PDEVMODEW PDEVMODE;
typedef NPDEVMODEW NPDEVMODE;
typedef LPDEVMODEW LPDEVMODE;
typedef DEVMODEW DEVMODE;
typedef PDEVMODEW PDEVMODE;
typedef NPDEVMODEW NPDEVMODE;
typedef LPDEVMODEW LPDEVMODE;
typedef DISPLAY_DEVICEW DISPLAY_DEVICE;
typedef PDISPLAY_DEVICEW PDISPLAY_DEVICE;
typedef LPDISPLAY_DEVICEW LPDISPLAY_DEVICE;
typedef OUTLINETEXTMETRICW OUTLINETEXTMETRIC;
typedef POUTLINETEXTMETRICW POUTLINETEXTMETRIC;
typedef NPOUTLINETEXTMETRICW NPOUTLINETEXTMETRIC;
typedef LPOUTLINETEXTMETRICW LPOUTLINETEXTMETRIC;
typedef POLYTEXTW POLYTEXT;
typedef PPOLYTEXTW PPOLYTEXT;
typedef NPPOLYTEXTW NPPOLYTEXT;
typedef LPPOLYTEXTW LPPOLYTEXT;
typedef GCP_RESULTSW GCP_RESULTS;
typedef LPGCP_RESULTSW LPGCP_RESULTS;
#define OLDFONTENUMPROC  OLDFONTENUMPROCW
typedef FONTENUMPROCW FONTENUMPROC;
typedef AXISINFOW AXISINFO;
typedef PAXISINFOW PAXISINFO;
typedef LPAXISINFOW LPAXISINFO;
typedef AXESLISTW AXESLIST;
typedef PAXESLISTW PAXESLIST;
typedef LPAXESLISTW LPAXESLIST;
typedef ENUMLOGFONTEXDVW ENUMLOGFONTEXDV;
typedef PENUMLOGFONTEXDVW PENUMLOGFONTEXDV;
typedef LPENUMLOGFONTEXDVW LPENUMLOGFONTEXDV;
typedef ENUMTEXTMETRICW ENUMTEXTMETRIC;
typedef PENUMTEXTMETRICW PENUMTEXTMETRIC;
typedef LPENUMTEXTMETRICW LPENUMTEXTMETRIC;
typedef DOCINFOW DOCINFO;
typedef LPDOCINFOW LPDOCINFO;
typedef STARTUPINFOW STARTUPINFO;
typedef LPSTARTUPINFOA LPSTARTUPINFO;
typedef STARTUPINFOEXW STARTUPINFOEX;
typedef LPSTARTUPINFOEXW LPSTARTUPINFOEX;
typedef WIN32_FIND_DATAW WIN32_FIND_DATA;
typedef PWIN32_FIND_DATAW PWIN32_FIND_DATA;
typedef LPWIN32_FIND_DATAW LPWIN32_FIND_DATA;
typedef HW_PROFILE_INFOW HW_PROFILE_INFO;
typedef LPHW_PROFILE_INFOW LPHW_PROFILE_INFO;
typedef ACTCTXW ACTCTX;
typedef PACTCTXW PACTCTX;
typedef PCACTCTXW PCACTCTX;
#endif

namespace bksge
{

namespace win32
{

template <typename CharT> struct WindowClassEx;
template <> struct WindowClassEx<char>
{
	using type = ::WNDCLASSEXA;
};
template <> struct WindowClassEx<wchar_t>
{
	using type = ::WNDCLASSEXW;
};

template <typename CharT> LONG_PTR SetWindowLongPtr(HWND hwnd, int index, LONG_PTR new_long);
template <> inline LONG_PTR SetWindowLongPtr<char>(HWND hwnd, int index, LONG_PTR new_long)
{
	return ::SetWindowLongPtrA(hwnd, index, new_long);
}
template <> inline LONG_PTR SetWindowLongPtr<wchar_t>(HWND hwnd, int index, LONG_PTR new_long)
{
	return ::SetWindowLongPtrW(hwnd, index, new_long);
}

template <typename CharT> LONG_PTR GetWindowLongPtr(HWND hwnd, int index);
template <> inline LONG_PTR GetWindowLongPtr<char>(HWND hwnd, int index)
{
	return ::GetWindowLongPtrA(hwnd, index);
}
template <> inline LONG_PTR GetWindowLongPtr<wchar_t>(HWND hwnd, int index)
{
	return ::GetWindowLongPtrW(hwnd, index);
}

template <typename CharT> LRESULT CALLBACK DefWindowProc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);
template <> inline LRESULT CALLBACK DefWindowProc<char>(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
	return ::DefWindowProcA(hwnd, msg, w_param, l_param);
}
template <> inline LRESULT CALLBACK DefWindowProc<wchar_t>(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
	return ::DefWindowProcW(hwnd, msg, w_param, l_param);
}

template <typename CharT> HINSTANCE GetModuleHandle(CharT const* module_name);
template <> inline HINSTANCE GetModuleHandle(char const* module_name)
{
	return ::GetModuleHandleA(module_name);
}
template <> inline HINSTANCE GetModuleHandle(wchar_t const* module_name)
{
	return ::GetModuleHandleW(module_name);
}

inline HWND CreateWindowEx(DWORD window_style_ex, char const* class_name, char const* title, DWORD window_style, int x, int y, int width, int height, HWND parent, HMENU menu, HINSTANCE instance, void* param)
{
	return ::CreateWindowExA(window_style_ex, class_name, title, window_style, x, y, width, height, parent, menu, instance, param);
}
inline HWND CreateWindowEx(DWORD window_style_ex, wchar_t const* class_name, wchar_t const* title, DWORD window_style, int x, int y, int width, int height, HWND parent, HMENU menu, HINSTANCE instance, void* param)
{
	return ::CreateWindowExW(window_style_ex, class_name, title, window_style, x, y, width, height, parent, menu, instance, param);
}

inline HMODULE LoadLibrary(char const* lpLibFileName)
{
	return ::LoadLibraryA(lpLibFileName);
}

inline HMODULE LoadLibrary(wchar_t const* lpLibFileName)
{
	return ::LoadLibraryW(lpLibFileName);
}

inline HICON LoadIcon(HINSTANCE instance, char const* icon_name)
{
	return ::LoadIconA(instance, icon_name);
}
inline HICON LoadIcon(HINSTANCE instance, wchar_t const* icon_name)
{
	return ::LoadIconW(instance, icon_name);
}

inline HCURSOR LoadCursor(HINSTANCE instance, char const* cursor_name)
{
	return ::LoadCursorA(instance, cursor_name);
}
inline HCURSOR LoadCursor(HINSTANCE instance, wchar_t const* cursor_name)
{
	return ::LoadCursorW(instance, cursor_name);
}

inline ATOM RegisterClassEx(::WNDCLASSEXA const* wc)
{
	return ::RegisterClassExA(wc);
}
inline ATOM RegisterClassEx(::WNDCLASSEXW const* wc)
{
	return ::RegisterClassExW(wc);
}

inline BOOL SetWindowText(HWND hWnd, char const* lpString)
{
	return ::SetWindowTextA(hWnd, lpString);
}
inline BOOL SetWindowText(HWND hWnd, wchar_t const* lpString)
{
	return ::SetWindowTextW(hWnd, lpString);
}

inline HFONT CreateFont(
	int nHeight,
	int nWidth,
	int nEscapement,
	int nOrientation,
	int fnWeight,
	DWORD fdwItalic,
	DWORD fdwUnderline,
	DWORD fdwStrikeOut,
	DWORD fdwCharSet,
	DWORD fdwOutputPrecision,
	DWORD fdwClipPrecision,
	DWORD fdwQuality,
	DWORD fdwPitchAndFamily,
	char const* lpszFace)
{
	return ::CreateFontA(
			   nHeight,
			   nWidth,
			   nEscapement,
			   nOrientation,
			   fnWeight,
			   fdwItalic,
			   fdwUnderline,
			   fdwStrikeOut,
			   fdwCharSet,
			   fdwOutputPrecision,
			   fdwClipPrecision,
			   fdwQuality,
			   fdwPitchAndFamily,
			   lpszFace);
}

inline HFONT CreateFont(
	int nHeight,
	int nWidth,
	int nEscapement,
	int nOrientation,
	int fnWeight,
	DWORD fdwItalic,
	DWORD fdwUnderline,
	DWORD fdwStrikeOut,
	DWORD fdwCharSet,
	DWORD fdwOutputPrecision,
	DWORD fdwClipPrecision,
	DWORD fdwQuality,
	DWORD fdwPitchAndFamily,
	wchar_t const* lpszFace)
{
	return ::CreateFontW(
			   nHeight,
			   nWidth,
			   nEscapement,
			   nOrientation,
			   fnWeight,
			   fdwItalic,
			   fdwUnderline,
			   fdwStrikeOut,
			   fdwCharSet,
			   fdwOutputPrecision,
			   fdwClipPrecision,
			   fdwQuality,
			   fdwPitchAndFamily,
			   lpszFace);
}

inline DWORD GetGlyphOutline(
	HDC hdc,
	UINT uChar,
	UINT uFormat,
	LPGLYPHMETRICS lpgm,
	DWORD cbBuffer,
	LPVOID lpvBuffer,
	CONST MAT2 *lpmat2)
{
	// Unicode指定に限定
#if 1
	return ::GetGlyphOutlineW(hdc, uChar, uFormat, lpgm, cbBuffer, lpvBuffer, lpmat2);
#else
	return ::GetGlyphOutlineA(hdc, uChar, uFormat, lpgm, cbBuffer, lpvBuffer, lpmat2);
#endif
}

inline BOOL GetTextMetrics(HDC hdc, TEXTMETRICA* lptm)
{
	return ::GetTextMetricsA(hdc, lptm);
}

inline BOOL GetTextMetrics(HDC hdc, TEXTMETRICW* lptm)
{
	return ::GetTextMetricsW(hdc, lptm);
}

inline FARPROC GetProcAddress(HMODULE hModule, char const* lpProcName)
{
	return ::GetProcAddress(hModule, lpProcName);
}

inline VOID PostQuitMessage(int nExitCode)
{
	return ::PostQuitMessage(nExitCode);
}

inline HBRUSH CreateSolidBrush(COLORREF color)
{
	return ::CreateSolidBrush(color);
}

inline BOOL DestroyWindow(HWND hWnd)
{
	return ::DestroyWindow(hWnd);
}

inline BOOL ShowWindow(HWND hWnd, int nCmdShow)
{
	return ::ShowWindow(hWnd, nCmdShow);
}

inline BOOL SetWindowPos(HWND hWnd, HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags)
{
	return ::SetWindowPos(hWnd, hWndInsertAfter, X, Y, cx, cy, uFlags);
}

inline BOOL PeekMessage(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
{
#if 1
	return ::PeekMessageW(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
#else
	return ::PeekMessageA(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
#endif
}

inline BOOL TranslateMessage(CONST MSG *lpMsg)
{
	return ::TranslateMessage(lpMsg);
}

inline LRESULT DispatchMessage(CONST MSG *lpMsg)
{
#if 1
	return ::DispatchMessageW(lpMsg);
#else
	return ::DispatchMessageA(lpMsg);
#endif
}

inline int TranslateAccelerator(HWND hWnd, HACCEL hAccTable, LPMSG lpMsg)
{
#if 1
	return ::TranslateAcceleratorW(hWnd, hAccTable, lpMsg);
#else
	return ::TranslateAcceleratorA(hWnd, hAccTable, lpMsg);
#endif
}

inline HANDLE CreateEvent(
	LPSECURITY_ATTRIBUTES lpEventAttributes,
	BOOL                  bManualReset,
	BOOL                  bInitialState,
	char const*           lpName)
{
	return ::CreateEventA(lpEventAttributes, bManualReset, bInitialState, lpName);
}

inline HANDLE CreateEvent(
	LPSECURITY_ATTRIBUTES lpEventAttributes,
	BOOL                  bManualReset,
	BOOL                  bInitialState,
	wchar_t const*        lpName)
{
	return ::CreateEventW(lpEventAttributes, bManualReset, bInitialState, lpName);
}

inline HANDLE CreateEventEx(
	LPSECURITY_ATTRIBUTES lpEventAttributes,
	char const*           lpName,
	DWORD                 dwFlags,
	DWORD                 dwDesiredAccess)
{
	return CreateEventExA(lpEventAttributes, lpName, dwFlags, dwDesiredAccess);
}

inline HANDLE CreateEventEx(
	LPSECURITY_ATTRIBUTES lpEventAttributes,
	wchar_t const*        lpName,
	DWORD                 dwFlags,
	DWORD                 dwDesiredAccess)
{
	return CreateEventExW(lpEventAttributes, lpName, dwFlags, dwDesiredAccess);
}

inline void OutputDebugString(char const* lpOutputString)
{
	::OutputDebugStringA(lpOutputString);
}

inline void OutputDebugString(wchar_t const* lpOutputString)
{
	::OutputDebugStringW(lpOutputString);
}

inline int MessageBox(
	HWND hWnd,
	char const* lpText,
	char const* lpCaption,
	UINT uType)
{
	return ::MessageBoxA(hWnd, lpText, lpCaption, uType);
}

inline int MessageBox(
	HWND hWnd,
	wchar_t const* lpText,
	wchar_t const* lpCaption,
	UINT uType)
{
	return ::MessageBoxW(hWnd, lpText, lpCaption, uType);
}

}	// namespace win32

}	// namespace bksge

#endif // BKSGE_DETAIL_WIN32_HPP
