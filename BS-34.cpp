

// Problem Link - https://www.codingninjas.com/studio/problems/median-of-a-row-wise-sorted-matrix_1115473



#include <bits/stdc++.h>
using namespace std;


// Brute Force
// Logic - Extreme naive solution is to go through each element...and then put them into a 1-D array...after that sort it..and 
//         get the middle element...
int median_Brute(vector<vector<int>> &matrix, int m, int n) {
    // m = number of rows..
    // n = number of columns..

    

    vector<int> nums;
    for(int i = 0;i<m;i++) {
        for(int j = 0;j<n;j++) {
            nums.push_back(matrix[i][j]);
        }
    }

    sort(nums.begin(),nums.end());
    // number og elements in the nums array will be m*n ....which will be odd as `m` and `n` both are odd...so our median is at
    // (m*n)/2 ...
    
    int k = m*n;
    return nums[k/2];

    // Time complexity is O(mn) + O(klogk) ....O(mn) for traversing the array....O(klogk) for sorting the 1-D array...
    // Space Complexity is O(k)......
}







// Optimal - (BinarySearch) ....
// suppose we have... matrix = {{1,5,7,9,11},
//                              {2,3,4,5,10},
//                              {9,10,12,14,16}} 

// as we need to find the median...and the matrix is just row-sorted...so let's see this numbers in a 1-D plane ...
//  1 2 3 4 5 5 7 `9` 9 10 10 11 12 14 16 .... now we know the number of elements in the matrix is ...15..so median is at index 7
// that is element 9(the first occurence of 9) ..we know to the left of median we have 7 elements ..and to the right of median
// we have 7 elements....now if we look closely ...as only row is sorted....so there is no way to traverse matrix and reach 
// median ....so we need to think in a different way...we know for this example we have 7 elements to the left of median and 7
// to the right of median...so can we say we just need to find the number(median) which has 7 elements to it's left ...or 
// to be precise....the first element who has 7 numbers lesser than it...if we see the first 9 ...is the first element who has 
// 7 numbers lesser to it...so it's the median....
// Now the logic is simple ...1 2 3 4 5 5 7 `9` 9 10 10 11 12 14 16  ...we know 9 is the median...and we have 7 numbers lesser than
// 9 to the left of median...and if i include this 9....then can i say i have 9 elements(1 2 3 4 5 5 7 9 9) <= 9....similarly if
// we would have 1 2 3 4 5 5 7 `9` 10 10 10 11 12 14 16  ...we can see the number of elements lesser than equal to 9 is 8...
// similarly if we consider 1 2 3 4 5 5 7 `7` 9 10 10 11 12 14 16 ....now in this case 7 would have been my median...and number
// of elements lesser than equal to 7 are...8...similarly if we have 1 2 3 4 5 5 7 `7` 7 7 7 11 12 14 16  ....our median is 7 ...
// and number of elements lesser than equal to 7 is ...11...so what we are observing is..  `the number of elements <= median` is
// greater than 7....
// lets again consider array as ... 1 2 3 4 5 5 7 `9` 9 10 10 11 12 14 16 
// Now why this logic is working is because...we know for sure to the left of median we have exactly 7 elements right? ..so if i
// include this median element in our count ...can we say the count is now 7+1=8 ......so can we say the first element ..who has
// 8 elements lesser than or equal to it ...will be our median ....NO!!! ...what if array is something like 
// 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 ...   it wont work ..as we only have element 7 in the array...whose count is too > 8...
// so i need to alter the logic a bit....instead of finding the first element who has 8 numbers lesser or equal to it....can we 
// say our answer is the first element who has elements that are lesser or equal to this median element as > 7....
// also think in this way ...if we count the  number of elements that are lesser than or equal to n/2 ....then the first 
// number which gives count > n/2 ...is the answer...because if we have a array..count>n/2 means..it occupying more than half
// portion which means...it is the median element...

// also our anwer will lie between the smallest element and the largest element of the matrix only ...wo we can use binary
// search on answers...

// now also to count the number of elements that are lesser than or equal to this element can be easily done using the binary
// search on the rows....sa the rows are sorted...


// now we are a particular element who has 5 as the count of  numbers lesser or equal to this number...than as wee >7 ...so we
// need towards right...
int upperBound(vector<int> &arr, int x, int n) {

    int low = 0;
    int high = n-1;
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

int count(vector<vector<int>> &matrix, int n, int m, int mid) {
    
    int count = 0;

    // We know we have upperBound function which will point to the first element that is greater than the passed number...
    for(int i = 0;i<n;i++) {
        count += upperBound(matrix[i],mid,m);
    }

    
    return count;
    // Time Complexity is O(nlogm) ...
    
    
}


int median_Optimal(vector<vector<int>> &matrix, int m, int n) {

    n = matrix.size();
    m = matrix[0].size();


    int low = INT_MAX;;
    int high = INT_MIN;
    
    // we are only checking in the first column ...because as the rows are sorted..which means the minimum element will always
    // be at 0th column...but as the column is not sorted...it can be anywhere in 0th column....
    for(int i = 0;i<n;i++) {
        low = min(low,matrix[i][0]);
        high = max(high,matrix[i][n-1]);
    }  
    
    
    

    int req = m*n/2;
    int ans;

    while(low <= high) {
        int mid = low + (high-low)/2;

        int smallerEquals = count(matrix,n,m,mid);

        if(smallerEquals <= req) {
            low = mid + 1;
        }else{
            ans = mid;
            high = mid - 1;
        }
    }


    return ans;
    // Time complexity is O(log(1e9))*O(nlogm) ...as we have 1<= mat[i][j] <= 1e9 ....at worst we can have minm = 1 & maxm = 1e9
    // as we are using the count function for almost every value ...
    
    // Space complexity is O(1)...
}





int main() {

    vector<vector<int>> matrix1 = {{1,5,7,9,11},
                                  {2,3,4,8,9},
                                  {4,11,14,19,20},
                                  {6,10,22,99,100},
                                  {7,15,17,24,28}};


    vector<vector<int>> matrix2 = {{1,2,3,4,5},
                                   {8,9,11,12,13},
                                   {21,23,25,27,29}};

    int m1 = matrix1.size();
    int n1 = matrix1[0].size();

    int m2 = matrix2.size();
    int n2 = matrix2[0].size();


    cout<<median_Brute(matrix1,m1,n1)<<endl;
    cout<<median_Brute(matrix2,m2,n2)<<endl;

    
    cout<<median_Optimal(matrix1,m1,n1)<<endl;
    cout<<median_Optimal(matrix2,m2,n2)<<endl;

    return 0;

}