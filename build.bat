pushd d:\projects\c++\gl_mingw_app
windres res\resource.rc -I include -o build\resource.o
g++ src\main.cpp -lgdi32 -user32 -lopengl32 -Iinclude build\resource.o -o build\game.exe
popd
set /p DUMMY=Hit ENTER to continue...
