mkdir ..\\out
mkdir ..\\out\\extension

call "..\\emsdk\\emsdk_env.bat" activate

cd ..
cd Extension
call ..\\scons\\scons platform=windows bits=64
call ..\\scons\\scons dlink_enabled=yes platform=web

xcopy /s ..\\out\\extension\\ ..\\GodotProject\\bin\\* /Y

cd ..
cd Scripts