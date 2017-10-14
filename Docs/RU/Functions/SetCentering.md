# SetCentering
Центрирование устройства (сброс вращения).

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

#### Параметры
dwIndex - Номер устройства, 1 - шлем, 2 и 3 - первый и второй контроллеры.

#### Возвращаемое значение
Если функция успешно завершилась, возвращаемое значение равно 1, иначе 0.
