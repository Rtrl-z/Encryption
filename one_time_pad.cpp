// g++ one_time_pad.cpp
#include <iostream>       
#include <string>       
#include <algorithm>
#include <math.h>  

using namespace std;

string RemoveSpace(string text){
    text.erase( 
                 remove(text.begin(), text.end(), ' '), 
                 text.end()
              );
    return text;
}

string ChangeToUpperCase(string text){
    
    int textLength = text.length();
    string result = "";

    for(int i = 0 ; i < textLength ; i++){

        if(text[i] >= 'A' && text[i] <= 'Z'){
            result = result + char(text[i]); 
        }
        else if(text[i] >= 'a' && text[i] <= 'z'){
            result = result + char(text[i] - 'a' + 'A');
        }
            
    }

    return result;
}

string GetOneTimePad(string plainText, int* key){
    
    int plainTextLength = plainText.length();
    string cipherText = "";
    
    for(int i = 0 ; i < plainTextLength ; i++){
        
        cipherText += char(((plainText[i]-'A') ^ key[i]) + 'A');
    }
        
    return cipherText;
} 

int* GetKeyDecimal(string key, int bitPerSet){
    
    int keyLength = key.length();
    string zero = "";
    
    for(int i = 0 ; (zero.length() + keyLength) % bitPerSet != 0 ; i++){
        zero += '0';
    }
    
    key = zero + key;
    cout << key << endl;
    keyLength = key.length();
    int* decimalKey = new int[keyLength/bitPerSet];
    int x = 0 , j = 0; 
    
    for(int i = 0 ; i < keyLength ; i++){

        x = x + pow(2, bitPerSet - 1 - i % bitPerSet) * int(key[i]-'0');

        if(i % bitPerSet == bitPerSet - 1){
            decimalKey[j++] = x;
            x = 0;
        }
    }
    
    return decimalKey;
}


int main (){
    
    string text, key, result;
    int* decimalKey;
    char type;

    cout << "Welcome to A One-time Pad " << endl;
    cout << "Enter type (E/D): ";
    cin >> type;
    getchar();
    cout << "Enter string: ";
    getline(cin, text);
    cout << "Enter key string (n bits): ";
    getline(cin, key);

    text = ChangeToUpperCase(RemoveSpace(text));
    key = RemoveSpace(key);

    decimalKey = GetKeyDecimal(key, 5);
    result = GetOneTimePad(text, decimalKey);

    cout << "String output is " << result << endl;
    
    return 0;
}