#include<bits/stdc++.h>
using namespace std;

const int P = 100;

//* Global Storage for Prime Numbers [300]
vector<int>primeNumbers;

void buildPrimeArray() {

    bool T[P];
    for (int i = 2; i < P; i++) 
        T[i] = true;
    
    for (int i = 2; i < (P/2); i++) {
        if (T[i] == true) {
            for (int j = i * 2; j < P; j = j + i)
                T[j] = false;
        }
    }

    for (int i = 2; i < P; i++) {
        if (T[i] == true)
            primeNumbers.push_back(i);
    }

}

int getRandomPrime(int N) {
    int index = rand() % N;
    return primeNumbers[index];
}

// int gcd(int a, int b){
//     if (a == 0)
//         return b;
//     return gcd(b % a, a);
// }

int gcd(int a, int h)
{
    int temp;
    while (1)
    {
        temp = a%h;
        if (temp == 0)
          return h;
        a = h;
        h = temp;
    }
}

int main(){

    buildPrimeArray();

    int PN = primeNumbers.size();

    srand(time(0));

    double p = getRandomPrime(PN);
    double q = getRandomPrime(PN);
    cout << "Prime Numbers = " << p << " " << q << "\n";

    double N = p * q;
    cout << "N = " << N << "\n";

    double e = 2;

    double PHI = (p - 1) * (q - 1);
    while (e < PHI) {
        if (gcd(e, PHI) == 1)
            break;
        else
            e = e + 1;
    }

    cout << "E = " << e << "\n";

    int K = 2;
    double D = ((K * PHI) + 1) / e;

    cout << "D = " << D << "\n";

    double encrypt = 67;


    return 0;
}