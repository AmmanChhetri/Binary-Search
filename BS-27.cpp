

// Problem Link - https://www.codingninjas.com/studio/problems/minimise-max-distance_7541449



#include <bits/stdc++.h>
using namespace std;



// Our aim is to minimize the maximum distance between the gas stations...so lets say we have 2 gas stations intially given by
// {1,7}....and we have k=1 ....which means we need to place this gas station so that the maximum distance between the adjacent
// gas stations is minimized...also we can place gas station at any point (either integer or not) ...in +ve x-axis...now tell me
// one thing...if i place this gas station at some point say ...7.00000001 ...so even if i place this nre gas station there
// the maximum distance between gas station is still 6 right?(ie between 1 and 7)...and if we would have placed at some distance 
// say 1000 ...then the maximum distance would have been 1000-7 993 ....but we can do much much better than this...even if we 
// place anywhere >=0 before the first gas station the gas would have been same...so what do we have left now....we can't place
// a new gas station to the left of the first gas station or to the right of last gas station....so we have only one option now
// that is between the gas stations...now we observe as well if we place a gas station between the initial gas stations our max
// distance will always be less than 6(7-1)...so we will definietly place the as station in between the inital gas stations..now
// the point is where i can keep ... i can place it anywhere but if i place some point say lesser than 4 ...say 3 ...so now the 
// distance of this new gas station from station 1 is 3-1=2...and from station 2 is 7-3=4..now the max of these distance is 4..
// but is this the lowest possible answer...no!!! ...why ?...lets say we would hadn't placed the new gas station at 3...and we
// would have placed it at exactly the middle point of {1,7}...that is 4...now the distance between adjacent gas stations are
// 4-1=3....7-4=3...now this is the minimum...why we got this because....if we place a new gas station even slightly shifted 
// from the middle point...than the distance from the opoosite gas station will always increases from the mid value...so we 
// dont want it right?...

// 1     4     7 ....
// 1    3      7....
// 1      5    7....

// As u can see above if we place at exactly at the middle point of gas stations we get the minimum ...otherwise one side becomes
// dominant in terms of distance ...and our max value increases...

// now if we have k=2...and for the same problem....{1,7}....where should we put the new gas station...so we pick a gas station
// and we put it exactly half of {1,7} ie 4....so after adding 1 gas station our answer looks like    1    4    7....
// now arises the problem...where will u put the 2nd gas currently the position of stations are {1,4,7} ...now if u place the 
// new gas station between say 1&4 or 4&7 ...the new stations would look like {1,2.5,4,7}or {1,4,5.5,7} ...in both the cases the
// maximum distance between the gas stations are 3 ....so is this our answer ? ... NO!!!.. initally we had 2 gas stations that 
// are {1,7}...and we need to place 2 new gas stations....so if we would have place them in beween {1,7} ....but equally ...now
// we know if we put 2 items in between a given range ...so to minimize the maximum distance between adjacent stations...we need
// to insert that the gas stations have equal distance with each other....so do this we know when we insert 2 gas stations between
// the {1,7}...it will  divide them into 3 sections...and the distance between these gas stations is minimum ...when the section
// lengths are equal which means..our best case will be to put gas stations like {1,3,5,7}...the maximum distance between the gas 
// stations is 2...and this is  the minimum possible distance...u can't get values lesser than this from other combiantions...



// similary suppose we had {1,2,3,4,5} and k=4....now the best combination would have been {1,1.5,2,2.5,3,3.5,4,4.5,5}...
// we could have diffenert combinations also like...{1,1.25,1.5,1.75,2,3,4,4.5,5}...but with this combination we are getting the 
// maximum distance as 1....




// ! Approach 1 - LinearSearch (Brute Force)
// Suppose arr = {1,13,17,23} ...and k=5
// as we need to place all k-new gas stations...let's check 1 by 1 ...where we can place it....for now the distance between each
// adjacent stations are 12,4,6 ...respectively...so we want to place our gas station between 1,13 ...as it has the maximum 
// distance...and we want to minimize the distance..now...we have 1 new gas station just in middle of 1,13 ... now updated array
// is {1,7,13,17,23} and the distance array is {6,6,4,6}...now to place the 2nd gas stations....we will try to minimise the 
// distance so we will minimize the 6 here ...as we have maximum distance as 6 currently..so what we will do is we place a station
// between 17 and 23...so our updated array is {1,7,13,17,20,23} ...so on....now one thing to notice here is we dont need to 
// keep the track of updated array ...if only we know how many new gas stations are there between each initial stations...for
// this let's maintain a count array...that stores the number of new gas stations between the original array...

