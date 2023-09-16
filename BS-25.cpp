

// Problem Link - https://leetcode.com/problems/split-array-largest-sum/


#include <bits/stdc++.h>
using namespace std;




// Helper function to count the number of partitions we can make from a given subarray...when we have a maxLimit on the sum...
int countPartitions(vector<int> &nums, int maxSumLimit) {

    int partitionsCount = 1;
    int sum = 0;

    for(int i = 0;i<nums.size();i++) {
        if(sum + nums[i] > maxSumLimit) {
            // if including this number exceeds our limit ...we will include it in next partition
            partitionsCount++;
            sum = nums[i];
        }else{
            // else this number can be included into the current partition..
            sum += nums[i];
        }
    }

    return partitionsCount;
}






// Approach 1 - Linear Search

// We need to find min(maximum sum subarray) ....now again the same concept of min(max)....we have to focus more on what inside
// the bracket...suppose we have an array = {7,2,5,10,8}...now tell me what is the lowest possible maximum sum of subarray of 
// the given array and waht is the highest possible maximum sum of subarray of the given array.... we know the lowest possible
// value of maximum sum of subarray is the max(array) right? ....as what we want is to divide the given array into k- subarrays 
// and then find what is the maximum sum among all the subarrays....we know the lowest possible maximum sum subarrays is 
// max(array)...when we divide the array into k(arr.size())...then each element of this array represents the subarray...so the
// maximum sum will be definitely the max(array)....similarly the highest posssible value of maximum sum subarray will be when 
// we consider the whole array as subarray ...this will happen when k = 1..(it is mentioned in the problem that k>=1) ...which 
// means highest possible value will  be sum(array[])..so we figured out that our answer will always lie between this range..

// now again im telling...we have to minimize the maximum sum of subarrays....but the thing is we should also able to divide
// the whole array into exactly k subarrays....what actually we are doing is we are checking the maximum sum given by each 
// differnt combinations...then we are minimizing it(finding minimum)...

// now let say arr[] = {7,2,5,10,8} ....now lets say k = 5...now we know our anwer will lie between [max(arr),sum(arr)] => 
// [10,32]...so we will keep checking from 10 ...considering the maxSumLimit we count the subarrays and we got 4 
// (that are {7,2}, {5}, {10}, {8})....which implies this maxSumLimit is not possible...now many will get doubt like we could
// have divided the array like {7},{2},{5},{10},{8} ....and got 5 partions...but this comination is wrong...when we consider 
// maxSumLimit as 10 ...we cant add the element to the next partition unless the previos one is filled....so that's why that 
// answer of dividing the arrays into 5 ...for maxSumLimit is 10...is wrong ...and the division into 4 subarrays is correct...
 
int linearSearch(vector<int> &nums, int k) {

    int low = *max_element(nums.begin(),nums.end());
    int high = accumulate(nums.begin(),nums.end(),0);

    for(int maxSumLimit = low;maxSumLimit<=high;maxSumLimit++) {
        if(countPartitions(nums,maxSumLimit) == k) {
            return maxSumLimit;
        }
    }

    
    // Here we are returning low ...because of the cases....when we are unable to divide the array into k-subarrays...
    // if u consider this example where arr[] = {2,3,1,1,1,1,1} and k = 5...our range will be [3,10] ..so if we dry run this we
    // observe we are not able to divide them into exactly 5 subarrays...hence limit is 3...the number of subarrays we are getting
    // is 4...which is less than 5 itself...and we know....as we are going to increase the limit the number of subarrays itself
    // going to decrease...so we can't make 5 subarrays...so we just returning the low...as it is the minimum possible maximum
    // sum of subarray....as a fallback value...if u remember we did say the max(arr[]) is the lowest possible value...so for 
    // lowest possible answer(3) ...we are getting 4 subarrays but we want 5...which means we need to reduce the limit...so that
    // a array can hold less...and number of arrays increases...but we can't reduce the sum before 3...that's why we returning
    // low...
    return low;

    // Time Complexity is O(sum-max+1) * O(n)
    
}








// Approach 2 - Binary Search


int binarySearch(vector<int> &nums, int k) {
    int low = *max_element(nums.begin(),nums.end());
    int high = accumulate(nums.begin(),nums.end(),0);

    while(low <= high) {
        int mid = low + (high-low)/2;

        if(countPartitions(nums,mid) > k) {
            // if we are getting more number of students ...which simply means our limit was less...we have to increase our limit
            // so a single array can hold much more sum...
            low = mid + 1;
        }else{
            high = mid - 1;
        }
    }



    return low;

    // Time Complexity is O(log(sum-max+1)) * O(n)
}



int main() {
    vector<int> nums = {7,2,5,10,8};
    int k = 2;

    cout<<linearSearch(nums,k) <<endl;
    cout<<binarySearch(nums,k) <<endl;
    return 0;
}