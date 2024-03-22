@echo off
setlocal

REM install post-checkout hook
set "source=.githooks\post-checkout"
set "destination=.git\hooks"
copy /y "%source%" "%destination%"

REM install post-merge hook
set "source=.githooks\post-merge"
set "destination=.git\hooks"
copy /y "%source%" "%destination%"

REM run premake
call vendor\premake5\premake5.exe vs2022

PAUSE

