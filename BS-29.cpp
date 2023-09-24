

// Problem Link - https://www.codingninjas.com/studio/problems/k-th-element-of-2-sorted-array_1164159



#include <bits/stdc++.h>
using namespace std;




// Brute Force approach - 
// Logic - using a pointer to check whether we have reached the kth element or not...then printing the respective element at 
//         kth position....

int kthElement_BruteForce(vector<int> &nums1, vector<int> &nums2, int n, int m, int k) {

    int i = 0;     // to keep track of the index in nums1 array
    int j = 0;     // to keep track of the index in nums2 array
    int cnt = 0;  // to keep track of the index we are in the merged array....

    while(i < n && j < m) {
        if(nums1[i] < nums2[j]) {
            if(cnt == k-1) return nums1[i];
            cnt++;
            i++;
        }else{
            if(cnt == k-1) return nums2[j];
            cnt++;
            j++;
        }
    }
    

    // Now there might be case when we still didn't reached the kth element (ie. index = k-1)  ...and one of the array has 
    // been exhausted...
    while(i < n) {
        if(cnt == k-1) return nums1[i];
        cnt++;
        i++;
    }

    while(j < m) {
        if(cnt == k-1) return nums2[j];
        cnt++;
        j++;

    }

    // Dummy return...
    return -1;

    // Time Complexity is O(k) ... ...because we are only traversing till k ...after we are just returning the value..
    // Space Complexity is O(1) ...as we are not using any extra space...
}








// ! Here ....we used the same logic of BinarySearch as in the previous question ...but here instead of drawing the line from 
// ! the median ... here we draw a line such that left part contains k elements...so if we are able to find a combination
// ! across the partition( in which left partition has k elements) ..that will give us the sorted array then we can find the 
// ! adjacent elements from this line...also what we observe is if we are keeping k-elements in the left portion then the 
// ! max(l1,l2) will always be our answer.... :)


// But we need to do a slight change here in the pointers that is low & high....what we are given in the question is to find the
// kth element in the sorted array...which means we are keeping k -elements in the left...so we know we are applying 
// binarySearch on jow many elements to take from the smaller array....so high represents the maximum number of elements we can
// pick...but lets say nums1.size() = 5 ....and we want k=2 elements....so do we need to check by placing 3,4 or 5 elements in 
// the left...no right? ....so we only need to check till min(nums1.size(),k) ....now why min(nums1.size(),k) ....because 
// suppose we have nums1.size()=5 and nums2.size()=6 ...and k = 10 ...then we need to check for all the elements of the nums1
// right ? otherwise we won't be able to get 10th element.. similarly we need to change the low pointer as well....
// what low indicates is the minimum number of elements to pick from the smaller array...that's why it is starting from 0...now
// it will work fine in cases like say k = 2 ...then we can have low as 0....because then we have combination like ...left=2 &
// right=9...where in left we have number of elements as nums1=0 and nums2 = 2....now suppose we have case where k=7...now 
// to make this can we take low=0 ...no because if we take low=0...because the maximum length of nums2 is itself 6 ..so even if
// we pick all elements from nums2 we still won't be able to make the desired combination...so we need at least 1 right ...
// from nums1 ...which means we need.... `low = max(0,7-6)` ...which means max(0,k-n2)...where n2=nums2.size()..... :) 

// Keeping in mind this conditions everything will be fine....



// ! Again repeating the same thing as it is very-very important !!! ...we have two sorted arrays given and we need to find the
// ! kth element when we sort them..now imagine u have merged the two sorted arrays into a combined sorted array....then 
// ! if u draw a partition line between any two elements of the merged sorted array ...we know the left part will be sorted as
// ! well as right part will be sorted too right ? ...and wherever we do partition  we know how many elements are in the left 
// ! partition and how many in the right partition are there...so can we say as the given two arrays are also sorted...so we
// ! can pick the elements in such way that we have required number of elements in the left...ans we check that if this 
// ! combination is valid...and if it is valid ..then we can find the elements just adjacent to the line where we divided..^_^
int kthElement_BinarySearch(vector<int> &nums1, vector<int> &nums2, int n, int m, int k) {
    // here n = size of smaller array...

    if(n > m) return kthElement_BinarySearch(nums2,nums1,m,n,k);

    int left = k;

    int low = max(0,k-m);    
    int high = min(n,k);

    while(low <= high) {
        int mid1 = low+(high-low)/2;
        int mid2 = left-mid1;

        int l1 = INT_MIN, l2 = INT_MIN;
        int r1 = INT_MAX, r2 = INT_MAX;

        if(mid1 < n) r1 = nums1[mid1];
        if(mid1 < m) r2 = nums2[mid2];
        if(mid1-1 >= 0) l1 = nums1[mid1-1];
        if(mid2-1 >= 0) l2 = nums2[mid2-1];

        if(l1 <= r2 && l2 <= r1) {
            // this is the answer...which means...this combination gave us the sorted array..so now our answer is 
            return max(l1,l2);
        }else if(l1 > r2) {
            high = mid1 - 1;
        }else{
            low = mid1 + 1;
        }
    }


    return -1;
    //dummy return

    // Time Complexity is O(log(n)) ...n = size of smaller array...
    // Space Complexity is O(1)... 
}




int main() {

    vector<int> nums1 = {1, 2, 3, 5, 6};
    vector<int> nums2 = {4, 7, 8, 9, 100};
    int n = nums1.size();
    int m = nums2.size();
    int k1 = 5;
    int k2 = 10;
    
    

    cout<<kthElement_BruteForce(nums1,nums2,n,m,k1)<<endl;

    

    // " Having fun with printing 😅 "
    
    cout<< k2;
    if(k2 % 1 == 1){
        // Here modulo because we can have k like 21 or 31 ...similarly for others conditions we can have k like 42 or 73..etc..
        cout<<"st";
    }else if(k2 % 2 == 2){
        cout<<"nd";
    } else if(k2 % 3 == 3) {
        cout<<"rd";
    }else {
        cout<<"th";
    }
    
    
    cout<<" Element from the merged sorted array is : "<<kthElement_BinarySearch(nums1,nums2,n,m,k2)<<endl;

    return 0;
}