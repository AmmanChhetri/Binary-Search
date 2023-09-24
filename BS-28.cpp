

// Problem Link - https://leetcode.com/problems/median-of-two-sorted-arrays/description/



#include <bits/stdc++.h>
using namespace std;



// BruteForce....
// Logic - as we have two sorted arrays given and we have to find the median of the merged array...we can simply merge this 
//         array and find the median....now merging of 2 sorted arrays into a larger array is simple and can be achieved using
//         2 pointer approach just like we used in `merge()` of `mergeSort` ...

double findMedianSortedArrays_BruteForce(vector<int> &nums1, vector<int> &nums2) {

    int m = nums1.size();
    int n = nums2.size();

    int len = m+n;   // merged array length...

    vector<int> merged;

    int i = 0;  // to track the index of nums1..
    int j = 0;  // to track the indec of nums2..

    while(i < m && j < n) {
        if(nums1[i] < nums2[j]) {
            merged.push_back(nums1[i]);
            i++;
        }else{
            merged.push_back(nums2[j]);
            j++;
        }
    }


    // after the above steps there will always be some portion of either nums1 or nums2 remaining...for that we need to deal
    // them seperately...
    
    while(i < m) {
        // still elements left in nums1....so we just need to add them directly in the merged array..as they are already sorted
        merged.push_back(nums1[i]);
        i++;
    }


    while(j < n) {
        merged.push_back(nums2[j]);
        j++;
    }


    
    if(len % 2 == 1) {
        // if length of the merged array is odd...then..median index will be len/2...
        return merged[len/2];
    }


    // else the len is even...we have two median indexes len/2 .... & ....(len/2)-1.....
    
    double average = (double)(merged[len/2] + merged[(len/2)-1])/2.0;

    return average;

    // Time Complexity is O(m+n) ...as we are traversing through both arrays...
    // Space Complexity is O(m+n) .... as we are using a merged array...
}











// Better Approach
// Intuition - From the BruteForce approach we observed that....we actually don't need to store the whole array right? ...
//             because we only need 2 or 1 index from the merged array....so we can optimize the space that is un-necessarily 
//             used by the merged array....

// Logic -  we know for merged array of odd length(len)...median element occurs at index len/2 ....similarly for merged array of
//          even length(len) median elements occurs at 2 indexes that are len/2 .... & ... (len/2)-1 ....also we know this
//          indexes beforehand itself...as we know the merged array length(length of both arrays..)...so we can calculate in
//          which index(s) ...this median occurs...and in place of storing... we can count the indexes in the merged array to 
//          check if hypothetically we had inserted the elements in which index it would have been...and if this index of 
//          merged array is equal to the index we are looking for ...then we got our answer...

double findMedianSortedArrays_Better(vector<int> &nums1,vector<int> &nums2) {
    
    int m = nums1.size();
    int n = nums2.size();

    int len = m+n;

    int ind2 = len/2;
    int ind1 = (len/2)-1;

    int elm1 = -1;
    int elm2 = -1;

    int i = 0;  // to track the elements of nums1
    int j = 0;  // to track the elements of nums2

    int cnt = 0;  // to track the elements in hypothetical merged array...

    
    // while we have something in both the arrays...between which we can compare...
    while(i < m && j < n) {

        if(nums1[i] < nums2[j]) {
            // wherever we are at in the merged array(cnt)...this nums1[i]...will be there ...
            if(cnt == ind1) elm1 = nums1[i];
            if(cnt == ind2) elm2 = nums1[i];
            cnt++;
            i++;
        }else{
            // this nums2[j] will be present in the cnt..
            if(cnt == ind1) elm1 = nums2[j];
            if(cnt == ind2) elm2 = nums2[j];
            cnt++;
            j++;
        }

    }


    while(i < m) {
        if(cnt == ind1) elm1 = nums1[i];
        if(cnt == ind2) elm2 = nums1[i];
        cnt++;
        i++;
    }

    while(j < n) {
        if(cnt == ind1) elm1 = nums2[j];
        if(cnt == ind2) elm2 = nums2[j];
        cnt++;
        j++;
    } 


    if(len % 2 == 1) {
        // median will be at ind2 ...meaning elm2...
        return elm2;
    }

    double average = (double)(elm1+elm2)/2.0;

    return average;
    
    // Time Complexity is O(m+n) ...as we are traversing through both arrays...
    // Space Complexity is O(1) .... as we are not using any extra space....
}













// Binary Search - (Symetry)....

