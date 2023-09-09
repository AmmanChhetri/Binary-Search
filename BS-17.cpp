

// Problem Link - https://www.codingninjas.com/studio/problems/nth-root-of-m_1062679


#include <bits/stdc++.h>
using namespace std;




// Approach - 1 ...LinearSearch (BruteForce) ..
int linearSearch(int n, int m) {

    int ans = -1;

    for(int i = 1;i<=n;i++) {
        if(pow(i,n) == m) {
            return i;
        }else if(pow(i,n) > m) {
            break;
        }
    }
    
    // Because it is given that if we din't find the root we have to return the -1....
    return ans;
}









// Appraoch 2 - BinarySearch ...
// suppose m = 69 ....and n = 4 ...therefore ...pow(1,4) = 1 < 69 ...=> pow(2,4) = 16 < 69 => pow(3,4) = 81 > 69 ...as we didn't
// find answer we return -1...
int binarySearch(int n, int m) {
    int ans = -1;

    int low = 1;
    int high = m;

    while(low <= high) {
        int mid = low + (high-low)/2;

        if(pow(mid,n) == m) {
            return mid;
        }else if(pow(mid,n) > m) {
            // go left and search...
            high = mid - 1;
        }else{
            // go right and search...
            low = mid + 1;
        }
    }

    return ans;

    // Time Complexity is O(logm)...
}



int main() {

    int n1 = 3;
    int m1 = 27;
    int n2 = 4;
    int m2 = 69;


    cout<<linearSearch(n1,m1)<<endl;
    cout<<linearSearch(n2,m2)<<endl;
    cout<<binarySearch(n1,m1)<<endl;
    cout<<binarySearch(n2,m2)<<endl;

    return 0;
}