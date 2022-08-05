// g++ mono_alphabetic_substitution.cpp
#include <iostream>
#include <time.h>
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

string GetEncodeMonoAlp(string key, string plainText){
    
    string cipherText = "";
    int plainTextLength = plainText.length();
    
    for(int i = 0 ; i < plainTextLength ; i++){
        cipherText = cipherText + key[plainText[i] - 'A'];
    }
    //cout << cipherText;
    return cipherText;
}

string GetDecodeMonoAlp(string key, string cipherText){
    
    string plainText = "";
    int cipherTextLength = cipherText.length();
    int keyLength = key.length();
    
    //search index in key
    for(int i = 0 ; i < cipherTextLength ; i++){
        for(int j = 0 ; j < keyLength ; j++){
            if(key[j] == cipherText[i]){
                plainText = plainText + char(j + 'A');
                break;
            }
        }
    }
    
    return plainText;
    
}

string GetRandomKeyShuffle(){
    srand(time(0));
    int length = 26;
    string alpArrIndex = "";
    
    // set index alphabet
    for(int i = 0 ; i < length ; i++){
        alpArrIndex = alpArrIndex + char(i + 'A');
    }
    
    // random shuffle
    for(int i = 0 ; i < length ; i++){
        swap(alpArrIndex[i], alpArrIndex[rand()%length]);
    }

    return alpArrIndex;
}


int main() {

    string text;
    string key;
    string result;
    char type;

    //key = GetRandomKeyShuffle();  // if want to get random key
    
    cout << "Welcome to A Mono-alphabetic Substitution Cipher" << endl;
    cout << "Enter type (E/D): ";
    cin >> type;
    getchar();
    cout << "Enter string: "; 
    getline(cin, text); 
    cout << "Enter key string [A-Z]: ";
    getline(cin, key); 

    text = ChangeToUpperCase(RemoveSpace(text));
    key = ChangeToUpperCase(RemoveSpace(key));

    if(type == 'E' || type == 'e'){
        result = GetEncodeMonoAlp(key, text);
        cout << "String output is " << result << endl;
    }
    else if(type == 'D' || type == 'd'){
        result = GetDecodeMonoAlp(key, text);
        cout << "String output is " << result << endl;
    }
    else{
        cout << "!!! error !!!" << endl;
    }


    

    
    return 0;
}