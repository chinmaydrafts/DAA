#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

int knapsack(int m, vector<int> &weights, vector<int> &values, int n)
{
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++)
    {
        for (int w = 0; w <= m; w++)
        {
            if (weights[i - 1] <= w)
            {
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            }
            else
            {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    return dp[n][m];
}

int main()
{
    int n;
    cout << "Enter the number of objects: ";
    cin >> n;
    vector<int> weights(n);
    vector<int> values(n);
    cout << "Enter weights of the objects: ";
    for (int i = 0; i < n; i++)
    {
        cin >> weights[i];
    }
    cout << "Enter the values of the objects: ";
    for (int i = 0; i < n; i++)
    {
        cin >> values[i];
    }

    int m;
    cout << "Enter the knapsack capacity: ";
    cin >> m;

    int res = knapsack(m, weights, values, n);
    cout << "Max value in knapsack: " << res << endl;
    return 0;
}