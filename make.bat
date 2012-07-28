:: Runs python scons, if possible
::
:: Peter Dodds (http://pddds.com) 2012

@goto start

:log
    @for %%I in (%*) do @echo.%~nx0: %%~I 1>&2
    @goto :EOF

:start

@setlocal
@set ErrorLevel=0
@pushd .

@%~d0
@cd %~p0

:: Try and use scons in the path...
@for %%I in ("scons.exe" "scons.bat" "scons.cmd" "scons.py") do @(
    if exist "%%~dp$PATH:I" (
        call:log "%%~I %*"
        %%~I %*
        goto quit
    )
)

:: Use the scons_local
@if not defined SconsPath @set SconsPath=site_scons\local
@if not exist "%SconsPath%\scons.py" @(
    call:log "Cannot find scons.py in `%SconsPath%'"
    call:log "You can get it from:"
    call:log "    http://www.scons.org/download.php"
    call:log "or set the correct path in %%%%SconsPath%%%%"
    set ErrorLevel=1
    goto quit
)

:: Check for python in the path.
@if not defined PythonPath @(
    for %%I in ("python.exe") do @set PythonPath=%%~dp$PATH:I
)
:: Try and find python if it's not in the path.
@if not defined PythonPath @(
    for /f "delims=" %%I in ('dir /b %SYSTEMDRIVE%\python*') do @(
        for %%J in ("%SYSTEMDRIVE%\%%~I") do @set PythonPath=%%~sfJ
    )
)

@if not exist "%PythonPath%\python.exe" @(
    call:log "Cannot find python.exe in `%PythonPath%`, try running:"
    call:log "    python site_scons\local\scons.py %*"
    call:log "or set the correct path in %%%%PythonPath%%%%"
    set ErrorLevel=1
    goto quit
)

@call:log "python %SconsPath%\scons.py %*"
@"%PythonPath%\python.exe" "%SconsPath%\scons.py" %*

:quit
@popd
@endlocal & "%COMSPEC%" /c exit /b %ErrorLevel%

:End