// The whole case discuss below is for the array with `EVEN` length....for array with odd length...is very easy to implement
// once we understand for the even case....

// Observation  - suppose we have two arrays nums1 = {1,3,4,7,10,12} & nums2 = {2,3,6,15}...we know when we merge them we will
//                have final array as {1,2,3,3,4,6,7,10,12,15}...and we also know median of this merged array will lie in 
//                between element 4 and 6...so which means this median line will divide our array such that we have 5 elements
//                in the left of the median line and 5 to the right of median line... 1,2,3,3,4 | 6,7,10,12,15 ... if we see 
//                closely ...we observe to the left of median line we have 3 elements from nums1 & 2 from nums2....if we shift 
//                this median line either to the leftwards or rightwards ...we observe that the number of elements from each 
//                array(nums1 or nums2) in the left or right side will also change...suppose if we have divided our array like
//                {1,2,3,3 | 4,6,7,10,12,15} ...like this then in the left side....we have 2 elements from nums1 and 2 elements 
//                from nums2 ...similary we can observe different patterns(number of elements from each array...) if we move 
//                this dividing line right or left...so observe is for a median line there will be also some symetry of elements
//                and for a particular sorted array there will be one unique symetry only...now for the above example...
//                {1 2 2 3 4 | 6 7 10 12 15} ...we see we have 5 elements in the left portion and 5 in right (because number of 
//                elements is 10..)...now to have 5 elements in the left we can have different combinations like 
//                from nums1            from nums2         
//                    0                     5
//                    1                     4
//                    2                     3
//                    3                     2
//                    4                     1
//                    5                     0              

// now there can be one more bruteForce approach for this same logic of symetry....that is we try for each combination....ie..

// Combination - 1.....
// if we take 0 elements from nums1    &  then we need to take 5-0=5 elements from nums2 .....but this combination is not possible 
// as we don't have 5 elements in the nums2....

// Combination - 2.....
// if we take 1 elements from nums1    &  then we need to take 5-1=4 elements from nums2....because in left we have 5 elements..
//    nums1 -        1     | 3 4 7 10 12        
//    nums2 -    2 3 6 15  |                     
// .. if we sort the elements both side we observe   1 2 3 6 15 | 3 4 7 10 12...but is this the valid configuration? NO!!..why? 
// because we see 15 > 3 ...therefore it should should have been in the RHS but its in LHS therefore invalid configuration...                  

// Combination - 3......
// if we take 2 elements from nums1    &  then we need to take 5-2=3 elements from nums2....
//    nums1 -        1 3   |  4 7 10 12
//    nums2 -       2 3 6  |  15      
// .. if we sort the elements both side we observe   1 2 3 3 6 | 4 7 10 12 15...but is this the valid configuration? NO!!..why? 
// because we see 6 > 4 ...therefore it should should have been in the RHS but its in LHS therefore invalid configuration... 

// Combination - 4......
// if we take 3 elements from nums1    &  then we need to take 5-3=2 elements from nums2....
//    nums1 -       1 3 4  |  7 10 12
//    nums2 -        2 3   |  6 15      
// .. if we sort the elements both side we observe   1 2 3 3 4 | 6 7 10 12 15...but is this the valid configuration? YES!!..why? 
// because we see 4 < 6 ...therefore its a valid configuration.....

// Similarly if we check for combination 5 and combination 6 ....we will onbserve both will be invalid....as we said array after
// sorting will be unique right? ...its not like u will get different arrays each time u sort it... so which means we also have
// only one unique combination.....


// Now we saw which configuration is valid and which not....but how to actually check it....is the question....
// for understanding this let's see these 3 combinations...


// Combination - 3......
// if we take 2 elements from nums1    &  then we need to take 5-2=3 elements from nums2....
//    nums1 -         1 3   |  4 7 10 12
//    nums2 -       2 3 6   | 15      
// now to check if this is a valid symetry what we need to check is the highest elements from each array in LHS should be lesser
// than equal to the lowest element in the RHS diagonally!!...that is 3 should be < 15 ....and 6 should be < 4....but in this 
// case as 6 > 4....which means it is not symetric ...now why this works and why we are checking diagonally is ....if we see
// carefully we are just grouping what will be the first  half of the sorted array right? ....so we know the elements in the
// top row are from nums1 and elements on the bottom row is from nums2 ....and we know both the array are sorted...so can we say
// 3 < 4 for nums1 and 6 < 15 ....because they belong to the same array which is sorted ...now think logically if they would 
// have been sorted then the left portion of the array whould have been lesser than the right portion of the array ...or  we 
// can say the maximum element from the left portion should be lesser than the right portion...so we can easily tell 3<4..as
// they belong to the same array but ..we can't say this directly when we compare it with other array....that's why we are 
// comparing diagonally ...so that we confirm that elements in the left are all smaller than right...

