#include <iostream>
#include <vector>
using namespace std;

class PrimeSieveOfEuler {
public:
    vector<int> Find(int n) {
        vector<int> primes;
        vector<bool> notPrime(n + 1);
        for (int i = 2; i <= n; i++) {
            if (!notPrime[i]) {
                primes.push_back(i);
            }
            for (auto p : primes) {
                if (i * p > n) {
                    break;
                }
                notPrime[i * p] = true;
                if (i % p == 0) {
                    break;
                }
            }
        }
        return primes;
    }
};

int main() {
    for (auto x : PrimeSieveOfEuler().Find(100)) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}
