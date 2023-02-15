@REM you should pass --debug to frontend (Wf--debug)
@REM you should pass -y to the linker to make it create a CDB file used for debugging (-Wl-y )
@REM and also pass -m -w to the linker to produce "wide maps" that are useful for emulicious (-Wl-m)
@REM add -Wl-j if you want to create NoICE symbol file .NOI for use in BGB emulator
@REM c:\gbdk\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-w -c -o main.o main.c
@REM c:\gbdk\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-w -o main.gb main.o


c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o main.o main.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -o main.gb main.o

START C:\Users\efcha\Documents\gb\helloworld\main.gb