double minimiseMaxDistance(vector<int> &nums, int k) {
    
    int n = nums.size();

    // as n is the lengh if the array ...which means initially we have n-1 sections...now our aim is to check how many new
    // gas stations will be included in each of this section...
    vector<int> count(n-1,0);

    for(int gasStation = 1;gasStation<=k;gasStation++) {

        // now the outer for loop picks the respective gasStation...now our next step is to find which section has maximum 
        // distance...and we put this particular gas station there...as to minimize it...
        double maxi = -1;
        int maxInd = -1;

        for(int i = 0;i<n-1;i++) {
            double diff = nums[i+1]-nums[i];
            // suppose we have new gas stations in between the first two given gas stations...ie {1,13} ...so which means 
            // number of sections is 2+1=3..which means length of each section is ((13-1=12)/3) = 4.. 
            double value = diff/(double)(count[i]+1);
            
            // this will check which section has the maximum length at the same time stores index...so we can add a new gasStation
            // here...
            if(value > maxi) {
                maxi = value;
                maxInd = i;
            }

        }

        count[maxInd]++;

    }





    // after we find what is the number of gas staions we should add in the original gas station arrayy....as to minimize the
    // distance between adjacent gaa station...we will find the maximum of this value...that will be our answer...


    // now we have got the arrangement which will have the minimum possible answer...we just need to find the maximum of all the
    // distance between adjacent gas stations...which will be our answer...

    double maxi = -1;
    for(int i = 0;i<n-1;i++) {
        double diff = nums[i+1]-nums[i];
        double value = diff/(double)(count[i]+1);

        if(value > maxi) {
            maxi = value;
        }
    }

    return maxi;

    // Time Complexity is O(n*k) ≈ O(n^2)...
    // Space Complexity is O(n-1) ...for the count array...
}










// ! Approach 2 - Priority Queue..(Heap)

// As the time complexity of the Brute Force approach is quadratic...O(kn) ...as both k and n worst case values are 10^6 and
// 10^5 respectively ...so it will give a near about quadratic time complexity....so we want to improve it....

// So if we check our BruteForce code...we can't optimize the outer loop ...as we need to place all gas stations 1 by 1 ...there 
// is no other way....but for the inner loop...hmmm...yes we can...our inner loop is just being used to find the maximum again
// and again ... for this we can use the priority queue dataStructure to find the maximum in log(n) time...and hence improving 
// the complexity...
// in our bruteforce logic we can see we are using inner loop to find the maximum value and also storing the index where it 
// occured...So we need to create a priorityQueue of pairs...as we know the priorityQueue always stores largest element to the
// top...so our max value will always be at the top.. also if the first element of the pair is same ...then whichever pair has 
// lasrgest second element will come at top....
    

double minimiseMaxDistancePriorityQueue(vector<int> &nums, int k) {

    int n = nums.size();
    vector<int> count(n-1,0);

    priority_queue< pair<double,int> > pq;

    // intializing the priorityQueue with the initial Sections Length...

    for(int i = 0;i<n-1;i++) {
        double diff = nums[i+1]-nums[i];
        pq.push({diff,i});
    }
    


    for(int gasStation = 1;gasStation<=k;gasStation++) {

        auto tp = pq.top();
        pq.pop(); // we have to pop the top element too...

        int ind = tp.second;
        count[ind]++;

        double diff = nums[ind+1] - nums[ind];
        double sectionLength = diff/(count[ind]+1);

        pq.push({sectionLength,ind});
    }



    // after all this has been executed...the top of our priority queue has the largest section length...after reducing it as 
    // much as possible....
    return pq.top().first;
    // Time Complexity is  O(nlogn) + O(klogn) ..... inserting in a priorityQueue takes logn time..so nlogn for the intial 
    //                                               insertion...and klogn for the main loop...
    // Space Complexity is O(n-1) + O(n-1) ...using priority queue of length n-1.....and one for count array...
}
    
    
    
    
    
    
    
    
    
    
    


// ! Approach 3 - Binary Search
// as in the problem again we have min(max) ...which means we need to find the minimum possible value for some maximums value
// so we can use binary Search...

