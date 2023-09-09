

// Problem Link - https://www.codingninjas.com/studio/problems/square-root-integral_893351


#include <bits/stdc++.h>
using namespace std;





// Approach - 1 ...LinearSearch (Brute Force)...
// We will search linearly for the square root of the number...and we know while iterating if we square a particular i ...and 
// this square is less than the given number n...then we can say this `i` ...can be our answer...but it is not sure...because...
//we may find a bigger i whose square is also less than the given number ...so this i will have higher probability of being the
//  square root...then the previous `i`.. ...so basicaly we are searching for the highest i for which i*i <= n....


int squareRootBF(int n) {

    int sqrt = 0;

    for(int i = 1;i<=n;i++) {
        if(i*i <= n) {
            sqrt = i;
        }else{
            break;
        }
    }


    return sqrt;
}









// Approach 2 - Using inbuilt function....(better than the normal BruteForce (linearSearch))...
// this function will always returns the sqrt root of the number ...if the number is perfect square...if it is not a perfect 
// square...then it returns the floor value of square root of n
int squareRoot(int n) {
    
    return sqrt(n);
}








// Approach 3 - Binary Search...

// Intuition - 
// Now suppose our n is 28 ...so we start traversing ...and find that....
// 1^2 = 1 <= 28 ..... implies this can be our answer...(✓)
// 2^2 = 4 <= 28 ...   this can be also a answer .....  (✓)
// 3^2 = 9 <= 28 ......                                 (✓)
// 4^2 = 16 <= 28 .....                                 (✓)
// 5^2 = 25 <= 28......                                 (✓)
// 6^2 = 36 >= 28.....                                  (🗴)
// 7^2 = 49 >= 28 ....                                  (🗴)    ....so on


// what we are observing is that ....we are diving the whole possibilies of our answer into two parts....one where our answer  
// may lie....and one part is where we know our answer can never lie...also we are searching for a number....so can we say we 
//can apply binary search ? ......yes we can...as we are eliminating the half where we know our answer is not possible...and 
// we are searching in the half where we know our answer will lie... for sure..

// Logic - we know if we are given a number say 28 ....and cuurrently our mid is at 7 ...so if we do 7^2= 49 >= 28...we know one 
// thing for sure ...that our answer(sqrt) ...will never lie after 7...because for every number after 7 it.s square will 
// definetly exceeds the given n ...so we can say our answer lie in the range of [1-6] ...similarly ...if our mid is at 4 ...
// now 4^2 = 16 <= 28 ...so we can say this might be our answer....because the square is less than the given number ...but
//  we can't guarantee ..this will be our final answer...because we need to find the greatest number whose square is <= 28..
// ...so we have to search after 4 ...that is from 5
int binarySearch(int n) {

    int low = 1;
    int high = n;

    int ans = 0;



    while(low <= high) {
        long long mid = low + (high-low)/2;

        if(mid*mid <= n) {
            ans = mid;
            // check if there is any greater number whose square is also either less than or equal to given number...
            low = mid + 1;
        }else{
            // if the square root of this number(mid) ...is greater than the required number...then our answer never lies after
            //  (mid)...so trim down the search space...and look to the numbers lesser than mid....
            high = mid - 1;
        }
    }

    
    // return high;

    // if you will dry run on some examples you will observe at the end of while loop ..ie. the moment your low > high...your 
    // high woul have been pointing to ur answer...so we can also return high in place of high....
    // and this is true for any binary search problem...for any binary search problem...either your high or low...at the end 
    // of the search ...will point to ur final answer.....

    // why is this logic working here because....we know initally our low is pointing at 0...which can be your answer...and 
    // high is pointing to a place where the answer is not possible...so we're just moving low variable to the left ...and 
    // high variable to the right...it is working because...if we see carefully we are moving low whenever we have 
    // mid*mid <= n....and we are moving high whenever mid*mid > n ....so suppose we are left with only one element ...say 6
    // and n is 28...now our mid , low and high all are pointing to 6....now if we check 6^2 = 36...that's why our low won't 
    // move...and as 6^2 = 36 > 28 ...so our high moves and now it will cross low ...and is now pointing to the number 5...
    // which is our answer...so if u observe...this will always work...in this problem...our high at the end of search...will  
    // always be pointing to the final answer...you can check for different examples...check for n=36...n = 23...and keep low 
    // at 1 ...in the beginning ...
    return ans;
    

}
 



int main() {
    int n = 28;
    int ans1 = squareRootBF(n);
    int ans2 = squareRoot(n);
    int ans3 = binarySearch(n);


    cout<<ans1<<endl;
    cout<<ans2<<endl;
    cout<<ans3<<endl;


    return 0;
}