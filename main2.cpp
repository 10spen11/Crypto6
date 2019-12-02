#include "RSA.h"
#include "BigInt.h"
#include <cmath>
#include<iostream>
#define RAND_LIMIT32 0x7FFFFFFF
using namespace RSAUtil;

void testRSA(RSA& myRSA1, RSA& myRSA2)
{
	unsigned long int* a;
	unsigned long int arr[4];
	a = &arr[0];
	BigInt message, cipher, deciphered;

	message = int(((double)std::rand() / RAND_MAX) * RAND_LIMIT32);
	message.toULong(a, 4);
	cipher = myRSA1.encrypt(message);
	deciphered = myRSA2.decrypt(cipher);
	std::cout << *a << std::endl;
	//  std::cout<<"message "<<message.toString();
	std::cout << "message: " << message.toHexString() << "\tcipher: " << cipher.toHexString() << "\tdeciphered: " << deciphered.toHexString() << std::endl;
}

int main(int argc, char* argv[]) {
	/*********************************************************
	* A Simple Driver
	* *******************************************************
	*/

	RSA rsa1, rsa2;
	rsa2.setPublicKey(rsa1.getPublicKey());
	rsa2.setN(rsa1.getModulus());

	testRSA(rsa1, rsa2);

}