program: main.o freeList.o
	g++ -o program main.o freeList.o

freeList.o:	freeList.h freeList.cc
	g++ -c -g freeList.cc

main.o:	main.cc
	g++ -c -g main.cc

clean:
	rm -f program main.o freeList.o *~
pr