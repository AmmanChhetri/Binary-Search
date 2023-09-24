

// Problem Link - https://leetcode.com/problems/search-a-2d-matrix/description/



#include <bits/stdc++.h>
using namespace std;



// Brute Force

bool searchMatrix_BruteForce(vector<vector<int>>& matrix, int target)  {


    int n = matrix.size();
    int m = matrix[0].size();

    for(int i = 0;i<n;i++) {
        for(int j = 0;j<m;j++) {
            if(matrix[i][j] == target) {
                return true;
            } 
            
        }
    }


    return false;
    // Time complexity is O(n*m) ....as we are traversing through every element..
    // Space complexity is O(1) .... as we are not using extra space ..

    // ! We can improve this much better if we add one more if condition after the 1st if condition inside the inner for loop...
    // if(matrix[i][j] > target) return false; 
    // because it is given the first element is greater than the last element of the previous row...so we can say not only row
    // is sorted...but column is sorted too...so can we say the moment our matrix[i][j] exceeds the target...there is no way 
    // we will find it after this... :) ...so we can say matrix is entirely sorted....

    // Here we will can use this extra condition because it is given that first element of each row is greater than the last
    // element from the previous row....so once we reach some value > target....then we won't have target present afterwards..
    // this index...

    //  we can't apply this extra if condition logic in matrix like ... {{1,4,7,11,15},
    //                                                                   {2,5,8,12,19},
    //                                                                   {3,6,9,16,22},
    //                                                                   {10,13,14,17,24},
    //                                                                   {18,21,23,26,30} }

    // Here the matrix is sorted row wise and column wise but the first element of each row is lesser than the last element of 
    // previous row... that's why we can't use that extra if condition here...because say we have target = 16...we search linaerly
    // we get into element 19 > 16 ..so we can't break it yet...because next row may contain 16...as next row will start by some
    // number <  19 ...so there might be possiblity of finding 16.... :)  so we can say matrix is not entirely sorted....
}






// Better Solution 
// Logic - As the array is sorted...so we don't need to check for every row...we know the first and last element of every row
//         so we can only search in the row where our number will lie....and that will be only one row ...if possible....
//         if we get a row we apply binarySearch to search the element as the array is sorted....
bool bs(vector<int> &arr, int target) {

    int low = 0;
    int high = arr.size()-1;

    while(low <= high)  {
        int mid = low +(high-low)/2;

        if(arr[mid] == target) {
            return true;
        }else if (arr[mid] > target) {
            high = mid  - 1;
        }else{
            low = mid + 1;
        }
    }


    return false;

}



bool searchMatrix_BetterSolution(vector<vector<int>>& matrix, int target) {

    int n = matrix.size();
    int m = matrix[0].size();

    for(int i = 0;i<n;i++) {
        
        if(target >= matrix[i][0] && target <= matrix[i][m-1]) {
            return bs(matrix[i],target);
        }
    }

    return false;
    // Time complexity is O(n) + O(logm)   .... O(n) for traversing ...andO(logm) for binarySearch....here we are only applying
    //                  binarySearch in 1 row....that's why only one time is counted for binarySearch in TimeComplexity ...

    // Space Complexity is O(1) ...
}









// Optimal Solution - Binary Search...
// Intuition - we need to search in a 2D matrix...the 2d matrix is sorted both column and row wise....what we observe in a 2D 
//             matrix is for any element at index say [i,j] ...the elements to the left of it in the same column and the all 
//             the elements above it is always lesser than this element...similarly all elements to the right and all the
//             elements to the down rows of [i,j] will be greater than the element at [i,j] ....so we see some kind of pattern
//             similar to BinarySearch here...but we only applied binarySearch in the 1D array till now...so if we convert this
//             2D matrix into a 1D array ...we observe the 1D array is also sorted....say example ..... let target = 18..
//             matrix = {{3,4,6,8},{10,12,13,15},{17,18,19,20}} ....if we flatten it into 1D array we observe ...
//             array = {3,4,6,8,10,12,13,15,17,18,19,20} ......we know in this 1D array if we apply BinarySearch then low=0 & 
//             high = 11 ....so for the first time mid will be 5 ...so at index 5 we have..12 ...so we see 12 < 18 ...so we move
//             right(low = mid + 1) ..but how do we apply this into 2D matrix..only if we are able to convert this 1D index into
//             2D index...our job would have been done..so can we convert this 1D index into 2D index ? ... Answer is YES!!!

// Logic -  suppose we are at index 5 right now,to convert it into 2D index we can do it like this ..here m = number of columns
//          row = 5/m   & col =  5%m ....now why this will work let see ....we observed every m-elements the row will change ..
//          so can we say to check how many rows have been passed till now we do 5/m ...now here m = 4 ...which means row=1 ...
//          remember it's a 0 based indexing....similarly ..when we are at particular row ....to check in which colum we are 
//          we just need to do 5%m ...because it's repeating after every m times....
                     
int searchMatrix_BinarySearch(vector<vector<int>>& matrix, int target) {
    
    int n = matrix.size();
    int m = matrix[0].size();

    int low = 0;
    int high = n*m - 1;

    while(low <= high) {
        int mid = low + (high-low)/2;

        int row = mid/m;
        int col = mid % m;

        if(matrix[row][col] == target) return true;
        else if (matrix[row][col] < target) low = mid + 1;
        else high = mid - 1;

    }

    return false;

    // Time Complexity is O(log(n*m)) ...
    // Space Complexity is O(1) ...


}





int main() {

    vector<vector<int>> matrix = {{1,3,5,7},{10,11,16,20},{23,30,34,60}};
    int target1 = 13;
    int target2 = 34;

    cout<<searchMatrix_BruteForce(matrix,target1)<<endl;
    cout<<searchMatrix_BruteForce(matrix,target2)<<endl;
    
    cout<<searchMatrix_BetterSolution(matrix,target1)<<endl;
    cout<<searchMatrix_BetterSolution(matrix,target2)<<endl;

    cout<<searchMatrix_BinarySearch(matrix,target1)<<endl;
    cout<<searchMatrix_BinarySearch(matrix,target2)<<endl;



    return 0;
}