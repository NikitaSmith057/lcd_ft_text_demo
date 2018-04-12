@echo off

set AnnoyingWarnings= -wd4100 -wd4189 -wd4127 -wd4702
set CommonCompilerFlags= -Od -D_CRT_SECURE_NO_WARNINGS -MTd  -fp:fast -fp:except- -GR- -EHa- -Zo -EHsc -Z7 -Oi -W4 -Iinclude\ %AnnoyingWarnings%
set Libs= user32.lib msvcrt.lib libcmtd.lib opengl32.lib gdi32.lib libs\freetype29.lib
set LinkerFlags= -incremental:no -opt:ref -MACHINE:x64 -debug -NODEFAULTLIB:libcmt.lib %Libs%

cl -nologo %CommonCompilerFlags% %DebuggerDefines% main.c -link %LinkerFlags% -out:demo.exe
