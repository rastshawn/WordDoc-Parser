#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <fstream>
#include <regex>
#include <algorithm>
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
    void printTSV() {
        vector<string> strings = {number, address, crimeType};
        for (string s : strings) {
            string::size_type i = 0;
            while (i<s.length()) {
                i = s.find('\n', i);
                if (i==string::npos) break;
                s.erase(i);
            }
            i = 0;
            while (i<s.length()) {
                i = s.find('\r', i);
                if (i==string::npos) break;
                s.erase(i);
            }
            cout << s << "\t";
        }
        string dateTime = "";
        for (int j = 0; j<date.length(); j++){
            if(isalnum(date[j])){
                dateTime += date[j];
            } else if (date[j] == ':') {
                dateTime += date[j];
            } else if (date[j] == '/') {
                dateTime += date[j];
            } else if (date[j] == -54) {
                while (date[j+1] == -54) j++;
                dateTime += '\t';
            }
        }
        cout << dateTime;
        cout << endl;
    }
};


int main() {

    ifstream fin;
    fin.open("report.txt");
    
    // holds array of each individual crime
    vector<crime> crimes;


    // copy every line of the file into an array. 
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

    // for every line in the file (string in the vector)
    // if the line matches "-OPD-", which is in every incident number, 
    // then:
    // the line before the current index is the date
    // the line of the current index is the incident number
    // the line following is the address
    // the line following that is either the offense type,
    // or the reporting officer. When an offense type is listed, it's
    // the offense type. If not, reporting officer. We can tell by finding
    // how far away the next instance of "MEDIA" is. 

    while(lineNumber < stringVec.size()) {
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
   
    cout << "Number\tAddress\tCrimeType\tDate\tTime" << endl;

    // print everything in the crimes vector.
    std::for_each(crimes.begin(), crimes.end(), 
        [] (crime &c) { c.printTSV(); });
    
    return 0;
}
