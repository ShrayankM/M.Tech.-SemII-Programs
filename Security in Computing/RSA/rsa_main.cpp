#include<bits/stdc++.h>
using namespace std;

const int P = 1000;

//* Global Storage for Prime Numbers [300]
vector<int>primeNumbers;
vector<bool>PMap(P, true);

void buildPrimeArray() {

    //bool T[P];
    for (int i = 2; i < P; i++) 
        PMap[i] = true;
    
    for (int i = 2; i < (P/2); i++) {
        if (PMap[i] == true) {
            for (int j = i * 2; j < P; j = j + i)
                PMap[j] = false;
        }
    }

    for (int i = 2; i < P; i++) {
        if (PMap[i] == true)
            primeNumbers.push_back(i);
    }

}

int getRandomPrime(int N) {
    int index = rand() % N;
    return primeNumbers[index];
}

int checkPrime(long int pr) { 
    for (int i = 2; i <= sqrt(pr); i++) {
        if (pr % i == 0)
            return 0;
    }
    return 1;
}

long int findD(long int E, long int T) {
    long int k = 1; 
    while(1) 
    { 
        k = k + T; 
        if(k % E == 0) 
            return(k/E); 
    } 
}

void findED(vector<long int>&E, vector<long int>&D, long int T, long int p, long int q) {

    long int flag;
    for (int e = 2; e < T; e++) {
        if (T % e == 0)
            continue;
        
        if (e < P)
            flag = PMap[e] ? 1 : 0;
        else
            flag = checkPrime(e);
        if (flag == 1 && e != p && e != q) {
            E.push_back(e);
            flag = findD(e, T);

            if (flag > 0) {
                D.push_back(flag);
                //return;
            }
        }
    }
}

void encryptMessage(string message, long int key, long int M[], long int N, vector<long int>& temp, vector<long int>& ency){
    for (int i = 0; i < message.size(); i++) {
        long int a = M[i];
        a = a - 96;

        long int k = 1;
        for (int j = 0; j < key; j++) {
            k = k * a;
            k = k % N;
        }

        temp.push_back(k);
        ency.push_back(k + 96);
    }
}

void decryptMessage(vector<long int>& ency, long int key, long int N, vector<long int>& temp, vector<long int>& decy) {
    for (int i = 0; i < ency.size(); i++) {
        long int b = temp[i];

        long int k = 1;
        for (int j = 0; j < key; j++) {
            k = k * b;
            k = k % N;
        }

        decy.push_back(k + 96);
    }
}

int main(){

    time_t start, end;
    double time_taken;
    time(&start);

    buildPrimeArray();
    int PN = primeNumbers.size();

    long int p, q;
    p = getRandomPrime(PN);
    q = getRandomPrime(PN);

    //string message = "Message To Be Encrypted";
    string message;
    string t;
    ifstream readPlain("plaintext.txt");

    while (getline(readPlain, t)) {
        message += t;
        message += "\n";
    }

    ifstream in_file("plaintext.txt", ios::binary);
    in_file.seekg(0, ios::end);
    int file_size = in_file.tellg();
    cout << "Size of the file is" << " " << file_size/1000 << " " << "Kilobytes\n";

    long int M[message.size() + 1];

    for (int i = 0; i < message.size(); i++)
        M[i] = message[i];
    
    long int N = p * q;
    long int T = (p - 1) * (q - 1);

    vector<long int>E, D, temp, ency, decy;

    findED(E, D, T, p, q);

    time(&end);
    time_taken = double(end - start);

    cout << "Time taken to generate Keys = " << fixed << time_taken << setprecision(5) << " secs" << "\n";

    time(&start);
    encryptMessage(message, E[0], M, N, temp, ency);
    cout << "[Encrypted Text] \n";
    
    for (int i = 0; i < ency.size(); i++) {
        cout << char(ency[i]);
    }
    cout << "\n";
    cout << "-----------------------------------------------------------------------------------------------------------------\n";

    time(&end);
    time_taken = double(end - start);

    cout << "Time taken to encrypt message = " << fixed << time_taken << setprecision(5) << " secs" << "\n";

    cout << "-----------------------------------------------------------------------------------------------------------------\n";
    time(&start);
    decryptMessage(ency, D[0], N, temp, decy);
    cout << "[Decrypted Text] \n";
    for (int i = 0; i < decy.size(); i++) {
        cout << char(decy[i]);
    }
    cout << "\n";

    time(&end);
    time_taken = double(end - start);

    cout << "-----------------------------------------------------------------------------------------------------------------\n";
    cout << "Time taken to decrypt message = " << fixed << time_taken << setprecision(5) << " secs" << "\n";

    return 0;
}