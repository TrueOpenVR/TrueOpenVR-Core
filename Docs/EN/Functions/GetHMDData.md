# GetHMDData
Retrieves the rotation and position state of headset.

С++
```c
DWORD GetHMDData(
	__out THMD *myHMD
);
```

Delphi
```pascal
function GetHMDData(
	out myHMD: THMD
): DWORD;
```

#### Parameters
myHMD [out] - Pointer to an THMD structure that receives the state of headset.

#### Structure THMD
C++
```c
typedef struct _HMDData
{
	double	X;
	double	Y;
	double	Z;
	double	Yaw;
	double	Pitch;
	double	Roll;
} THMD, *PHMD;
```

Delphi
```pascal
PHMD = ^THMD;
_HMDData = record
	X: double;
	Y: double;
    Z: double;
    Yaw: double;
    Pitch: double;
    Roll: double;
end;
HMD = _HMDData;
THMD = HMD;
```

| Type | Description | Values |
| ------------- | ------------- | ------------- |
| X, Y, Z | Position tracking | 0.000 (in meters) |
| Yaw, Pitch, Roll | Rotation tracking | Between -180 and 180 (in degrees) |

If you prefer to use a quaternion, you can get it from Yaw, Pitch, Roll.
```c
double qW, qX, qY, qZ;
myYaw = yaw * (3.14159265358979323846 / 180); //degrees to radians
myRoll = roll * (3.14159265358979323846 / 180); //degrees to radians
myPitch = pitch * (3.14159265358979323846 / 180); //degrees to radians
qW = cos(myYaw * 0.5) * cos(myRoll * 0.5) * cos(myPitch * 0.5) + sin(myYaw * 0.5) * sin(myRoll * 0.5) * sin(myPitch * 0.5);
qX = cos(myYaw * 0.5) * sin(myRoll * 0.5) * cos(myPitch * 0.5) - sin(myYaw * 0.5) * cos(myRoll * 0.5) * sin(myPitch * 0.5);
qY = cos(myYaw * 0.5) * cos(myRoll * 0.5) * sin(myPitch * 0.5) + sin(myYaw * 0.5) * sin(myRoll * 0.5) * cos(myPitch * 0.5);
qZ = sin(myYaw * 0.5) * cos(myRoll * 0.5) * cos(myPitch * 0.5) - cos(myYaw * 0.5) * sin(myRoll * 0.5) * sin(myPitch * 0.5);
```

#### Return value
If the headset is connected and the function succeeded, the return value is 1, otherwise 0.