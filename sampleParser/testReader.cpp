#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <fstream>
#include <regex>
using namespace std;

struct crime {
    string number;
    string address;
    string date;
    string crimeType;
    void print() {
        cout << "{" << endl;
        cout << "\tDate: " << date << endl;
        cout << "\tNumber: " << number << endl;
        cout << "\tAddress: " << address << endl;
        cout << "\tCrime: " << crimeType << endl;
        cout << "}" << endl;
    }
};


int main() {

    ifstream fin;
    fin.open("report.txt");

    vector<crime> crimes;
    


    vector<string> stringVec;
    
    string input;
    while (getline(fin, input)) {
        stringVec.push_back(input);
    }

    int lineNumber = 0;
    crime c;

    string date;
    string number;
    string address;
    string crimeType;

    string m("-OPD-");

    //regex re("*-OPD-*");
    smatch match;
    while(lineNumber < stringVec.size()) {
//        if (regex_search(stringVec[lineNumber], match, re) && match.size() > 1) {
        if (stringVec[lineNumber].find(m, 0) != string::npos) {
            c.date = stringVec[lineNumber - 1];
            c.number = stringVec[lineNumber];
            c.address = stringVec[lineNumber + 1];
            c.crimeType = stringVec[lineNumber + 2];
            if (stringVec[lineNumber + 3] == "MEDIA") {
                crimeType = "unspecified";
            }

            crimes.push_back(c);
        }
        lineNumber++;
    }
    
    std::for_each(crimes.begin(), crimes.end(), 
        [] (crime &c) { c.print(); });
    
    return 0;
}
