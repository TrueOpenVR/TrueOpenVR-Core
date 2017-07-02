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
	DWORD	Buttons;
	BYTE	Trigger;
	SHORT	ThumbX;
	SHORT	ThumbY;
} TController, *PController;

//
// TrueOpenVR APIs
//

#ifdef __cplusplus
extern "C" {
#endif

DWORD WINAPI GetHMDData
(
    __out PHMD* myHMD
);

DWORD WINAPI GetControllersData
(
    __out PController* MyController,
    __out PController* MyController2
);

DWORD WINAPI SetControllerData
(
    __in INT	dxIndex,	
    __in DWORD	MotorSpeed	
);

DWORD WINAPI SetCentering
(
    __in INT	dxIndex	
);


#ifdef __cplusplus
}
#endif

#endif 

