library TOVR;

uses
  SysUtils, Classes, Windows, Registry;

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

  //Controllers
  PController = ^TController;
  _Controller = record
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
  Controller = _Controller;
  TController = Controller;

var
  DriverPath: string;
  DllHandle: HMODULE;

  DriverGetHMDData: function(out myHMD: THMD): DWORD; stdcall;
  DriverGetControllersData: function(out myController, myController2: TController): DWORD; stdcall;
  DriverSetControllerData: function (dwIndex: integer; MotorSpeed: dword): DWORD; stdcall;
  DriverSetCentering: function (dwIndex: integer): DWORD; stdcall;

{$R *.res}

procedure GetDriverPath;
var
  Reg: TRegistry;
begin
  Reg:=TRegistry.Create;
  Reg.RootKey:=HKEY_CURRENT_USER;
  if Reg.OpenKey('\Software\TrueOpenVR', false) = false then Exit;
  if FileExists(Reg.ReadString('Driver')) = false then Exit;
  DriverPath:=Reg.ReadString('Driver');
  Reg.Free;
end;

function GetHMDData(out myHMD: THMD): DWORD; stdcall;
var
  DriverHMD: THMD;
begin
  if FileExists(DriverPath) = false then begin Result:=0; Exit; end;
  Result:=DriverGetHMDData(DriverHMD);
  if Result <> 0 then begin
    myHMD.X:=DriverHMD.X;
    myHMD.Y:=DriverHMD.Y;
    myHMD.Z:=DriverHMD.Z;
    myHMD.Yaw:=DriverHMD.Yaw;
    myHMD.Pitch:=DriverHMD.Pitch;
    myHMD.Roll:=DriverHMD.Roll;
  end;
end;

function GetControllersData(out myController, myController2: TController): DWORD; stdcall;
var
  DriverController, DriverController2: TController;
begin
  if FileExists(DriverPath) = false then begin Result:=0; Exit; end;
  Result:=DriverGetControllersData(DriverController, DriverController2);
  if Result <> 0 then begin
    //Controller 1
    myController.X:=DriverController.X;
    myController.Y:=DriverController.Y;
    myController.Z:=DriverController.Z;

    myController.Yaw:=DriverController.Yaw;
    myController.Pitch:=DriverController.Pitch;
    myController.Roll:=DriverController.Roll;

    myController.Buttons:=DriverController.Buttons;
    myController.Trigger:=DriverController.Trigger;
    myController.ThumbX:=DriverController.ThumbX;
    myController.ThumbY:=DriverController.ThumbY;

    //Controller 2
    myController2.X:=DriverController2.X;
    myController2.Y:=DriverController2.Y;
    myController2.Z:=DriverController2.Z;

    myController2.Yaw:=DriverController2.Yaw;
    myController2.Pitch:=DriverController2.Pitch;
    myController2.Roll:=DriverController2.Roll;

    myController2.Buttons:=DriverController2.Buttons;
    myController2.Trigger:=DriverController2.Trigger;
    myController2.ThumbX:=DriverController2.ThumbX;
    myController2.ThumbY:=DriverController2.ThumbY;
  end;
end;

function SetControllerData(dwIndex: integer; MotorSpeed: dword): DWORD; stdcall;
begin
  if FileExists(DriverPath) = false then begin Result:=0; Exit; end;
  Result:=DriverSetControllerData(dwIndex, MotorSpeed);
end;

function SetCentering(dwIndex: integer): DWORD; stdcall;
begin
  if FileExists(DriverPath) = false then begin Result:=0; Exit; end;
  Result:=DriverSetCentering(dwIndex);
end;

exports
  GetHMDData index 1, GetControllersData index 2, SetControllerData index 3, SetCentering index 4;

begin
  GetDriverPath;
  if FileExists(DriverPath) then begin
    DllHandle:=LoadLibrary(PChar(DriverPath));
    @DriverGetHMDData:=GetProcAddress(DllHandle, 'GetHMDData');
    @DriverGetControllersData:=GetProcAddress(DllHandle, 'GetControllersData');
    @DriverSetControllerData:=GetProcAddress(DllHandle, 'SetControllerData');
    @DriverSetCentering:=GetProcAddress(DllHandle, 'SetCentering');
  end;
end.
 