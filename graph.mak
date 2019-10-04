LDFLAGS  = -L/usr/lib/X11\
            -L/usr/local/lib\
	   -L/usr/X11R6/lib
	

LIBRARIES = $(LDFLAGS) -lX11 -lm

INCLUDE = -I/usr/include -I/usr/local/include -I/usr/include/X11
 

CFLAGS = -g $(INCLUDE)

graph.run : gra.o curves.o color.o graph.o
	cc gra.o curves.o color.o graph.o -o graph.run $(LIBRARIES)
sim.o update.o util.o set.o io.o fft.o gra.o draw.o show.o new_draw.o neuron.o functions.o curves.o color.o : cell.init lib.init my.init 
gra.o draw.o new_draw.o show.o curves.o : gra.init draw.init

