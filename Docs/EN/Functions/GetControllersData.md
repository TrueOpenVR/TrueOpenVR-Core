# GetControllersData
Retrieves the state of the position, rotation, buttons, sticks and triggers of the two controllers.

С++
```c
DWORD GetControllersData(
	__out TController *FirstController,
	__out TController *SecondController
);
```

Delphi
```pascal
function GetControllersData(
	out FirstController, SecondController: TController
): DWORD;
```

#### Parameters
FirstController [out] - Pointer to an TController structure that receives the state of first controller.
SecondController [out] - Pointer to an TController structure that receives the state of second controller.

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
	unsigned short	Buttons;
	float	Trigger;
	float	AxisX;
	float	AxisY;
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
    Buttons: word;
    Trigger: single;
    AxisX: single;
    AxisY: single;
end;
  Controller = _Controller;
  TController = Controller;
```

| Type | Description | Values |
| ------------- | ------------- | ------------- |
| X, Y, Z | Position tracking | 0.000 (in meters) |
| Yaw, Pitch, Roll | Rotation tracking | Between -180 and 180 (in degrees) |
| Trigger | Analog trigger | Between 0 and 1 |
| AxisX | Thumbstick x-axis | Between -1 and 1 |
| AxisY | Thumbstick y-axis | Between -1 and 1 |

#### Buttons
Bitmask of the buttons controllers. Set bit indicates that the corresponding button is pressed. 

| Button | Bitmask |
| ------------- | ------------- |
| GRIP_BTN | 0x0001  |
| THUMB_BTN | 0x0002  |
| A_BTN | 0x0004  |
| B_BTN | 0x0008  |
| MENU_BTN | 0x0010  |
| SYS_BTN | 0x0020  |

#### Return value
If the controllers are connected and the function succeeded, the return value is 0, otherwise 1.