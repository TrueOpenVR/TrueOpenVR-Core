# GetControllersData
Получение состояния кнопок, стиков и триггеров двух контроллеров.

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

#### Параметры
MyController [out] - Указатель на структуру TController, которая получает текущее состояние первого контроллера.
MyController2 [out] - Указатель на структуру TController, которая получает текущее состояние второго контроллера.

#### Структура TController
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
    Buttons: word;
    Trigger: byte;
    ThumbX: smallint;
    ThumbY: smallint;
end;
```

#### Возвращаемое значение
Если контроллеры подключенены и функция успешно завершилась, возвращаемое значение равно 1, иначе 0.