
// Problem Link - https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/


#include <bits/stdc++.h>
using namespace std;



// Approach 1 - LinearSearch (Brute Force)
int linearSearchBruteForce(vector<int> &nums) {
    int ans = 1e9;

    for(int i = 0;i<nums.size();i++) {
        ans = min(ans,nums[i]);
    }


    return ans;
}









// Approach 2 - BinarySearch..
// As the array was sorted and it is only rotated once from a point...we can always apply binary search...because....in the rotated array,,,if we take any indexed number....either the
//  left part of it or the right part of it is always sorted....so we can easily apply binary search in the sorted part..ans 
// search the target...and eliminate the space that is not required...


// Always remember ...binary search is all about removing the unrequired search space....and search where the answer may 
// possibly occur.....and this type of rotated sorted array question...we have to determine which half(right or left) is sorted...
// so we can easily apply binary search there....and look for our answer....

int findMin(vector<int> &nums) {
    int ans = 1e9;
    int low = 0;
    int high = nums.size()-1;


    while(low <= high) {
        int mid = low + (high-mid)/2;


        // if the array is left sorted...which means....the lowest element of this sorted array will always lie at index
        // low(property of sorted array)....similarly if the array is right sorted...the minimum element will always present 
        // in index mid...

        // dry running the binary search of the roatated array ...we find that...we can't directly say that the lowest element 
        // will always present in the unsorted or sorted half...but we can easily detect the minimum in the sorted array ...that's why if we find a sorted half....the 
        // first element of the sorted half can be the minimum...that's why storing it....after which we eliminate the whole
        //  sorted half...as we no longer needed it

        if(nums[low] <= nums[mid]) {
            // left sorted
            ans = min(ans,nums[low]);
            low = mid + 1;
        }else{
            // right sorted
            ans = min(ans,nums[mid]);
            high = mid - 1;
        }
    }



    return ans;
    
}



int main() {

    vector<int> nums = {4,5,6,7,0,1,2};
    int n = nums.size();

    cout<<linearSearchBruteForce(nums)<<endl;
    cout<<findMin(nums)<<endl;


    return 0;
}