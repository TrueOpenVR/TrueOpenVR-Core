# GetControllersData
Получение состояния позиции, вращения, кнопок, стиков и триггеров двух контроллеров.

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

| Тип | Описание | Значения |
| ------------- | ------------- | ------------- |
| X, Y, Z | Отслеживание позиции | От -1.000 до 1.000 |
| Yaw, Pitch, Roll | Отслеживание вращения | От -180 до 180 |
| Trigger | Триггера контроллера | От 0 до 255 |
| ThumbX | Ось X стика | От -32768 до 32767 |
| ThumbX | Ось Y стика | От -32768 до 32767 |

#### Buttons
Битовая маска кнопок контроллеров. Установленный бит указывает, что нажата соответствующая кнопка. 

| Кнопка | Битовая маска |
| ------------- | ------------- |
| GRIPBTN | 0x0001  |
| THUMBSTICKBTN | 0x0002 |
| MENUBTN | 0x0004 |
| SYSTEMBTN | 0x0008 |

#### Возвращаемое значение
Если контроллеры подключенены и функция успешно завершилась, возвращаемое значение равно 1, иначе 0.