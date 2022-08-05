// g++ elgamal.cpp
#include <iostream>       
#include <string>       
#include <math.h>
#include <time.h>

using namespace std;

int GCD(int a, int b) {
   
    if (b == 0)
        return a;
    return GCD(b, a % b);

}

bool IsCoPrime(int n, int coPrime){

    if(GCD(n,coPrime) != 1)
        return false;    
    return true;

}

int PowerMod(int a, int k, int m){

    if(k == 0)
        return 1;

    return (a * PowerMod(a, k - 1, m)) % m;

}

int main (){
    
    int p, g, k, m, x, y, c1, c2;
    int numOfAlp; 
    char type, text;
    bool flag = true, isCoPrime = false; 

    srand(time(NULL));

    cout << "Welcome to ElGamal Cryptosystem!" << endl;
    cout << "Enter prime p: " ;
    cin >> p;
    
    while(!isCoPrime){
        cout << "Enter co-prime g [1," << p-1 << "]: " ;
        cin >> g;
        isCoPrime = IsCoPrime(p,g);
    
        if(!isCoPrime)
            cout << "Sorry! "<< g <<" is not co-prime of " << p << endl;   

    }
    
    cout << "Enter private key x ]1," << p-1 << "[: ";
    cin >> x;

    y = PowerMod(g, x, p);
    cout << "plublic key y is " << y << endl;
    
    while(flag){
    
        cout << "Enter the progress type E/D: ";
        cin >> type;
        getchar();

        if(type == 'E' || type == 'e'){
            cout << "Enter the plaintext: ";
            cin >> text;
            k = rand() % 100 ;
            cout << "The random number k is " << k << endl;
            c1 = PowerMod(g, k, p);
            c2 = ( (text - 'A') * PowerMod(y, k, p) ) % p;
            cout << "The ciphertext 1 is " << c1 << endl;
            cout << "The ciphertext 2 is " << c2 << endl;
            flag = false;
        }
        else if(type == 'D' || type == 'd'){
            cout << "Enter the ciphertext 1: ";
            cin >> c1;
            cout << "Enter the ciphertext 2: ";
            cin >> c2;
            m = ( c2 * PowerMod(c1, p-x-1, p) ) % p ;
            text = m + 'A';
            cout << "The plaintext is " << text << endl;
            flag = false;
        }
        else{
            cout << "Sorry! progress type is 'E' or 'D' " << endl;
        }

    }

    return 0;

}
