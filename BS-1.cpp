

// Problem link - https://leetcode.com/problems/binary-search/description/


#include <bits/stdc++.h>
using namespace std;


int iterativeBS(int low, int high, vector<int> &arr, int n, int x) {

    
    int ans = -1;

    while(low <= high) {
        
        // Here we can also take mid as (low+high)/2 .... but in some int cases it will cause overflow...suppose we have numbers
        // from 0 to INT_MAX....and now our both high and low pointer is at INT_MAX...now if we do (low+high)/2 .... ie. 
        // (INT_MAX + INT_MAX)/2 ...it will cause integer overflow....one way to solve it is by using 'long long' other way is 
        // to change mid to low+(high-low)/2
        int mid = low + (high-low)/2;

        if(arr[mid] == x) {
            ans =  mid;
            break;
        }else if(arr[mid] > x) {
            // move left
            high = mid - 1;
        }else{
            // move right
            low = mid + 1;
        }
    }

    return ans;

}


int recursiveBS(int low, int high, vector<int> &arr, int n, int x) {
    
    // Base case
    if(low > high) {
        // element is not present
        return -1;
    }


    int mid = low + (high-low)/2;
    if(arr[mid] == x) {
        return mid;
    }else if(arr[mid] > x) {
        // move left
        return recursiveBS(low,mid-1,arr,n,x);
    }

    
    // This will execute when arr[mid] < x...
    return recursiveBS(mid+1,high,arr,n,x);

}



int main() {
    
    vector<int> arr = {-1,0,3,5,9,12};
    int n = arr.size();
    int x = 9;
    int ans1 = iterativeBS(0,n-1,arr,n,x);
    int ans2 = recursiveBS(0,n-1,arr,n,x);

    
    if(ans1 == -1) {
        cout<<"Using IterativeBS ...Given element "<<x<<" is not present in the arr"<<endl;
    }else{
        cout<<"Using IterativeBS ...Given Element " << x << " found at index " << ans1 <<endl;
    }


    if(ans2 == -1) {
        cout<<"Using recursiveBs ...Given element "<<x<<" is not present in the arr"<<endl;
    }else{
        cout<<"Using recursiveBS ...Given Element " << x << " found at index " << ans2 <<endl;
    }
    
    

    return 0;
}