

// Problem Link - https://leetcode.com/problems/single-element-in-a-sorted-array/

#include <bits/stdc++.h>
using namespace std;



// Approach 1 - LinearSearch (BruteForce )
int linearSearchBruteForce_1(vector<int> &nums) {
    
    // as we are jumping to i+2 each time...so we will only use for loop till nums.size()-2....in this way the last element will always remains unchecked...that's why
    // we initialize the variable unique with it..if we are able to find our answer before last index then we will return 
    // that index...otherwise return the default value of unique(ie. last element of the array)....consider nums={1,1,2,2,3}...
    int unique = nums[nums.size()-1];

    if(nums.size() == 1) {
        // if the array size is 1...our logic will give runtime error because of the i+1 going out of bound...so we are 
        // handling this case seperately....
        return nums[0];
    }
    
    for(int i = 0;i<=nums.size()-2;i = i+2) {
        
        if(nums[i+1] != nums[i]) {
            unique = nums[i];
            break;
        }

    }


    // for(int i = 0;i<nums.size();i++) {
    //     if(i == 0) {
    //         if(nums[i+1] != nums[i]) {
    //             unique =  nums[i];
    //             break;
    //         }
    //     }else if(i == nums.size()-1) {
    //         if(nums[i-1] != nums[i]) {
    //             unique =  nums[i];
    //             break;
    //         }
    //     }else{
    //         if(nums[i]!=nums[i+1] && nums[i]!=nums[i-1]) {
    //             unique =  nums[i];
    //             break;
    //         }
    //     }
    // }

    return unique;
}





// Approach 2 - LinearSearch (BruteForce  using bitwise operator XOR)...(remember their is only one unique element and rest of 
//                                                  the elements have dupicates...that's why this logic will work)

    // Here this logic will perform better than the bruteForce_1 ...when the array is not sorted...but here as the array is 
    // sorted...so this both BruteForce method will perform similar....and if the array is sorteed...the BruteForce_1 ..wil 
    // perform slightly better...as if the unique element lies somewhere  in the array...we dont need to traverse the whole 
    // array...we can simply break as soon we got our answer...as there is only one unique...

// Intuition - as all the elements have their pair so their xor will always be 0...as xor of 2 same numbers are always 0...also
//             xor of 0 with a number is the number itself...so all the duplicates...will Xor'ed as 0...and when this 0 is Xor'ed with the unique element ...we will get the unique element
int linearSearchBruteForce_2(vector<int> &nums) {

    int ans = 0;
    for(int i = 0;i<nums.size();i++) {
        ans ^= nums[i];
    }

    return ans;
}








// Approach 3 - BinarySearch
// Intuition - As the array is sorted ...and we are searching for a element(here unique to be precise)...so we can apply 
//             binary search
int singleNonDuplicate(vector<int>& nums) {

    int n = nums.size();
    

    // Now here we are finding a unique element in the preoblem....and for finding a unique element ...we have to compare the 
    // element to it's right and to the element in its left....which means ...if the element at nums[mid] is not equal to 
    // element at nums[mid+1] and nums[mid-1]...we can surely say....that element at index mid is unique...But there are edge 
    // cases...suppose we are standing at index 0 (mid == 0) ...then we dont have left element to compare...similary if we are 
    // index n-1...we dont have right element...so to handle this cases...we have to right more conditions inside our while 
    // loop of Binary Search...which will make our code less readable...so what we will do is vhange our search space from 
    // low=0 to low=1 and high=n-1 to high=n-2......and we will deal with the edge case seperately...
    int low = 1;
    int high = n-2;


    if(nums[0] != nums[1]) {
        // which means nums[0] is unique....because..whatever number we have at 0th index...it's pair should be there at index
        // 1..as we can have only one unique element...so if it's pair is not there...which simply means...nums[0] is the 
        // unique element...
        return nums[0];
    }

    

    if(nums[n-1] != nums[n-2]) {
        // which means the last element of the array is unique...
        return nums[n-1];
    }
    

    

    while(low <= high) {
        int mid = low + (high-low)/2;


        if( (nums[mid] != nums[mid-1]) && (nums[mid] != nums[mid+1]) ) {
            // element at mid is unique....
            return nums[mid];
        }
        

        // we always think of trimming our search space in a binary search....so we will try to do the same here as well....

        // If we observe carefully ...suppose we have a normal sorted array ..in which each element haa it's pair (duplicate)
        // ....so can we say that the length of this type of array is always even...as each element is in pairs...so for each 
        // element pairs...its first number will be at even index....and the second number of the pair will be at odd index...
        // Example = {1,1,3,3,5,5}...here indexes are 0,1,2,3,4,5...so as we can see....that property of first element at even 
        // index and second being at odd index....now what if we add a unique element without it's pair(duplicate) [remember
        //  we can have only one unique element according to the problem and rest of them will be in pairs...that;s why this 
        // logic will work]....it will always alter this flow...
        // Example - nums = {1,1,3,3,4,5,5} ....
        // Index are      = {0,1,2,3,4,5,6} ....now if we observe carefully ...all the elements that are before the unique 
        // elements follow ...the pattern of indexes as (even,odd) ...where for each pair the first element is att even index 
        // and the second element is at odd index.... but for all the pairs after the unique element...the first element of 
        // the pair occurs at a odd index..and the second element at even index......so we can say if we have a pair as index
        // (even,odd) ...we can say we are at left of the unique element ....which means we need to move right...similarly if we
        // have a pair as index (odd,even) ...which means...we are at right of unique element...which means our unique element
        // is to the left...




        // we are to the left of the unique element.....if we are at a even index(mid is even)...we have to check if the 
        // element at right of mid is same as element at mid....OR.....if we are standing at odd index...we have to check if 
        // we have the same element at left of mid...if any of this case is true...which means we are at left of unique 
        // element...because.. ```if we are to the left of the unique element``` the pair always will be in the form of indexes 
        // (even,odd) ...so that's why if mid is even ...which means it pair should be to its right...similary if mid is odd..
        // which means...it pair should be at left...
        if( (mid%2==0 && nums[mid+1]==nums[mid]) || (mid%2==1 && nums[mid-1]==nums[mid]) ) {
            // as we 
            // move right
            low = mid + 1;
        }else{
            // move left...as we are to the right of unique element...
            high = mid - 1;
        }


    }

    

    // dummy return....we won't ever return this value..as our function will always return the unique value....
    return -1;
        
}





int main() {

    vector<int> nums = {1,1,2,2,3,3,4,5,5,6,6};

    cout<<linearSearchBruteForce_1(nums)<<endl;
    cout<<linearSearchBruteForce_2(nums)<<endl;
    cout<<singleNonDuplicate(nums)<<endl;



    return 0;
}