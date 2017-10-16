[![EN](https://user-images.githubusercontent.com/9499881/27683803-659dc988-5cd8-11e7-9c05-0b747e917666.png)](https://github.com/TrueOpenVR/TrueOpenVR-Core/blob/master/Docs/README.md) 
[![RU](https://user-images.githubusercontent.com/9499881/27683795-5b0fbac6-5cd8-11e7-929c-057833e01fb1.png)](https://github.com/TrueOpenVR/TrueOpenVR-Core/blob/master/Docs/README.RU.md) 
[![CN](https://user-images.githubusercontent.com/9499881/31012373-978ce414-a522-11e7-9936-387b1c530e2f.png)](https://github.com/TrueOpenVR/TrueOpenVR-Core/blob/master/Docs/README.CN.md) 
[![ES](https://user-images.githubusercontent.com/9499881/31012379-9d8f7764-a522-11e7-8bf4-739077369e8b.png)](https://github.com/TrueOpenVR/TrueOpenVR-Core/blob/master/Docs/README.ES.md) 
[![FR](https://user-images.githubusercontent.com/9499881/31012387-a7b4aaac-a522-11e7-8485-36ce58dc2d4a.png)](https://github.com/TrueOpenVR/TrueOpenVR-Core/blob/master/Docs/README.FR.md) 
[![DE](https://user-images.githubusercontent.com/9499881/31012392-ac051326-a522-11e7-9c8c-2186ddf553d0.png)](https://github.com/TrueOpenVR/TrueOpenVR-Core/blob/master/Docs/README.DE.md) 
[![PT](https://user-images.githubusercontent.com/9499881/31012384-a1d1b544-a522-11e7-8a13-3cb53450d55c.png)](https://github.com/TrueOpenVR/TrueOpenVR-Core/blob/master/Docs/README.PT.md)
# Functions TrueOpenVR
All functions are imported directly from the "TOVR.dll" library. The library path can be obtained from the registry.

| Name  | Description |
| ------------- | ------------- |
| [GetHMDData](https://github.com/TrueOpenVR/TrueOpenVR-Core/blob/master/Docs/EN/Functions/GetHMDData.md) | Retrieves the rotation and position state of headset. |
| [GetControllersData](https://github.com/TrueOpenVR/TrueOpenVR-Core/blob/master/Docs/EN/Functions/GetControllersData.md) | Retrieves the state of the position, rotation, buttons, sticks and triggers of the two controllers. |
| [SetControllerData](https://github.com/TrueOpenVR/TrueOpenVR-Core/blob/master/Docs/EN/Functions/SetControllerData.md) | Sends data to a controller. Function is used to activate the feedback (vibration) of a controllers. |
| [SetCentering](https://github.com/TrueOpenVR/TrueOpenVR-Core/blob/master/Docs/EN/Functions/SetCentering.md) | Centering the device (reset rotation). |

# Parameters TrueOpenVR
It is desirable that the application has two windows, a main window with a game or program for the VR display and a second small window located on the desktop of a conventional display (not a VR), with the ability to close the application and possibly some more functions.
The main window should be launched in the "Borderless Windowed FullScreen" mode, which means a normal window, without borders, with the size of the display resolution.

![](https://user-images.githubusercontent.com/9499881/27838382-5d76aadc-60fb-11e7-9a1c-a312f2dddccc.png)


The registry settings are in the branch `HKEY_CURRENT_USER\Software\TrueOpenVR`.

| Name  | Description |
| ------------- | ------------- |
| `Library` | The path to the main 32-bit library with functions. |
| `Library64` | The path to the main 64-bit library  with functions. |
| `ScreenIndex`  | VR screen index. For example, 1 is the main display, and 2 is the VR display.  |
| `Scale` | Scaling an image. If the value contains 1, the image with the long "RenderWidth" and the height of "RenderHeight" is stretched to "UserWidth" and "UserHeight". If the value contains 0, the image is not scaled and displayed in the center of the window. Empty areas of the window have a black background. |
| `UserWidth` and `UserHeight` | The size image in the window. By default, this is the size of the "ScreenIndex" display, but the user can change it to eliminate blind areas in the VR headset. |
| `RenderWidth` and `RenderHeight` | Resolution of the render area. For example, a user lacks a productive computer and reduces the resolution of the game to improve performance.  |
| `FOV` | Field of view. |
| `Driver` | Current driver name. |
| `Drivers` | Path to the folder with drivers. |
| `ScreenControl` | Automatically turn on and off VR display. Enabling the option is 1, the shutdown is 0. |