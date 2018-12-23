# GetControllersData
Получение состояния позиции, вращения, кнопок, стиков и триггеров двух контроллеров.

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

#### Параметры
FirstController [out] - Указатель на структуру TController, которая получает текущее состояние первого контроллера.
SecondController [out] - Указатель на структуру TController, которая получает текущее состояние второго контроллера.

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

| Тип | Описание | Значения |
| ------------- | ------------- | ------------- |
| X, Y, Z | Отслеживание позиции | 0.000 (в метрах) |
| Yaw, Pitch, Roll | Отслеживание вращения | От -180 до 180 (в градусах) |
| Trigger | Триггера контроллера | От 0 до 1 |
| AxisX | Ось X стика | От -1 до 1 |
| AxisY | Ось Y стика | От -1 до 1 |

#### Buttons
Битовая маска кнопок контроллеров. Установленный бит указывает, что нажата соответствующая кнопка. 

| Кнопка | Битовая маска |
| ------------- | ------------- |
| GRIP_BTN | 0x0001  |
| THUMB_BTN | 0x0002  |
| A_BTN | 0x0004  |
| B_BTN | 0x0008  |
| MENU_BTN | 0x0010  |
| SYS_BTN | 0x0020  |

#### Возвращаемое значение
Если контроллеры подключенены и функция успешно завершилась, возвращаемое значение равно 0, иначе 1.