

// Problem Link - https://leetcode.com/problems/find-a-peak-element-ii/description/



#include <bits/stdc++.h>
using namespace std;



// Brute Force
// Logic - a number in a cell is peak element ...if it is greater than it's adjacent elements...(ie. top,bottom,left,right)..
//         so basic approach is to traverse through each element and check it's adjacent elements...also as it is given that
//         the given matrix is surrounded by -1 on all it's sides...which means...we need to initialize the variable with -1 ..
//         to prevenent from runtime error(dure to indexing)....

vector<int> findPeakGrid_BruteForce(vector<vector<int>>& mat) {

    int n = mat.size();
    int m = mat[0].size();

    for(int i = 0;i<n;i++) {
        for(int j = 0;j<m;j++) {

            int left = (j-1 >= 0) ? mat[i][j-1] : -1;
            int right = (j+1 < m) ? mat[i][j-+1] : -1;
            int top = (i-1 >= 0) ? mat[i-1][j] : -1;
            int bottom = (i+1 < n) ? mat[i+1][j] : -1;

            if(mat[i][j] > left && mat[i][j] > right && mat[i][j] > top && mat[i][j] > bottom) {
                return {i,j};
            }
        }
    }
    
    // if element not found...
    return {-1,-1};

    // Time Complexity is O(4*m*n) ... as we are traversing n*m matrix..and at each steps we are checking in 4 directions..
    // Space Complexity is O(1) ...
}







// Better Solution ...
// There is a slight better solution from BruteForce approach,for this problem...if we see carefully we need to return the index
// of the element which is greater than all adjacent elements right? ....so think logically ...can't we return the index of the
// largest element of the matrix 🤐....we can !!...because as it is the largest so it will be definitely greater then adjacent
// elements...
vector<int> findPeakGrid_Better(vector<vector<int>>& mat) {

    int n = mat.size();
    int m = mat[0].size();

    int maxi = -1e9;
    int mx_i = - 1;
    int mx_j = - 1;

    for(int i = 0;i<n;i++) {
        for(int j = 0;j<m;j++) {

            if(mat[i][j] > maxi) {
                maxi = mat[i][j];
                mx_i = i;
                mx_j = j;
            }
        }
    }
    
    // if element not found...
    return {mx_i,mx_j}; 

    // Time Complexity is O(m*n) ...
    // Space Complexity is O(1)....

}








// Optimal - (Binary Search)...
// The intuition for this problem is combination of intuition of finding peak element in the 1D array and the intuition we used 
// in the `better-Approach` of the same problem....

// intuition of finding peak-element in the 1D array - suppose we are at a point i, if to the left of i we have lower elements
// (ie. nums[i-1] < nums[i]) ...then which means we need to move right..to go to the peak ....similarly if we have higher 
// elements to the left of i (ie nums[i-1] > nums[i]) ...which means to go the peak ...we need to go to left....that is towards
// higher element...(imagine the mountain ⛰️ for better understanding) ....

// intuition we used in the better-approach of the same problem ...the maximum element will always be the peak element in a 2D
// matrix ...because it will always be greater than it's adjacent elements....

// suppose we have....{{4,2,5,1,4,5},
//                    {2,9,3,2,3,2},
//                    {1,7,6,0,1,3},
//                    {3,6,2,3,7,2}} ....
// let's say we're applying binarySearch on the columns ...that is [0,m-1] ...initially our mid point is 2 ...so think logically
// in column 2..which element has the maximum probability of being the peak-element...ahm...ofCourse the lasrgest element..
// so in column 2 largest element is 6...now we check the left and right of 6 only...why left and right only ...becasue as it is
// the maximum element of the column we know the value above and below 6 will definitely lesser than this element 6....
// we check right of 6...we have 0 ...as 0<6 ...so it's correct....to the left of 6 we have 7 ...which means 7>6 ...which means
// 6 is not a peak element...now ask yourself...where will you move...left or right...if u compare this case with 1-D peak 
// problem we have to move left..wo we are at ist column now...again mid = 0 ...now which element in the 0th column has the max
// probability of being peak ...ahm 4(as it is highest in the column)...so if we check ...it is greater than it's right and left..
// so we say this is our peak element...

