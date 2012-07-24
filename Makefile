# Sous Linux, utiliser sdl-config --cflags et sdl-config --libs pour completer
# les deux lignes ci dessous
CFLAGS=-Wall -g -I/opt/local/include/SDL -D_GNU_SOURCE=1 -D_THREAD_SAFE
LDFLAGS=-g -L/opt/local/lib -lSDLmain -lSDL -Wl,-framework,Cocoa
EXTRA=

# Sous MAC OS X
# CFLAGS=-g -Wall -I/Library/Frameworks/SDL.framework/Headers  -I/System/Library/Frameworks/OpenGL.framework/Headers
# LDFLAGS=-framework SDL -framework Cocoa -I/System/Library/Frameworks/OpenGL.framework/Headers -framework OpenGL
# EXTRA=SDLmain.o

tower: tower.o Mob.o game.o graphics.o Fonts.o Point.o timer.o TowerMob.o ${EXTRA}
	gcc -Wall -o $@ ${LDFLAGS} $^

SDLmain.o: SDLmain.m
	gcc -c ${CFLAGS} $<
tower.o: tower.c game.h 
	gcc -c ${CFLAGS} $<
Fonts.o: Fonts.c Fonts.h 
	gcc -c ${CFLAGS} $<
Point.o: Point.c Point.h 
	gcc -c ${CFLAGS} $<
timer.o: timer.c
	gcc -c ${CFLAGS} $<
Mob.o: Mob.c Mob.h
	gcc -c ${CFLAGS} $<
TowerMob.o: TowerMob.c TowerMob.h
	gcc -c ${CFLAGS} $<
game.o: game.c game.h
	gcc -c ${CFLAGS} $<
graphics.o: graphics.c graphics.h game.h
	gcc -c ${CFLAGS} $<

clean: 
	rm tower *.o
