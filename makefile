ALL: MAIN DRIVER TRY
	
MAIN: main.cpp RSA
	g++ -m32 main.cpp -L. libRSAutil.a -o prog

DRIVER: rsaDriver.cpp RSA
	g++ -m32 rsaDriver.cpp -L. libRSAutil.a -o driver

TRY: rsatry1.cpp RSA
	g++ -m32 rsatry1.cpp -L. libRSAutil.a -o try

RSA: libRSAutil.a

clean:
	rm -f prog

run: ALL
	./prog