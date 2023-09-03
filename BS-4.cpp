

// Problem link - https://leetcode.com/problems/search-insert-position/description/

#include <bits/stdc++.h>
using namespace std;

int bs(int low, int high, vector<int> &nums, int n, int target) {


    int ans = 0;
    while(low <= high) {

        int mid = low + (high-low)/2;

        if(nums[mid] == target) {
            ans = mid;
            break;
        }else if(nums[mid] < target){
            // there is a possibility that it can be inserted at mid+1
            ans = mid + 1;

            // move right
            low = mid + 1;
        }else{

            // move left
            high = mid - 1;
        }
    }



    return ans;

}


int main() {

    vector<int> nums = {1,2,5,6};
    int n = nums.size();
    int target = 0;

    cout<<bs(0,n-1,nums,n,target);



    return 0;
}