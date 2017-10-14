#ifndef __TOVR_H
#define __TOVR_H

#include <windef.h>


#define TOVR_DLL_A  "TOVR.dll"
#define TOVR_DLL_W L"TOVR.dll"
#ifdef UNICODE
    #define TOVR_DLL TOVR_DLL_W
#else
    #define TOVR_DLL TOVR_DLL_A
#endif 

//
// Structures
//

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

//
// TrueOpenVR APIs
//

#ifdef __cplusplus
extern "C" __declspec(dllimport) {
#endif

DWORD _stdcall GetHMDData
(
    __out THMD *myHMD
);

DWORD _stdcall GetControllersData
(
    __out TController *myController,
    __out TController *myController2
);

DWORD _stdcall SetControllerData
(
    __in INT	dwIndex,	
    __in WORD	MotorSpeed	
);

DWORD _stdcall SetCentering
(
    __in INT	dwIndex	
);


#ifdef __cplusplus
}
#endif

#endif 

