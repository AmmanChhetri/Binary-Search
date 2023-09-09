


// Problem Link - https://leetcode.com/problems/koko-eating-bananas/


#include <bits/stdc++.h>
using namespace std;




// Helper function to find the maximum ...from the piles vector....
int findMax(vector<int> &piles) {
    int maxi = INT_MIN;

    for(int i = 0;i<piles.size();i++) {
        maxi = max(maxi,piles[i]);
    }

    return maxi;
}






// Helper function to calculate the number of hours required to eat all the banana piles....for a particular value of `k`(bananas-per-hour eating speed)..
int hoursTotal(vector<int> &piles, int k) {
    
    long hrs = 0;
    for(int i = 0;i<piles.size();i++) {
        
        // if(piles[i] < k) {
        //     hrs += 1;
        // }else{
        //     if(piles[i] % k == 0) {
        //         hrs += piles[i]/k;
        //     }else{
        //         hrs += 1 + piles[i]/k;
        //     }
        // }

        // instead of above conditions...if we noticed carefully we are just adding the ceil value of piles[i]/k...so we can do...
        hrs += ceil((double)(piles[i]) / (double)(k));
    }

    return hrs;
}





// Approach 1 - LinearSearch (Brute Force) ...
long linearSearch(vector<int> &piles, int h) {
    
    int maxi = findMax(piles);
    long ans;
    
    // as we know k(bananas-per-hour eating speed) ...we have to minimize this k...we have to return a k value...for which koko
    // will be able to eat all bananas before h hrs...NOTE - here h is included....now we have created a function to find the
    // maximum from the piles array and a function to calculate the total time required to eat all the bananas with a 
    // particular speed of `k`...we made a function of finding the maximum from the piles vector...because we know our 
    // answer(k) always lies between 1 and the maximum element of the vector...because the moment the k attains the value of the
    // max_element from the piles vector....even if u increase the value of k ....the total amount to finish the banans from 
    // the piles becomes constant...so there is no need to search further...as we only have to print the minimum possible value 
    // of k....say piles = {3,6,7,11} ...if we see if k = 11 ...the total time required to fininsh the banana is 4(length of 
    // the array) ...and if k = 12...the total time to eat is still 4...same for further values of k...so our search space 
    // will be between [1,MaximumValueFromPiles]...as we are searching linearly from 1 ...the moment we find a particular value
    // of k for which `time to eat <= h` ..we will break the function ..as it will be th minimum value of k...
    for(int k = 1;k<=maxi;k++) {
    
        if(hoursTotal(piles,k) <= h) {
            ans = k;
            break;
        }
    }

    return ans;

    // Time Complexity is O(maxi*n) ...as we have a nested loop...where the outerloop runs from 1 to maxi...and we have a 
    //                    function inside too which...takes O(n) time... 
}







// Approach 2 - BianrySearch 
// Intuition - ..why binarySearch ? ....
//             The primary objective of the Binary Search algorithm is to efficiently determine the appropriate half to 
//             eliminate, thereby reducing the search space by half. It does this by determining a specific condition that 
//             ensures that the target is not present in that half.....Now, we are not given any sorted array in which we can 
//             apply binary search...but if we observe carefully...our search space for k lies in between [1,max(piles)]...
//             which is definitely sorted ...right?...and as we are searching for a particular value of k...we can definitely
//             apply binary search...


// Logic - now...suppose we are applying binary search...and we are standing at a particular point(k = mid)....now if we 
//         calculate the time required by koko to finish the pile of bananas with speed k = mid...and if this speed exceeds the
//         given time(h)...what does this signify? isn't this signifies our k value is less and we need to increase our k 
//         value?...yes!!! it does....but why? we know k is the bananas-per-hour eating speed ...so it's obvious if we increase
//         this speed time taken to eat a particular pile of banana will definitely reduce...hence which will reduce the 
//         overall time to eat the pile of bananas...also we can see the time taken to eat a particular pile of banana is 
//         piles[i]/k ...so if we want to reduce the time...obviously we have to increase k....now the second case is if for a 
//         particular k(k = mid)...if the time to eat whole banana pile is lesser than the given time...we can say ...this can 
//         be our answer...but as we have to get the lowest value possible...we will check to the values ...lesser than mid...
long binarySearch(vector<int> &piles, int h) {
    long low = 1;
    long high = findMax(piles);

    long ans = -1 ;

    while(low <= high) {
        int mid = low + (high-low)/2;
        int totalHours = hoursTotal(piles,mid);

        if(totalHours <= h) {
            ans = mid;
            high = mid - 1;
        }else{
            low = mid + 1;
        }
    }
    
    // if we dry run this logic/code...we will see that just after this while loop ends...our `low` will be pointing to the 
    // answer ...so we can simply return low.. after the while loop...
    
    // return low;
    return ans;


    // Time Complexity is O(n*log(maxi))...log for binary search...and nested loop for calulating total hours is O(n)..
    // therefore final time is O(n*log(maxi))
}






int main() {

    vector<int> piles = {3,6,7,11};
    int h = 8;

    cout<<"Minimum speed koko needs to eat all the bananas before "<<h<<" hrs is : "<<linearSearch(piles,h)<<endl;
    cout<<"Minimum speed koko needs to eat all the bananas before "<<h<<" hrs is : "<<binarySearch(piles,h)<<endl;
    return 0;
}