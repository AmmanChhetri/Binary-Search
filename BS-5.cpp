

// Problem link - https://www.codingninjas.com/studio/problems/ceiling-in-a-sorted-array_1825401


#include <bits/stdc++.h>
using namespace std;




// Floor of a number simply means `a number that is just lesser` than the given number
int floor (int low, int high, vector<int> &arr, int n, int x) {

    int ans = -1;
    while(low <= high) {

        int mid = low + (high-low)/2;

        if(arr[mid] == x) {
            return arr[mid];
        }else if(arr[mid] < x) {
            // as arr[mid] < x ...so we can say it might be the answer...ie ..it might be just lesser than the given number in
            // sorted array...
            ans = arr[mid];
            low = mid + 1;
        }else{
            high = mid - 1;
        }
    }

    
    
    return ans;

}







// Ceil of a number simply means `a number that is just greater` than the given number
int ceil (int low, int high, vector<int> &arr, int n, int x) {

    int ans = -1;

    while(low <= high) {
        int mid = low + (high-low)/2;

        if(arr[mid] == x) {
            return arr[mid];
        }else if (arr[mid] > x) {
            ans = arr[mid];
            high = mid - 1;
        }else{
            low = mid + 1;
        }
    }


    return ans;
}







pair<int, int> getFloorAndCeil(vector<int> &arr, int n, int x) {
	sort(arr.begin(), arr.end());

	return {floor(0,n-1,arr,n,x),ceil(0,n-1,arr,n,x)};
	
}


int main() {

    vector<int> arr = {4,3,8,4,7,10};
    int n = arr.size();
    int x = 2;


    pair<int,int > ans = getFloorAndCeil(arr,n,x);

    cout<<"Floor of the given number "<< x << " is : " << ans.first<<endl;
    cout<<"Ceil of the given number "<< x << " is : " << ans.second<<endl;

    return 0;
}