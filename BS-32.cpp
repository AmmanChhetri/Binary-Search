

// Problem Link - https://leetcode.com/problems/search-a-2d-matrix-ii/description/



#include <bits/stdc++.h>
using namespace std;


// BruteForce
bool searchMatrix_Brute(vector<vector<int>>& matrix, int target) {

    for(int i = 0;i<matrix.size();i++) {   
        for(int j = 0;j<matrix[i].size();j++) {
            if(matrix[i][j] == target) {
                return true;
            }
        }
    }

    return false;

    // Time Complexity is O(n*m) ....
    // Spaace Complexit is O(1) ....
        
}







// Better Approach -
// As we know each row is sorted too...so inistead of just going column by column we use binarySearch to search if the element 
// is present or not....
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


bool searchMatrix_Better(vector<vector<int>>& matrix, int target) {
        
    int n = matrix.size();
    int m = matrix[0].size();

    for(int i = 0;i<matrix.size();i++) {
        bool ans = bs(matrix[i],target);
        if(ans) return true;
    }

    return false;

    // Time Complexity is O(n*log(m)) ...
    // Space Complexity is O(1) ...
        
}






// Optimal Search (binarySearch) - 
// Here the method  we are using is not related to the normal binarySearch but it this method is kinda binarySearch as we are
// eliminating the halfs...where answer is not possible ....

// Observation - consider the matrix...defined in the main() ....suppose we are standing at index [0,0] ..and someone says  to
//               find element 8 ..can we confirmly say if it lies on the 0th row(1,4,7,11,15) or 0th column(1,2,3,10,18)...no
//               right? because both rows and colum are increasing and our answer can be either in this row or column...similarly
//               for when we are standing at [m-1,m-1] ...where m = number of rows....we can't correctly determine in which
//               direction to find target....but if we stand at the index say [0,m-1] or [n-1,0] ...we see..on one side the 
//               element is decreasing and in the other side the element is increasing....so we can predict where our answer may
//               be..lets consider that we are standing at [0,m-1] in the beginning...so we are movnig  either left or down...so
//               we might cross the boundary in the left or down....so we search within the matrix only ...


//  ! if we stand at any cell in the matrix...if we see the entire row(from 0th column to the cell we are in) and 
//  ! column (from the cell to n-1 th row ) we observe this will always be an sorted 1D array,so this is the `intuition` behind 
//  ! our logic...
// example - for the same matrix given in the example....suppose we are at cell [1,3] (ie. element 12)...so if we check the 
//           elements...   1 5 8 12
//                               16
//                               14
//                               23   .... are sorted...similarly we see for any cell....
// 
bool searchMatrix_Binary(vector<vector<int>>& matrix, int target) {


    int n = matrix.size();
    int m = matrix[0].size();

    int row = 0;
    int col = m-1;

    while(row < n && col>=0) {
        
        if(matrix[row][col] == target) return true;
        else if(matrix[row][col] < target) row++;    // because the numbers are increasing downwards...
        else col--;                                  // because the numbers are decreasing as we go left....
    }


    return false;

    // Time Complexity is O(n+m) .... we are at [0,m-1] ...and at worst we need to reach [n-1,0] while searching....so as we
    //                 are only moving left and downwards....so at worst we need to travel the whole array in row
    //                 similarly for col .....like the path .... {{1,4,7,11,15},
   //                                                           {2,5,8,12,19},
   //                                                           {3,6,9,16,22},
   //                                                           {10,13,14,17,24},
   //                                                           {18,21,23,26,30}}; 
   //   for worst case there can be many cases like we can travel like suppose we are looking for 18 ..so our travel path is 
   //   {15,19,12,16,17,26,23,21,18} ...we are moving downwards in 4 steps {ie. 15->19 , 12->16, 16->17, 17->26} ..and we are
   //   moving left in 4 steps {ie. 19->12, 26->23, 23->21, 21->18} ...so total of 8 steps(m+n) ...there might be more cases 
   //   like we are travelling down,down,down,.... then left,left,left....till we reach [n-1,0] from [0,m-1]...or 
   //   left,left,left.... then down,down,down....till we reach [n-1,0] from [0,m-1] .... 
   


}



int main() {

    vector<vector<int>> matrix = {{1,4,7,11,15},
                                  {2,5,8,12,19},
                                  {3,6,9,16,22},
                                  {10,13,14,17,24},
                                  {18,21,23,26,30}};
    int target1 = 5;
    int target2 = 20;

    cout<<searchMatrix_Brute(matrix,target1)<<endl;
    cout<<searchMatrix_Brute(matrix,target2)<<endl;

    cout<<searchMatrix_Better(matrix,target1)<<endl;
    cout<<searchMatrix_Better(matrix,target2)<<endl;

    cout<<searchMatrix_Binary(matrix,target1)<<endl;
    cout<<searchMatrix_Binary(matrix,target2)<<endl;

    return 0;
}