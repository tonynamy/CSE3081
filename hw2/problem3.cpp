#include <iostream>
#include <fstream>
#include <string>
#include <vector>

typedef long long ll;

using namespace std;

int ls, rs, ps;
vector<int> l, r, p;
/**
 * dp[i][j] = 왼손에서 i번째 원소를 뽑고 오른손에서 j번째 원소를 뽑았을 때 i+j번째 카드가 될 수 있나?
 *
 */
vector<vector<int>> dp;

int solve()
{
    dp.clear();
    dp.resize(ls + 1, vector<int>(rs + 1, 0));

    for (int i = 1; i <= ls; i++)
    {
        dp[i][0] = l[i] == p[i] ? 1 : 0;
    }

    for (int i = 1; i <= rs; i++)
    {
        dp[0][i] = r[i] == p[i] ? 1 : 0;
    }

    for (int i = 1; i <= ls; i++)
    {
        for (int j = 1; j <= rs; j++)
        {
            dp[i][j] |= dp[i - 1][j] & (l[i] == p[i + j]);
            dp[i][j] |= dp[i][j - 1] & (r[j] == p[i + j]);
        }
    }

    return dp[ls][rs];
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

    in >> ls;

    l.resize(ls + 1);

    for (int i = 1; i <= ls; i++)
    {
        in >> l[i];
    }

    in >> rs;

    r.resize(rs + 1);

    for (int i = 1; i <= rs; i++)
    {
        in >> r[i];
    }

    int tc = 2;
    while (tc--)
    {
        in >> ps;

        p.clear();
        p.resize(ps + 1);
        for (int i = 1; i <= ps; i++)
        {
            in >> p[i];
        }

        out << solve();
    }

    out << "\n";

    in.close();
    out.close();

    return 0;
}