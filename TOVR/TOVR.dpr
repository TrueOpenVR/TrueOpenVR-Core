library TOVR;

uses
  SysUtils, Classes, Windows, IniFiles, Registry, Dialogs;

type
  //HMD
  PHMD = ^THMD;
  _HMDData = record
    X: double;
    Y: double;
    Z: double;
    Yaw: double;
    Pitch: double;
    Roll: double;
end;
  HMD = _HMDData;
  THMD = HMD;

  //VR Init
  PVRInfo = ^TVRInfo;
  _VRInfo = record
    ScreenIndex: integer;
    Scale: boolean;
    UserWidth: integer;
    UserHeight: integer;
  end;
  VRInfo = _VRInfo;
  TVRInfo = VRInfo;

  //Controllers
  PControllers = ^TControllers;
  _Controllers = record
    X: double;
    Y: double;
    Z: double;
    Yaw: double;
    Pitch: double;
    Roll: double;
    Buttons: dword;
    Trigger: byte;
    ThumbX: smallint;
    ThumbY: smallint;
end;
  Controllers = _Controllers;
  TControllers = Controllers;

var
  PluginPath: string;
  DllHandle: HMODULE;

  PluginGetInfo: function(out myVRInfo: TVRInfo): DWORD; stdcall;
  PluginGetHMDData: function(out myHMD: THMD): DWORD; stdcall;
  PluginGetControllersData: function(out myController, myController2: TControllers): DWORD; stdcall;
  PluginSetControllerData: function (dwIndex: integer; MotorSpeed: dword): DWORD; stdcall;
  PluginSetCentering: function (dwIndex: integer): DWORD; stdcall;

{$R *.res}

procedure GetPluginPath;
var
  Ini: TIniFile; Reg: TRegistry;
begin
  Reg:=TRegistry.Create;
  Reg.RootKey:=HKEY_CURRENT_USER;
  if Reg.OpenKey('\Software\TrueOpenVR', false) = false then Exit;
  if FileExists(Reg.ReadString('Path') + 'TOVR.ini') = false then Exit;

  Ini:=TIniFile.Create(Reg.ReadString('Path') + 'TOVR.ini');
  PluginPath:=Reg.ReadString('Path') + 'Plugins\' + Ini.ReadString('Plugin', 'Path', 'OpenTrackUDP.dll');
  Ini.Free;
  Reg.Free;
end;

function GetInfo(out myVRInfo: TVRInfo): DWORD; stdcall;
var
  Ini: TIniFile; Reg: TRegistry;
begin
  if FileExists(PluginPath) then begin
    Reg:=TRegistry.Create;
    Reg.RootKey:=HKEY_CURRENT_USER;
    Result:=0;
    if Reg.OpenKey('\Software\TrueOpenVR', false) = false then Exit;
    if FileExists(Reg.ReadString('Path') + 'TOVR.ini') = false then Exit;

    Ini:=TIniFile.Create(Reg.ReadString('Path') + 'TOVR.ini');
    MyVRInfo.ScreenIndex:=Ini.ReadInteger('VRInit', 'ScreenIndex', 0);
    myVRInfo.Scale:=Ini.ReadBool('VRInit', 'Scale', false);
    myVRInfo.UserWidth:=Ini.ReadInteger('VRInit', 'UserWidth', 1280);
    myVRInfo.UserHeight:=Ini.ReadInteger('VRInit', 'UserHeight', 720);
    PluginPath:=Reg.ReadString('Path') + 'Plugins\' + Ini.ReadString('Plugin', 'Path', 'OpenTrackUDP.dll');
    Ini.Free;
    Reg.Free;
    Result:=1;
  end else Result:=0;
end;

function GetHMDData(out myHMD: THMD): DWORD; stdcall;
var
  PluginHMD: THMD;
begin
  if FileExists(PluginPath) = false then begin Result:=0; Exit; end;
  Result:=PluginGetHMDData(PluginHMD);
  if Result <> 0 then begin
    myHMD.X:=PluginHMD.X;
    myHMD.Y:=PluginHMD.Y;
    myHMD.Z:=PluginHMD.Z;
    myHMD.Yaw:=PluginHMD.Yaw;
    myHMD.Pitch:=PluginHMD.Pitch;
    myHMD.Roll:=PluginHMD.Roll;
  end;
end;

function GetControllersData(out myController, myController2: TControllers): DWORD; stdcall;
var
  PluginController, PluginController2: TControllers;
begin
  if FileExists(PluginPath) = false then begin Result:=0; Exit; end;
  Result:=PluginGetControllersData(PluginController, PluginController2);
  if Result <> 0 then begin
    //Controller 1
    myController.X:=PluginController.X;
    myController.Y:=PluginController.Y;
    myController.Z:=PluginController.Z;

    myController.Yaw:=PluginController.Yaw;
    myController.Pitch:=PluginController.Pitch;
    myController.Roll:=PluginController.Roll;

    myController.Buttons:=PluginController.Buttons;
    myController.Trigger:=PluginController.Trigger;
    myController.ThumbX:=PluginController.ThumbX;
    myController.ThumbY:=PluginController.ThumbY;

    //Controller 2
    myController2.X:=PluginController2.X;
    myController2.Y:=PluginController2.Y;
    myController2.Z:=PluginController2.Z;

    myController2.Yaw:=PluginController2.Yaw;
    myController2.Pitch:=PluginController2.Pitch;
    myController2.Roll:=PluginController2.Roll;

    myController2.Buttons:=PluginController2.Buttons;
    myController2.Trigger:=PluginController2.Trigger;
    myController2.ThumbX:=PluginController2.ThumbX;
    myController2.ThumbY:=PluginController2.ThumbY;
  end;
end;

function SetControllerData(dwIndex: integer; MotorSpeed: dword): DWORD; stdcall;
begin
  if FileExists(PluginPath) = false then begin Result:=0; Exit; end;
  Result:=PluginSetControllerData(dwIndex, MotorSpeed);
end;

function SetCentering(dwIndex: integer): DWORD; stdcall;
begin
  if FileExists(PluginPath) = false then begin Result:=0; Exit; end;
  Result:=PluginSetCentering(dwIndex);
end;

exports
  GetInfo index 1, GetHMDData index 2, SetCentering index 3, GetControllersData index 4, SetControllerData index 5;

begin
  GetPluginPath;
  if FileExists(PluginPath) then begin
    DllHandle:=LoadLibrary(PChar(PluginPath));
    @PluginGetInfo:=GetProcAddress(DllHandle, 'GetInfo');
    @PluginGetHMDData:=GetProcAddress(DllHandle, 'GetHMDData');
    @PluginGetControllersData:=GetProcAddress(DllHandle, 'GetControllersData');
    @PluginSetControllerData:=GetProcAddress(DllHandle, 'SetControllerData');
    @PluginSetCentering:=GetProcAddress(DllHandle, 'SetCentering');
  end;
end.
 