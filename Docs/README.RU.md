[![EN](https://user-images.githubusercontent.com/9499881/27683803-659dc988-5cd8-11e7-9c05-0b747e917666.png)](https://github.com/TrueOpenVR/TrueOpenVR-Core/blob/master/Docs/README.md) 
[![RU](https://user-images.githubusercontent.com/9499881/27683795-5b0fbac6-5cd8-11e7-929c-057833e01fb1.png)](https://github.com/TrueOpenVR/TrueOpenVR-Core/blob/master/Docs/README.RU.md) 
[![CN](https://user-images.githubusercontent.com/9499881/31012373-978ce414-a522-11e7-9936-387b1c530e2f.png)](https://github.com/TrueOpenVR/TrueOpenVR-Core/blob/master/Docs/README.CN.md) 
[![ES](https://user-images.githubusercontent.com/9499881/31012379-9d8f7764-a522-11e7-8bf4-739077369e8b.png)](https://github.com/TrueOpenVR/TrueOpenVR-Core/blob/master/Docs/README.ES.md) 
[![FR](https://user-images.githubusercontent.com/9499881/31012387-a7b4aaac-a522-11e7-8485-36ce58dc2d4a.png)](https://github.com/TrueOpenVR/TrueOpenVR-Core/blob/master/Docs/README.FR.md) 
[![DE](https://user-images.githubusercontent.com/9499881/31012392-ac051326-a522-11e7-9c8c-2186ddf553d0.png)](https://github.com/TrueOpenVR/TrueOpenVR-Core/blob/master/Docs/README.DE.md) 
[![PT](https://user-images.githubusercontent.com/9499881/31012384-a1d1b544-a522-11e7-8a13-3cb53450d55c.png)](https://github.com/TrueOpenVR/TrueOpenVR-Core/blob/master/Docs/README.PT.md)
# Функции TrueOpenVR
Все функции импортируются напрямую из библиотеки "TOVR.dll". Путь библиотеки можно получить из реестра Windows. 

| Название  | Описание |
| ------------- | ------------- |
| [GetHMDData](https://github.com/TrueOpenVR/TrueOpenVR-Core/blob/master/Docs/RU/Functions/GetHMDData.md) | Получение состояния вращения и позиции шлема. |
| [GetControllersData](https://github.com/TrueOpenVR/TrueOpenVR-Core/blob/master/Docs/RU/Functions/GetControllersData.md) | Получение состояния позиции, вращения, кнопок, стиков и триггеров двух контроллеров. |
| [SetControllerData](https://github.com/TrueOpenVR/TrueOpenVR-Core/blob/master/Docs/RU/Functions/SetControllerData.md) | Отправка данных контролеру. Функция используется для активации обратной отдачи (вибрации) на контроллерах. |
| [SetCentering](https://github.com/TrueOpenVR/TrueOpenVR-Core/blob/master/Docs/RU/Functions/SetCentering.md) | Центрирование устройства (сброс вращения). |


# Параметры TrueOpenVR
The application has two windows, the first window is the render for the VR display, and the second window is the control window. The control window is displayed on the desktop from which the application was launched. The control window has the ability to close the application, as well as other functions at the discretion of the developer.

The first render window should be run in the "Borderless Windowed FullScreen" mode, which means a normal window, without borders, with the size of the display resolution.

![](https://user-images.githubusercontent.com/9499881/27838382-5d76aadc-60fb-11e7-9a1c-a312f2dddccc.png)


Параметры реестра находятся в ветке `HKEY_CURRENT_USER\Software\TrueOpenVR`.

| Название  | Описание |
| ------------- | ------------- |
| `Library` | Путь до основной 32-битной библиотеки с функциями. |
| `Library64` | Путь до основной 64-битной библиотеки с функциями. |
| `ScreenIndex` | Индекс VR экрана. Например, 1 это основной дисплей, а 2 это VR дисплей. |
| `Scale` | Маштабирование изображения. Если значение содержит 1, изображение с длинной "RenderWidth" и высотой "RenderHeight" растягивается до "UserWidth" и "UserHeight". Если значение содержит 0, изображение не маштабируется и отображается в центре окна. Пустые области окна имеют черный фон. |
| `UserWidth` и `UserHeight` | Размеры изображения в окне. По умолчанию это размер дисплея "ScreenIndex", однако пользователь может его изменить, для устранения слепых зон в VR шлеме. |
| `RenderWidth` и `RenderHeight` | Разрешение области рендера. Например, у пользователя недостаточно производительный компьютер и он уменьшает разрешение игры для повышения производительности. |
| `FOV` | Поле зрения. |
| `Driver` | Название текущего драйвера. |
| `Drivers` | Путь до папки с драйверами.  |
| `ScreenControl` | Автоматическое включение и отключение VR дисплея. Включение опции - 1, выключение - 0. |
