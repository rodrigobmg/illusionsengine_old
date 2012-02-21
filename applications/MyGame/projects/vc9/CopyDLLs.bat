@echo off
CD %~dp0

FOR /F %%i IN (RequiredDLLs.txt) DO COPY "%%~i" ..\..\binaries\
