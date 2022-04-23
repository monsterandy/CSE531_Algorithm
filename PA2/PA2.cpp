
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
    //int lcsTable[1001][1001];
    vector< vector <int> > lcsTable; // lcsTable to store the lcs information
    vector< vector <char> > lcsTableforPrint; // lcsTable to store the lcs information for print "\ match < left ^ up"
    int lcsSize; // Size of the longest common sub-sequence 
    LCS(string s1, string s2); // Constructor of LCS class
    ~LCS();   // Destructor of LCS class
    int lcsDP();  // DP method to compute the lcs
    int lcsPrint(); // Output (all) the LCS
    int lcsTablePrint();
};
  

// LCS DP method
int LCS::lcsDP(){
    for(int n = 0; n <= LCS::lenStr1; n++){
        for(int m = 0; m <= LCS::lenStr2; m++){
            if (n == 0 || m == 0){
                LCS::lcsTable[n][m] = 0;
                LCS::lcsTableforPrint[n][m] = '-';
                }
            else if (LCS::Str1[n-1] == LCS::Str2[m-1]){
                LCS::lcsTable[n][m] = LCS::lcsTable[n-1][m-1] + 1;
                LCS::lcsTableforPrint[n][m] = '\\'; // match
                }
            else if(LCS::lcsTable[n-1][m] > LCS::lcsTable[n][m-1]){
                LCS::lcsTable[n][m] = LCS::lcsTable[n-1][m];
                LCS::lcsTableforPrint[n][m] = '<'; // left
            }
            else {
                 LCS::lcsTable[n][m] = LCS::lcsTable[n][m-1];
                 LCS::lcsTableforPrint[n][m] = '^'; // up 
                }
        } 
    }
    LCS::lcsSize = LCS::lcsTable[LCS::lenStr1][LCS::lenStr2];
    cout << LCS::lcsSize;
    cout << "\n";  
    return 0;
}

// Method to print (all) the LCS
int LCS::lcsPrint(){
    int n = LCS::lenStr1;
    int m = LCS::lenStr2;
    while(n > 0 && m > 0){
        if(LCS::lcsTableforPrint[n][m] == '\\'){
            LCS::lcsStr.push_back(LCS::Str1[n-1]); //need to be reversed 
            n--;
            m--;
        }
        else if(LCS::lcsTableforPrint[n][m] == '<'){
            n--;
        }
        else{
            m--;
        }
    }
    reverse(LCS::lcsStr.begin(),LCS::lcsStr.end());
    cout << LCS::lcsStr;
    cout << "\n";
    return 0;
}

// Method to print the DP table
int LCS::lcsTablePrint(){

    for(int n = 0; n <= LCS::lenStr1; n++){
        for(int m = 0; m <= LCS::lenStr2; m++){
            cout << LCS::lcsTable[n][m]<<LCS::lcsTableforPrint[n][m]<<" ";
        }
        cout << "\n";
    }
    return 0;
}
  
// The Constructor of LCS Class
LCS::LCS(string s1, string s2){
    LCS::Str1 = s1;
    LCS::Str2 = s2; 
    LCS::lenStr1 = LCS::Str1.size();
    LCS::lenStr2 = LCS::Str2.size();
    // Set the initial lcsTable to all zeros
    vector <vector <int> > temp(lenStr1+1,vector<int>(lenStr2+1,0));
    LCS::lcsTable = temp;
    vector <vector <char> > tempChar(lenStr1+1,vector<char>(lenStr2+1,' '));
    LCS::lcsTableforPrint = tempChar;    
    // Set the initial lenght of LCS to 0
    LCS::lcsSize = 0;
    // Set the initial lcsStr to empty
    LCS::lcsStr = "";
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
    l.lcsDP();
    l.lcsPrint();
    //l.lcsTablePrint();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    //cout << "Time taken by function: "<< duration.count() << " microseconds" << "\n";  
    return 0;
}
