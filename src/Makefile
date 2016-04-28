# Add PANDA_LIB and PANDA_CPATH environment variables

all: main.o Game.o Object.o Bone.o Shampoo.o
	g++ $^ -o a.out -fPIC --std=gnu++11 -L$(PANDA_LIB) -lp3framework -lpanda -lpandafx -lpandaexpress -lp3dtoolconfig -lp3dtool -lp3pystub -lp3direct -lpthread -fpermissive

%.o: %.cpp
	g++ -c $< -o $@ -fPIC -O0 -ggdb3 --std=gnu++11 -fpermissive -I$(PANDA_CPATH) -I/usr/include/eigen3

clean:
	rm *.o *.out
