# SetControllerData
Sends data to a controller. Function is used to activate the feedback (vibration) of a controllers.

С++
```c
DWORD SetControllerData(
	__in INT	dwIndex,
	__in unsigned char	MotorSpeed
);
```

Delphi
```pascal
function SetControllerData(
	dwIndex: integer;
	MotorSpeed: byte
): DWORD;
```

#### Parameters
dwIndex - Controller number (1 or 2).

MotorSpeed - Vibration strength (from 0 to 255).

#### Return value
If the controllers are connected and the function succeeded, the return value is 0, otherwise 1.