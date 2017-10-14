# GetControllersData
Retrieves the state of the buttons, sticks and triggers of the two controllers.

С++
```c
DWORD __stdcall GetControllersData(
	__out TController *MyController,
	__out TController *MyController2
);
```

Delphi
```pascal
function GetControllersData(
	out myController, myController2: TController
): DWORD;
```

#### Return value
If the controllers are connected and the function succeeded, the return value is 1, otherwise 0.

#### Parameters
MyController [out] - Pointer to an TController structure that receives the state of first controller.
MyController2 [out] - Pointer to an TController structure that receives the state of second controller.

#### Structure TController
C++
```c
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
```

Delphi
```pascal
PController = ^TController;
_Controller = record
	X: double;
    Y: double;
    Z: double;
    Yaw: double;
    Pitch: double;
    Roll: double;
    Buttons: dword;
    Trigger: byte;
    ThumbX: smallint;
    ThumbY: smallint;
end;
```
