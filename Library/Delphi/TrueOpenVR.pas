unit TrueOpenVR;

interface

uses
  Windows, Registry, SysUtils;

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
  GetHMDData: function(out myHMD: THMD): DWORD; stdcall;
  GetControllersData: function(out myController, myController2: TController): DWORD; stdcall;
  SetControllerData: function (dwIndex: integer; MotorSpeed: dword): DWORD; stdcall;
  SetCentering: function (dwIndex: integer): DWORD; stdcall;

function TOVR_Init: Boolean;
procedure TOVR_Free;

implementation

var
  DllHandle: HMODULE;

function TOVR_Init: Boolean;
var
  Reg: TRegistry;
begin
  Reg:=TRegistry.Create;
  Reg.RootKey:=HKEY_CURRENT_USER;

  if Reg.OpenKey('\Software\TrueOpenVR', false) = false then begin
    Reg.CloseKey;
    Reg.Free;
    Result:=false;
    Exit;
  end;

  if FileExists(Reg.ReadString('Drivers') + Reg.ReadString('Driver')) = false then begin
    Reg.CloseKey;
    Reg.Free;
    Result:=false;
    Exit;
  end;

  if FileExists(Reg.ReadString('Drivers') + Reg.ReadString('Driver')) then begin
    DllHandle:=LoadLibrary(PChar(Reg.ReadString('Drivers') + Reg.ReadString('Driver')));
    @GetHMDData:=GetProcAddress(DllHandle, 'GetHMDData');
    @GetControllersData:=GetProcAddress(DllHandle, 'GetControllersData');
    @SetControllerData:=GetProcAddress(DllHandle, 'SetControllerData');
    @SetCentering:=GetProcAddress(DllHandle, 'SetCentering');
    Result:=true;
  end else
    Result:=false;

  Reg.CloseKey;
  Reg.Free;
end;

procedure TOVR_Free;
begin
  FreeLibrary(DllHandle);
end;

end.
