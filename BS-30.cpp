

// Problem Link - https://www.codingninjas.com/studio/problems/row-of-a-matrix-with-maximum-ones_982768



#include <bits/stdc++.h>
using namespace std;






// Brute Force 
// Logic - is simple we just traverse through each row of the matrix and for each row we count the number of ones...and if is 
//         greater than the max_count then we update it....at last print the row index with maximum number of ones..


int rowWithMax1s_BruteForce(vector<vector<int>> &matrix, int n, int m) {
    
    int max_count = 0;
    int ind = -1;

    for(int i = 0;i<n;i++) {
        int count = 0;
        for(int j = 0;j<m;j++) {
            count += matrix[i][j];
        }

        if(count > max_count) {    
            // This will also ensure if there are multiple rows with same number of maximum ones..to print the first occurence...
            max_count = count;
            ind = i;
        }

    }


    return ind;

    // Time Complexity is O(nm) .....
    // Space Complexity is O(1) ....
}



// Remember u can also break the inner loop if u find the index of first 1 in the row ...as the row is sorted...so after this
// 1 ..every other element is also 1...so we can just count the number of 1s using this index....





// Optimal - (Binary Search)....
// Intuition - ...we See as every row is sorted...we can find the first index where 1 has occured...and using this index we can
//             find the numer of 1s in that row....

int helper(vector<int> &arr, int m) {

    int ind = -1;

    int low = 0;
    int high = m-1;

    while(low <= high) {
        int mid = low + (high-low)/2;

        if(arr[mid] == 1) {
            ind = mid;     // This can be our answer....
            high = mid - 1;  // But as we are looking for first occurecnce we search more on the left...
        }else{
            low = mid + 1;
        }
    }

    if(ind == -1) return 0;       // means no 1 is there in the row...

    return m-ind;

}

int rowWithMax1s_BinarySearch(vector<vector<int>> &matrix, int n, int m) {


    int max_count = 0;
    int ind = -1;
    for(int i = 0;i<n;i++) {
        int count = helper(matrix[i],m);
        if(count > max_count) {
            max_count = count;
            ind = i;
        }
    }

    return ind;

    // Time Complexity is O(nlogm) ....
    // Space Complexity is O(1) ....
}




int main() {

    vector<vector<int>> matrix = {{0,0,0,0},
                                  {0,0,0,0},
                                  {0,0,0,0},
                                  {1,1,1,1},
                                  {0,1,1,1},
                                  {0,0,0,1} } ;
    
    int n = 6;
    int m = 4;

    cout<<rowWithMax1s_BruteForce(matrix,n,m)<<endl;
    cout<<rowWithMax1s_BinarySearch(matrix,n,m)<<endl;

    return 0;
}