

// Problem link - https://leetcode.com/problems/find-peak-element/description/


#include <bits/stdc++.h>
using namespace std;



// Approach 1 - LinearSearch (Brute Force)
int linearSearch(vector<int> &nums) {

    // a index i is called a peak when num[i-1] < nums[i] and nums[i] > nums[i+1]... ..it is given it is strictly greater....

    // Here one thing is very important to note....it is given the elements before index 0 of the array is -∞ ....similarly the element 
    // after the last element of the array is also -∞....so our logic is to iterate through each index and check if the current
    //  element is greater than the previous element and greater than the next element ...if yes this is our answer and we break.
    // ..but if we use this logic we will get a runtime error because of the out of bound case....at index 0 ...which does not 
    // have a left element ...and at index n-1...which does not have a right element.....so for this cases we will write a ..
    // seprate code...and check first before checking for whole array...now we know consider a mountain peak....so to the left
    //  of mountain the height is less(simply the value of element will be less to the left of peak) ..similary the right of the 
    // mountain peak is also less(which means smaller element..) ..so if the value before the index 0 is always -∞...we know as 
    // array contains all positive numbers...which means...nums[0] > -∞.... which in terms means...this index 0 ...will be 
    // peak if the element at index 1....is smaller than element at index 0.....similarly the right of the last element of the 
    //array is -∞...and nums[n-1] > -∞...we can say the element at index n-1 ...is peak...when the element at index n-2...is 
    // lesser than the element at index n-1...


    // so we need to check edge cases...as we can't check to the left of num[0] and to the right of nums[n-1]....

    int n = nums.size();

    if(nums[1] < nums[0]) {
        return 0;
    }

    if(nums[n-1] > nums[n-2]) {
        return n-1;
    }

    // we could also have written the cases like ...
    // if(i == 0) {
    //     if(nums[1] < nums[0]) return 0
    // }

    // ..... OR....

    // if(i == n-1) {
    //     if(nums[n-2] < nums[n-1]) {
    //         return n-1;
    //     }
    // }

    for(int i = 1;i<=n-2;i++) {
        if(nums[i-1] < nums[i] && nums[i] > nums[i+1]) {
            return i;
        }
    }

    return -1;
}








// Approrach - 2 - BruteForce (using STL) ...

// Logic - we observe because of the condition given that the array is surrounded by -∞ ..we observe the maximum element of 
// the array is always a peak...so we just have to return the index of the maximum element ...

int stlBruteForce(vector<int> &nums) {
    int ind = max_element(nums.begin(),nums.end()) - nums.begin();

    return ind;
}








// Approach - 3 - Binary Search...

// Intuition - As we are searching for a element ...here peak element....and also if we obseve some part of the array is 
// always sorted....so we think of using binary search and using the property of binary search of elimating the unrequired 
// part of the vector ..and the solution of O(n) is not accepted ...so all these factors...push us to think towards binarySearch

// Logic - Consider the example of a mountain peak...the height of the adjacent area of the peak is always smaller than the 
// peak...so when we use binary search ...wherever our mid is pointing we are checking if that is peal element or not by 
// comparing it with it's adjacent element...if it is peak we return this....otherwise we either move left or right..now 
// suppose your are standing at a particular point of the mountain...now you know when you move to ur right....the height of the mountain 
// increases...and if u move to ur left ...the height of the mountain decreases...so if we want to reach the peak it's obvious
//  we will move to the side which is increaing..because it's the most probable point where we can find the peak ...

// dry run this code...while drawing a mountain like structure according to the array...increase the height of the mountain 
// whenever the array is increasing...and decrease the height of the mountain ehever the array is decreasing...in this way u 
// can visualise and understand much better.... 
int binarySearch(vector<int> &nums) {

    int n = nums.size(); 

    // if array has 1 element only..and we know the left and right of the array is -∞ ....so this element itself is peak..
    if(n == 1) {
        return 0;
    }
 

    // For edge cases...that is for i = 0 and i = n-1 ....as it is given we only need to print a single peak..if there are
    // multiple peaks..that's why we are checking for the edge cases....if it is peak we return the index of peak element...
    
    // Now this is working because it is given that we have to consider -∞ before the array....and -∞ after the array...and we
    //  can also see from the constraints given in the question that.... -2^31 <= nums[i] <= 2^31 - 1 ... so we can easily
    // conclude that the first element of the array will always be greater than the -∞ ...similarly the last element of the 
    // array is also greater than -∞ ...so think ...when this index (0 or n-1) ...will be peak element ...if nums[0] > nums[1] 
    // then nums[0] is the peak element...similarly if nums[n-2] < nums[n-1] ...then nums[n-1] is the peak element...
    

    // these 2 cases ...will also execute when the array is either ascending or descending...
    if(nums[0] > nums[1]) {
        return 0;
    }
    

    if(nums[n-1] > nums[n-2]) {
        return n-1;
    }


            
    //        /\
    //       /  \
    //  /\  /    
    // /  \/   
    // 1 2 1 4 5 3 
    // Here we observe the element 2 and 5 are peak...
    

    // now our logic is to compare the adjacent elements...but there is no left element to the first element...and there is no
    // element to the right of last element of the array...that's why we are checking them seprately....and changing our search
    // space between 1 to n-2.... this will prevent writing this lines inside the while loop ...which will reduce the 
    // readability of the code...so it's better to write the classic binary search and write the if condition seperately....
    
    int low = 1;
    int high = n-2;
    while(low <= high) {
        int mid = low + (high-low)/2;

        if(nums[mid-1] < nums[mid] && nums[mid] > nums[mid+1]) {
            // we have to first check if the mid itself is peak or not...
            return mid;
        }

        if(nums[mid-1] < nums[mid]) {
            // we are at the increasing curve...(consider the mountain) ....
            // peak is towards right... move right
            low = mid + 1;
        }else{
            // we are at the decreasing curve...
            // peak is towards left... move left...
            high = mid - 1;
        }
    }


    return -1;

}


int main() {
    

    // There can be multiple cases..
    
    // Case 1 - Array has a single peak....
    vector<int> nums1 = {1,3,4,6,8,2,1};


    // Case - 2 - Array has multiple peak...
    vector<int> nums2 = {1,2,1,3,5,6,4};


    // Case - 3 - Array is in descending order...
    vector<int> nums3 = {7,6,5,4,3,2,1};


    // Case - 4 - Array is in ascending order....
    vector<int> nums4 = {1,2,4,5,7,9};



    cout<<linearSearch(nums1)<<endl;
    cout<<linearSearch(nums2)<<endl;
    cout<<linearSearch(nums3)<<endl;
    cout<<linearSearch(nums4)<<endl;


    cout<<binarySearch(nums1)<<endl;
    cout<<binarySearch(nums2)<<endl;
    cout<<binarySearch(nums3)<<endl;
    cout<<binarySearch(nums4)<<endl;





    return 0;
}