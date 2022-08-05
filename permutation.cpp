// g++ permutation.cpp
#include <iostream>       
#include <string>       
#include <algorithm>
#include <math.h>
#include <sstream>
#include <time.h>

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

int* ArrangeKey(int* key, int numOfKey){

    int* newKey = new int[numOfKey];

    for(int i = 0 ; i < numOfKey ; i++){
        newKey[key[i] - 1] = i + 1; 
    }

    return newKey;
}

string GetPermutation(int* key, string plainText, int numOfkey){
    
    int round = ceil(plainText.length()/float(numOfkey));
    int plainTextLength = plainText.length();
    string result = plainText;

    for(int i = 0 ; i < plainTextLength ; i++){
        result[i / numOfkey * numOfkey + key[i % numOfkey] - 1] = plainText[i];
    }

    return result;
} 

string PadText(string plainText, int numOfKey){
                         
    int numOfRound = (numOfKey - plainText.length() % numOfKey) % numOfKey;

    for(int i = 0 ; i < numOfRound ; i++){
        plainText += char(rand() % 26 + 'A');
    }

    return plainText;
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

int main (){

    //   letth emfre
    //   thtel ferme
    //   5 4 1 3 2
    //   3 5 4 2 1   
    
    srand(time(NULL));
    
    string text, key, result;
    int numOfKey; 
    char type;
    int* keyArr;

    cout << "Welcome to A Permutation Cipher " << endl;
    cout << "Enter type (E/D): ";
    cin >> type;
    getchar();
    cout << "Enter string: ";
    getline(cin, text);
    cout << "Enter a number of key: ";
    cin >> numOfKey;
    getchar();
    cout << "Enter a set of keys: ";
    getline(cin, key);

    keyArr = ExtractInteger(key, numOfKey);
    text = ChangeToUpperCase(RemoveSpace(text));

    
    if(type == 'E' || type == 'e'){
        text = PadText(text, numOfKey);
        result = GetPermutation(keyArr, text, numOfKey);
        cout << "String output is " << result << endl; 
    }
    else if(type == 'D' || type == 'd'){
        int* newKeyArr = ArrangeKey(keyArr, numOfKey);
        result = GetPermutation(newKeyArr, text, numOfKey);
        cout << "String output is " << result << endl; 
    }
    else{
        cout << "!!! error !!!" << endl;
    }


    return 0;
}
