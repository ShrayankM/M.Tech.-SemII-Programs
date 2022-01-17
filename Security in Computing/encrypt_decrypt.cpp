//TODO 122022010 Shrayank Mistry
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

int main(int argc, char *argv[]){

    string filename = "";
    if (argc > 1) {
        filename = argv[1];

        //TODO Filename specific task
        //* plaintext.txt  -> encrypt the data in file (write to ciphertext.txt)
        //* ciphertext.txt -> decrypt the data in file (write to output.txt)
        string plaintext = "";
        string ciphertext = "";
        string temp;

        if (filename == "plaintext.txt") {

            time_t start, end;
            time(&start);

            ifstream readPlain(filename);
            while (getline(readPlain, temp)) {
                plaintext += temp;
                plaintext += "\n";
            }
            cout << "[Plaintext] \n";
            cout << plaintext << "\n";

            vector<int> ascii;
            for (int i = 0; i < plaintext.length(); i++) {
                ascii.push_back(int(plaintext[i]));
            }

            invertBitsEncrypt(ascii);
            for (int i = 0; i < plaintext.length(); i++) {
                ciphertext.push_back(char(ascii[i]));
            }

            ofstream cipherFile("ciphertext.txt");
            cipherFile << ciphertext;

            cout << "-----------------------------------------------------------------------------------------------------------------\n";
            cout << "[Encrypted Text] \n";
            cout << ciphertext << "\n";

            time(&end);
            double time_taken = double(end - start);

            cout << "Plaintext encrypted: Encryption time = " << fixed << time_taken << setprecision(5) << "\n";
        }
        else if (filename == "ciphertext.txt") {

            time_t start, end;
            time(&start);

            ifstream readCipher(filename);
            while (getline(readCipher, temp)) {
                ciphertext += temp;
            }

            vector<int> ascii;
            for (int i = 0; i < ciphertext.length(); i++) {
                ascii.push_back(int(ciphertext[i]));
            }

            invertBitsDecrypt(ascii);
            for (int i = 0; i < ciphertext.length(); i++) {
                plaintext.push_back(char(ascii[i]));
            }

            ofstream outputFile("output.txt");
            outputFile << plaintext;

            cout << "[Decrypted Text] \n";
            cout << plaintext << "\n";

            time(&end);
            double time_taken = double(end - start);

            cout << "Ciphertext decrypted: Decryption time = " << fixed << time_taken << setprecision(5) << "\n";

            //cout << "Ciphertext decrypted \n";
        }
        else {
            cout << "Please provide only 1 of 2 files plaintext.txt or ciphertext.txt\n";
        }
    }
    else {
        cout << "Please provide a filename to encrypt or decrypt\n";
    }
    return 0;
}