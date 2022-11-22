#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <stack>

typedef long long ll;

using namespace std;

int l;
string s;

/**
 * dp[i][j] = i~j 구간에서 최소 회문의 개수
 *
 */
vector<vector<int>> dp;
vector<vector<int>> path;
stack<pair<int, int>> ps;
queue<int> b;

int solve()
{

    // init
    dp.clear();
    path.clear();
    stack<pair<int, int>>().swap(ps);
    queue<int>().swap(b);

    dp.resize(l + 1, vector<int>(l + 1, 0));
    path.resize(l + 1, vector<int>(l + 1, 0));

    // dp[i][i] = 1; (자기 자신은 팰린드롬)
    for (int i = 1; i <= l; i++)
    {
        dp[i][i] = 1;
    }

    // 구간의 길이
    for (int i = 1; i < l; i++)
    {
        // 시작 인덱스
        for (int j = 1; j <= l; j++)
        {
            if (j + i > l)
                break;

            int m = l + 1;

            if (s[j - 1] == s[j + i - 1] && (i == 1 || dp[j + 1][j + i - 1] == 1))
            {
                m = 1;
                path[j][j + i] = j + i;
            }
            else
            {
                for (int k = j; k < j + i; k++)
                {
                    if (m > dp[j][k] + dp[k + 1][j + i])
                    {
                        m = dp[j][k] + dp[k + 1][j + i];
                        path[j][j + i] = k;
                    }
                }
            }

            dp[j][j + i] = m;
        }
    }

    ps.push({1, l});

    while (ps.size())
    {
        auto x = ps.top();
        auto p = path[x.first][x.second];
        ps.pop();

        b.push(p);

        if (x.second == p)
            continue;

        ps.push({p + 1, x.second});
    }

    return dp[1][l];
}

int main()
{

    ifstream in("input.txt");
    ofstream out("output.txt");

    if (!in || !out)
    {
        cout << "failed to open file"
             << "\n";
        return 1;
    }

    int tc;
    in >> tc;
    out << tc << "\n";

    while (tc--)
    {

        in >> l;

        s.clear();
        char c;

        for (int i = 0; i < l; i++)
        {
            in >> c;
            s.push_back(c);
        }

        out << solve() << "\n";

        for (int i = 1; i <= l; i++)
        {
            out << s[i - 1];
            if (b.size() && b.front() == i)
            {
                b.pop();
                out << "\n";
            }
        }
    }

    in.close();
    out.close();

    return 0;
}