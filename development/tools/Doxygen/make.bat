@echo off

rem First we remove the old documentation...
rmdir /S /Q ..\..\docs\api

rem Now we create the new documentation...
doxygen API
