#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <time.h>

#define COMMAND_FILE_NAME "commands.txt"

typedef long long ll;

using namespace std;

ll V, E, M;
string folder;
string input_file, output_file;

priority_queue<pair<ll, ll>> pq;    // w, { v1, v2}
vector<vector<pair<ll, ll>>> edges; // w, v

vector<pair<ll, ll>> ans; // vertices, weight

clock_t time_start, time_end;
double result;

void read_command();

void uni(ll x, ll y);
ll find(ll x);

void prim();

int main()
{
    read_command();

    ifstream in(input_file);

    if (!in.is_open())
    {
        cout << "File open error : " << input_file << "\n";
        return 1;
    }

    in >> V >> E >> M;

    edges.resize(V, vector<pair<ll, ll>>());

    for (ll i = 0; i < E; i++)
    {
        ll a, b, c;

        in >> a >> b >> c;

        edges[a].push_back({c, b});
        edges[b].push_back({c, a});
    }

    time_start = clock();

    prim();

    time_end = clock();

    result = (double)(time_end - time_start);

    cout << "time : \n"
         << result << "\n";

    ofstream out(output_file);

    out << ans.size() << "\n";

    for (auto x : ans)
    {
        out << x.first << " " << x.second << "\n";
    }

    return 0;
}

void read_command()
{
    ifstream in(COMMAND_FILE_NAME);
    in >> folder >> input_file >> output_file;

    input_file = folder + "/" + input_file;
    output_file = output_file;
}

void prim()
{
    vector<ll> visited(V, 0); // visited

    for (ll i = 0; i < V; i++)
    {
        if (visited[i] > 0)
            continue;

        ll wSum = 0;
        ll c = 0;

        pq.push({0, i});

        while (pq.size())
        {
            auto t = pq.top();
            pq.pop();

            auto w = -t.first;
            auto d = t.second;

            if (visited[d] > 0)
                continue;

            visited[d] = 1;

            wSum += w;
            c++;

            for (auto e : edges[d])
            {
                if (visited[e.second] > 0)
                    continue;

                pq.push({-e.first, e.second});
            }
        }

        ans.push_back({c, wSum});
    }
}