#Change absolute paths to your paths that lead these folders

PANDA_LIB="$(HOME)/Documents/2015-16/OpenGL/panda3d-1.9.2/built/lib"
PANDA_CPATH="$(HOME)/Documents/2015-16/OpenGL/panda3d-1.9.2/built/include"

all: main.o
	g++ $< -o a.out -fPIC -L$(PANDA_LIB) -lp3framework -lpanda -lpandafx -lpandaexpress -lp3dtoolconfig -lp3dtool -lp3pystub -lp3direct -lpthread

%.o: %.cpp
	g++ -c $< -o $@ -fPIC -O2 -I$(PANDA_CPATH)

clean:
	rm *.o *.out
