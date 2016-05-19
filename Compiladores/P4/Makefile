LIBS = code.o complejo.o symbol.o init.o
FUENTE = code.cpp complejo.cpp symbol.cpp init.cpp

Maquina: y.tab.c $(LIBS)
	g++ y.tab.c $(LIBS) -w -lm -std=c++0x -fpermissive -o Maquina

$(LIBS): $(FUENTE)
	g++ $(FUENTE) -c -std=c++0x

y.tab.c: maquina.y
	byacc -d maquina.y

clean:
	rm y.tab.c $(LIBS) Maquina