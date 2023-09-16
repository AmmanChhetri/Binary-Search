

// Problem Link - 


#include <bits/stdc++.h>
using namespace std;




// !!!! NOTE - 
// here after reading the question most of us will start thinking like...trying all combinations and finding the maximum pages
// that can be allocated.....but don't u think this will become so messy when we have too many students....so we need to think
// something else....so our problem is revolving around maximum pages that can be allocated...lets think solving this itself...



// ! NOTE
// this kind of problem where we have to find like max(min) {like in previous problem where we need to find max(minimum 
// distance between two cows..)}  or min(max) {Like in this problem min(maximum number of pages allocated to a student...)}...
// this can be solved using the `Binary Search problem`....always solve this problem using `Linear Search` first
// then think of Binary Search...now in this kind of problem always think about the part inside the bracket...like in this 
// question `maximum number of pages allocated to a student` ...now think of the lowest and highest possible value of this....
// now the maximum pages to be allocated to the student can be anything like 1 or 2 or 3 etc...but the lowest possible pages to
// be allocated completely depends upon the pages array...example pages = {25,46,28,49,24}...let say we take maxm pages to be
// allocated as 1...but think logically if we take it as 1...we won't be able to assign any of the books to the students...
// similarly...let say maximum is 25 ...so we can assign first book to some student and last book to some other student...but 
// there will be some books left again...therefore we need to take the lowest possible value by which we can assign all the 
// books to the students...which will be max(pages[])...so if we take the pages as 49...we can assign these all books...and we
// know we have to assign all the books...similary the highest possible value of `maximum number of pages that can be allocated
// to a student is...sum(pages[])...when we have only one student...in this case we can say oue answer will lie between 
// [49,172]...it will never lie before 49 ...because let say if we take maximum pages that can be allocated to a
// student as 48...then we won't be able to allocate the book with 49 pages...if we want to allocate all the books we need to 
// start looking from max(pages[])..that's the first value from which we can allocate all books...

// think of the lowest and highest possible values of the `maximum pages that can be allocated to the students` ...can we say 
// the lowest value can be 1...no because if we consider 1 as the lowest possible value of `maximum pages that can be allocated
// to sdtudents` ...then we won't be able to assign all books to students...





// Helper function to tell if for a given limit of maximum number pages that can be allocated to any student...how many students
// got the books allocated to them...
int countStudents(vector<int> &pages, int maxLimit) {
    
    // initialising these variables....so we will first allocate books to student 1..as it is given we need to allocate books in
    // contigous fashion so we can't allocate books to student 2 ...until student 1 capacity is reached...
    int students = 1;
    int pagesAllocated = 0;

    for(int i = 0;i<pages.size();i++) {
        if(pagesAllocated + pages[i] <= maxLimit) {
            pagesAllocated += pages[i];
        }else{ 
            // if a particular student can't hold it we go to next student...
            students ++;
            pagesAllocated = pages[i];
        }
    }
    
    // suppose if this students is high(greater)...what does this mean ...think logically...it means the maxLimit to hold book
    // is less...that's why books allocated to many students...similarly if the number of students is less...which simply means
    // the maxLimit that a student can holds is greater that's why a particular student is able to hold many books....dry run 
    // the example of this problem and you will understand....
    return students;
}






// Approach 1 - Linear Search
int linearSearch(vector<int> &pages, int m) {
    
    // suppose if the books is lesser than the number of students...then there will be some students who didnt get any book...
    // which is not possiible....as every student atleast need to get a book...
    if(pages.size() < m) {
        return -1;
    }

    
    int mini = *max_element(pages.begin(),pages.end());
    int maxi = 0;

    for(int i = 0;i<pages.size();i++) {
        maxi += pages[i];
    }

    for(int maxLimit = mini;maxLimit<=maxi;maxLimit++) {

        if(countStudents(pages,maxLimit) == m) {
            return maxLimit;
        }
    }


    return -1;


    // Time complexity is O(sum-max+1)*O(n)...
}














// Approach 2 - Binary Search
int binarySearch(vector<int> &pages, int m) {

    if(pages.size() < m) {
        return -1;
    }

    int low = *max_element(pages.begin(),pages.end());
    int high = 0;
    for(int i = 0;i<pages.size();i++) {
        high += pages[i];
    }

    

    int ans = -1;

    while(low <= high) {
        int mid = low + (high-low)/2;
        if(countStudents(pages,mid) > m) {

            low = mid + 1;
            
            
        }else{
            // This can be our answer...
            ans = mid;
            // but as we need to check for lower values...
            high = mid - 1;
            
        }

    }


    // return low;
    return ans;
    
    // Time complexity is O(log(sum-max+1))*O(n)...
}




int main() {

    vector<int> pages = {25,46,28,49,24};
    int m = 4;

    cout<<linearSearch(pages,m)<<endl;
    cout<<binarySearch(pages,m)<<endl;
    return 0;
}