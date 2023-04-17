@REM Clean up the previous build
del *.o
del *.lst
del *.map
del *.sym
del *.adb
del *.asm

C:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o main.o main.c

@REM ////// BANKS

C:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Wf-ba0 -c -o bank_0.o bank_0.c
C:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Wf-bo1 -Wf-ba1 -c -o bank_1.o bank_1.c
@REM C:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Wf-bo2 -Wf-ba2 -c -o savestate.o savestate.c
C:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Wf-bo2 -Wf-ba2 -c -o bank_2.o bank_2.c
C:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Wf-bo3 -Wf-ba3 -c -o bank_3.o bank_3.c Data/Cursors/Cursors.c
C:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Wf-bo4 -Wf-ba4 -c -o bank_4.o bank_4.c
C:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Wf-bo5 -Wf-ba5 -c -o bank_5.o bank_5.c


@REM //////// MERGE TO GAME
C:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Wl-yt2 -Wl-yo4 -Wl-ya4 -o main.gb main.o bank_0.o bank_1.o bank_2.o savestate.o bank_3.o bank_4.o bank_5.o
@REM bank_6.o




@REM /////// REMOVE CLUTTER
del *.o
del *.lst

@REM ///////// LOAD GAME
START C:\Users\efcha\Documents\banked\main.gb
