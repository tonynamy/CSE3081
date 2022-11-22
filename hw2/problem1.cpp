#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <queue>

typedef long long ll;

using namespace std;

int m, n, s, f, p;
vector<char> X, Y;

vector<vector<ll>> dp;
vector<vector<pair<int, int>>> path;

int xi, yi;
deque<char> Xf, Yf;

int read_input_data()
{
    ifstream in("input.txt");
    string binary_file;

    in >> binary_file >> s >> f >> p;

    in.close();

    if (!in)
    {
        return 0;
    }

    ifstream bin(binary_file);

    if (!bin)
    {
        return 0;
    }

    bin.read(reinterpret_cast<char *>(&m), sizeof(m));
    bin.read(reinterpret_cast<char *>(&n), sizeof(n));

    char t;

    X.resize(m + 1);

    for (int i = 1; i <= m; i++)
    {
        bin.read(&t, sizeof(t));
        X[i] = t;
    }

    Y.resize(n + 1);

    for (int i = 1; i <= n; i++)
    {
        bin.read(&t, sizeof(t));
        Y[i] = t;
    }

    bin.close();

    return 1;
}

int write_output_data()
{

    ofstream out("output.txt");

    // 유사성 점수
    out << dp[m][n] << "\n";

    // 전체 길이
    int xs = Xf.size();
    int ys = Yf.size();

    out << xs << "\n";
    // 동일
    // out << ys << "\n";

    // X indel 개수
    out << xi << "\n";
    // X indel 정보
    for (int i = 1; i < xs; i++)
    {
        if (Xf[i] == '-')
            out << i << "\n";
    }
    // Y indel 개수
    out << yi << "\n";
    // Y indel 정보
    for (int i = 1; i < ys; i++)
    {
        if (Yf[i] == '-')
            out << i << "\n";
    }

    out.close();

    return 1;
}

int main()
{

    if (!read_input_data())
    {
        return 1;
    }

    /**
     * DP 배열 dp[m][n]
     *
     * dp[i][j]는 X의 i와 Y의 j가 만난다고 생각했을 때 최대 값
     * 어떻게 계산하냐?
     * 이전 단계에서 -가 추가되었는지 아닌지 2개의 경우로 나누어서 계산할 수 있지
     * 이전 단계란?
     * dp[i-1][j], dp[i-1][j-1], dp[i][j-1]이 있을 수 있고
     * dp[i-1][j-1]을 제외하면 indel이 추가된 경우
     *
     *
     */

    // init
    dp.clear();
    path.clear();

    dp.resize(m + 1, vector<ll>(n + 1, 0));
    path.resize(m + 1, vector<pair<int, int>>(n + 1));

    dp[0][0] = 0;
    path[0][0] = {-1, -1};

    for (int i = 1; i <= m; i++)
    {
        // i 개의 indel이 X 앞에 첨가
        dp[i][0] = -p * i;
        path[i][0] = {-1, 0};
    }
    for (int j = 1; j <= n; j++)
    {
        // j 개의 indel이 Y 앞에 첨가
        dp[0][j] = -p * j;
        path[0][j] = {0, -1};
    }

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {

            ll w = (X[i] == Y[j] ? s : -f);

            pair<ll, pair<int, int>> s1 = {dp[i - 1][j - 1] + w, {-1, -1}};
            pair<ll, pair<int, int>> s2 = {dp[i - 1][j] - p, {-1, 0}};
            pair<ll, pair<int, int>> s3 = {dp[i][j - 1] - p, {0, -1}};

            auto m = max(s1, max(s2, s3));

            dp[i][j] = m.first;
            path[i][j] = m.second;
        }
    }

    stack<pair<int, int>> ps;
    ps.push({m, n});

    xi = 0;
    yi = 0;

    while (ps.size())
    {
        auto t = ps.top();
        ps.pop();

        if (t.first < 0 || t.second < 0)
            break;

        auto p = path[t.first][t.second];

        if (p.first < 0)
        {
            Xf.push_front(X[t.first]);
        }
        else
        {
            Xf.push_front('-');
            xi++;
        }

        if (p.second < 0)
        {
            Yf.push_front(Y[t.second]);
        }
        else
        {
            Yf.push_front('-');
            yi++;
        }

        ps.push({t.first + p.first, t.second + p.second});
    }

    write_output_data();

    return 0;
}