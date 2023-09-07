

// Problem Link - https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/

#include <bits/stdc++.h>
using namespace std;





vector<int>  linearSearchBruteForce(vector<int> &nums, int target) {
    
    // We will search the array linearly...if we find the occurence of the element ..we will update the index...otherwise we 
    // won't update...and return this default vector (ans)
    vector<int> ans(2,-1);
    int n = nums.size();

    // this variable will keep track...if the target has occured only once or more...initially k ==0 ....which means...when 
    // nums[i]==target....and if k==0...which means this is the first time target is appearing ...that's why we update both the
    // index...as if the element has occured only once...then the first and last occurence index will be same...therefore as
    // soon we are encountering the target for the first time..after updating the index...we will increment the k ...so after 
    // this ..later whenever target will appear...only the index==1 ...will gets updated...


    int k = 0;

    for(int i = 0;i<n;i++) {
        if(nums[i] == target) {
            if(k == 0) {
                ans[0] = i;
                ans[1] = i;
                k++;
            }else{
                ans[1] = i;

            }
        }
    }

    return ans;
}











// Using in-built lower_bound and upper_bound functions...
vector<int>  boundsLogic(vector<int> &nums, int target) {
    

    // using the in-built functions....also...this functions return an iterator....that's why we subtract nums.begin() ...to 
    // convert thme into numerical index...
    int lb = lower_bound(nums.begin(),nums.end(),target) - nums.begin();
    int ub = upper_bound(nums.begin(),nums.end(),target) - nums.begin() - 1;


    int n = nums.size();

    // Here we can have multiple cases...
        // Case 1 : 
            // if the target is present in the array ..then lower_bound will return the iterator to the element that is either 
            // equal to the target or just greater than the target...and the upper bound will return an iterator to the value in
            // the array ..that is just greater than the target.....therefore last occurence always be (ub-1).
        // Case 2:
            // if the target element is greater than the last element of the array...then lower_bound will return an iterator 
            // pointing to the hypothetical index(ie. n ...where n = nums.size() )....just after last element...
            // Ex - nums = {2,4,5,7} ....target = 9...
        // Case 3:
            // if the target is not present in the array ...and also it is lesser than the last element...then it will return the 
            // iterator...where it should have present ...if arranged in the ascending order...
            // Ex - nums = {2,4,5,7} ...target = 3....so lower_bound will return an iterator pointing to index = 1....


    if(lb == n || nums[lb] != target) {
        // lb == n  ...for Case 2
        // nums[lb] != target ... for Case 3
        // both together means...if the target is not present...
        return {-1,-1};
    }else{
        // if target is present
        return {lb,ub};
    }


}










// Approach 3 ....is to use plane binary Search...and find the index for the first occurence and the last occurence of the target
int firstOccurence(vector<int> &nums, int target) {
    
    int low = 0;
    int high = nums.size()-1;

    int first = -1;

    while(low <= high) {
        int mid = low + (high-low)/2;

        if(nums[mid] == target) {
            first = mid;
            high = mid - 1;
        }else if(nums[mid] > target){
            high = mid - 1;
        }else{
            low = mid + 1;
        }
    }

    return first;
}



int lastOccurence(vector<int> &nums, int target) {
    int low = 0;
    int high = nums.size()-1;

    int last = -1;

    while(low <= high) {
        int mid = low + (high-low)/2;

        if(nums[mid] ==  target) {
            last = mid;
            low = mid + 1;
        }else if(nums[mid] > target){
            high = mid - 1;
        }else{
            low = mid + 1;
        }
    }

    return last;


}



int main() {


    vector<int> nums = {2,4,6,8,8,8,11,13};
    int target = 8;
    
    //  Approach 1
    vector<int> ans1 = linearSearchBruteForce(nums,target);
    cout<<ans1[0]<<" "<<ans1[1] <<endl;
    
    //  Approach 2
    vector<int> ans2 = boundsLogic(nums,target);
    cout<<ans2[0]<<" "<<ans2[1] <<endl;

    //  Approach 3
    int first = firstOccurence(nums,target);
    if(first == -1) {
        cout<<"-1"<<" "<<"-1"<<endl;
    }

    int last = lastOccurence(nums,target);

    cout<<first<<" "<<last<<endl;


    return 0;
}