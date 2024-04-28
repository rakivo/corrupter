@echo on
setlocal

set CFLAGS=/Wall /WX /EHsc /Zi /MDd

cl %CFLAGS% /c main.c /Fo:main.obj

link main.obj /OUT:corruptor.exe /DEBUG

del main.obj

endlocal
