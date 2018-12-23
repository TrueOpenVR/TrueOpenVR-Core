# GetHMDData
Получение состояния вращения и позиции шлема.

С++
```c
DWORD GetHMDData(
	__out THMD *MyHMD
);
```

Delphi
```pascal
function GetHMDData(
	out MyHMD: THMD
): DWORD;
```

#### Параметры
MyHMD [out] - Указатель на структуру THMD, которая получает текущее состояние шлема.

#### Структура THMD
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

| Тип | Описание | Значения |
| ------------- | ------------- | ------------- |
| X, Y, Z | Отслеживание позиции | 0.000 (в метрах) |
| Yaw, Pitch, Roll | Отслеживание вращения | От -180 до 180 (в градусах) |

Если вы предпочитаете использовать кватернион, вы можете получить его из Yaw, Pitch, Roll.
```c
double qW, qX, qY, qZ;
myYaw = yaw * (3.14159265358979323846 / 180); //градусы в радианы
myRoll = roll * (3.14159265358979323846 / 180); //градусы в радианы
myPitch = pitch * (3.14159265358979323846 / 180); //градусы в радианы
qW = cos(myYaw * 0.5) * cos(myRoll * 0.5) * cos(myPitch * 0.5) + sin(myYaw * 0.5) * sin(myRoll * 0.5) * sin(myPitch * 0.5);
qX = cos(myYaw * 0.5) * sin(myRoll * 0.5) * cos(myPitch * 0.5) - sin(myYaw * 0.5) * cos(myRoll * 0.5) * sin(myPitch * 0.5);
qY = cos(myYaw * 0.5) * cos(myRoll * 0.5) * sin(myPitch * 0.5) + sin(myYaw * 0.5) * sin(myRoll * 0.5) * cos(myPitch * 0.5);
qZ = sin(myYaw * 0.5) * cos(myRoll * 0.5) * cos(myPitch * 0.5) - cos(myYaw * 0.5) * sin(myRoll * 0.5) * sin(myPitch * 0.5);
```

#### Возвращаемое значение
Если шлем подключен и функция успешно завершилась, возвращаемое значение равно 0, иначе 1.
