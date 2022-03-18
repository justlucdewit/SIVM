@echo off

gcc ..\SIDOC\src\main.c -o ..\output\SIDOC -std=c99
echo SIDOC

gcc ..\SIVM\src\main.c -o ..\output\SIVM -std=c99
echo SIVM

gcc ..\SIAS\src\main.c -o ..\output\SIAS -std=c99
echo SIAS

gcc ..\SIDA\src\main.c -o ..\output\SIDA -std=c99
echo SIDA