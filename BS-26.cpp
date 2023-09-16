

// Problem Link - https://www.codingninjas.com/studio/problems/painter-s-partition-problem_1089557



#include <bits/stdc++.h>
using namespace std;


// we have to find `minimum` time to paint the boards using `k` painters.......where painters can only paint in consecutive 
// manner...

// Problem is similar to the last problem...here we need to find the lowest possible  maximum amount of time required by any 
// painters to paint the boards....example - arr[] = {2,1,5,6,2,3} and k = 2....here we can divide it into different sequence
// but if painter 1 paints the first 3 boards it will take him 8 units of time ....and the remaining is painted by painter 2
// ...which will take him 11 units of time ...so max(8,11) = 11 ...this is the minimum possible maximum time taken...if you 
// try different combinations u will find every `max` time being greater than this 11....so this means 11 is the time required 
// to paint the boards...


// So here we are finding min(maximum time required to paint the boards)..





// Helper function to count the number of painters that can paint  the board ...if we consider the some timeLimit...
int countPainters(vector<int> &nums, int maxTimeLimit) {

    int count = 1;
    int sum = 0;

    for(int i = 0;i<nums.size();i++) {
        if(sum + nums[i] > maxTimeLimit) {
            count++;
            sum = nums[i];
        }else{
            sum += nums[i];
        }
    }

    return count;
}









// ! Approach - 1  Linear Search

// This problem is similar to last problem....
// The lowest possible maximum time required to paint the boards is the max(boards[]) ...when we have k = boards.size()...so 
// which means we only have 1 combination possible ...that too...when each board is painted by exactly 1 painter....similarly
// the maximum possible value of maximum amount of time to paint the boards....is when we have k = 1...which means a single
// painter needs to paint the whole wall....which means sum(boards[])...so if you observe carefully we just found out the range
// where our answer will definitely lie...for a particular problem(particular boards[]).... ie. [max(boards),sum(boards)]...
// it will never be lesser than max(boards)...because max(boards) is possible when we exactly have boards.size() ...painters...
// so if we increase the painter counts from this value(ie len(boards)) ...we won't be able to assign every painter the boards...
// as boards.size() > numberOFpainters..similarly our value wont exceeds the sum(boards)...well that for sure...we can only paint
// what we have....

int linearSearch(vector<int> &nums, int k) {
    int low  = *max_element(nums.begin(),nums.end());
    int high = accumulate(nums.begin(),nums.end(),0);

    for(int maxTimeLimit = low; maxTimeLimit<=high; maxTimeLimit++ ) {
        if(countPainters(nums,maxTimeLimit) == k) {
            return maxTimeLimit;
        }
    }

    return low;
    // Time complexity is O(sum-max+1)*O(n)...
}







// ! Appraoch - 2 Binary Search.
int binarySearch(vector<int> &nums, int k) {
    int low  = *max_element(nums.begin(),nums.end());
    int high = accumulate(nums.begin(),nums.end(),0);


    while(low <= high) {
        int mid = low + (high-low)/2;

        if(countPainters(nums,mid) > k) {
            low = mid + 1;
        }else{
            high = mid - 1;
        }
    }


    return low;
    // Time complexity is O(log(sum-max+1))*O(n)...

}




int main() {
    vector<int> nums = {2,1,5,6,2,3};
    int k = 2;

    cout<<linearSearch(nums,k) <<endl;
    cout<<binarySearch(nums,k) <<endl;
    return 0;
}