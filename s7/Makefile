.PHONY: all
all: s7.o plus.o s7_newplus

s7.o: s7.c
	gcc -c s7.c -I. -O2 -g3

plus.o: ../newplus/plus.h ../newplus/plus.c
	gcc -c ../newplus/plus.c -I../newplus -O2 -g3

s7_newplus: s7_newplus.c ../newplus/plus.h
	gcc -o s7_newplus s7_newplus.c s7.o plus.o -I. -I../newplus -lm -ldl -O2
