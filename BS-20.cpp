

// Problem Link - https://leetcode.com/problems/find-the-smallest-divisor-given-a-threshold/


#include <bits/stdc++.h>
using namespace std;



// Helper function to tell if for a given divisor ...the sum of the values obtained by dividing each number of the array is
// less than or equal to the threshold...
bool isPossible(vector<int> &nums, int threshold, int divisor) {
    int sum = 0;
    for(int i = 0;i<nums.size();i++) {
        // it is very - very important to convert the nums[i] and divisor to double before divding and taking ceil...because if
        // we dont convert then it will perform an integer divison ...plus the divison result is integer ...so the ceil wont 
        // work...example suppose nums[i]=7 and divisor = 3...so if we do integer division then (7/3)=2..so ceil(3) = 2...which
        // is wrong...suppose if we convert the numbers to double then (7/3)=2.33...which means ceil(2.33) = 3...which is 
        // correct....
        sum += ceil((double)nums[i]/(double)divisor);
    }

    return (sum <= threshold) ? true : false;
}





// Helper function to find the maximum of the given nums array...
int findMax(vector<int> &nums) {
    int mxm = INT_MIN;

    for(int i = 0;i<nums.size();i++) {
        mxm = max(mxm,nums[i]);
    }

    return mxm;
}





// Approach 1 - LinearSearch (Brute Force)...

// Intuition - As we are required to find the minimum value of divisor...and divisor can be anything from 1 to 
//             max(nums[])...now why till max(nums[]) ..because the result obtained by taking max(nums[]) as divisor ..will be 
//             same as for any divisor > max(nums[])..so it is pointless to search ....

// Logic - the moment we get our answer...we store it and berak from loop ...as we need to print the minimum...
int linearSearch(vector<int> &nums, int threshold) {

    int ans = -1;

    int mxm = findMax(nums);

    // we are checking from the the divisor 1 because...suppose the thresold value is greater than or equal to the sum of all 
    // numbers of threshold...in that case our divior will always be `1`...as we need to get the lowest possible divisor....
    for(int i = 1;i<=mxm;i++) {
        if(isPossible(nums,threshold,i)){
            ans = i;
            break;
        }
    }


    return ans;

    // Time complexity is O(mxm*n) ...where n = nums.size() ....and mxm = maximum value of the nums[]....the worst case occurs
    //  when we have to search till mxm....and this will only happen if the thershold is very lesss..


    // Now there can be a follow up question like ...suppose we have a array = {1,2,3,4} ...and threshold as `3` ...now tell 
    // me ...for which minimum value of divisor will give the result lesser than or equal to threshold....the answer is 
    // `there is no possible value`....why? because the thresold value should be atleast the length of the array...here the
    //  threshold(3) < nums.size()...that's why it is not possible....because the minimum threshold we can obtained from a 
    // given nums array is when we take our divisor as the max(nums[])...so whenver we take our divisor as max(nums[])...our
    //  result will always be length of nums[]...so if the given threshold value is less than this result then the answer is 
    // not possible....
}









// Approach - 2 ... Binary Search
// Intuition - As we can see our answer space is lying in between [1,max(nums[])]...which is sorted ...and also as we are
//             looking for a value....and as we know that the whole answer space is divided into two sections....one where 
//             answer is possible and one where ans is not possible...and we look at the possible answer section...which means 
//             we are removing the section which is not possible....all this are enough reason to apply `binarySearch`....now
//             what the sections mentioned here means ..suppose if we are finding divisor ans we see got 5 as of now as our 
//             answer...now we know all the numbers after 5 wont fit for our search space...even if they yield a result of 
//             lesser threshold value...because we 5 will be the minimum among them..which we want...and if 5 is the temporary 
//             answer....threfore there is a chance we might get a lesser answer...in the range [1,5)...so our search sapce is
//             like...         1   2  3  4   5  6  7  8  9  10 ...so on..
//                             ✓  ✓  ✓  ✓  ✓  🗴  🗴  🗴  🗴  🗴

// .... as we can see our answer space is divided into possible and not possible sections..... :)


// Logic -    Suppose we are standing at a particular divisor(mid)...now using this divior we got our result greater then 
//            threshold...which simply means..our divisor value is less....(because as we are dividing nums[i]/divisor)...so if
//            we want to reduce this divison value we need to increase divisor value....now suppose for a particular divisor 
//            we got divisor result lesser than or equal to threshold we can say this point(mid)...may be our answer....but we
//            need to check if there are any lesser value of mid...which aso gives divison result lesser than or equal to 
//            threshold... (Which is our ultimate goal ...to get the lowest divisor....)
int binarySearch(vector<int> &nums, int threshold) {
    int low = 1;

    // int high = *max_element(nums.begin(),nums.end());
    int high = findMax(nums);



    int ans;

    while(low <= high) {
        int mid = low + (high-low)/2;

        if(isPossible(nums,threshold,mid)) {
            ans = mid;
            high = mid - 1;
        }else{
            low = mid + 1;
        }
    }
    
    // return low;
    return ans;

    // Time Complexity is O(log(high) * n) ...n for checking isPossible...
}


int main() {

    vector<int> nums = {44,22,33,11,1};
    int threshold = 5;

    cout<<"The minimum value of divisor will be : "<<linearSearch(nums,threshold) << endl;
    cout<<"The minimum value of divisor will be : "<<binarySearch(nums,threshold) << endl;

    return 0;
}