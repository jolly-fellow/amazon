#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;



int osa_distance(const std::string & s1, const std::string & s2) {
    int m = s1.size(), n = s2.size();

    if(m == n == 0) return 0;
    if(m == 0) return n;
    if(n == 0) return m;

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));


    for (int i = 1; i <= m; i++) {
        dp[i][0] = i;
    }
    for (int j = 1; j <= n; j++) {
        dp[0][j] = j;
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1]; // letters are equal
            } else {
                int substitution = dp[i - 1][j - 1];
                int insertion = dp[i][j - 1];
                int deletion = dp[i - 1][j];
                int result = std::min({substitution, insertion, deletion});
                if(result == substitution) {
                    cout << "INSERT " << s1[i - 1];
                }
                else if(result == insertion) {
                    cout << "INSERT " << s1[i - 1];
                }
                else if(result == deletion) {
                    cout << "REMOVE " << s1[i - 1];
                }

                if ( (i > 1) && (j > 1) && (s1[i-1] == s2[j-2]) && (s1[i-2] == s2[j-1]) ) {

                    // transposition
                    cout << "MOVE " << s1[i - 1];
                }
            }
        }
    }
    return dp[m][n];
}


const string IsOneEditAway(string s1, string s2) {

    int s1_size = s1.size();
    int s2_size = s2.size();

    if(s1 == s2) {
        return "NOTHING";
    }

    if (s2_size == 0 || s1_size == 0) {
        return "IMPOSSIBLE";
    }

    if ((s1_size - s2_size) > 1 || (s2_size - s1_size) > 1  ) {
        return "IMPOSSIBLE";
    }

    int i = 0, j = 0;
    int diff = 0;
    while (i < s1_size && j < s2_size) {
        char f = s1[i];
        char s = s2[j];
        if (f != s) {
            diff++;
            if (s1_size > s1_size)
                i++;
            if (s1_size > s1_size)
                j++;
            if (s1_size == s1_size)
                i++; j++;
        }
        else{
            i++; j++;
        }
        if (diff > 1) {
            return "IMPOSSIBLE";
        }
    }

    sort(s1.begin(), s1.end());
    sort(s2.begin(), s2.end());

    if (diff == 1 && s1 == s2) {
        return "MOVE";
    }

    if (diff == 1 && s1_size != s2_size) {
        return "REMOVE";
    }

    return "INSERT";

}

int r(const vector<int>& cost, int i) {
    if (i < 0) return 0;
    if (i==0 || i==1) return cost[i];
    return cost[i] + min( r( cost, i-1 ), r( cost, i-2 ) );
}

int minCostClimbingStairs(const vector<int>& cost) {
    int i = cost.size();
    return min( r( cost, i-1 ), r( cost, i-2 ) );
}

string test(string input1) {
    string &s = input1, st, res;
    int j = 0, top = -1;
    for (int i = s.length() - 1; i >= 0; i--) {
        if ((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z') || (s[i] >= '0' && s[i] <= '9')) {
            res.push_back(s[i]);
        }
        else {
            if (s[i] == ')') {
                top++;
                st[top] = s[i];
            }
            else if (s[i] == '+' || s[i] == '-') {
                for (int k = top; k >= 0; k--) {
                    if (st[k] != ')') {
                        if (st[k] == '*' || st[k] == '/') {
                            res.push_back(st[k]);
                            top--;
                        }
                    }
                    else {
                        break;
                    }
                }
                top++;
                st[top] = s[i];
            }
            else if (s[i] == '*' || s[i] == '/') {
                top++;
                st[top] = s[i];
            }
            else if (s[i] == '(') {
                for (int k = top; k >= 0; k--) {
                    if (st[k] != ')') {
                        res.push_back(st[k]);
                        top--;
                    } else {
                        top--;
                        break;
                    }
                }
            }
        }
    }
    while (top != -1) {
        res.push_back(st[top]);
        top--;
    }
    std::reverse(res.begin(), res.end());
    return res;
}


const int MAX = 10000;

vector <int> primes;

void sieve()
{
    bool marked[MAX/2 + 100] = {0};
    for (int i=1; i<=(sqrt(MAX)-1)/2; i++)
        for (int j=(i*(i+1))<<1; j<=MAX/2; j=j+2*i+1)
            marked[j] = true;

    primes.push_back(2);

    for (int i=1; i<=MAX/2; i++)
        if (marked[i] == false)
            primes.push_back(2*i + 1);
}

// Function to perform Goldbach's conjecture
void findPrimes(int n)
{
    vector<int> res;
    // Return if number is not even or less than 3
    if (n<=2 || n%2 != 0)
    {
        cout << "Invalid Input \n";
        return;
    }

    // Check only upto half of number
    for (int i=0 ; primes[i] <= n/2; i++)
    {
        // find difference by subtracting current prime from n
        int diff = n - primes[i];

        // Search if the difference is also a prime number
        if (binary_search(primes.begin(), primes.end(), diff))
        {
//            cout << primes[i] << " + " << diff << " = "
//                 << n << endl;
            return;
        }
    }
}
void test2() {

}

int main() {

    sieve();

    findPrimes(60);

//    cout << test("8+(7-9)*2");

//    cout << minCostClimbingStairs({10,15,20});

    // IsOneEditAway("asd", "abd");

    return 0;
}

