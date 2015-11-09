; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!
;
; you need to build libarea and voxelcut first, then copy area.pyd, Microsoft.VC90.CRT.manifest, msvcm90.dll, msvcm90.dll, msvcp90.dll, msvcp90.dll, wxbase28ud_vc_custom.dll, wxmsw28ud_core_vc_custom.dll into this folder
; download py2exe, run py2exe using a command prompt and typing "python setup.py py2exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{B86D8536-EBDB-4A3B-B63D-B6B957308F66}
AppName=VoxelCut
AppVerName=VoxelCut 0.4.0
AppPublisher=Heeks Software
AppPublisherURL=http://code.google.com/p/voxelcut/
AppSupportURL=http://code.google.com/p/voxelcut/
AppUpdatesURL=http://code.google.com/p/voxelcut/
DefaultDirName={pf}\VoxelCut
DefaultGroupName=VoxelCut
OutputBaseFilename=VoxelCut 0.4.0
Compression=lzma
SolidCompression=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "C:\dev\VoxelCut\dist\*"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\dev\VoxelCut\redir.py"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\dev\VoxelCut\run.py"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\dev\VoxelCut\test.tap"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\dev\VoxelCut\initial.py"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\dev\VoxelCut\bitmaps\*"; DestDir: "{app}\bitmaps"; Flags: ignoreversion
Source: "C:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\redist\x86\Microsoft.VC90.CRT\*"; DestDir: "{app}"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\VoxelCut"; Filename: "{app}\voxelcut.exe"
Name: "{commondesktop}\VoxelCut"; Filename: "{app}\voxelcut.exe"; Tasks: desktopicon

[Run]
Filename: "{app}\voxelcut.exe"; Description: "{cm:LaunchProgram,VoxelCut}"; Flags: nowait postinstall skipifsilent

