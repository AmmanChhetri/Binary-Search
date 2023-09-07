

// Problem Link - https://www.codingninjas.com/studio/problems/rotation_7449070


#include <bits/stdc++.h>
using namespace std;




// Intuition is again...as the array was sorted and rotated from a single point...but as we know it is rotated from the 
// ``same point``  ....so we can and we will apply bianry Search here..


// now the logic is simple...we know if we have a normal sorted array ...so in this sorted array the minimum element of the 
// array will always lie @index 0....for eaach rotation we are doing (i+1)mod(n)...here i=index..and n=size of array....now if 
// we are able to find the index of the minimum element in the rotated sorted array...we can say this index will be our answer....
// suppose nums = {3,4,5,1,2}...so the index of the minimum element in the array is 3...so we can say the array is rotated 
// 3 times...as 3-0 = 3....our normal sorted array should have {1,2,3,4,5}...
// execution -  after 1st rotation = {5,1,2,3,4}...
//              after 2nd rotation = {4,5,1,2,3}...
//              after 3rd rotation = {3,4,5,1,2}...

int findKRotation(vector<int> &nums) {

    int low = 0;
    int high = nums.size()-1;

    int ans = INT_MAX; // to store the minimum element...
    int min_index = 0; // to store the index of the minimum element...

    while(low <= high) {
        int mid = low + (high-low)/2;

        // left sorted
        if(nums[low] <= nums[mid]) {
            // if it is left sorted...then the minimum of this sorted part will lie at index low...so we will check if the 
            // element @index low...si lesser than the previously found min element ...if yes...we will update 
            // ans(minimum element)...at the same time we also update the min_index
            if(nums[low] < ans) {
                ans = nums[low];
                min_index = low;
            }
            // this if condition may or may not execute...so if it executes..we will update our variables...and move right...
            // if the condition is not executed...we still have to move right
            low = mid + 1;
        }else{
            // Right sorted
            if(nums[mid] < ans) {
                ans = nums[mid];
                min_index = mid;                
            }
            high = mid - 1;
        }

    }

    return min_index;


    // Now in this prblem we had...unique elements...if in the interview...the interviewer gave a follow up..saying there can 
    // be duplicates...then we have to handle the duplicates in the rotated sorted array ...as done in the problem ``BS-9``
    //...the rest of this code remains same...

}


int main() {

    vector<int> nums = {32,37,47,49,2,9,11,15,16,30};

    cout<<findKRotation(nums)<<endl;
    
    
    return 0;
}