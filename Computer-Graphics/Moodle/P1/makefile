LIBS = bresenham.o

run: main.c $(LIBS)
	gcc main.c $(LIBS) -Wall -o main

$(LIBS): bresenham.c
	gcc -c bresenham.c

clean: $(LIBS) main
	rm $(LIBS) main
