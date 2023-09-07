
// Problem link  - https://www.codingninjas.com/studio/problems/occurrence-of-x-in-a-sorted-array_630456



#include <bits/stdc++.h>
using namespace std;




// Approach 1 - LinearSearch (BruetForce)
int linearSearchBruteForce(vector<int> &nums, int target) {
    int count = 0;

    for(int i = 0;i<nums.size();i++) {
        if(nums[i] == target) {
            count++;
        }
    }

    return count;

    // Time Complexity is O(n)
}








// Approach 2 - BinarySearch
// Intuition - As the array is sorted...and we have to search for a particular value....we can use...the BinarySearch Algorithm..
//             We can get the first and last index of occurence of the target....then the number of occurences will be just
//             last-first+1

int firstOccurence(vector<int> &nums, int target) {
    // Initializing with -1...which simply means....the target element is not present
    int first = -1;
    int low = 0;
    int high = nums.size()-1;

    while(low <= high) {
        int mid = low + (high-low)/2;

        if(nums[mid] == target) {
            first = mid;
            // as we have to get the first occurence ...so if this index has a value target...we have to search if the target 
            // is present befire this index as well or not..
            high = mid - 1;
        }else if(nums[mid] > target) {
            high = mid - 1;
        }else{
            low = mid + 1;
        }

    }


    return first;

}


int lastOccurence(vector<int> &nums, int target) {
    int last = -1;
    int low = 0;
    int high = nums.size()-1;


    while(low <= high) {
        int mid = low + (high-low)/2;

        if(nums[mid] == target) {
            last = mid;
            // as we have to find the last occurence of the element...we will check whether the target is present after this 
            // index(mid) or not...
            low = mid + 1;
        }else if(nums[mid] > target) {
            high = mid - 1;
        }else{
            low = mid + 1;
        }
    }


    return last;


}

int main() {
    vector<int> nums = {1 ,1 ,1 ,2 ,2 ,3 ,3};
    int target1 = 3;
    int target2 = 4;

    cout<<linearSearchBruteForce(nums,target1)<<endl;;
    cout<<linearSearchBruteForce(nums,target2)<<endl;;




    int first1 = firstOccurence(nums,target1);
    if(first1 == -1) {
        // which means ...the element is not present
        cout<< 0;
    }else{
        int last1 = lastOccurence(nums,target1);
        cout<<last1-first1+1<<endl;
    }
    



    int first2 = firstOccurence(nums,target2);
    if(first2 == -1) {
        // which means ...the element is not present
        cout<< 0;
    }else{
        int last2 = lastOccurence(nums,target2);
       cout<<last2-first2+1<<endl;
    }

    



    return 0;
}