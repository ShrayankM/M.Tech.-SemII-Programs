#include<bits/stdc++.h>
using namespace std;

//* ASCII RANGE 34 - 125
void invertBitsEncrypt(vector<int> &a) {
    for (int i = 0; i < a.size(); i++) {
        int n = a[i];
        // int bits = log2(n) + 1;
        int bits = 7;
        for (int b = 0; b < bits; b++) {
            n = (n ^ (1 << b)); 
        }
        
        a[i] = (n + 34) % 125;
    }
}

void invertBitsDecrypt(vector<int> &a) {
    for (int i = 0; i < a.size(); i++) {
        int n = a[i]; 
        n = n - 34;
        if (n > 0)
            n = n % 125;
        else
            n = (n + 125) % 125;
        
        int bits = 7;
        for (int b = 0; b < bits; b++) {
            n = (n ^ (1 << b)); 
        }

        a[i] = n;
    }
}

int main(){

    string plaintext = "This text should be encrypted. [All brackets should also () work fine I think ?] Special symbols should also work fine, {@, &, *, $} and also numbers [9, 3, 4, 2, 1] with this encryption technique";

    string ciphertext = "";
    string decryptedtext = "";

    vector<int> ascii;

    for (int i = 0; i < plaintext.length(); i++) {
        ascii.push_back(int(plaintext[i]));
    }

    //* Encrypting the plaintext
    invertBitsEncrypt(ascii);

    for (int i = 0; i < plaintext.length(); i++) {
        ciphertext.push_back(char(ascii[i]));
    }

    cout << ciphertext << "\n";
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------\n";


    //* Decrypting the ciphertext
    invertBitsDecrypt(ascii);
    for (int i = 0; i < plaintext.length(); i++) {
        decryptedtext.push_back(char(ascii[i]));
    }

    cout << decryptedtext << "\n";
    return 0;
}