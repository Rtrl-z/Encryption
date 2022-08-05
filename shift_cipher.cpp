// g++ shift_cipher.cpp
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

int Operation(int alp, int key, char operation){
    switch(operation) {
        case '+':
            return alp - 'A' + key;
        break;
        case '-':
            return alp - 'A' + key;
        break;
        case '*':
            return (alp - 'A') * key;
        break;
        case '/':
            return (alp - 'A') / key;
        break;

    }
}

string ShiftCipher(string plainText, int key, char operation) {
    
    string cipherText = "";
    char result;
    plainText = RemoveSpace(plainText);
    int plainTextLength = plainText.length();

    switch(operation) {
        
        case '+':
            for(int i = 0 ; i < plainTextLength ; i++){
                result = 'A' + PositiveMod(Operation(plainText[i], key, '+'), 26);
                cipherText = cipherText + result;
            }
        break;
        case '-':
            for(int i = 0 ; i < plainTextLength ; i++){
                result = 'A' + PositiveMod(Operation(plainText[i], key, '-'), 26);
                cipherText = cipherText + result;
            }
        break;
        case '*':
            for(int i = 0 ; i < plainTextLength ; i++){
                result = 'A' + PositiveMod(Operation(plainText[i], key, '*'), 26);
                cipherText = cipherText + result;
            }
        break;
        case '/':
            if(key == 0)
                cipherText = "!!! ERROR !!!";
            else{
                for(int i = 0 ; i < plainTextLength ; i++){
                    result = 'A' + PositiveMod(Operation(plainText[i], key, '/'), 26);
                    cipherText = cipherText + result;
                }
            }
        break;
        default:
            cout << "!!! error !!!" << endl;

    }
   
    return cipherText;
}

char getType(char type){
    if(type == 'E' || type == 'e'){
        return '+';
    }
    if(type == 'D' || type == 'd'){
        return '-';
    }
    return 'X'; // error
}

int main() {
    string text, result;
    int key;
    char type;
    cout << "Welcome to the Caesar Cipher" << endl;
    cout << "Enter type (E/D): ";
    cin >> type;
    cout << "Enter string: "; 
    cin >> text;
    cout << "Enter key: ";
    cin >> key;
    
    text = ChangeToUpperCase(RemoveSpace(text));
    type = getType(type);

    result = ShiftCipher(text,key,type);
    cout << "String output is " << result << endl;

    return 0;
}
