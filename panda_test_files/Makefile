PANDA_LIB=		# panda3d/built/lib
PANDA_INC=		# panda3d/build/include

all: main.o
	g++ $< -o a.out -fPIC -L$(PANDA_LIB) -lp3framework -lpanda -lpandafx -lpandaexpress -lp3dtoolconfig -lp3dtool -lp3pystub -lp3direct -lpthread


%.o: %.cpp
	g++ -c $< -o $@ -fPIC -O2 -I$(PANDA_INC)
