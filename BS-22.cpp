

// Problem link - https://leetcode.com/problems/kth-missing-positive-number/

#include <bits/stdc++.h>
using namespace std;




// Appraoch 1 ...LinearSearch (brute Force)...
// Logic - Here we are using a simple math logic....suppose if we say we have numbers from 1 to ∞ ....and we have to choose 
//         number 5....so we just count 1,2,3,4,5 ...so 5 is ur answer....now suppose we add some constraints here like...say 
//         normally it should be 5..but let say condition is u cant pick number 2...now say what is the 5th number....so we say
//         5th number is 6...why because to choose 5 without constraints...we have crossed(in simple terms we considered 2 as 
//         well as 2 < 5)....but as we can't pick 2 ...our answer will shift by +1...therefore our answer is 6...now suppose i say
//         we cant pick 3 too...so now our answer wil be 6+1 = 7...because as 3 < 6...so to reach 6 we have picked 3 as well...
//         so if we can't pick 3..which means our answer shift by 1....now similary if i say we cant pick 4 too so our answer 
//         is 8 (because 4 < 7)..now if i say we cant pick 7 so our answer is 9(7 < 8) ...now now...if i say we can't pick 11..
//         so now our answer still remains 9...because...11>9 ..so this constraint doesn't affects our answer...now same thing 
//         is given in the words of array...in the problem ...where k refers to the anwer that normally should have been...and 
//         array acts as constraints....dry run this example and you will understand much better...arr = [2,3,4,7,11] , k=5...

//         Here also we are able to use this logic...because our arr is sorted as given in the problem...

//         Now suppose our array is [5,6] and k = 2 ...so can we say our 2nd missing number is 2 directly ...because k < arr[0]
//         ...so for rest of the array elements k would be lesser them as well.....so this thing also gave us an idea when to 
//         return k...that's why the moment our arr[i] > k ...we return k

int linearSearch(vector<int> &arr, int k) {
    
    for(int i = 0;i<arr.size();i++) {
        if(arr[i] < k) {
            k++;
        }else{
            break;
        }
    }

    return k;
    // Time complexity is O(n) ...that is worst case...
}




// Approach 2 - Binary Search ...

// Intuition - Now if the interviewer says to improve this logic or rather timecomplexity ...and we observe the array is
//             sorted...so all this observations (sorted,better than O(n))...will hint us to think for binary Search....

// Logic - Now we can't apply normal binary search here because the we are searching for a `missing number`...which is not in 
//         our sorted array(arr)... also we cant apply the binary search in answers even if we able to find a range...because
//         in binary search as we know....we reduce the search space by elimating the portion where we know our answer is not 
//         there....but here we are not eliminating anything...suppose ur at some point `mid`...now you dont have any options
//         to do with it....even i say u check if this number `mid` is present in the array or not....so what u will do..how u 
//         eliminate the search space...so we can't apply binary search on answers...now we have to think some logic ...in 
//         which can eliminate the search space...lets see the arr={2,3,4,7,11} and k = 5...we know for sure our 5th missing 
//         number will be between 7 and 11...but why are we so sure...why it wint lie before or after this indexex ? ...if we 
//         observe carefully ..our problem is revolving around missing numbers...
//         so if somehow i can say where my kth missing number lies i can solve this problem....now suppose our array is -
//         arr = {2,3,4,7,11} ...now we know normally in place of 2 ...it should have been 1...but as there is 2 => number of 
//         numbers misssing till index 0 is 2-1 = 1....similary for index 1...it should have 2 ...but as there is 3..which 
//         means...number of numbers missing till index 1 is 3-2=1...simlary lets say for index 3 it should have 4 there...but
//         as we have 7 which means 7-4=3 numbers are missing till here...similarly till index 4 number of numbers missing are 
//         11-5=6..now we know in problem we have to calculate the 5th missing numbers that will lie between index 3 and index
//         4 for sure....as count of missing numbers..3<5<6..


// Here what we actually doing is finding a index range where our answer will lie...example [3,4]...[2,3].. like this...
// remember the index we are finding are consecutive...also at one point of in binary search where bol high and low will be 
// pointing to same index along with the mid...there can be two possibilites either low moves forward or high moves backward...

// so our high will always be pointing to the first index of the index pair and low to the second index of the pair...but here
// we have to write our answer in terms of high...as low is incerasing it will give us the runtime error if we are standing at
// last index of the array...so now for finding ansswer...lets consider the example arr={2,3,4,7,11} and k = 5...now if u dry 
// run it u will observe at the end high=3 and low=4..so we know till index 3 only 3 numbers are missing and till index 4 ..6
// numbers are missing..so our answer lies between [7,11]..therefore as till index 3 only 3 numbers are missing but we need to 
// find the 5th missing number...so we need 2 more missing numbers..so  5th missing number is 7+(5-3)...or we can say ...
// arr[high] + k - (number of missing till index=high) = arr[high]+k-(arr[high]-(high+1))...

int binarySearch(vector<int> &arr, int k) {

    int low = 0;
    int high = arr.size()-1;
    
    // to handle cases where k < arr[0] ....in these types of cases our high will point to index<0 ...which will give runtime 
    // error...so to fix this we need to deal with such case seperately in the beginning...
     if(k < arr[0]) {
        return k;
    }


    while(low <= high) {
        int mid = low + (high-low)/2;
        

        // its because at 0th index it should have been 1(0+1) ...ideally...in index 5...it should have been 6(5+1) ideally...
        int numberOfMissing = arr[mid] - (mid+1);
        if(numberOfMissing < k) {
            low = mid + 1;
        }else{
            high = mid - 1;
        }

    }

    return arr[high] + k - (arr[high]-(high+1));

    // if we solve it further we get our answer as `high+1+k` ....but as we know `low = high+1` ..because as we know our range
    // is the consecutive indexes of the form [high,low]  (as said earlier when we have all the three pointers ie high,low,mid
    // at the same index....either low move forwards or high move backwards by 1 index)...so the belo return statements are 
    // also correct...so if we return any of the following we dont need to write the if condition we used for checking edge cass

    // return high+1+k;
    // return low+k;

    // Time complexity is O(logn)



}

int main() {
    vector<int> arr1 = {2,3,4,7,11};
    vector<int> arr2 = {1,2,3,4};
    vector<int> arr3 = {5,6};

    int k1 = 5;
    int k2 = 2;
    int k3 = 3;

    cout<<"Linear Search on arr1 : "<<linearSearch(arr1,k1)<<endl;
    cout<<"Linear Search on arr2 : "<<linearSearch(arr2,k2)<<endl;
    cout<<"Linear Search on arr3 : "<<linearSearch(arr3,k3)<<endl;

    cout<<"Binary Search on arr1 : "<<binarySearch(arr1,k1)<<endl;
    cout<<"Binary Search on arr2 : "<<binarySearch(arr2,k2)<<endl;
    cout<<"Binary Search on arr3 : "<<binarySearch(arr3,k3)<<endl;
    return 0;
}