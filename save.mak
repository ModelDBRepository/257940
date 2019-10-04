LDFLAGS  = -L/usr/lib/X11\
            -L/usr/local/lib\
	   -L/usr/X11R6/lib\
		-L/usr/include/X11
	

LIBRARIES = $(LDFLAGS) -lX11 -lm

INCLUDE = -I/usr/include -I/usr/local/include -I/usr/include/X11
 

CFLAGS = -g $(INCLUDE)

save.run : set.o sim.o update.o util.o io.o fft.o gra.o draw.o show.o save.o functions.o curves.o color.o
	cc set.o sim.o update.o util.o io.o fft.o gra.o draw.o show.o save.o functions.o curves.o color.o -o save.run $(LIBRARIES)
set.o sim.o update.o util.o io.o fft.o gra.o draw.o show.o save.o functions.o curves.o color.o : cell.init lib.init my.init 
gra.o draw.o show.o curves.o : gra.init draw.init

