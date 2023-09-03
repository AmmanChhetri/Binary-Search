

// Problem link - https://www.codingninjas.com/studio/problems/lower-bound_8165382


#include <bits/stdc++.h>
using namespace std;




int bruteForce(vector<int> &arr,int n,int x) {

    
    // initialising index with -1..
    int ans = -1;

    for(int i = 0;i<n;i++) {
        if(arr[i] >= x) {
            ans = i;
            break;
        }
    }
    
    
    // Now after searching whole array if your index is still 1 ...which implies we're not able to find the first element that
    // is greater than or equal to the given number x (which simply means all the elements of the array are leser than x)..
    // that's why we have to return n...otherwise if ans != -1 ...which means...the index has been foundd and we will return it.
    

    // we could also have initialised the ans with the size of the array(n)...in that case we can just return ans...if we didn't 
    // find any number in the arr ..greater than x...
    return (ans == -1) ? n : ans;
   

    // Time complexity is O(n)  ..... as we are searching the whole array
    // Space complexity is O(1) .... as we are not using any other data-structure
}











int lowerBound(int low,int high,vector<int> arr, int n, int x) {

    int ans = n;

    while(low <= high) {
        
        int mid = low + (high-low)/2;

        if(arr[mid] >= x) {
            // This can be my answer...therefore storing this index...
            ans = mid;
            // go left
            high = mid - 1;
        }else{
            // go right
            low = low + 1;
        }
    }

    return ans;

    // Time Complexity is O(logn)
    // Space Complexity is O(1)
	
}







int main() {

    vector<int> arr = {3,5,8,15,19};
    int n = arr.size();
    int x = 9;

    cout<<"The lower Bound of the element " << x << " in arr is at index using BruteForce: "<<bruteForce(arr,n,x)<<endl;
    cout<<"The lower Bound of the element " << x << " in arr is at index using BinarySearch: "<<lowerBound(0,n-1,arr,n,x);

    return 0;
}