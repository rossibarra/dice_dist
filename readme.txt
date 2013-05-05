Code to calculate Dice distance from ms-like simulation output.

Requires the libsequence C++ library.

Version 1:  Assumes dominant markers and requires SimDataDip for use on dominant markers.

Reads ms-formatted coalescent simulations from stdout.  Requires specification of the number of populations and number of alleles with the "-I <pops> <alleles>" flag:

ms 20 1 -t 5 | dice -I 1 10

dist.cc reads in a single ms coalescent simulation of 20 alleles combined to form 10 dominant haplotypes.

Compiles with:

g++ -I. -I.. -I/usr/local/include -Wall -W -ansi -pedantic -DNDEBUG -O2 -c dist.cc SimDataDIP.cc
g++  -DNDEBUG -O2 -o dice  dist.o SimDataDIP.o -lsequence 

dist_cod.cc is similar, but assumes codominant markers. 

Compiles with:

g++ -I. -I.. -I/usr/local/include -Wall -W -ansi -pedantic -DNDEBUG -O2 -c dist_cod.cc   
g++ -DNDEBUG -O2 -o diceCod dist_cod.o  -lsequence
