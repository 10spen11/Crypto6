mainVersion=main3.cpp

ALL: MAIN DRIVER TRY
	
MAIN: $(mainVersion) RSA
	g++ -m32 $(mainVersion) -L. libRSAutil.a -o prog

DRIVER: rsaDriver.cpp RSA
	g++ -m32 rsaDriver.cpp -L. libRSAutil.a -o driver

TRY: rsatry1.cpp RSA
	g++ -m32 rsatry1.cpp -L. libRSAutil.a -o try

RSA: libRSAutil.a BigInt.cpp RSA.cpp
	g++ -m32 -c BigInt.cpp RSA.cpp
	ar rc libRSAutil.a BigInt.o RSA.o
	ranlib libRSAutil.a

clean:
	rm -f prog

run: ALL
	./prog