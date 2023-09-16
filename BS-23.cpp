

// Problem Link - https://www.codingninjas.com/studio/problems/aggressive-cows_1082559


#include <bits/stdc++.h>
using namespace std;



bool isPossible(vector<int> &stalls, int mnmdistance, int k) {
    int n = stalls.size();
    
    // we initialize it with 1 because we always place 1st cow at 0th index ...as we want to place all the k cows...so we will 
    // start greedily by placing the 1st cow at 0th index (1st stall)...
    int cows = 1;  // variable to count the number of cows...



    int last = stalls[0]; //  variable to store where the last cow has been placed...
    

    for(int i = 1;i<n;i++) {
        
        if(stalls[i] - last >= mnmdistance) {
            cows++;
            last = stalls[i];
            if(cows == k) {
                return true;
            }
        }
    }

    return false;
}






// Approach 1 - Linear Search...
// We have to find the maximum of (minimum distance between cows ...when all given cows have been placed)...suppose if the 
// stalls array is not sorted ...then when we place cows like for example c1 at index 0 , c2 at index 3, c3 at index 4 and c4 at
// index 6..for k = 4....then we have to find the minimum distance between differnent combinations of cow...like minimum 
// distance can be between (c1 & c2) or may be between (c1 & c4)..etc...its not guarantee...but if our array is sorted ..now 
// if we place the cows in the positions as earlier we can definitely say the minimum distance will be between any two 
// consecutive cows..like it will be between (c1&c2) or (c2&c3) or (c3&c4)..but it will never be between c1 and c4 as the array
// is sorted ...so (c4-c3) < (c4-c1)...so now we see by sorting the stalls array ...our computation of distance become much
// easier...Now  distance between cow can be 1 or 2 or 3.....and so on...but the lowest possible minimum distance between cows 
// is 1...similarly the maximum possible distance between two cows is always max(stalls)-min(stalls) when we are given two cows
// ...also k>=2...so minimum distance between cow can be 1 or 2 or 3....and whichever is the maximum amonng these ...we need to
// return it...

// Logic - So as we have to find the maximum of the minimum distance between cows...we will check for each disatance from 1 to
//         max(stalls)-min(stalls)..and we check ...that whether considering this distance as the minimum distance are we able
//         to place all the cows...if yes then we check for higher distance(as we need to find macimum)...if for a particular
//         distance we are not able to place the cows....which means...our answer (maximum distance) is distance-1....

//         lets say by considering minimum distance as 1...are we able to place all the cows with distance between two cows 
//         ...being atleast 1...if yes this means this can be the answer...but as we have to find the maximum...we check for 
//         higher distance...



// One thing to note here ...is as we want to place all our cows...so will place them greedily...
int linearSearch(vector<int> &stalls, int k) {

    sort(stalls.begin(),stalls.end());
    int n = stalls.size();
    int mini = stalls[0];
    int maxi = stalls[n-1];

    for(int distance = 1;distance<=(maxi-mini);distance++) {
        if(isPossible(stalls,distance,k)) {
            continue;
        }else{
            return distance-1;
        }
    }


    return -1;

    // Time Complexity is O(nlogn)+O(n) * O(max(stalls)-min(stalls))...
}




// !!!!IMPORTANT 

// Here one thing is very important that is sorting of the array...becasuse...lets say we have 3 cows and the stalls are in 
// which we placed them are respectively...10,3,8 .... c1 @ 10, c2 @ 3 and c3 @8...now distance between cows are 7 between c1 
// and c2, 5 between c2 and c3 , and 2 between c1 and c3....but the minimum distance is between c1 and c3...so if the array is 
// not sorted ...minimum distance can occur between anywhere..so if the nuumber of cows are huge...it will becomde difficult to
// check each pair for minimum distance ..but if we sort our array...its  guraentee that the distance are always in increasing 
// order...so now array is 3,8,10 ...so we can guaranteely say minimum distance will occur between either 3&8 or 8&10...it will
// never lie between 3&10..so in this way we make our calcualtions much easier...






// Approach 2 - Binary Search
// Intuition - If we see we have a range of value where our answer will lie...that is (1,max(stalls)-min(stalls))...also 
//             suppose at some point we check and find considering this as minimumday we are able to get answer so we check for
//             higher distance...if it would not have possible we would have checked lesser indexes...so what we are actually 
//             doing is dividing our answer space into regions where the answer is possible and where it is not....so we can 
//             apply binary Search....

int binarySearch(vector<int> &stalls, int k) {
    
    sort(stalls.begin(),stalls.end());

    int n = stalls.size();

    int low = 1;
    int high = stalls[n-1] - stalls[0];

    int ans = -1;

    while(low <= high) {
        int mid = low + (high-low)/2;

        if(isPossible(stalls,mid,k)) {
            ans = mid;
            low = mid + 1; // check for higher answer...as we need to find the maximum...
        }else{
            high = mid - 1;
        }
    }


    return ans;

    // Time Complexity is O(nlogn) + ( O(n)*O(max(stalls)-mini(stalls)) )
}






int main() {

    vector<int> stalls = {0,3,4,7,10,9};
    int k = 4;

    cout<<linearSearch(stalls,k)<<endl;
    cout<<binarySearch(stalls,k)<<endl;
    return 0;
}