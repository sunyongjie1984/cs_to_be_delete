@echo off

Rem Registering the server
.\ExceptionDemo\Debug\DemoServer.exe -regserver

Rem Run the demo
.\ExceptionDemo\Debug\ExceptionDemo.exe

Rem Terminate the server
tskill DemoServer