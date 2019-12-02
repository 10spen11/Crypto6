#include "RSA.h"
#include "BigInt.h"
#include <cmath>
#include<iostream>
#define RAND_LIMIT32 0x7FFFFFFF
using namespace RSAUtil;

int main(int argc, char*argv[]){
    /*********************************************************
    * A Simple Driver
    * *******************************************************
    */
    unsigned long int *a;
    unsigned long int arr[4];
    a=&arr[0];

    RSA myRSA[10];
  int start = 30000;
  int primes[20];

  for (int j=0; j<20; j++)
  {
    for(int k=start+1; ; k++)
    {
      if(!isPrime(k))
      {
        std::cout<<"Prime num "<<j<<" : "<<k<<"\n";
        start = k;
        primes[j] = k;
        break;
      }
    }
  }


  BigInt message, cipher, deciphered;

    for(int i=0; i<10; i++)
    {
        myRSA[i] = RSA(primes[2 * i], primes[(2*i + 1)]);
        std::cout<<"Prime num p : "<<primes[2*i]<<" q : "<<primes[2*i + 1]<<"\n";
        message = int(((double)std::rand()/RAND_MAX)*RAND_LIMIT32);
        message.toULong(a,4);
        cipher = myRSA[i].encrypt(message);
        deciphered = myRSA[i].decrypt(cipher);
        std::cout<<*a<<std::endl;
        //  std::cout<<"message "<<message.toString();
        std::cout<<"message: "<<message.toHexString()<<"\tcipher: "<<cipher.toHexString()<<"\tdeciphered: "<<deciphered.toHexString()<<std::endl;    
    }

}