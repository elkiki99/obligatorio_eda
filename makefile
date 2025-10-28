todo: main.o archivo.o versiones.o version.o lineas.o linea.o
	g++ -Wall -o main main.o archivo.o versiones.o version.o lineas.o linea.o

main.o: main.c
	g++ -Wall -c main.c

archivo.o: archivo.c archivo.h versiones.h lineas.h
	g++ -Wall -c archivo.c

versiones.o: versiones.c versiones.h version.h
	g++ -Wall -c versiones.c

version.o: version.c version.h lineas.h
	g++ -Wall -c version.c

lineas.o: lineas.c lineas.h linea.h
	g++ -Wall -c lineas.c

linea.o: linea.c linea.h
	g++ -Wall -c linea.c

clean:
	rm -f *.o main