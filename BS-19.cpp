

// Problem Link - https://leetcode.com/problems/minimum-number-of-days-to-make-m-bouquets/


#include <bits/stdc++.h>
using namespace std;


// helper function to tell if for the given `day` ...if we are able to make `m-bouquets` ....with `k-adjacent` flowers at a time....
bool isPossible(vector<int> &bloomDay, int day, int m, int k) {
    

    int count = 0;
    int numberOfBouquets = 0;

    for(int i = 0;i<bloomDay.size();i++) {
        if(bloomDay[i] <= day) {
            // if this flower has bloomed then...we increase the count....
            count++;
        }else{
            // the moment we encounter a un-Bloomed flower...we update our numberOfBouquets....and reset count to 0...for
            // again checking for adjacent flowers...
            numberOfBouquets += count/k;
            count = 0;
        }
    }
    
    // there can be cases when we still have some count left and we reached the end of foor loop...so whatever count we left 
    // we add the the number of bouquets we can make with this count... 
    numberOfBouquets += count/k;


    return (numberOfBouquets >= m) ? true : false;
}




// Helper function to find the minimum day required by the flower to bloom ...of all the bloomDay's ...
int minimumDay(vector<int> &bloomDay) {
    int mnm = INT_MAX;

    for(int i = 0;i<bloomDay.size();i++) {
        mnm = min(mnm,bloomDay[i]);
    }

    return mnm;
}





// Helper function to find the maximum day required by the flower to bloom ...of all the bloomDay's ...
int maximumDay(vector<int> &bloomDay) {
    int mxm = INT_MIN;

    for(int i = 0;i<bloomDay.size();i++) {
        mxm = max(mxm,bloomDay[i]);
    }

    return mxm;
}









// Approach 1 - LinearSearch (Brute Force)...You should always write a brute force solution first ...so that we can get a 
//              better idea for optimization....
int linearSearch(vector<int> &bloomDay, int m, int k) {

    // now we are starting our iteration from minium of the `bloomDay array` because...suppose minimum of `bloomDay array` is 
    // 7...so which means....we have to for 7 days...to get a flower bloomed....so it's pointless to check for days lesser than
    //  7...becasue we know no flowers would be bloomed till we reach 7th day
    int mnm = minimumDay(bloomDay);

    // similarly we are ending till maximum of the `bloomDay array` only ...becasuse once we wait for `maximum of bloomDay` 
    // days....we will definetly have all flowers bloomed...so for all the later days it will still be bloomed...but we need 
    // to minimize the days...that's why we are considering till the maximum value only.....
    int mxm = maximumDay(bloomDay);


    if(m*k > bloomDay.size()) {
        // Because even if we wait infinitely we won'e be able to make the required number of bouquets ...with the condition of
        //  k-adjacent flowers...because we don't even have that much flower....so we can always make the required amount of 
        // bouquets with k-adjacent flowers in each bouquets....if and only if the flowers count is greater than equal to 
        // m*k ....so if this the case...we always be able to bloom the flower...
        
        // It simply means if demand is higher than what we can supply/produce ...we can't do it...
        return -1;
    }

    int ans = mnm;


    for(int day = mnm;day<=mxm;day++) {
        if(isPossible(bloomDay,day,m,k)) {
            ans = day;
            return ans;
        }
    }


    return ans;

    // Time Complexity is O(mxm-mnm+1)*n ....here n for finding if it possible to make required bouquets...
}











// Approach - 2 ....Binary Search 

// Intuition - As we see ...what we have to return is minimum number of days till which we have to wait to get required number 
//             of bouquets with the required condition....so if we observe carefully ...the bloomDay array we have is not 
//             sorted...but the `answer space` is itself sorted....and also we are looking for a particular day...which means
//             ...we can use binary Search


// Logic - Now we know the solution of this problem always exits...as we can always wait for the x(maximum value from bloomDay)
///        days...to get all flowers bloomed and make our respective amount of bouquets...but there is one case where we can 
//         say ...we won't be able to make the bouquets......now we know we will be given a `m` representing the number of 
//         bouquets to be made....and a `k` representing the amount of adjacent flowers we need to make bouquets....(also we 
//         can't use one flower in more than one bouqets...)...so if we dont even have the required amount of flowers to make
//         bouqets...then there's no point in checking for minimum day....

//         secondly, if we are standing at some day(mid)...and if we check if we will be able to make the required bouquets by 
//         waiting for days(mid)..then we can say this may be our answer...but we will try to search for values lower than 
//         mid...as we need to minimize day...there may be a lower value of day...we can alos make required bouquets....
int binarySearch(vector<int> &bloomDay, int m, int k) {
    int low = minimumDay(bloomDay);
    int high = maximumDay(bloomDay);
    
    
    // if number of flowers we have is lesser than number of flowers we need we say...it is not possible....otherwise it is 
    // always possible...
    int n = bloomDay.size();
    if(n < m*k) {
        return -1;
    }

    int ans;
    while(low <= high) {
        int mid = low + (high-low)/2;
        int day = mid;

        if(isPossible(bloomDay,day,m,k)) {
            // if with this day ...we are able to make bouquets...then we will store this value ...and search further lower than this day...
            ans = day;
            high = mid - 1;
        }else{
            low = mid + 1;
        }
    }

    
    return ans;

    // Time Complexity is O(log(max(bloomDay[])-min(bloomDay[])+1) * N)                 .... ...O(n) for checking if the 
    // number is possible or not....
}






int main() {

    vector<int> bloomDay1 = {7,7,7,7,12,7,7};
    vector<int> bloomDay2 = {1,10,3,10,2};
    vector<int> bloomDay3 = {1,10,3,10,2};

    int m1 = 2, k1 = 3;
    int m2 = 3, k2 = 2;
    int m3 = 3, k3 = 1;

    
    cout<<"Linear Search : " <<endl;
    
    cout<<"The minimum possible days we need to wait is : "<<linearSearch(bloomDay1, m1, k1)<<endl;
    cout<<"The minimum possible days we need to wait is : "<<linearSearch(bloomDay2, m2, k2)<<endl;
    cout<<"The minimum possible days we need to wait is : "<<linearSearch(bloomDay3, m3, k3)<<endl;


    cout<<"Binary Search : " <<endl;
   
    cout<<"The minimum possible days we need to wait is : "<<binarySearch(bloomDay1, m1, k1)<<endl;
    cout<<"The minimum possible days we need to wait is : "<<binarySearch(bloomDay2, m2, k2)<<endl;
    cout<<"The minimum possible days we need to wait is : "<<binarySearch(bloomDay3, m3, k3)<<endl;


    return 0;
}