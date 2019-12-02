ALL: MAIN
	
MAIN: rsaDriver.cpp 
	g++ -m32 main.cpp -L. libRSAutil.a -o prog

RSA: libRSAutil.a

clean:
	rm -f prog

run: ALL
	./prog