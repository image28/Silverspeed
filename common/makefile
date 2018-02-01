############################################################################
# Makefile - 20th June 2005 11:23pm
############################################################################

CC = g++
LD = g++
CFLAGS = -O2 -g -c
LDFLAGS = -O2 -g -o

all: lib/init.o lib/draw.o lib/timer.o lib/collision.o lib/shuffle.o lib/generator.o lib/path.o lib/texture.o lib/menu.o lib/screenshot.o lib/sound.o lib/config.o lib/score.o

lib/init.o: src/init.cpp
	$(CC) $(CFLAGS) $< -I./ -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT -Dmain=SDL_main
	cp init.o lib
	rm -f init.o
lib/draw.o: src/draw.cpp
	$(CC) $(CFLAGS) $< -I./ -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT -Dmain=SDL_main
	cp draw.o lib 
	rm -f draw.o
lib/timer.o: src/timer.cpp
	$(CC) $(CFLAGS) $< -I./ -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT -Dmain=SDL_main
	cp timer.o lib
	rm -f timer.o
lib/collision.o: src/collision.cpp
	$(CC) $(CFLAGS) $< -I./ -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT -Dmain=SDL_main
	cp collision.o lib
	rm -f collision.o
lib/shuffle.o: src/shuffle.cpp
	$(CC) $(CFLAGS) $< -I./ -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT -Dmain=SDL_main
	cp shuffle.o lib
	rm -f shuffle.o
lib/generator.o: src/generator.cpp
	$(CC) $(CFLAGS) $< -I./ -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT -Dmain=SDL_main
	cp generator.o lib
	rm -f generator.o
lib/path.o: src/path.cpp
	$(CC) $(CFLAGS) $< -I./ -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT -Dmain=SDL_main
	cp path.o lib
	rm -f path.o
lib/texture.o: src/texture.cpp
	$(CC) $(CFLAGS) $< -I./ -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT -Dmain=SDL_main
	cp texture.o lib
	rm -f texture.o
lib/menu.o: src/menu.cpp
	$(CC) $(CFLAGS) $< -I./ -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT -Dmain=SDL_main -DCHEAT
	cp menu.o lib
	rm -f menu.o
lib/screenshot.o: src/screenshot.cpp
	$(CC) $(CFLAGS) $< -I./ -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT -Dmain=SDL_main
	cp screenshot.o lib
	rm -f screenshot.o
lib/sound.o: src/sound.cpp
	$(CC) $(CFLAGS) $< -I./ -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT -Dmain=SDL_main
	cp sound.o lib
	rm -f sound.o
lib/config.o: src/config.cpp
	$(CC) $(CFLAGS) $< -I./ -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT -Dmain=SDL_main
	cp config.o lib
	rm -f config.o
lib/score.o: src/score.cpp
	$(CC) $(CFLAGS) $< -I./ -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT -Dmain=SDL_main
	cp score.o lib
	rm -f score.o

clean:
	rm -f lib\*.o
	rm -f ERRORS.TXT
