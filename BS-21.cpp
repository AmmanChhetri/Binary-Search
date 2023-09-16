


// Problem Link - https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/


#include <bits./stdc++.h>
using namespace std;




// Helper function to find the amount of days....it will take to ship all the weights for a given capacity...
int daysRequired(vector<int> &weights, int capacity) {

    int day = 1; // our target is to load the weights in day 1...as soon we reach the capacity of that day...we go to next day
                 // ans start filling again...
    int load = 0;

    for(int i = 0;i<weights.size();i++) {
        if(load + weights[i] > capacity) {
            // if we are at weights[i] ..and we can't fill this weight in our load for a particular day we will move to next day            
            // next day the weight that cause me trouble last day needs to be filled..that's why we assign load with weights[i]..
            day ++;
            load = weights[i];
        }else{
            // if we are at weights[i] ..and we can fill this weight in our load for a particular day we will fill it...
            load += weights[i];
        }
    }

    return day;
    
}



// Approach 1 - LinearSearch (Brute Force)....


// Intuitution - As our aim is to find the minimum capacity of the ship by which we can ship every load from weights array ...
//              what we can do is ...we can check for each capacity....whether we are able to ship all the weights from this 
//              capapcity or not....and so thus the first capacity of the ship by which we are able to ship everything within 
//              the given `d days` is our answer...and dont forget....we can always fill the ship in the same order as weights..
//              its not like we can pick from any weights...we have to start from the 1st weight..



// Logic -     As our aim is to minimize the `Capacity of the ship`....now we are given a array of weights...and we have to ship
//             them all within `d days`...we can't left anythinig un-shipped....so thing logically...what can be the minimum
//             capacity of our ship...if we want to ship all the weights...it's obvious the minimum capacity should be equal to
//             the maximum load weight from weights array..if we take anything less than the maxm of the weights array...we 
//             won't be able to ship everything...Now the maximum weight capacity can be anything like 100,10k,100k etc anything
//             but do we need to take this much capacity...No!!...suppose we have weights array as [1,2,3,4,5,6,7,8,9,10]..now 
//             the sum of all the weights here is `55` ...which means...even in the worst case when we pick every weights 
//             together on a same day....the maximum weight of the load will be the sum of all weights....so which means...our
//             weight never exceeds the sum of all weights...which means...the maximum capacity of the ship never exceeds the 
//             sum of all weights...so we got our range now as [max(weights),sum(weights)]...now we just have to seach linearly
//             for each capacity
int linearSearch(vector<int> &weights, int days) {

    int mini = *max_element(weights.begin(),weights.end());
    int maxi = 0;
    for(int i = 0;i<weights.size();i++) {
        maxi += weights[i];
    }

    int ans = -1;

    for(int capacity = mini;capacity<=maxi;capacity++) {

        int calcDays = daysRequired(weights,capacity);
        if(calcDays <= days) {
            ans = capacity;
            break;
        }

    }

    return ans;    
    // Time complexity is O(max(weights)-sum(weights)-1) * O(n)...
    

}








// Approach 2 - BinarySearch...

// Intuition - As we are searching in a given range....which is sorted....and as we are looking for a number (minimum capacity)...
//             we can definitely apply binary search here...also if we see our whole answer space is divided into sections...
//             where our solution is possible and where it is not possible...

int binarySearch(vector<int> &weights, int days) {
    int low = *max_element(weights.begin(),weights.end());
    int high = 0;
    int ans = -1;

    for(int i = 0;i<weights.size();i++) {
        high += weights[i];
    }

    while(low <= high) {
        int mid = low + (high-low)/2;
        if(daysRequired(weights,mid) <= days) {
            ans = mid;
            high = mid - 1;
        }else{
            low = mid + 1;
        }
    }


    // return low 
    return ans;

    // Time complexity is O(max(weights)-sum(weights)-1) * O(logn)...


    // Here is a trick for binary Search - we dont need to create a separate variable (ie. ans) ...for binary search..because 
    // at the end of searching either our low or high pointer will be pointing towards the ans....to detect whether it is low or
    // high...simply see the above binary search...the condition in which we are updating our `ans` in the same condition we 
    // are changing our `high pointer` too...so our answer always be @low...if suppose we would have updating our low pointer...
    // whenever we are updating our `ans` then the final answer would have been `high pointer` ...
    
    // So always first create a `ans` variable and solve using updating it..so u can understand better ...at least just remove 
    // the ans variable and return high or low...whatever is not getting updated in the same branch as `ans`....

}



int main() {
    

    vector<int> weights = {3,2,2,4,1,4};
    int days = 3;

    cout<<"Minimum capacity of the ship to load all this weights within the given days is : "<<linearSearch(weights,days)<<endl;
    cout<<"Minimum capacity of the ship to load all this weights within the given days is : "<<binarySearch(weights,days)<<endl;
    

    return 0;
}