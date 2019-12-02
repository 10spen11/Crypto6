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

int main(int argc, char* argv[]) {
	/*********************************************************
	* A Simple Driver
	* *******************************************************
	*/

	RSA alice, bob;

	/*
	 * a.      Alice obtains the public key and Modulus N of the person (Bob) who is to sign the message
	 */
	BigInt bobKey = bob.getPublicKey();
	BigInt bobN = bob.getModulus();

	/*
	 * b.      Obtain a random number and its inverse with respect to the Modulus [Not phi] of Bob
	 */
	BigInt randomNumber = randomBigInt();
	BigInt randomNumberInverse = RSAUtil::modInverse(randomNumber, bobN);

	/*
	 * c.       Alice obtains/generates a message to be signed.
	 */
	BigInt message = randomBigInt();
	std::cout << "message: ";
	printBigInt(message);

	/*
	 * d.      Alice encrypts the random number with the public key.
	 */
	BigInt encryptedRand = RSAUtil::modPow(randomNumber, bobKey, bobN);

	/*
	 * e.      Alice multiplies this value by the message
	 */
	BigInt product = encryptedRand * message;

	/*
	 * f.        Alice then takes a modulus over N
	 */
	product = product % bobN;

	/*
	 * g.      Alice sends it to Bob
	 */
	// since this is a simulation, nothing has to be done here
	// we now say Bob has access to product

	/*
	 * h.      Bob simply decrypts the received value with the private key
	 */
	BigInt result = bob.decrypt(product);

	/*
	 * i.        Bob sends it back to Alice
	 */
	 // since this is a simulation, nothing has to be done here
	 // we now say Alice has access to result

	/*
	 * j.        Alice then multiplied the received value with the inverse and takes a modulus over N.
	 */	
	BigInt signedMessage = (result * randomNumberInverse) % bobN;

	/*
	 * k.       The value obtained above is the signed message. To obtain the original message from it, again encrypt it with Bob’s Public Key.
	 */
	BigInt decryptedMessage = bob.encrypt(signedMessage);
	std::cout << "decrypted message: ";
	printBigInt(decryptedMessage);

}