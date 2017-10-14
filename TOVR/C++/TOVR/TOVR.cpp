#include "stdafx.h"
#include <windows.h>
#include <atlbase.h>
#include "Shlwapi.h"
#include <atlstr.h>  

#define DLLEXPORT extern "C" __declspec(dllexport)

typedef struct _HMDData
{
	double	X;
	double	Y;
	double	Z;
	double	Yaw;
	double	Pitch;
	double	Roll;
} THMD, *PHMD;

typedef struct _Controller
{
	double	X;
	double	Y;
	double	Z;
	double	Yaw;
	double	Pitch;
	double	Roll;
	DWORD	Buttons;
	BYTE	Trigger;
	SHORT	ThumbX;
	SHORT	ThumbY;
} TController, *PController;

typedef DWORD(__stdcall *_GetHMDData)(__out THMD *myHMD);
typedef DWORD(__stdcall *_GetControllersData)(__out TController *MyController, __out TController *MyController2);
typedef DWORD(__stdcall *_SetControllerData)(__in INT	dwIndex, __in WORD	MotorSpeed);
typedef DWORD(__stdcall *_SetCentering)(__in int dwIndex);

_GetHMDData DriverGetHMDData;
_GetControllersData DriverGetControllersData;
_SetControllerData DriverSetControllerData;
_SetCentering DriverSetCentering;

DLLEXPORT DWORD __stdcall GetHMDData(__out THMD *myHMD);
DLLEXPORT DWORD __stdcall GetControllersData(__out TController *MyController, __out TController *MyController2);
DLLEXPORT DWORD __stdcall SetControllerData(__in INT	dwIndex, __in WORD	MotorSpeed);
DLLEXPORT DWORD __stdcall SetCentering(__in int dwIndex);

HMODULE hDll;
DWORD ScreenIndex;
DWORD ScreenControl;

void ScreenEnable(int dwIndex)
{
	DISPLAY_DEVICE Display;
	DEVMODE DevMode;

	Display.cb = sizeof(DISPLAY_DEVICE);
	EnumDisplayDevices(NULL, dwIndex, &Display, EDD_GET_DEVICE_INTERFACE_NAME);
	EnumDisplaySettings((LPCSTR)Display.DeviceName, ENUM_REGISTRY_SETTINGS, &DevMode);
	DevMode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY | DM_DISPLAYFLAGS | DM_POSITION;
	if (!(Display.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE)) {
		ChangeDisplaySettingsEx((LPCSTR)Display.DeviceName, &DevMode, 0, CDS_UPDATEREGISTRY | CDS_NORESET, NULL);
		ChangeDisplaySettingsEx(NULL, NULL, NULL, NULL, NULL);
	}
}


void ScreenDisable(int dwIndex)
{
	DISPLAY_DEVICE Display;
	DEVMODE DevMode;
	ZeroMemory(&DevMode, sizeof(DEVMODE));
	
	Display.cb = sizeof(DISPLAY_DEVICE);
	DevMode.dmSize = sizeof(DEVMODE);
	DevMode.dmBitsPerPel = 32;
	DevMode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY | DM_DISPLAYFLAGS | DM_POSITION;
	EnumDisplayDevices(NULL, dwIndex, &Display, EDD_GET_DEVICE_INTERFACE_NAME);
	if (!(Display.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE)) {
		ChangeDisplaySettingsEx((LPCSTR)Display.DeviceName, &DevMode, 0, CDS_UPDATEREGISTRY | CDS_NORESET, NULL);
		ChangeDisplaySettingsEx(NULL, NULL, NULL, NULL, NULL);
	}
}

void Init() {
	CRegKey key;
	TCHAR _driversPath[MAX_PATH];
	TCHAR _driverName[MAX_PATH];

	LONG status = key.Open(HKEY_CURRENT_USER, _T("Software\\TrueOpenVR"));
	if (status == ERROR_SUCCESS)
	{
		ULONG regSize = sizeof(_driverName);
		status = key.QueryStringValue(_T("Driver"), _driverName, &regSize);

		if (status == ERROR_SUCCESS)
		{
			regSize = sizeof(_driversPath);
			status = key.QueryStringValue(_T("Drivers"), _driversPath, &regSize);
		}

		key.QueryDWORDValue(_T("ScreenControl"), ScreenControl);
		key.QueryDWORDValue(_T("ScreenIndex"), ScreenIndex);
		ScreenIndex -= 1;
	}
	key.Close();

	if (status == ERROR_SUCCESS) {
		CString driversPath(_driversPath); 
		CString driverName(_driverName);

		if (PathFileExists(driversPath + driverName)) {

			hDll = LoadLibrary(driversPath + driverName);

			if (hDll != NULL) {

				DriverGetHMDData = (_GetHMDData)GetProcAddress(hDll, "GetHMDData");
				DriverGetControllersData = (_GetControllersData)GetProcAddress(hDll, "GetControllersData");
				DriverSetControllerData = (_SetControllerData)GetProcAddress(hDll, "SetControllerData");
				DriverSetCentering = (_SetCentering)GetProcAddress(hDll, "SetCentering");

				if (ScreenControl == TRUE)
					ScreenEnable(ScreenIndex);
			}
		}
	}
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH: {
			Init();
			break;
		}

		case DLL_PROCESS_DETACH: {
			if (hDll != NULL) {
				FreeLibrary(hDll);
				hDll = nullptr;
				if (ScreenControl == TRUE)
					ScreenDisable(ScreenIndex);
			}
			break;
		}
	}
	return TRUE;
}

DLLEXPORT DWORD __stdcall GetHMDData(__out THMD *myHMD)
{

	if (hDll != NULL) {
		return DriverGetHMDData(myHMD);
	}
	else {
		return 0;
	}
}

DLLEXPORT DWORD __stdcall GetControllersData(__out TController *myController, __out TController *myController2)
{
	if (hDll != NULL) {
		return DriverGetControllersData(myController, myController2);
	}
	else {
		return 0;
	}
}

DLLEXPORT DWORD __stdcall SetControllerData(__in INT dwIndex, __in WORD MotorSpeed)
{
	if (hDll != NULL) {
		return DriverSetControllerData(dwIndex, MotorSpeed);
	}
	else {
		return 0;
	}
}

DLLEXPORT DWORD __stdcall SetCentering(__in int dwIndex)
{
	if (hDll != NULL) {
		return DriverSetCentering(dwIndex);
	}
	else {
		return 0;
	}
}
