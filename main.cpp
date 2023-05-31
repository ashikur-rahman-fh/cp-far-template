#include <bits/stdc++.h>

using namespace std;

namespace nt { // Number theory

enum DEFAULT {
  MAX_CAL_PRIME     = 0x00100000, // 1048576 -> 2^20
  RESERVE_P_SIZE    = 0x00020000, // 131072 -> 2^17
};

/**
 * @brief A specialized Prime class that deals with prime numbers optimally.
*/
class Prime {
public:
  Prime() : n(DEFAULT::MAX_CAL_PRIME) { init(); evaluate(); }
  Prime(int pn) : n(pn) { init(); evaluate(); }

  inline void init() {
    markedPrime = vector<bool> (n, true);
  }

  void evaluate() {
    seive();
    getPrimes();
  }

  void seive() {
    markedPrime[0] = markedPrime[1] = false;

    for (int i = 4; i < n; i += 2) { markedPrime[i] = false; }

    for (int i = 3; i * i < n; i += 2) {
      if (!markedPrime[i]) { continue; }

      const int inc = i << 1;
      for (int j = i * i; j < n; j += inc) {
        markedPrime[j] = false;
      }
    }
  }

  void getPrimes() {
    primes.push_back(2);

    for (int i = 3; i < n; i += 2) {
      if (markedPrime[i]) { primes.push_back(i); }
    }

    psize = (int) primes.size();
  }

  /**
   * @brief Check primality of an integer number.
   * @tparam T The type of number.
   * @param num An integer number.
   * @return bool true if input num is a prime. Otherwise, false.
  */
  template<typename T>
  bool checkPrimality(const T &num) {
    if (num < DEFAULT::MAX_CAL_PRIME) {
      return markedPrime[num];
    }

    for (int i = 0; i < psize && primes[i] * primes[i] <= num; i++) {
      if (num % primes[i] == 0) { return false; }
    }

    return true;
  }
  /**
   * @brief Prime factorization of a number.
   * @tparam T The type of number.
   * @param num An integer number.
   * @return unordered_map<T, int> where prime number as a key and count of the prime number as value.
  */
  template<typename T>
  unordered_map<T, int> getPrimeFactors(T num) {
    unordered_map<T, int> factors;

    for (int i = 0; i < psize && primes[i] * primes[i] <= num; i++) {
      int cnt = 0;
      while (num % primes[i] == 0) {
        cnt++;
        num /= primes[i];
      }

      if (cnt) {
        factors[primes[i]] = cnt;
      }
    }
    if (num > 1) {
      factors[num] = 1;
    }

    return factors;
  }

  /**
   * @brief Display the first few calculated primes.
   * @param mx Number of primes need to display. Default set to 25.
  */
  void displayPrimes(const int &mx = 25) {
    cerr << "Total: " << psize << "\n";

    const int max_range = min(mx, psize);
    for (int i = 0; i < max_range; i++) {
      if (i > 0) { cerr << " "; }
      cerr << primes[i];
    }

    if (psize > max_range) {
      cout << " ...";
    }

    cerr << "\n";
  }

private:
  int n;
  vector<bool> markedPrime;
  vector<int> primes;
  int psize;
};

} // end nt

int main() {
  nt::Prime primes;
  primes.displayPrimes();

  auto factors = primes.getPrimeFactors(1000000000000);
  for (auto v : factors) {
    cout << v.first << " " << v.second << "\n";
  }

  cout << primes.checkPrimality(1000000000000) << "\n";
  return 0;
}