
// Problem Link - https://leetcode.com/problems/search-in-rotated-sorted-array/

#include <bits/stdc++.h> 
using namespace std;


// Approach 1 - LinearSearch (BruteForce)
 int linearSearchBruteForce(vector<int>& nums, int target) {

        int ind = -1;

        for(int i = 0;i<nums.size();i++) {
            if(nums[i] == target) {
                ind = i;
                // as elements are unique...we will only have one solution if possible...
                break;
            }
        }


        return ind;
}







// Approach 2 - BinarySearch...
// Intuition ....as the array is rotated from a single point....so whatever element we pick from the array...either the left 
// part of the array from that element or the right part of the array from that element is always sorted
// If the array is roated from a pivot once...then we can always apply binary Search..
int binarySearch(vector<int> &nums, int target) {

    int ans = -1;
    int low = 0;
    int high = nums.size()-1;

    while(low <= high) {
        int mid = low + (high-low)/2;

        if(nums[mid] == target) {
            
            // as nums has unique element ...there is only one answer possible..
            return mid;
        }

        if(nums[low] <= nums[mid]) {
            // left sorted ...
            // Here the intuition is ...we can easily check if the target values lies between given numbers or not if it is 
            // sorted...so our first aim is to check which part of the array is sorted...if we can detect the sorted array 
            // ...we can easily trim our search space
            if(nums[low] <= target && target <=  nums[mid]) {
                // if the array is left sorted...we can simply find if the target lies within the nums[low],nums[mid]...as it 
                // is sorted...if it lies...then the target can lie in this range.. we dont want the right part of the array...
                // if it doesnt lies then we dont want the left part of the array
                high = mid -1;
            }else{
                low = mid + 1;
            }

        }else{
            // right sorted
            if(nums[mid] <= target && target <= nums[high]) {
                low = mid + 1;
            }else{
                high = mid - 1;
            }

        }

    }



    return ans;

}




int main() {

    vector<int> nums = {7,8,9,1,2,3,4,5,6};
    int target = 1;

    cout<<linearSearchBruteForce(nums,target)<<endl;
     
    cout<<binarySearch(nums,target)<<endl;

    return 0;
}