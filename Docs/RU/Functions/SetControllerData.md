# SetControllerData
Отправка данных контролеру. Функция используется для активации обратной отдачи (вибрации) на контроллерах.

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

#### Параметры
dwIndex - Номер контроллера (1 или 2).

MotorSpeed - Сила вибрации (от 0 до 65535).

#### Возвращаемое значение
Если контроллеры подключены и функция успешно завершилась, возвращаемое значение равно 1, иначе 0.