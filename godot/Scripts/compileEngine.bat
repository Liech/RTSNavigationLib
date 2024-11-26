mkdir ..\\out
mkdir ..\\out\\godot
cd ..
cd godot
call ..\\scons\\scons
cd ..
cd Scripts

xcopy /s ..\\godot\\bin ..\\out\\godot\\* /Y
