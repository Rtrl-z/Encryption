// g++ vigenere.cpp
#include <iostream>
#include <string>
#include <algorithm>

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

int PositiveMod(int Numerator, int Denominator){ 

    if(Numerator >= 0 && Numerator < Denominator) // e.g. 0 - 25
        return Numerator;
    
    if(Numerator >= Denominator)  // e.g. > 25
        return Numerator % Denominator; 
    
    int x = abs(Numerator) / Denominator;    // < 0
    if(Denominator*x + Numerator < 0)
        return Denominator*(x + 1) + Numerator;
    return Denominator*x + Numerator;
}

string EncodeVigenere(string plainText, string key){
    
    string cipherText = "";
    int plainTextLength = plainText.length();
    int keyLength = key.length();
    
    for(int i = 0 ; i < plainTextLength ; i++){
        cipherText += char('A' + PositiveMod(plainText[i] + key[i % keyLength] - 2 * 'A', 26));
    }
    
    return cipherText;
}

string DecodeVigenere(string cipherText, string key){
    
    string plainText = "";
    int cipherTextLength = cipherText.length();
    int keyLength = key.length();
    
    for(int i = 0 ; i < cipherTextLength ; i++){
        plainText += char('A' + PositiveMod(cipherText[i] - key[i % keyLength] - 2 * 'A', 26));
    }
    
    return plainText;
}

int main() {
    string text, key, result;
    char type;

    cout << "Welcome to the Vigenère Cipher " << endl;
    cout << "Enter type (E/D): " ;
    cin >> type;
    getchar();
    cout << "Enter string: "; 
    getline(cin, text);
    cout << "Enter key string: ";
    getline(cin, key);

    text = ChangeToUpperCase(RemoveSpace(text));
    key = ChangeToUpperCase(RemoveSpace(key));

    if(type == 'E' || type == 'e'){
        result = EncodeVigenere(text, key);
        cout << "String output is " << result << endl;
    }
    else if(type == 'D' || type == 'd'){
        result = DecodeVigenere(text, key);
        cout << "String output is " << result << endl; 
    }
    else{
        cout << "!!! error !!!" << endl;
    }

    return 0;
}
