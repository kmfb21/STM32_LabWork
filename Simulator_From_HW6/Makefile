
CFLAGS=  $(shell  sdl-config --cflags) -g -I/opt/local/include -I. 
LDFLAGS= -g $(shell sdl-config --libs) -lSDL_gfx -lSDLmain -lm 
CC=gcc

OBJS = c335sim.o screen.o game.o glcdfont.o tank.o
 
all: game

game: $(OBJS) 
	$(CC) $(OBJS) -o game $(LDFLAGS)

clean:
	rm -f $(OBJS) game
