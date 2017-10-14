# SetCentering
Centering the device (reset rotation).

С++
```c
DWORD SetCentering(
	__in int dwIndex
);
```

Delphi
```pascal
function SetCentering(
	dwIndex: integer
): DWORD;
```

#### Parameters
dwIndex - Device number, 1 - headset, 2 and 3 - the first and second controllers.

#### Return value
If the function succeeded, the return value is 1, otherwise 0.
