@ECHO OFF
tasm /m2 lab_7.asm
tlink /3 lab_7.obj
del *.obj
del *.map