// ! Now why always we are looking for a max element in a column because it has the highest probability of being the peak...its
// ! not compulsary though that this will be definitely a peak...

// ! next why are we only checking left and right because ...we are at a max element of that row right? ...so we know above
// ! and below this max element...will have elements that will be lesser than max element...

// ! now how are we deciding where to move is ...simple..suppose we are a particular element ...say 6 for example which will be
// ! the max element of this column...so we know top and bottom elements of this 6 are lesser than 6...now lets say i assume the
// ! right element of 6 is also lesser than 6....but the left element is greater than 6....from this point 6...we can move either
// ! left or right...but we will  move to the direction that has larger element than the one we are standing...its because
// ! say we have 7 to the left of 6 ...so if we move to the column of 7 ...and say 7 is the maximum element of this column...so
// ! again it is sure that 7 is larger than its top and bottom element...now this 7 will also be greater than its right element
// ! which is 6 ...so u see how are search has been reduced now.. 
// ! Now u may ask ..what if the 7 is the not the maximum element of that column...suppose in that column we have a number 9 as
// ! well so we now max is 9...so tell logically do we need to check the right now again? ...no because we moved to this column
// ! because 7>6 ...and 6 was the maximum element of his column...so 9>7...which means 9>6...right? ...which means to the right
// ! of 9...whichever element is present it will be also less than 9...because to the right of 9 we have the column which has 
// ! maximum as 6...so it's obvious 9>element to it's right...so this is how we are searching....by reducing space..

// When we moved to 7 from 6 ...as 7>6..then we can say 7 is greater than every element of the column having this 6..which 
// ultimately means 9 > all elements of the column having this 6...so this is how we are reducing our search space...now this 9
// is greater than its right element...so we just need to check for the left now...and even if we dont have anything in the left
// we need to consider we have -1..so which means this method always work....

int findMax(vector<vector<int>>& mat, int mid, int n) {
    
    int j;
    int maxi = INT_MIN;
    for(int i = 0;i<n;i++) {
        if(mat[i][mid] > maxi) {
            maxi = mat[i][mid];
            j = i;
        }
    }

    return j;
}


vector<int> findPeakGrid_Optimal(vector<vector<int>>& mat) {
    int n = mat.size();
    int m = mat[0].size();

    int low = 0;
    int high = m-1;

    while(low <= high) {
        int mid = low + (high-low)/2;

        int row = findMax(mat,mid,n);
        int left = (mid-1 >= 0) ? mat[row][mid-1] : -1;
        int right = (mid+1 < m) ? mat[row][mid+1] : -1;

        if(mat[row][mid] > mat[row][mid-1] && mat[row][mid] > mat[row][mid+1]) {
            return {row,mid};
        }else if(mat[row][mid] < left) {
            high  = mid - 1;
        }else{
            low = mid + 1;
        }
    }

    return {-1,-1};

    // Time complexity is O(logm)*O(n) ....O(n) for finding maximum in each column...and O(logm) ...because we are doing Binary
    //                 Search on Columns...
    // Space complexity is O(1)...
}





int main() {

    vector<vector<int>> mat = {{10,20,15},{21,30,14},{7,16,32}};

    vector<int> ans1 = findPeakGrid_BruteForce(mat);
    vector<int> ans2 = findPeakGrid_Better(mat);
    vector<int> ans3 = findPeakGrid_Optimal(mat);
    
    cout<<"Row is : "<<ans1[0]<<endl;
    cout<<"Column is : "<<ans1[1]<<endl;

    cout<<"Row is : "<<ans2[0]<<endl;
    cout<<"Column is : "<<ans2[1]<<endl;

    cout<<"Row is : "<<ans3[0]<<endl;
    cout<<"Column is : "<<ans3[1]<<endl;

    return 0;
}