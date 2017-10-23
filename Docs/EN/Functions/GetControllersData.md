# GetControllersData
Retrieves the state of the position, rotation, buttons, sticks and triggers of the two controllers.

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
	WORD	Buttons;
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

| Type | Description | Values |
| ------------- | ------------- | ------------- |
| X, Y, Z | Position tracking | Between -1.000 and 1.000 |
| Yaw, Pitch, Roll | Rotation tracking | Between -180 and 180 |
| Trigger | Analog trigger | Between 0 and 255 |
| ThumbX | Thumbstick x-axis | Between -32768 and 32767 |
| ThumbX | Thumbstick y-axis | Between -32768 and 32767 |

#### Buttons
Bitmask of the buttons controllers. A set bit indicates that the corresponding button is pressed. 

| Button | 	Bitmask |
| ------------- | ------------- |
| GRIPBTN | 0x0001  |
| THUMBSTICKBTN | 0x0002 |
| MENUBTN | 0x0004 |
| SYSTEMBTN | 0x0008 |

#### Return value
If the controllers are connected and the function succeeded, the return value is 1, otherwise 0.