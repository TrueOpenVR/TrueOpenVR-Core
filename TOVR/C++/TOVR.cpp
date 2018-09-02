//============ True Open Virtual Reality ============
//========== https://github.com/TrueOpenVR ==========

#include "stdafx.h"
#include <atlstr.h> 
//#include <Windows.h>

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
	WORD	Buttons;
	BYTE	Trigger;
	SHORT	ThumbX;
	SHORT	ThumbY;
} TController, *PController;

#define TOVR_SUCCESS 1
#define TOVR_FAILURE 0

typedef DWORD(__stdcall *_GetHMDData)(__out THMD *myHMD);
typedef DWORD(__stdcall *_GetControllersData)(__out TController *myController, __out TController *myController2);
typedef DWORD(__stdcall *_SetControllerData)(__in int dwIndex, __in WORD MotorSpeed);
typedef DWORD(__stdcall *_SetCentering)(__in int dwIndex);

_GetHMDData DriverGetHMDData;
_GetControllersData DriverGetControllersData;
_SetControllerData DriverSetControllerData;
_SetCentering DriverSetCentering;

HMODULE hDll;

void Init() {
	CRegKey key;
	TCHAR _driversPath[MAX_PATH];
	TCHAR _driverName[MAX_PATH];

	LONG status = key.Open(HKEY_CURRENT_USER, _T("Software\\TrueOpenVR"));
	if (status == ERROR_SUCCESS)
	{
		ULONG regSize = sizeof(_driverName);
		
		#ifdef _WIN64
			status = key.QueryStringValue(_T("Driver64"), _driverName, &regSize);
		#else
			status = key.QueryStringValue(_T("Driver"), _driverName, &regSize);
		#endif

		if (status == ERROR_SUCCESS)
		{
			regSize = sizeof(_driversPath);
			status = key.QueryStringValue(_T("Drivers"), _driversPath, &regSize);
		}
	}
	key.Close();

	if (status == ERROR_SUCCESS) {
		CString driversPath(_driversPath); 
		CString driverName(_driverName);

		if (driverName != "" && PathFileExists(driversPath + driverName)) {

			hDll = LoadLibrary(driversPath + driverName);

			if (hDll != NULL) {

				DriverGetHMDData = (_GetHMDData)GetProcAddress(hDll, "GetHMDData");
				DriverGetControllersData = (_GetControllersData)GetProcAddress(hDll, "GetControllersData");
				DriverSetControllerData = (_SetControllerData)GetProcAddress(hDll, "SetControllerData");
				DriverSetCentering = (_SetCentering)GetProcAddress(hDll, "SetCentering");

				if (DriverGetHMDData == NULL || DriverGetControllersData == NULL || DriverSetControllerData == NULL || DriverSetCentering == NULL)
					hDll = NULL;

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
			}
			break;
		}
	}
	return true;
}

DLLEXPORT DWORD __stdcall GetHMDData(__out THMD *myHMD)
{
	if (hDll != NULL) {
		return DriverGetHMDData(myHMD);
	}
	else {
		myHMD->X = 0;
		myHMD->Y = 0;
		myHMD->Z = 0;
		myHMD->Yaw = 0;
		myHMD->Pitch = 0;
		myHMD->Roll = 0;

		return TOVR_FAILURE;
	}
}

DLLEXPORT DWORD __stdcall GetControllersData(__out TController *myController, __out TController *myController2)
{
	if (hDll != NULL) {
		return DriverGetControllersData(myController, myController2);
	}
	else {
		myController->X = 0;
		myController->Y = 0;
		myController->Z = 0;

		myController->Yaw = 0;
		myController->Pitch = 0;
		myController->Roll = 0;

		myController->Buttons = 0;
		myController->Trigger = 0;
		myController->ThumbX = 0;
		myController->ThumbY = 0;

		myController2->X = 0;
		myController2->Y = 0;
		myController2->Z = 0;

		myController2->Yaw = 0;
		myController2->Pitch = 0;
		myController2->Roll = 0;

		myController2->Buttons = 0;
		myController2->Trigger = 0;
		myController2->ThumbX = 0;
		myController2->ThumbY = 0;

		return TOVR_FAILURE;
	}
}

DLLEXPORT DWORD __stdcall SetControllerData(__in int dwIndex, __in WORD MotorSpeed)
{
	if (hDll != NULL) {
		return DriverSetControllerData(dwIndex, MotorSpeed);
	}
	else {
		return TOVR_FAILURE;
	}
}

DLLEXPORT DWORD __stdcall SetCentering(__in int dwIndex)
{
	if (hDll != NULL) {
		return DriverSetCentering(dwIndex);
	}
	else {
		return TOVR_FAILURE;
	}
}