// Now here as we are dealing with double values in our answer space...and this value can be anything like 0.32352323325667..
// so on...so in the most of the `online compiler` ...in these such cases...we just need to ensure the first 6 digits after
// decimal should match with the answer...we don't care about the digits after 6 decimal places....so in this type of binary
// search ...we change our classical binary Search format into something like ....
// while(high-low > 1e-6) ....remember if it is required that we need to match uptp 7 decimal places we have done...
// while (high-low > 1e-7)...

// what this condition will do is...it will keep checking the difference between high & low....as we know we reduce the search
// space in the binary search ...which means the difference between high & low ...will keep on decreasing ....one point will
// come when the difference becomes very-very small ...after this point high-low becomes >=1e-6 ....this is the case where we 
// need to stop....so here we are using 1e-6...because we want the answer to be accurate till 6 decimal places...the difference
// between high&low ....becomes so less ...like 0.000001 ...that they will be almost same...we stop when distance becomes smaller
// than 1e-6...

// also to reduce the search space in normal case ...we would have did ....low = mid + 1....or high = mid - 1....but think 
//  logically ...can we do it here in case of double? ...answer is NO!..we can't because...if we straight away reduce or 
// increment the value of the unrequired space....we will be loosing so many numbers...so the thing is ....what should we do ...
// it's not like in place of 1....by using 0.1 or 0.00000001 ....or 0.00001 ....will give us the answer...it is not guaranteed...
// so what we do is ...instead of updating low and high by mid + 1 and mid - 1 ....respectively...we just replace low and high
// by `mid`...in this way we are not skipping any decimal values....

// also for any case....the lowese value of the maximum distance between two gas station will be 0...becasue suppose we have
// gas stattions at {1,1,1} ...and k = 3...now the minimum distance between adjacent gas stations will be ocourse `0` ie..
// when i place it at `1` itself...

// Now, the highest possible value of maximum distance between adjacent gas stations will be the maximum distance among the 
// initial stations....suppose arr={1,13,17,23}....the maximum distance among gas stations is 12....which means our answer lies
// between [0,12] ...now why 12? ...we could  have picked some other greater numbers as well like...100,1000 ....etc..but 
// ultimately our answer lies between [0,12] only....as we are trying to minimize the distance ....first gas station is going to
// be placed at the junction of initial gas stattions having maximum length...




int numberOfGasStationsRequired(long double dist, vector<int> &arr) {
    int n = arr.size(); // size of the array
    int cnt = 0;
    for (int i = 1; i < n; i++) {
        int numberInBetween = ((arr[i] - arr[i - 1]) / dist);
        if ((arr[i] - arr[i - 1]) == (dist * numberInBetween)) {
            numberInBetween--;
        }
        cnt += numberInBetween;
    }
    return cnt;
}



double minimiseMaxDistanceBinarySearch(vector<int> &arr, int k) {
    int n = arr.size(); // size of the array
    double low = 0;
    double high = 0;

    //Find the maximum distance:
    for (int i = 0; i < n - 1; i++) {
        high = max(high, (double)(arr[i + 1] - arr[i]));
    }

    //Apply Binary search:
    double diff = 1e-6 ;
    while (high - low > diff) {
        double mid = (low + high) / (2.0);
        int cnt = numberOfGasStationsRequired(mid, arr);
        if (cnt > k) {
            low = mid;
        }
        else {
            high = mid;
        }
    }
    return high;

    // Time Complexity is O(n*log(len)) + O(n)  ..... where O(n) for finding maximum section length initially...and len=length
    //                                              of answer space...
    // Space Complexity is O(1)
}


    

// We could have write the linearSearch code based on the same logic used in binary search as well ...but as our answer lies 
// between [0,max(arr)]...therefore we will search our linear search from 0 ...then instead of incrementing by +1 ...we need
// to increment the variable by +1e-6 ....like i += 1e-6...so this logic will take too much time...



int main() {    

    vector<int> nums = {1,2,3,4,5,6,7};
    int k = 7;

    cout<<minimiseMaxDistance(nums,k)<<endl;
    cout<<minimiseMaxDistancePriorityQueue(nums,k)<<endl;
    cout<<minimiseMaxDistanceBinarySearch(nums,k)<<endl;

    

    return 0;
}