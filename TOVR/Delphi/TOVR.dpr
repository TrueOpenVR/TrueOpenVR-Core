//============ True Open Virtual Reality ============
//========== https://github.com/TrueOpenVR ==========

library TOVR;

uses
  SysUtils, Windows, Registry;

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
    Trigger: single;
    AxisX: single;
    AxisY: single;
end;
  Controller = _Controller;
  TController = Controller;

const
  TOVR_SUCCESS = 0;
  TOVR_FAILURE = 1;

var
  DriverPath: string;
  DriverDll: HMODULE;

  DriverGetHMDData: function(out MyHMD: THMD): DWORD; stdcall;
  DriverGetControllersData: function(out FirstController, SecondController: TController): DWORD; stdcall;
  DriverSetControllerData: function (dwIndex: integer; MotorSpeed: byte): DWORD; stdcall;

  HMD_YPR: array[0..2] of double = (0, 0, 0);
  FirstCtrl_YPR: array[0..2] of double = (0, 0, 0);
  SecondCtrl_YPR: array[0..2] of double = (0, 0, 0);

  HMD_Offset_YPR: array[0..2] of double = (0, 0, 0);
  FirstCtrl_Offset_YPR: array[0..2] of double = (0, 0, 0);
  SecondCtrl_Offset_YPR: array[0..2] of double = (0, 0, 0);

{$R *.res}

function OffsetYPR(f, f2: double): double;
begin
	f:=f - f2;
	if f < -180 then
		f:=f + 360
	else if f > 180 then
		f:=f - 360;
	Result:=f;
end;

function GetHMDData(out MyHMD: THMD): DWORD; stdcall;
var
  Status: integer;
begin
  if DriverDll <> 0 then begin
    Status:=DriverGetHMDData(MyHMD);
		HMD_YPR[0]:=MyHMD.Yaw;
		HMD_YPR[1]:=MyHMD.Pitch;
		HMD_YPR[2]:=MyHMD.Roll;
		MyHMD.Yaw:=OffsetYPR(HMD_YPR[0], HMD_Offset_YPR[0]);
		MyHMD.Pitch:=OffsetYPR(HMD_YPR[1], HMD_Offset_YPR[1]);
		MyHMD.Roll:=OffsetYPR(HMD_YPR[2], HMD_Offset_YPR[2]);
    
    Result:=Status;
  end else begin
    MyHMD.X:=0;
    MyHMD.Y:=0;
    MyHMD.Z:=0;
    MyHMD.Yaw:=0;
    MyHMD.Pitch:=0;
    MyHMD.Roll:=0;

    Result:=TOVR_FAILURE;
  end;
end;

function GetControllersData(out FirstController, SecondController: TController): DWORD; stdcall;
var
  Status: integer;
begin
  if DriverDll <> 0 then begin
    Status:=DriverGetControllersData(FirstController, SecondController);

		FirstController.Yaw:=OffsetYPR(FirstController.Yaw, FirstCtrl_Offset_YPR[0]);
		FirstController.Pitch:=OffsetYPR(FirstController.Pitch, FirstCtrl_Offset_YPR[1]);
		FirstController.Roll:=OffsetYPR(FirstController.Roll, FirstCtrl_Offset_YPR[2]);
		FirstCtrl_YPR[0]:=FirstController.Yaw;
		FirstCtrl_YPR[1]:=FirstController.Pitch;
		FirstCtrl_YPR[2]:=FirstController.Roll;

		SecondController.Yaw:=OffsetYPR(SecondController.Yaw, SecondCtrl_Offset_YPR[0]);
		SecondController.Pitch:=OffsetYPR(SecondController.Pitch, SecondCtrl_Offset_YPR[1]);
		SecondController.Roll:=OffsetYPR(SecondController.Roll, SecondCtrl_Offset_YPR[2]);
		SecondCtrl_YPR[0]:=SecondController.Yaw;
		SecondCtrl_YPR[1]:=SecondController.Pitch;
		SecondCtrl_YPR[2]:=SecondController.Roll;

    Result:=Status;
  end else begin
    FirstController.X:=0;
    FirstController.Y:=0;
    FirstController.Z:=0;

    FirstController.Yaw:=0;
    FirstController.Pitch:=0;
    FirstController.Roll:=0;

    FirstController.Buttons:=0;
    FirstController.Trigger:=0;
    FirstController.AxisX:=0;
    FirstController.AxisY:=0;

    SecondController.X:=0;
    SecondController.Y:=0;
    SecondController.Z:=0;

    SecondController.Yaw:=0;
    SecondController.Pitch:=0;
    SecondController.Roll:=0;

    SecondController.Buttons:=0;
    SecondController.Trigger:=0;
    SecondController.AxisX:=0;
    SecondController.AxisY:=0;

    Result:=TOVR_FAILURE;
  end;
end;

function SetControllerData(dwIndex: integer; MotorSpeed: byte): DWORD; stdcall;
begin
  if DriverDll <> 0 then
    Result:=DriverSetControllerData(dwIndex, MotorSpeed)
  else
    Result:=TOVR_FAILURE;
end;

function SetCentering(dwIndex: integer): DWORD; stdcall;
begin
  if DriverDll <> 0 then begin
      case dwIndex of
        0:
          begin
            HMD_Offset_YPR[0]:=HMD_YPR[0];
            HMD_Offset_YPR[1]:=HMD_YPR[1];
            HMD_Offset_YPR[2]:=HMD_YPR[2];
          end;
        1:
          begin
            FirstCtrl_Offset_YPR[0]:=FirstCtrl_YPR[0];
            FirstCtrl_Offset_YPR[1]:=FirstCtrl_YPR[1];
            FirstCtrl_Offset_YPR[2]:=FirstCtrl_YPR[2];
          end;
        2:
          begin
            SecondCtrl_Offset_YPR[0]:=SecondCtrl_YPR[0];
            SecondCtrl_Offset_YPR[1]:=SecondCtrl_YPR[1];
            SecondCtrl_Offset_YPR[2]:=SecondCtrl_YPR[2];
          end;
      end;
    Result:=TOVR_SUCCESS;
  end else
    Result:=TOVR_FAILURE;
end;

procedure GetRegValues;
var
  Reg: TRegistry;
begin
  Reg:=TRegistry.Create;
  Reg.RootKey:=HKEY_CURRENT_USER;
  if Reg.OpenKey('\Software\TrueOpenVR', false) = true then begin
    if (Reg.ReadString('Driver') <> '') and (FileExists(Reg.ReadString('Drivers') + Reg.ReadString('Driver'))) then
      DriverPath:=Reg.ReadString('Drivers') + Reg.ReadString('Driver')
    else
      DriverPath:='';
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
          DriverDll:=LoadLibrary(PChar(DriverPath));
          @DriverGetHMDData:=GetProcAddress(DriverDll, 'GetHMDData');
          @DriverGetControllersData:=GetProcAddress(DriverDll, 'GetControllersData');
          @DriverSetControllerData:=GetProcAddress(DriverDll, 'SetControllerData');

          if (addr(DriverGetHMDData) = nil) or (addr(DriverGetControllersData) = nil) or (addr(DriverSetControllerData) = nil) then
					  DriverDll:=0;
        end;
      end;

    DLL_PROCESS_DETACH:
      if DriverDll <> 0 then
        FreeLibrary(DriverDll);
  end;
end;

exports
  GetHMDData index 1, GetControllersData index 2, SetControllerData index 3, SetCentering index 4;

begin
  DllProc:=@DllMain;
  DllProc(DLL_PROCESS_ATTACH);
end.
 