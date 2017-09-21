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

typedef DWORD(_stdcall *_GetHMDData)(__out THMD* myHMD);
typedef DWORD(__stdcall *_GetControllersData)(__out TController* MyController, __out TController* MyController2);
typedef DWORD(__stdcall *_SetControllerData)(__in INT	dwIndex, __in DWORD	MotorSpeed);
typedef DWORD(__stdcall *_SetCentering)(__in int dwIndex);

_GetHMDData DriverGetHMDData;
_GetControllersData DriverGetControllersData;
_SetControllerData DriverSetControllerData;
_SetCentering DriverSetCentering;

DLLEXPORT DWORD __stdcall GetHMDData(__out THMD* myHMD);
DLLEXPORT DWORD __stdcall GetControllersData(__out TController* MyController, __out TController* MyController2);
DLLEXPORT DWORD __stdcall SetControllerData(__in INT	dwIndex, __in DWORD	MotorSpeed);
DLLEXPORT DWORD __stdcall SetCentering(__in int dwIndex);

HMODULE hDll;
bool Init = false;

void DriverAttach() {
	CRegKey key;
	TCHAR driversPath[MAX_PATH];
	TCHAR driverName[MAX_PATH];

	LONG status = key.Open(HKEY_CURRENT_USER, _T("Software\\TrueOpenVR"));
	if (status == ERROR_SUCCESS)
	{
		ULONG regSize = sizeof(driverName);
		status = key.QueryStringValue(_T("Driver"), driverName, &regSize);

		if (status == ERROR_SUCCESS)
		{
			regSize = sizeof(driversPath);
			status = key.QueryStringValue(_T("Drivers"), driversPath, &regSize);
		}
	}
	key.Close();

	if (status == ERROR_SUCCESS) {
		CString _driversPath(driversPath);
		CString _driverName(driverName);

		if (PathFileExists(_driversPath + _driverName)) {

			hDll = LoadLibrary(_driversPath + _driverName);

			if (hDll != NULL) {

				DriverGetHMDData = (_GetHMDData)GetProcAddress(hDll, "GetHMDData");
				DriverGetControllersData = (_GetControllersData)GetProcAddress(hDll, "GetControllersData");
				DriverSetControllerData = (_SetControllerData)GetProcAddress(hDll, "SetControllerData");
				DriverSetCentering = (_SetCentering)GetProcAddress(hDll, "SetCentering");
			}
		}
	}
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH: //DriverAttach(); 

	case DLL_PROCESS_DETACH: {
		if (hDll != NULL) {
			FreeLibrary(hDll);
			hDll = nullptr;
		}
	}

	//case DLL_THREAD_ATTACH: 
	//case DLL_THREAD_DETACH:
	break;
	}
	return TRUE;
}

DLLEXPORT DWORD __stdcall GetHMDData(__out THMD* myHMD)
{
	
	if (Init == false) { //Temporary solution, DllMain is not called
		Init = true;
		DriverAttach();
	}

	if (hDll != NULL) {
		return DriverGetHMDData(myHMD);
	}
	else {
		return 0;
	}
}

DLLEXPORT DWORD __stdcall GetControllersData(__out TController* myController, __out TController* myController2)
{
	if (hDll != NULL) {
		return DriverGetControllersData(myController, myController2);
	}
	else {
		return 0;
	}
}

DLLEXPORT DWORD __stdcall SetControllerData(__in INT	dwIndex, __in DWORD	MotorSpeed)
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
