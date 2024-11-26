mkdir ..\\out
mkdir ..\\out\\engine
cd ..
cd engine
call ..\\scons\\scons
cd ..
cd Scripts

xcopy /s ..\\engine\\bin ..\\out\\engine\\* /Y
