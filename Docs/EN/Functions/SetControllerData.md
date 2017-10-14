# SetControllerData
Sends data to a controller. Function is used to activate the feedback (vibration) of a controllers.

С++
```c
DWORD SetControllerData(
	__in INT	dwIndex,
	__in WORD	MotorSpeed
);
```

Delphi
```pascal
function SetControllerData(
	dwIndex: integer;
	MotorSpeed: word
): DWORD;
```

#### Parameters
dwIndex - Controller number (1 or 2).

MotorSpeed - Vibration strength (from 0 to 65535).

#### Return value
If the controllers are connected and the function succeeded, the return value is 1, otherwise 0.