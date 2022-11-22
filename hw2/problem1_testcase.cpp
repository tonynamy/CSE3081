#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{

    // string X = "ATCGGATCT";
    // string Y = "ACGGACT";

    string X = "BBBCBBBA";
    string Y = "BBBBBA";

    string filename = "twostrings.bin";

    ofstream out(filename, std::ios::binary);

    if (!out)
    {
        cout << "failed to open file"
             << "\n";
    }

    int xl = X.length();
    int yl = Y.length();

    out.write(reinterpret_cast<const char *>(&xl), sizeof(xl));
    out.write(reinterpret_cast<const char *>(&yl), sizeof(yl));

    for (auto x : X)
    {
        out.write(reinterpret_cast<const char *>(&x), sizeof(x));
    }

    for (auto x : Y)
    {
        out.write(reinterpret_cast<const char *>(&x), sizeof(x));
    }

    out.close();

    return 0;
}