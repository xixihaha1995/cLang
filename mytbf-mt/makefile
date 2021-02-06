GFLAGS+=pthread
LFLAGS+=pthread
all:mytbf

mytbf:main.o mytbf.o
	gcc $^ -o $@ $(GFLAGS) $(LFLAGS)

clean:
	rm *.o mytbf -rf