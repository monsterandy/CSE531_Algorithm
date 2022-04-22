
// CSE 431/531 (Fall 2022) PA2
// Due Date: Monday, 05/11/2022
// Feng Wei  50428109
// Use Dynamic Programming (DP) algorithm 
// to solve the longest common sub-sequence (LCS) problem 



#include <iostream>
#include <string>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;


// LCS class to output the LCS of String1 and String2
class LCS {
    public:
    string  Str1; // String1 (the length of each string is at most 1000)
    string  Str2; // String2
    string  lcsStr; // One of the longest common sub-sequence(s)
    vector<string> lcsStrs; // All of the LCS
    int lenStr1; // Size of str1
    int lenStr2; // Size of str2
    int lcsSize; // Size of the longest common sub-sequence 
    LCS(string s1, string s2); // Constructor of LCS class
    ~LCS();   // Destructor of LCS class
    int lcsDP(int n, int m);  // DP method to compute the lcs
    int lcsPrint(bool outputAll); // Output (all) the LCS
};
  

// LCS DP method
int LCS::lcsDP(int n, int m){
    if (n == 0 || m == 0){
        return 0;
    }
    else if (LCS::Str1[n-1] == LCS::Str2[m-1]){

        return LCS::lcsDP(n-1, m-1) + 1;
        LCS::lcsStr.push_back(LCS::Str1[n-1]);
    }
    else {
        return max (LCS::lcsDP(n, m-1), LCS::lcsDP(n-1, m));
    }
}

// Method to print (all) the LCS
int LCS::lcsPrint(bool outputAll){
    ;
    return 0;
}
  
// The Constructor of LCS Class
LCS::LCS(string s1, string s2){
    LCS::Str1 = s1;
    LCS::Str2 = s2; 
    LCS::lenStr1 = LCS::Str1.size();
    LCS::lenStr2 = LCS::Str2.size();
    // Set the initial lenght of LCS to 0
    LCS::lcsSize = 0;
    // Set the initial lcsStr to empty
    LCS::lcsStr = "";
    LCS::lcsStrs.push_back(LCS::lcsStr);
}

// The Destructor of LCS class  
LCS::~LCS() { 
    ;
}

//Driver code 
int main(int argc, char ** argv){    
    string s1; // string1
    string s2; // string2
    // Input s1 and s2
    // Use getline instead of cin to handle empty sequneces
    getline(cin, s1); 
    getline(cin, s2);
    // Create a lcs 
    LCS l(s1, s2); 
    // Process the lcs 
    auto start = high_resolution_clock::now();
    cout << l.lcsDP(l.lenStr1, l.lenStr2) <<"\n";
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << "\n";
    cout << "\n";
    cout << l.lcsStr;
    cout << "\n";
    return 0;
}
