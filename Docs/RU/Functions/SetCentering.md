# SetCentering
Центрирование устройства (сброс вращения и позиции).

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
dwIndex - Номер устройства, 0 - шлем, 1 и 2 - первый и второй контроллеры.

#### Возвращаемое значение
Если функция успешно завершилась, возвращаемое значение равно 1, иначе 0.
