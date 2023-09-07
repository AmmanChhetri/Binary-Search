

// Problem Link - https://leetcode.com/problems/search-in-rotated-sorted-array-ii/


#include <bits/stdc++.h>
using namespace std;


// Approach 1 - LinearSearch (Brute Force)
bool linearSearchBruteForce(vector<int> &nums, int target) {
   
    for(int i = 0;i<nums.size();i++) {
        if(nums[i] == target) {
            return true;
        }
    }

    return false;
}







// Approach 2 - BinarySearch....

bool binarySearch(vector<int> &nums, int target) {

    int low = 0;
    int high = nums.size()-1;

    while(low <= high) {
        int mid = low + (high-low)/2;

        // agian as the array is rotated from one point...we can still say either of the right or left portion of nums[mid]...
        // will always be sorted...but to check which part is sorted...in the problem ... BS-8 ...we did the comparison between
        //  nums[low] & nums[mid] ... and .... nums[mid] & nums[high].... as all the elements are unique we did comparison 
        // easily....we can use the same code here but...it will fail the case ...wehen we are unable to compare...and this 
        // will only happen when...( nums[low] == nums[mid] == nums[high] ).. ..so we need to handle this case...so if we know 
        // that the element at mid,low and high are equal and they are not equal to target as welll so we just trim our search 
        // space by 1...from low and high 
        

        if(nums[mid] == target) {
            return true;
        }
        

        if(nums[low] == nums[mid] && nums[mid] == nums[high]) {
            low = low + 1;
            high = high + 1;
            continue;
        }

        // left sorted
        if(nums[low] <= nums[mid]) {
            // as left part is sorted...we can easily predict where we have to search..if the nums[low] <= target <= nums[mid]...
            // if it is present we just search here ...otherwise we search right side...
            // The sole purpose of checking which part is sorted is because to predict ...where our answer will be...
            if(nums[low] <= target && target <= nums[mid]) {
                high = mid - 1;
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


    return false;


    // Time complexity will be generally ~O(logn)....but if the test case is like {3,3,3,.......1,3,3,3,3,.........3} ...a huge
    // length... ...then we almost trim the half of the array (!!! almost !!!) ...so for that time complexity may go ~O(n/2)
}

int main() {

    vector<int> nums1 = {2,5,6,0,0,1,2};
    vector<int> nums2 = {3,3,1,3,3,3,3};

    int target1  = 0;
    int target2  = 1;

    cout<<linearSearchBruteForce(nums1,target1)<<endl;
    cout<<binarySearch(nums2,target2)<<endl;

    return 0;
}