// Combination - 4......
// if we take 3 elements from nums1    &  then we need to take 5-3=2 elements from nums2....
//    nums1 -       1 3 4  |  7 10 12
//    nums2 -         2 3  |  6 15      
// This is valid configuration because.... 4 < 6 and 3 < 7 .....so this our answer..

// Combination - 5......
// if we take 4 elements from nums1    &  then we need to take 5-4=1 elements from nums2....
//    nums1 -       1 3 4 7  |  10 12
//    nums2 -             2  |  3 6 15      
// This is not a valid symetry because 2 < 10 is true....but 7 < 3 is false....


// So basically we are applying our binarySearch in which our answer space will be how many elements we can pick from nums1..
// which means answer space [0,1,2,3,4,5,6]  ...


// so we observe ....
// for the number of elements from the nums1 we see ...the answer is possibile or not as the pattern...
//   0   1    2   3    4    5   6
//   🗴   🗴   🗴   ✓    🗴    🗴   🗴  ......
// So we don't see the normal pattern of BinarySearch on Answers...where we have something like  ✓✓✓✓✓🗴🗴🗴🗴🗴  ....where we 
// eliminated the wrong half....and search in the half where our answer is possible....

// So we need to find the condition which will allow us to move and search in the direction where our answer can be....for this 
// let's see below combinations...



// Combination - 3......
// if we take 2 elements from nums1    &  then we need to take 5-2=3 elements from nums2....
//    nums1 -         1 3   |  4 7 10 12
//    nums2 -       2 3 6   | 15 
// Here we observe 3 < 15 is true ..... but 6 < 4 is false...therefore ask yourself what you will do to make this condition true
// because we know we would have a valid symetry(array is sorted) ...when l1<l2 && r1 < r2 ....here l1 and l2 are 3 and 6
// respectively and r1 and r2 are 4 and 15 respectively....so to make the conditon 6<4 valid....we need some thing lesser than
// 6... in place of 6 ...so to do this we need to decrease the count of numbers from nums2 right...because we know to the left
// of 6 we have numbers that are lesser than 6...so we need to reduce the count of numbers from nums2...which...which...
// ultimately means we need to increase the count of numbers taken from nums1...as we need to maintain the count of 5(in this
// case) in the LHS...so which means if (l2 > r1) ..then ....low = mid+1.... right :)



// Combination - 5......
// if we take 4 elements from nums1    &  then we need to take 5-4=1 elements from nums2....
//    nums1 -       1 3 4 7  |  10 12
//    nums2 -             2  |  3 6 15      
// now we see 2 < 10 which is true...but 7 < 3 is false....so to fix this we need something lesser in place of 7...so to 
// achieve this we need to decrease the count of numbers from nums1....as numbers to the left of 7 will be lesser(sorted nums1)
// so which means we decrease the count of elements from the lHS ...so which means if(l1 > r2) ...then ..high = mid - 1  :)


// Combination - 4......
// if we take 3 elements from nums1    &  then we need to take 5-3=2 elements from nums2....
//    nums1 -       1 3 4  |  7 10 12
//    nums2 -         2 3  |  6 15      
// Here we observe 4 < 6 and 3 < 7 ...which means this is a valid configuration.....


// so we now have our answer space as well the condition to search left and right ....so we can solve binary Search easily now..
// But one last thing instead of appling BinarySearch on the nums1 with length 6 which will take O(log6) time...it is far better
// if we apply BinarySearch on nums2 ...with length 4 which will take O(log4) time...so we will apply binarySearch on the answer
// space of smaller array...




// Now after finding the correct sorted merged combination....how to find the median....?
// we now the correct combination is when we take 3 elements from nums1  &  5-3=2 elements from nums2.... 
//    nums1 -       1 3 4  |  7 10 12
//    nums2 -         2 3  |  6 15  
// and the sorted merged array is {1,2,3,3,4,6,7,10,12,15} ...we know median lies between 4 & 6...if we see the combination
// again when we sort the left half the maximum of 4 & 3 will lie just before the median line...similarly when we sort the right
// half the minimum of the 7 & 6 will come just after the median line....so can we say median for the array of even length is..
//  (max(l1,l2) + min(r1,r2)) / 2 ...



