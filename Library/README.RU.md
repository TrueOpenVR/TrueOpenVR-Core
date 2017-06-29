[![Yummygum-Icon](https://user-images.githubusercontent.com/9499881/27683803-659dc988-5cd8-11e7-9c05-0b747e917666.png)](https://github.com/TrueOpenVR/TrueOpenVR-Core/blob/master/Library/README.md) [![Yummygum-Icon](https://user-images.githubusercontent.com/9499881/27683795-5b0fbac6-5cd8-11e7-929c-057833e01fb1.png)](https://github.com/TrueOpenVR/TrueOpenVR-Core/blob/master/Library/README.RU.md)
# Функции TrueOpenVR
**GetInfo** - Получение данных (индекс монитора, разрешение игры и маштабирование) для инциализации VR окна. В случае удачного получения возвращает 1, иначе 0. 


**GetHMDData** - Получение данных вращения (Yaw, Pitch, Roll) и позиционирования (X, Y, Z) VR шлема. В случае удачного получения возвращает 1, иначе 0. 

Если вам необходим кватернион, то можно рассчитать получить из Yaw, Pitch, Roll следующим образом:

t0, t1, t2, t3, t4, t5, qW, qX, qY, qZ - double.
>t0 = cos(DegToRad(yaw) * 0.5);
>t1 = sin(DegToRad(yaw) * 0.5);
>t2 = cos(DegToRad(roll) * 0.5);
>t3 = sin(DegToRad(roll) * 0.5);
>t4 = cos(DegToRad(pitch) * 0.5);
>t5 = sin(DegToRad(pitch) * 0.5);
>qW() = t0 * t2 * t4 + t1 * t3 * t5;
>qX() = t0 * t3 * t4 - t1 * t2 * t5;
>qY() = t0 * t2 * t5 + t1 * t3 * t4;
>qZ() = t1 * t2 * t4 - t0 * t3 * t5;


**GetControllersData** - Получение данных (кнопки, стики, триггеры) о VR контроллере. В случае удачного получения возвращает 1, иначе 0. 


**SetControllerData** - Обратная отдача для контроллера (вибрация). В случае удачного устаноки возвращает 1, иначе 0. 


**SetCentering** - Центрирование устройства (сброс вращения). В случае удачного установки возвращает 1, иначе 0. 