#include <bits/stdc++.h>
using namespace std;

int optimalStorageTape(vector<int> &tapes)
{
    sort(tapes.begin(), tapes.end());

    cout << "Optimal order to store files: ";
    for (int i = 0; i < tapes.size(); i++)
    {
        cout << tapes[i] << " ";
    }
    cout << endl;

    int cumulativeStorageTime = 0;
    int totalRetrievalTime = 0;

    for (int i = 0; i < tapes.size(); i++)
    {
        cumulativeStorageTime += tapes[i];
        totalRetrievalTime += cumulativeStorageTime;
    }

    double meanRetrievalTime = (double)totalRetrievalTime / tapes.size();

    cout << "Total Retrieval Time: " << totalRetrievalTime << endl;
    cout << "Mean Retrieval Time: " << meanRetrievalTime;
}

int main()
{
    int n;
    cout << "Enter number of tapes: ";
    cin >> n;

    vector<int> tapes(n);
    cout << "Enter the tapes: ";
    for (int i = 0; i < n; i++)
    {
        cin >> tapes[i];
    }

    optimalStorageTape(tapes);
    return 0;
}