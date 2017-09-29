# tests

gcc -Wall -c vmod.c;ar cr libvmod.a vmod.o
g++ test.cpp -I./clibs  -L./clibs -lvmod






