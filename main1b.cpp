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

    RSA myRSA[5];
  int start = 30000;

  for (int j=0; j<5; j++)
  {
    for(int k=start+1; ; k++)
    {
      if(isPrime(k))
      {
        std::cout<<"Prime num : "<<k<<"\n";
        start = k;
        myRSA[j] = RSA(k);
        break;
      }
    }
  }


  BigInt message, cipher, deciphered;

    for(int i=0; i<5; i++)
    {
        message = int(((double)std::rand()/RAND_MAX)*RAND_LIMIT32);
        message.toULong(a,4);
        cipher = myRSA[i].encrypt(message);
        deciphered = myRSA[i].decrypt(cipher);
        std::cout<<*a<<std::endl;
        //  std::cout<<"message "<<message.toString();
        std::cout<<"message: "<<message.toHexString()<<"\tcipher: "<<cipher.toHexString()<<"\tdeciphered: "<<deciphered.toHexString()<<std::endl;    
    }

}