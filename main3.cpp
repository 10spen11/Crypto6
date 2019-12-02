#include "RSA.h"
#include "BigInt.h"
#include <cmath>
#include<iostream>
#define RAND_LIMIT32 0x7FFFFFFF
using namespace RSAUtil;

BigInt randomBigInt()
{
	return BigInt(int(((double)std::rand() / RAND_MAX) * RAND_LIMIT32));
}

void printBigInt(BigInt message)
{
	std::cout << message.toHexString() << std::endl;
}

void sendprint(BigInt t)
{
    std::cout<<"\nAlice sends ["<<t.toHexString()<<"] >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Bob recieves it\n";
}

void sendbackprint(BigInt t)
{
    std::cout<<"\nBob sends ["<<t.toHexString()<<"] >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Alice recieves it\n";
}

int main(int argc, char* argv[]) {
	/*********************************************************
	* A Simple Driver
	* *******************************************************
	*/

	RSA alice, bob;
	unsigned long int *k;
	unsigned long int key[10];
    k = &key[0];
	/*
	 * a.      Alice obtains the public key and Modulus N of the person (Bob) who is to sign the message
	 */
	BigInt bobKey = bob.getPublicKey();
	BigInt bobN = bob.getModulus();

	bobKey.toULong(k, 4);
	std::cout<<"Alice got Bob's Publickey : "<<*k<<"\n";
    std::cout<<"Alice got Bob's Modulus N : "<<bobN.toHexString()<<"\n";

    /*
     * b.      Obtain a random number and its inverse with respect to the Modulus [Not phi] of Bob
     */
	BigInt randomNumber = randomBigInt();
	BigInt randomNumberInverse = RSAUtil::modInverse(randomNumber, bobN);
    std::cout<<"Random Number w.r.t to modulus is : "<<randomNumber.toHexString()<<"\n";
    std::cout<<"Random Number Inverse w.r.t to modulus is : "<<randomNumberInverse.toHexString()<<"\n";

	/*
	 * c.       Alice obtains/generates a message to be signed.
	 */
	BigInt message = randomBigInt();
    std::cout<<"================================================================\n";
    std::cout << "message (generated randomly): ";
    printBigInt(message);
    std::cout<<"================================================================\n";

    /*
     * d.      Alice encrypts the random number with the public key.
     */
	BigInt encryptedRand = RSAUtil::modPow(randomNumber, bobKey, bobN);
    std::cout<<"Encrypted random number with public key generating the cipher : "<<encryptedRand.toHexString()<<"\n";

	/*
	 * e.      Alice multiplies this value by the message
	 */
	BigInt product = encryptedRand * message;
    std::cout<<"product of cipher and message : "<<product.toHexString()<<"\n";


	/*
	 * f.        Alice then takes a modulus over N
	 */
	product = product % bobN;
    std::cout<<"N modulus of (product of cipher and message) : "<<product.toHexString()<<"\n";

    /*
     * g.      Alice sends it to Bob
     */
	// since this is a simulation, nothing has to be done here
	// we now say Bob has access to product
    sendprint(product);

	/*
	 * h.      Bob simply decrypts the received value with the private key
	 */
	BigInt bobprivkey = bob.getPrivateKey();
	BigInt result = bob.decrypt(product);
    std::cout<<"\nBob will now decrypt the received value with his private key : "<<bobprivkey.toHexString()<<"\n";
    std::cout<<"Bob gets the decrypted value as : "<<result.toHexString()<<"\n";

	/*
	 * i.        Bob sends it back to Alice
	 */
	 // since this is a simulation, nothing has to be done here
	 // we now say Alice has access to result
    sendbackprint(result);


	/*
	 * j.        Alice then multiplied the received value with the inverse and takes a modulus over N.
	 */	
	BigInt signedMessage = (result * randomNumberInverse) % bobN;
    std::cout<<"Alice multiplies the received value with the inverse and takes a modulo over N : "<<signedMessage.toHexString()<<"\n";

    /*
     * k.       The value obtained above is the signed message. To obtain the original message from it, again encrypt it with Bob�s Public Key.
     */
	BigInt decryptedMessage = bob.encrypt(signedMessage);
	std::cout<<"The value obtained above is the signed message. To obtain the original message from it, again encrypt it with Bob�s Public Key.\n";
	std::cout<<"================================================================\n";
	std::cout << "decrypted message: ";
	printBigInt(decryptedMessage);
    std::cout<<"================================================================\n";

}