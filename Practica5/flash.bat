@echo off
set LOGFILE=flash_log.txt

:: Start fresh log
echo [%DATE% %TIME%] Starting flash for %1 > %LOGFILE%
echo Current directory: %CD% >> %LOGFILE%
dir %1 >> %LOGFILE% 2>&1

:: Try to locate ssh.exe
echo Searching for ssh.exe... >> %LOGFILE%
where ssh >> %LOGFILE% 2>&1

:: Check common locations (32-bit vs 64-bit)
if exist C:\Windows\System32\OpenSSH\ssh.exe (
    set SSH_CMD=C:\Windows\System32\OpenSSH\ssh.exe
    echo Using System32\OpenSSH\ssh.exe >> %LOGFILE%
) else if exist C:\Windows\Sysnative\OpenSSH\ssh.exe (
    set SSH_CMD=C:\Windows\Sysnative\OpenSSH\ssh.exe
    echo Using Sysnative\OpenSSH\ssh.exe >> %LOGFILE%
) else if exist C:\Windows\SysWOW64\OpenSSH\ssh.exe (
    set SSH_CMD=C:\Windows\SysWOW64\OpenSSH\ssh.exe
    echo Using SysWOW64\OpenSSH\ssh.exe >> %LOGFILE%
) else (
    set SSH_CMD=ssh
    echo Falling back to 'ssh' (must be in PATH) >> %LOGFILE%
)

:: Test SSH version
echo Testing SSH: %SSH_CMD% -V >> %LOGFILE%
%SSH_CMD% -V >> %LOGFILE% 2>&1
echo SSH version check exit code: %ERRORLEVEL% >> %LOGFILE%

:: Run the full flashing command
%SSH_CMD% -T eugeniolr@127.0.0.1 "cat > /tmp/bin_flash.hex; openocd -f interface/jlink.cfg -f target/lpc17xx.cfg -c \"program /tmp/bin_flash.hex; reset run; exit\"" < %1 >> %LOGFILE% 2>&1
set EXITCODE=%ERRORLEVEL%

:: Log and display results
echo [%DATE% %TIME%] Exit code: %EXITCODE% >> %LOGFILE%
type %LOGFILE%
exit /b %EXITCODE%