mkdir ..\\out
mkdir ..\\out\\godot-cpp

call "..\\emsdk\\emsdk_env.bat" activate

cd ..
cd godot-cpp
call ..\\scons\\scons platform=windows vsproj=yes dev_build=yes
cd ..
cd Scripts


cd ..
cd out
call .\\godot\\godot.windows.editor.x86_64.exe --dump-extension-api
cd ..
cd godot-cpp
call ..\\scons\\scons platform=windows bits=64 custom_api_file=..\\out\\extension_api.json
call ..\\scons\\scons platform=web dlink_enabled=yes custom_api_file=..\\out\\extension_api.json

xcopy /s ..\\godot-cpp\\bin ..\\out\\godot-cpp\\* /Y

cd ..
cd Scripts