// For case when number of elements is `ODD` ----
// we can partition it from anywhere like these two....suppose nums1 = {2,4} and nums2 = {1,3,4} ...then there sorted merged
// array will be {1,2,3,4,4} ....so i can partition either like {1,2,3 | 4,4} or  {1,2 | 3,4,4} ....but i will be using the 
// first configuration where we always have 1 element greater in the left then the right ....
// suppose if n1 = nums1.size() & n2 = nums2.size() ...then length of merged array is n=n1+n2 ...so we use formula 
// (n+1)/2 ...that will determine the number of elements in the left....we could also have used...n/2 ..if we wanted more 
// elements on the Right side....

// and we observe when we have odd length merged array then....
//    nums1 -         2  |  4
//    nums2 -       1 3  |  4
// median is max(2,3) ie .... max(l1,l2)...as we have kept 1 extra element in the left half compared to right half...



// There can be cases like ...

//    nums1 -              1   |  3 4 7 10 12
//    nums2 -       2 3 6 15  |  
// In above we don't have r2 ...as ideally 1 < r2 .....so we initialize r2 with INT_MAX ...similarly we initialize r1 with 
// INT_MAX...

//    nums1 -  1 3 4 7 10 |  12
//    nums2 -             |  2 3 6 15 
// Here l2 is missing ...ideally l2<12.....so we initialize l2 with INT_MIN...similarly we initialize l1 with INT_MIN...



// ! what actually we are doing is we are finding the numbers that are just adjacent to the median line....which will be our 
// ! median ...so this whole logic is based on a very simple thing...as the merged array going to be sorted...so there will 
// ! always be a symetry...once i found a combination that will give me the sorted array...we can find the median...

// ! instead of drawing line in the median ...we can also draw line from anywhere in the merged array ....as the array will be 
// ! sorted ...we will find the combination which will give the sorted array ..and hence we can find the numbers just adjacent
// ! to the line u draw.... :)



double findMedianSortedArrays_BinarySearch(vector<int> &nums1, vector<int> &nums2) {

    int n1 = nums1.size();           // length of the first array
    int n2 = nums2.size();           // Length of the second array
    
    int n = n1+n2;                   // Merged array length
    
    int left = (n+1)/2;                // the number of elements in the left portion....
    

    if(n1 > n2) {
        // which means size of nums1 > size of nums2 ...so we again call the function to swap the vectors...because we want to
        // apply binarySearch on smaller array...
        return findMedianSortedArrays_BinarySearch(nums2,nums1);
    }


    int low = 0;                   // We can take 0 elements from this array
    int high = n1;                 // or we can take upto n1(size of smaller array) elements from this array....

    
    // applying binarySearch on how many elements to take from the smaller array(nums1) in the left partition....
    while(low <= high) {

        int mid1 = low + (high-low)/2;       // Here mid1 will be pointing to the first element in the right portion of nums1...
        int mid2 = left-mid1;                // Here mid2 will be pointing to the first element in the right portion of nums2...  
        

        int l1 = INT_MIN, l2 = INT_MIN;
        int r1 = INT_MAX, r2 = INT_MAX;

        if(mid1 < n1) r1 = nums1[mid1];
        if(mid2 < n2) r2 = nums2[mid2];
        if(mid1-1 >= 0) l1 = nums1[mid1-1];
        if(mid2-1 >= 0) l2 = nums2[mid2-1];


        if(l1 <= r2 && l2 <= r1) {
            // found the element...
            if(n % 2 == 1) {
                // if the elements are odd
                return max(l1,l2);
            }else{
                return  (max(l1,l2) + min(r1,r2))/(double) 2;
            }
        }else if(l1 > r2) {
            // decrease the count of elements from the nums1 in Left Side...
            high = mid1 - 1;
        }else{
            low = mid1 + 1;
        }
        

    }
    
    // dummy return...
    return -1;
    

    // Time Complexity is O(log(n1)) ...where n1 = size of smaller array...
    // Space Complexity is O(1)....


}




int main() {

    vector<int> nums1 = {1,2,6};
    vector<int> nums2 = {3,4};
    
    // here ensuring to only have two elements after decimal...
    cout<<fixed<<setprecision(2)<<findMedianSortedArrays_BruteForce(nums1,nums2)<<endl;
    cout<<fixed<<setprecision(2)<<findMedianSortedArrays_Better(nums1,nums2)<<endl;
    cout<<fixed<<setprecision(2)<<findMedianSortedArrays_BinarySearch(nums1,nums2)<<endl;
    

    return 0;
}