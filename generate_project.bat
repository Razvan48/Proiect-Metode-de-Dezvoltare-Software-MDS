@echo off
setlocal

set "source=.githooks\post-checkout"
set "destination=.git\hooks"

copy /y "%source%" "%destination%"

call vendor\premake5\premake5.exe vs2022

PAUSE

