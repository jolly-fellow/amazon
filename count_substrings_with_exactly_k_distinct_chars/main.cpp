#include <iostream>
#include <utility>
#include <vector>
#include <unordered_map>

using namespace std;

int subarraysWithKDistinct(const string & s, int K) {
    int res = 0;
    int s_size = s.size();
    vector<int> m(s_size + 1);

    for(auto i = 0, j = 0, prefix = 0, cnt = 0; i < s_size; ++i) {

        if (m[s[i]]++ == 0) {
            ++cnt;
        }

        if (cnt > K) {
            --m[s[j++]];
            --cnt;
            prefix = 0;
        }

        while (m[s[j]] > 1) {
            ++prefix;
            --m[s[j++]];
        }

        if (cnt == K) {
            res += prefix + 1;
        }
    }
    return res;
}


int main() {
    std::cout << subarraysWithKDistinct("pqpqs", 2) << std::endl;
    return 0;
}
