cl.exe /Zi /O2 /MD /TP /c src\init.cpp
cl.exe /Zi /O2 /MD /TP /c src\timer.cpp
cl.exe /Zi /O2 /MD /TP /c src\collision.cpp
cl.exe /Zi /O2 /MD /TP /c src\shuffle.cpp
cl.exe /Zi /O2 /MD /TP /c src\generator.cpp
cl.exe /Zi /O2 /MD /TP /c src\draw.cpp
cl.exe /Zi /O2 /MD /TP /c src\path.cpp
cl.exe /Zi /O2 /MD /TP /c src\texture.cpp
cl.exe /Zi /O2 /MD /TP /c src\menu.cpp
REM cl.exe /Zi /O2 /MD /TP /c src\screenshot.cpp
cl.exe /Zi /O2 /MD /TP /c src\sound.cpp
cl.exe /Zi /O2 /MD /TP /c src\config.cpp
move *.obj lib
