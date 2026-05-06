#include <iostream>
#include <vector>
#include <string>
using namespace std;

string lcs(string x, string y)
{
    int m = x.size();
    int n = y.size();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (x[i - 1] == y[j - 1])
            {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
            }
        }
    }

    string subsequence = "";
    int i = m, j = n;

    while (i > 0 && j > 0)
    {
        if (x[i - 1] == y[j - 1])
        {
            subsequence = x[i - 1] + subsequence;
            i--, j--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
        {
            i--;
        }
        else
        {
            j--;
        }
    }
    return subsequence;
}

int main()
{
    string x, y;
    cout << "Enter two strings: ";
    cin >> x >> y;

    string res = lcs(x, y);
    cout << "LCS = " << res << endl;
    return 0;
}