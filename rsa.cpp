// g++ rsa.cpp
#include <iostream>       
#include <string>       
#include <math.h>
#include <sstream>

using namespace std;

int GCD(int a, int b) {
    if (b == 0)
        return a;
    return GCD(b, a % b);
}

bool IsCoPrime(int n, int limit, int coPrime){

    if(coPrime <= 1 || coPrime >= limit)
        return false;

    if(GCD(n,coPrime) != 1 || GCD(limit,coPrime) != 1)
        return false;
    
    return true;

}

int PowerMod(int a, int k, int m){

    if(k == 0)
        return 1;

    return (a * PowerMod(a, k - 1, m)) % m;

}

int* RSA(int* textDecimal, int textDecimalLength, int e, int n){

    int* result = new int[textDecimalLength];

    for(int i = 0 ; i < textDecimalLength ; i++){  
        result[i] = PowerMod(textDecimal[i], e, n);
    }

    return result;
}

int* ExtractInteger(string key, int numOfKey){
    
    stringstream ss; 
    ss << key; 
    string temp;
    int found, i = 0;
    int* keyArr = new int[numOfKey]; 
    while (!ss.eof()) {
        ss >> temp;
        if (stringstream(temp) >> found)
            keyArr[i++] = found;        
        temp = "";
    }
    return keyArr;
}

int* TextToDecimal(string text, bool isEncode){
    
    int textLength = text.length();
    int* result = new int[textLength];

    if(isEncode){
        for(int i = 0 ; i < textLength ; i++){
            result[i] = int(text[i] - 'A');
        }
    }
    else{
        int countAlp = 1;
        for(int i = 0 ; i < textLength ; i++){
            if(text[i] == '-'){
                countAlp++;
                text[i] = ' ';
            }
        }
        result = ExtractInteger(text, countAlp);
    }

    return result;
}

void PrintResult(int* value, int length, bool isEncode){

    string result = "";
    
    if(isEncode){    
        for(int i = 0 ; i < length ; i++){            
            cout << value[i];
            if(i != length - 1)
                cout << "-";
        }
    }
    else{
        for(int i = 0 ; i < length ; i++){  
            cout << char('A' + value[i]);    
        }
    }
    cout << endl;
}

int CountAlp(string text, bool isEncode){

    int textLength = text.length();
    int count = 1;
    if(isEncode)
        return textLength;
    
    for(int i = 0 ; i < textLength ; i++){
        if(text[i] == '-')
            count++;
    }

    if(text[textLength-1] < '0' || text[textLength-1] > '9')
        count--;

    return count;
}

int GetPrivateKey(int p, int q, int e){
    
    int N = p*q;
    int n = (p-1)*(q-1);
    // e * (d) (mod n) = 1 
    // 13 * 8 mod 60 = 1

    for(int i = 0 ; i < n ; i++){
        if( (e * i) % n == 1 )
            return i;  
    }

    return -1;
}

int main (){
    
    int p, q, n, limit, coPrime, key, numOfAlp;
    bool isCoprime = false, flag = true;
    char type;
    string text;
    int* rsa;
    int* textEncodeDecimal; 
    int* textDecodeDecimal; 

    cout << "Welcome to RSA!" << endl;
    cout << "Enter prime p: ";
    cin >> p;
    cout << "Enter prime q: ";
    cin >> q;
    n = p * q;
    limit = (p-1)*(q-1);

    cout << "The value of n is "<< p << " x " << q << " = " << n << endl;
    
    while(!isCoprime){
        cout << "Enter co-prime e ]1," << limit << "[: ";
        cin >> coPrime;
        isCoprime = IsCoPrime(n, limit, coPrime);

        if(!isCoprime)
            cout << "Sorry! "<< coPrime <<" is not co-prime of " << "(" << p << " - 1)(" << q << " - 1) = " 
                 << limit << " and " << p << " x " << q << " = " << n << endl;
    }


    while(flag){
        
        cout << "Enter the progress type E/D: ";
        cin >> type;
        getchar();
        
        if(type == 'E' || type == 'e'){
            cout << "Enter the plaintext: ";
            getline(cin, text);
            numOfAlp = CountAlp(text, true);

            textEncodeDecimal = TextToDecimal(text, true);
            rsa = RSA(textEncodeDecimal, numOfAlp, coPrime, n);
            
            cout << "The ciphertext is ";
            PrintResult(rsa, numOfAlp, true);
            flag = false;
        }
        else if(type == 'D' || type == 'd'){
            cout << "Enter the ciphertext: ";
            getline(cin, text);
            numOfAlp = CountAlp(text, false);

            cout << "The private key d is ";
            cin >> key;

            textDecodeDecimal = TextToDecimal(text, false);
            rsa = RSA(textDecodeDecimal, numOfAlp, key, n);

            cout << "The ciphertext is ";
            PrintResult(rsa, numOfAlp, false);
            flag = false;
        }
        else{
            cout << "Sorry! progress type is 'E' or 'D' " << endl;
        }

    }
    //cout << GetPrivateKey(7, 11, 13); // p, q, e

    
    return 0;
}
