

// Problem link - https://www.codingninjas.com/studio/problems/implement-upper-bound_8165383

#include <bits/stdc++.h>
using namespace std;

int upperBound(int low, int high, vector<int> &arr, int n, int x) {

    int ans = n;
    while(low <= high) {
        int mid = low + (high-low)/2;

        if(arr[mid] > x) {
            // This can be our answer...
            ans = mid;
            
            // move left
            high = mid - 1;
        }else{
            // move right
            low = mid + 1;
        }

    }

    return ans;

}

int main() {
    
    vector<int> arr = {2,4,6,7};
    int n = arr.size();
    int x = 5;

    cout<<"The Upper Bound of the element " << x << " in arr is at index using BinarySearch: "<<upperBound(0,n-1,arr,n,x);

    return 0;
}