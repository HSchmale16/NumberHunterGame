# Number Hunter Game Makefile for cross platform builds
# From Linux.
# @author Henry J Schmale
# @date January 28, 2015

CXX=mingw32-gcc-c++
CFLAGS=-Wall -std-c++11 -O2 -DSFML_STATIC \
     -ISQLite/include -ISFML-2.1/include \
LDFLAGS=-LSQLite/lib \
     -LSFML-2.1/lib
STATIC_MODS=
SRC= main.cpp \
     ini.c \
     INIReader.cpp \
     Hjs_StdLib_Implement.cpp \
     src/GameMenu.cpp \
     src/LevelHandler.cpp \
     src/gameDB.cpp \
     src/UI.cpp \
     src/LevelEndScreen.cpp \
     src/Salvage.cpp \
     src/Asteroids.cpp \
     src/LaserHandler.cpp \
     src/MenuButton.cpp \
     src/Background.cpp \
     src/Player.cpp \
     src/Laser.cpp
OBJ=$(SRC:.cpp=.o)
EXE=NumberHunter.exe
PackDir=distro
# Primary Release Target, Build Everything
all: win32


# Win32 Release Target, Build it for win32
win32: $(SRC) $(EXE)
    # Package the game for distrubution
    mkdir $(PackDir)
    cp $(EXE) $(PackDir)
    cp -r resources $(PackDir)
    cp libsndfile-1.dll $(PackDir)
    cp openal32.dll $(PackDir)


$(EXE): $(OBJ)
    $(CXX) $(LDFLAGS) $(OBJ) -o $@


.o:
    $(CXX) $(CFLAGS) $< -o $@

clean:
    rm -rf *.o

