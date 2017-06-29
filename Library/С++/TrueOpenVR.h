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

typedef struct _VRInfo
{
    INT	ScreenIndex;
    BOOL	Scale;
    INT	UserWidth;
    INT	UserHeight;
} TVRInfo, *PVRInfo;

typedef struct _Controllers
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
} TControllers, *PControllers;

//
// TrueOpenVR APIs
//

#ifdef __cplusplus
extern "C" {
#endif

DWORD WINAPI GetInfo
(
    __out PVRInfo* myVRInfo
);

DWORD WINAPI GetHMDData
(
    __out PHMD* myHMD
);

DWORD WINAPI GetControllersData
(
    __out PControllers* MyController,
    __out PControllers* MyController2
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

