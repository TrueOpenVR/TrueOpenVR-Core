[![EN](https://user-images.githubusercontent.com/9499881/27683803-659dc988-5cd8-11e7-9c05-0b747e917666.png)](https://github.com/TrueOpenVR/TrueOpenVR-Core/blob/master/Library/README.md) [![RU](https://user-images.githubusercontent.com/9499881/27683795-5b0fbac6-5cd8-11e7-929c-057833e01fb1.png)](https://github.com/TrueOpenVR/TrueOpenVR-Core/blob/master/Library/README.RU.md)
# Functions TrueOpenVR
**GetInfo** - Receiving data (monitor index, game resolution and scaling) to initialize the VR window. In case of successful reception, returns 1, otherwise 0.


**GetHMDData** - Receiving rotation data (Yaw, Pitch, Roll) and positioning (X, Y, Z) of the VR headset. In case of successful reception, returns 1, otherwise 0.

If you need a quaternion, you can calculate from Yaw, Pitch, Roll as follows:

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


**GetControllersData** - Receiving data (buttons, sticks, triggers) about the VR controller. In case of successful reception, returns 1, otherwise 0.


**SetControllerData** - Reverse feedback for the controller (vibration). In case of successful set, returns 1, otherwise 0.


**SetCentering** - Centering the device (reset rotation). In case of successful set, returns 1, otherwise 0.
