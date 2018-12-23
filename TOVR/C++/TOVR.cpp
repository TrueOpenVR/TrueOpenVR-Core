//============ True Open Virtual Reality ============
//========== https://github.com/TrueOpenVR ==========

#include "stdafx.h"
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
	unsigned short	Buttons;
	float	Trigger;
	float	AxisX;
	float	AxisY;
} TController, *PController;

#define TOVR_SUCCESS 0
#define TOVR_FAILURE 1

typedef DWORD(__stdcall *_GetHMDData)(__out THMD *HMD);
typedef DWORD(__stdcall *_GetControllersData)(__out TController *FirstController, __out TController *SecondController);
typedef DWORD(__stdcall *_SetControllerData)(__in int dwIndex, __in unsigned char MotorSpeed);
typedef DWORD(__stdcall *_SetCentering)(__in int dwIndex);

_GetHMDData DriverGetHMDData;
_GetControllersData DriverGetControllersData;
_SetControllerData DriverSetControllerData;

double HMD_YPR[3] = {0, 0, 0};
double FirstCtrl_YPR[3] = { 0, 0, 0 };
double SecondCtrl_YPR[3] = { 0, 0, 0 };

double HMD_Offset_YPR[3] = { 0, 0, 0 };
double FirstCtrl_Offset_YPR[3] = { 0, 0, 0 };
double SecondCtrl_Offset_YPR[3] = { 0, 0, 0 };

HMODULE DriverDll;

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

			DriverDll = LoadLibrary(driversPath + driverName);

			if (DriverDll != NULL) {

				DriverGetHMDData = (_GetHMDData)GetProcAddress(DriverDll, "GetHMDData");
				DriverGetControllersData = (_GetControllersData)GetProcAddress(DriverDll, "GetControllersData");
				DriverSetControllerData = (_SetControllerData)GetProcAddress(DriverDll, "SetControllerData");

				if (DriverGetHMDData == NULL || DriverGetControllersData == NULL || DriverSetControllerData == NULL)
					DriverDll = NULL;
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
			if (DriverDll != NULL) {
				FreeLibrary(DriverDll);
				DriverDll = nullptr;
			}
			break;
		}
	}
	return true;
}

double OffsetYPR(double f, double f2)
{
	f -= f2;
	if (f < -180) {
		f += 360;
	}
	else if (f > 180) {
		f -= 360;
	}

	return f;
}

DLLEXPORT DWORD __stdcall GetHMDData(__out THMD *HMD)
{
	if (DriverDll != NULL) {
		int Status = DriverGetHMDData(HMD);
		HMD_YPR[0] = HMD->Yaw;
		HMD_YPR[1] = HMD->Pitch;
		HMD_YPR[2] = HMD->Roll;
		HMD->Yaw = OffsetYPR(HMD_YPR[0], HMD_Offset_YPR[0]);
		HMD->Pitch = OffsetYPR(HMD_YPR[1], HMD_Offset_YPR[1]);
		HMD->Roll = OffsetYPR(HMD_YPR[2], HMD_Offset_YPR[2]);
		return Status;
	}
	else {
		HMD->X = 0;
		HMD->Y = 0;
		HMD->Z = 0;
		HMD->Yaw = 0;
		HMD->Pitch = 0;
		HMD->Roll = 0;

		return TOVR_FAILURE;
	}
}

DLLEXPORT DWORD __stdcall GetControllersData(__out TController *FirstController, __out TController *SecondController)
{
	if (DriverDll != NULL) {
		int Status = DriverGetControllersData(FirstController, SecondController);
		FirstController->Yaw = OffsetYPR(FirstController->Yaw, FirstCtrl_Offset_YPR[0]);
		FirstController->Pitch = OffsetYPR(FirstController->Pitch, FirstCtrl_Offset_YPR[1]);
		FirstController->Roll = OffsetYPR(FirstController->Roll, FirstCtrl_Offset_YPR[2]);
		FirstCtrl_YPR[0] = FirstController->Yaw;
		FirstCtrl_YPR[1] = FirstController->Pitch;
		FirstCtrl_YPR[2] = FirstController->Roll;
		SecondController->Yaw = OffsetYPR(SecondController->Yaw, SecondCtrl_Offset_YPR[0]);
		SecondController->Pitch = OffsetYPR(SecondController->Pitch, SecondCtrl_Offset_YPR[1]);
		SecondController->Roll = OffsetYPR(SecondController->Roll, SecondCtrl_Offset_YPR[2]);
		SecondCtrl_YPR[0] = SecondController->Yaw;
		SecondCtrl_YPR[1] = SecondController->Pitch;
		SecondCtrl_YPR[2] = SecondController->Roll;
		return Status;
	}
	else {
		FirstController->X = 0;
		FirstController->Y = 0;
		FirstController->Z = 0;

		FirstController->Yaw = 0;
		FirstController->Pitch = 0;
		FirstController->Roll = 0;

		FirstController->Buttons = 0;
		FirstController->Trigger = 0;
		FirstController->AxisX = 0;
		FirstController->AxisY = 0;

		SecondController->X = 0;
		SecondController->Y = 0;
		SecondController->Z = 0;

		SecondController->Yaw = 0;
		SecondController->Pitch = 0;
		SecondController->Roll = 0;

		SecondController->Buttons = 0;
		SecondController->Trigger = 0;
		SecondController->AxisX = 0;
		SecondController->AxisY = 0;

		return TOVR_FAILURE;
	}
}

DLLEXPORT DWORD __stdcall SetControllerData(__in int dwIndex, __in unsigned char MotorSpeed)
{
	if (DriverDll != NULL) {
		return DriverSetControllerData(dwIndex, MotorSpeed);
	}
	else {
		return TOVR_FAILURE;
	}
}

DLLEXPORT DWORD __stdcall SetCentering(__in int dwIndex)
{
	if (DriverDll != NULL) {
		switch (dwIndex)
		{
			case 0:
			{
				HMD_Offset_YPR[0] = HMD_YPR[0];
				HMD_Offset_YPR[1] = HMD_YPR[1];
				HMD_Offset_YPR[2] = HMD_YPR[2];
				break;
			}
			case 1:
			{
				FirstCtrl_Offset_YPR[0] = FirstCtrl_YPR[0];
				FirstCtrl_Offset_YPR[1] = FirstCtrl_YPR[1];
				FirstCtrl_Offset_YPR[2] = FirstCtrl_YPR[2];
				break;
			}
			case 2:
			{
				SecondCtrl_Offset_YPR[0] = SecondCtrl_YPR[0];
				SecondCtrl_Offset_YPR[1] = SecondCtrl_YPR[1];
				SecondCtrl_Offset_YPR[2] = SecondCtrl_YPR[2];
				break;
			}
			default:
				break;
		}
		return TOVR_SUCCESS;
	}
	else {
		return TOVR_FAILURE;
	}
}
