mkdir ..\\out
mkdir ..\\out\\templates

call "..\\emsdk\\emsdk_env.bat" activate

cd ..\\emsdk\\upstream\\emscripten\\
SET PATH=%PATH%;"%CD%"
cd ..
cd ..

cd ..
cd engine
call ..\\scons\\scons platform=windows target=template_debug arch=x86_64
call ..\\scons\\scons platform=windows target=template_release arch=x86_64
call ..\\scons\\scons platform=web dlink_enabled=yes target=template_debug production=yes
call ..\\scons\\scons platform=web dlink_enabled=yes target=template_release production=yes
cd ..
cd Scripts

xcopy /s ..\\engine\\bin ..\\out\\engine\\* /Y