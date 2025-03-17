
// C++ program to print all primes smaller than or equal to
// n using Sieve of Eratosthenes O(N log (log N))
#include <bits/stdc++.h>
#include <sys/resource.h>
#include <iostream>
using namespace std;

// Function for getting Max rss memory
long get_mem_usage()
{
    struct rusage myusage;
    getrusage(RUSAGE_SELF, &myusage);
    return myusage.ru_maxrss;
}

vector<bool> SieveOfEratosthenes(int n)
{
    // Create a boolean array "prime[0..n]" and initialize
    // all entries it as true. A value in prime[i] will
    // finally be false if i is Not a prime, else true.
    vector<bool> prime(n + 1, true);
    prime[0] = false;
    prime[1] = false;

  for (int p = 2; p * p <= n; p++) {


        if (prime[p] == true) {
            
            // Update all multiples of p greater than or
            // equal to the square of it numbers which are
            // multiple of p and are less than p^2 are
            // already been marked.
            for (int i = p * p; i <= n; i += p)
                prime[i] = false;
        }
    }

/*     // Print all prime numbers
    for (int p = 2; p <= n; p++)
        if (prime[p])
            cout << p << " "; */
    return prime;
}

// Driver Code
int main()
{
    clock_t start, end;
    int n = 10000000;
    int res_count = 0;
    cout << "Calculating prime numbers smaller "
         << "than or equal to " << n << endl;
    start = clock();
    vector<bool> res = SieveOfEratosthenes(n);
    end = clock();

    double ticks_taken = double(end - start);
    double time_taken = ticks_taken / double(CLOCKS_PER_SEC);

    for (int i = 0; i < res.size(); i++)
    {
        if (res[i]) { res_count++; }
    }

    cout << "\nPrime numbers found: " << res_count << "\n";
    cout << "Time in seconds: " << time_taken << "\n";
    cout << "Memory usage in bytes: " << get_mem_usage() << endl;

    return 0;
}