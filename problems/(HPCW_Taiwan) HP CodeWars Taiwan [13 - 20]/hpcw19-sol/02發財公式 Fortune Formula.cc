#include <algorithm>
#include <inttypes.h>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>


int64_t dp[50][210] = {0};

std::string get_line(void)
{
    std::string line;
    std::getline(std::cin, line);
    return line;
}

int get_mod_num(std::string& line, int beg, int end)
{
    int res = 0;
    for (int i = beg; i <= end; i++) {
        res = (res * 10 + line[i] - '0') % 210;
    }
    return res;
}

int64_t solve(std::string line)
{
    memset(dp, 0, sizeof(dp));
    dp[0][line[0] - '0'] = 1;

    for (int i = 1; i < line.size(); i++) {
        for (int len = 1; len <= (i + 1); len++) {
            int num = get_mod_num(line, i + 1 - len, i);
            if (i - len < 0) {
                dp[i][num % 210]++;
                break;
            }
            for (int x = 0; x < 210; x++) {
                dp[i][(x + num) % 210] += dp[i - len][x];
            }
            for (int x = 0; x < 210; x++) {
                dp[i][(x - num + 210) % 210] += dp[i - len][x];
            }
        }
    }

    int64_t res = 0;
    for (int i = 0; i < 210; i++) {
        if (i % 2 == 0 || i % 3 == 0 || i % 5 == 0 || i % 7 == 0)
            res += dp[line.size() - 1][i];
    }

    return res;
}

int main(int argc, char* argv[])
{
    int test_cases = atoi(get_line().c_str());

    for (int i = 0; i < test_cases; ++i) {
        auto line = get_line();
        printf("%ld\n", solve(line));
    }
    return 0;
}
