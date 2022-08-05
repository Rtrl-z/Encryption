// g++ poly_alphabetic_substitution.cpp
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


string GetDecodeSubstitution(string key[], string cipherText, int numberOfkeys){
    
    string plainText = "";
    int cipherTextLength = cipherText.length();
    int layer;
    
    for(int i = 0 ; i < cipherTextLength ; i++){
        layer = i % numberOfkeys;
        for(int j = 0 ; j < key[layer].length() ; j++){
            if(key[layer][j] == cipherText[i]){
                plainText = plainText + char('A'+j);
            }
        }
    }

    return plainText;
    
}


string GetEncodeSubstitution(string key[], string plainText, int numberOfkeys){
    
    string cipherText = "";
    int plainTextLength = plainText.length();
    
    for(int i = 0 ; i < plainTextLength ; i++){
        cipherText = cipherText + key[i % numberOfkeys][plainText[i] - 'A'];
    }
    //cout << numberOfkeys << endl;
    return cipherText;
}

string GetRandomKeyShuffle(){
    
    int length = 26;
    //int* alpArrIndex = new int[length];
    string alpString = "";
    
    // set index alphabet
    for(int i = 0 ; i < length ; i++){
        alpString = alpString + char(i + 'A');
    }
    
    // random shuffle
    for(int i = 0 ; i < length ; i++){
        swap(alpString[i], alpString[rand()%length]);
    }

    return alpString;
}

void printAtoZ(){
    
    char alp = 'A';
    
    for(int i = 0 ; i < 26 ; i++){
        cout << char(alp + i) ;
    }
    
    cout << endl;
}

int main() {

    srand(time(NULL));
    string text, result;
    int layerNum;
    char type;


    cout << "Welcome to A Polyalphabetic Substitution Cipher " << endl;
    cout << "Enter type (E/D): ";
    cin >> type;
    getchar();
    cout << "Enter string: "; 
    getline(cin, text);
    cout << "Enter a number of keys: ";
    cin >> layerNum;
    getchar();
    
    string key[layerNum];
    text = ChangeToUpperCase(RemoveSpace(text));
    
    for(int i = 0 ; i < layerNum ; i++){
        cout << "Enter "<< i+1 << "-key string ";
        getline(cin, key[i]);
        key[i] = ChangeToUpperCase(RemoveSpace(key[i]));
    }

    //for(int i = 0 ; i < layerNum ; i++){   // if want to get a random key
    //    key[i] = GetRandomKeyShuffle();
    //}

    if(type == 'E' || type == 'e'){
        result = GetEncodeSubstitution(key, text, layerNum);
        cout << "String output is " << result << endl;
    }
    else if(type == 'D' || type == 'd'){
        result = GetDecodeSubstitution(key, text, layerNum);
        cout << "String output is " << result << endl; 
    }
    else{
        cout << "!!! error !!!" << endl;
    }

    return 0;
}