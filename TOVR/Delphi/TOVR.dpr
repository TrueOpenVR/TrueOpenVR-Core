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
    Buttons: word;
    Trigger: byte;
    ThumbX: smallint;
    ThumbY: smallint;
end;
  Controller = _Controller;
  TController = Controller;

var
  DriverPath: string;
  ScreenIndex: integer;
  ScreenControl: boolean;
  DllHandle: HMODULE;

  DriverGetHMDData: function(out myHMD: THMD): DWORD; stdcall;
  DriverGetControllersData: function(out myController, myController2: TController): DWORD; stdcall;
  DriverSetControllerData: function (dwIndex: integer; MotorSpeed: word): DWORD; stdcall;
  DriverSetCentering: function (dwIndex: integer): DWORD; stdcall;

{$R *.res}

function GetHMDData(out myHMD: THMD): DWORD; stdcall;
begin
  if DllHandle <> 0 then
    Result:=DriverGetHMDData(myHMD)
  else
    Result:=0;
end;

function GetControllersData(out myController, myController2: TController): DWORD; stdcall;
begin
  if DllHandle <> 0 then
    Result:=DriverGetControllersData(myController, myController2)
  else
    Result:=0;
end;

function SetControllerData(dwIndex: integer; MotorSpeed: word): DWORD; stdcall;
begin
  if DllHandle <> 0 then
    Result:=DriverSetControllerData(dwIndex, MotorSpeed)
  else
    Result:=0;
end;

function SetCentering(dwIndex: integer): DWORD; stdcall;
begin
  if DllHandle <> 0 then
    Result:=DriverSetCentering(dwIndex)
  else
    Result:=0;
end;

const
  EDD_GET_DEVICE_INTERFACE_NAME = 1;
  ENUM_REGISTRY_SETTINGS = DWORD(-2);

procedure ScreenEnable(dwIndex: integer);
var
  Display: TDisplayDevice;
  DevMode: TDevMode;
begin
  Display.cb:=SizeOf(TDisplayDevice);
  EnumDisplayDevices(nil, dwIndex, Display, EDD_GET_DEVICE_INTERFACE_NAME);
  EnumDisplaySettings(PChar(@Display.DeviceName[0]), ENUM_REGISTRY_SETTINGS, DevMode);
  DevMode.dmFields:=DM_BITSPERPEL or DM_PELSWIDTH or DM_PELSHEIGHT or DM_DISPLAYFREQUENCY or DM_DISPLAYFLAGS or DM_POSITION;
  if (Display.StateFlags and DISPLAY_DEVICE_PRIMARY_DEVICE) <> DISPLAY_DEVICE_PRIMARY_DEVICE then begin
    ChangeDisplaySettingsEx(PChar(@Display.DeviceName[0]), DevMode, 0, CDS_UPDATEREGISTRY or CDS_NORESET, nil);
    ChangeDisplaySettingsEx(nil, PDevMode(nil)^, 0, 0, nil);
  end;
end;

procedure ScreenDisable(dwIndex: integer);
var
  Display: TDisplayDevice;
  DevMode: TDevMode;
begin
  Display.cb:=SizeOf(TDisplayDevice);
  EnumDisplayDevices(nil, dwIndex, Display, EDD_GET_DEVICE_INTERFACE_NAME);
  ZeroMemory(@DevMode, SizeOf(TDevMode));
  DevMode.dmSize:=SizeOf(TDevMode);
  DevMode.dmBitsPerPel:=32;
  DevMode.dmFields:=DM_BITSPERPEL or DM_PELSWIDTH or DM_PELSHEIGHT or DM_DISPLAYFREQUENCY or DM_DISPLAYFLAGS or DM_POSITION;
  if (Display.StateFlags and DISPLAY_DEVICE_PRIMARY_DEVICE) <> DISPLAY_DEVICE_PRIMARY_DEVICE then begin
    ChangeDisplaySettingsEx(PChar(@Display.DeviceName[0]), DevMode, 0, CDS_UPDATEREGISTRY or CDS_NORESET, nil);
    ChangeDisplaySettingsEx(nil, PDevMode(nil)^, 0, 0, nil);
  end;
end;

procedure GetRegValues;
var
  Reg: TRegistry;
begin
  Reg:=TRegistry.Create;
  Reg.RootKey:=HKEY_CURRENT_USER;
  if Reg.OpenKey('\Software\TrueOpenVR', false) = true then begin
    if FileExists(Reg.ReadString('Drivers') + Reg.ReadString('Driver')) then
      DriverPath:=Reg.ReadString('Drivers') + Reg.ReadString('Driver')
    else
      DriverPath:='';
    ScreenIndex:=Reg.ReadInteger('ScreenIndex') - 1;
    ScreenControl:=Reg.ReadBool('ScreenControl');
  end;
  Reg.CloseKey;
  Reg.Free;
end;

procedure DllMain(Reason: integer);
begin
  case Reason of
    DLL_PROCESS_ATTACH:
      begin
        GetRegValues;
        if DriverPath <> '' then begin
          DllHandle:=LoadLibrary(PChar(DriverPath));
          @DriverGetHMDData:=GetProcAddress(DllHandle, 'GetHMDData');
          @DriverGetControllersData:=GetProcAddress(DllHandle, 'GetControllersData');
          @DriverSetControllerData:=GetProcAddress(DllHandle, 'SetControllerData');
          @DriverSetCentering:=GetProcAddress(DllHandle, 'SetCentering');
          if (ScreenControl) then
            ScreenEnable(ScreenIndex);
        end;
      end;

    DLL_PROCESS_DETACH:
      if DllHandle <> 0 then begin
        FreeLibrary(DllHandle);
        if (ScreenControl) then
          ScreenDisable(ScreenIndex);
      end;
  end;
end;

exports
  GetHMDData index 1, GetControllersData index 2, SetControllerData index 3, SetCentering index 4;

begin
  DllProc:=@DllMain;
  DllProc(DLL_PROCESS_ATTACH);
end.
 