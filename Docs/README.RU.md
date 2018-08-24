[![EN](https://user-images.githubusercontent.com/9499881/33184537-7be87e86-d096-11e7-89bb-f3286f752bc6.png)](https://github.com/TrueOpenVR/TrueOpenVR-Core/blob/master/Docs/README.md) 
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
Параметры реестра находятся в ветке `HKEY_CURRENT_USER\Software\TrueOpenVR`.

| Название  | Описание |
| ------------- | ------------- |
| `Library` | Путь до основной 32-битной библиотеки с функциями. |
| `Library64` | Путь до основной 64-битной библиотеки с функциями. |
| `ScreenIndex` | Индекс VR дисплея. Например, 1 это основной дисплей, а 2 это VR дисплей. |
| `RenderWidth` и `RenderHeight` | Разрешение области рендера. Например, у пользователя недостаточно производительный компьютер и он уменьшает разрешение игры для повышения производительности. |
| `Driver` | Название текущего 32-битного драйвера. |
| `Driver64` | Название текущего 64-битного драйвера. |
| `Drivers` | Путь до папки с драйверами. |
| `IPD` | Межзрачковое расстояние. |
| `DistortionK1`, `DistortionK2` | Коэффициенты коррекции искажений линз для VR шлемов. |
| `DistanceScaleX`, `DistanceScaleY` | Масштабирование стерео изображений по вертикали и горизонтали. Значения от 0 до 1, где 1 это 100% одного стерео изображения. Пользователь может уменьшить их. Необходимо для изменения стерео изображений под размер линз VR гарнитуры. |
| `OffsetX`, `OffsetY` | Смещение изображения по вертикали и горизонтали. Пользователь может сместить изображение вверх (-n) или вниз (n), влево (-n) или вправо (n). Значения в процентах от -1 до 1, по умолчанию 0. Необходимо для самодельных VR шлемов и шлемов на базе Android смартфона. |
| `HMDProfiles` | Путь до папки с профилями VR шлемов. |
| `ScreenControl` | Автоматическое включение и отключение VR дисплея. Включение опции - 1, выключение - 0. |
