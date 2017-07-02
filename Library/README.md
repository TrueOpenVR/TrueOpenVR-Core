[![EN](https://user-images.githubusercontent.com/9499881/27683803-659dc988-5cd8-11e7-9c05-0b747e917666.png)](https://github.com/TrueOpenVR/TrueOpenVR-Core/blob/master/Library/README.md) [![RU](https://user-images.githubusercontent.com/9499881/27683795-5b0fbac6-5cd8-11e7-929c-057833e01fb1.png)](https://github.com/TrueOpenVR/TrueOpenVR-Core/blob/master/Library/README.RU.md)
# Functions TrueOpenVR
**GetHMDData** - Receiving rotation data (Yaw, Pitch, Roll) and positioning (X, Y, Z) of the VR headset. In case of successful reception, returns 1, otherwise 0.

If you need a quaternion, you can calculate from Yaw, Pitch, Roll as follows:

t0, t1, t2, t3, t4, t5, qW, qX, qY, qZ - double.
>t0 = cos(DegToRad(yaw) * 0.5);<br>
>t1 = sin(DegToRad(yaw) * 0.5);<br>
>t2 = cos(DegToRad(roll) * 0.5);<br>
>t3 = sin(DegToRad(roll) * 0.5);<br>
>t4 = cos(DegToRad(pitch) * 0.5);<br>
>t5 = sin(DegToRad(pitch) * 0.5);<br>
>qW() = t0 * t2 * t4 + t1 * t3 * t5;<br>
>qX() = t0 * t3 * t4 - t1 * t2 * t5;<br>
>qY() = t0 * t2 * t5 + t1 * t3 * t4;<br>
>qZ() = t1 * t2 * t4 - t0 * t3 * t5;<br>


**GetControllersData** - Receiving data (buttons, sticks, triggers) about the VR controller. In case of successful reception, returns 1, otherwise 0.


**SetControllerData** - Reverse feedback for the controller (vibration). In case of successful set, returns 1, otherwise 0.


**SetCentering** - Centering the device (reset rotation). In case of successful set, returns 1, otherwise 0.


Types and parameters of functions can be seen in libraries.

# Parameters TrueOpenVR
It is desirable that the application has two windows, a main window with a game or program for the VR display and a second small window located on the desktop of a conventional display (not a VR), with the ability to close the application and possibly some more functions.
The main window should be launched in the "Borderless Windowed FullScreen" mode, which means a normal window, without borders, with the size of the display resolution.


All parameters are in the registry branch "HKEY_CURRENT_USER\Software\TrueOpenVR".


The "ScreenIndex" parameter is responsible for the display number. For example, 1 is the main display, and 2 is the VR helmet.


The "Scale" parameter is responsible for scaling the image. If the parameter is set to "True", then the image with width "UserWidth" and height of "UserHeight" is stretched to the entire display "ScreenIndex".
If the parameter is set to "False", the image is not scaled and displayed in the center of the window, empty areas of the window have a black background. The parameter is necessary to eliminate blind areas in the VR headset.


The "UserWidth" and "UserHeight" parameters are responsible for the size of the image in the window. By default, this is the size of the "ScreenIndex" display, but the user can change it to eliminate blind areas.


The "RenderWidth" and "RenderHeight" parameters are responsible for resolution in applications or games. For example, a user lacks a productive computer and reduces the resolution of the game or application to improve performance.


The "Library" parameter is responsible for the path to the main library with the functions that you need to load to retrieve data.