#include <iostream>
#include <vector>
using namespace std;

pair<int, int> findMinMax(vector<int>& nums, int low, int high) {
    int n=nums.size();
    if(low==high) {
        return {nums[low], nums[low]};
    }
    if(high==low+1) {
        if(nums[low]<nums[high]) {
            return {nums[low], nums[high]};
        }
        else {
            return {nums[high], nums[low]};
        }
    }

    int mid=(low+high)/2;

    pair<int, int> left=findMinMax(nums, low, mid);
    pair<int, int> right=findMinMax(nums, mid+1, high);

    int mini=min(left.first, right.first);
    int maxi=max(left.second, right.second);

    return {mini, maxi};
}

int main() {
    vector<int> nums={2, 10, 4, 13, 24, 19, 30, 55, 60, 29};

    pair<int, int> res=findMinMax(nums, 0, nums.size()-1);

    cout<<"Minimum Element: "<<res.first<<endl;
    cout<<"Maximum Element: "<<res.second<<endl;

    return 0;
}