CD %~dp0
RD /S /Q .\Distribute\
mkdir .\Distribute\

COPY ..\Release\VideoStreamGUI.exe .\Distribute\
COPY ..\Externals\datariver_sdk_c\datariver32delphi.dll .\Distribute

FOR /F %%i IN (RequiredDLLs.txt) DO COPY "..\Externals\OpenCV-2.2.0\Build\bin\Release\%%~i.dll" .\Distribute\

PAUSE