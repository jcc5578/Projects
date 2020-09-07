// File: Ram.h
// Author(s): Joseph Chieng, Marcel Thio
// Date: 04/19/2020
// Section: 508, 509
// E-mail: jcc5578@tamu.edu 
// Description:
// e.g. The content of this file implements a ram from a file to a vector
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class Ram {
public:
    Ram() {}
    ~Ram() {
        ram.empty();
    }
    int file(string fname) {
        ifstream in(fname);
        if (in.is_open()) {
            string line;
            while (!in.eof()) {
                in >> line;
                if (line.length() == 2) {
                    ram.push_back(line);
                    //cout<<line<<endl;
                }
                else {
                    ram.push_back(line.substr(0, 2));
                    //cout<<line.substr(0,2)<<endl;
                }
            }
            cout << ram.size();
        }
        else {
            cerr << "No file open";
            return 0;
        }
        in.close();
    }
    vector<string> getRamVector() {
        return ram;
    }
    void setRamVector(vector<string>vec) {
        ram = vec;
    }
    void view() {
        cout << "memory-view" << endl;
        cout << "memory_size:" << ram.size() << endl;
        cout << "memory_content:\nAddress:Data";
        // ram data
        for (int i = 0; i < ram.size(); i++) {
            // data address
            if (i % 8 == 0) {
                if (i==0)
                    cout << "\n0x00" << DecHex(i) << ":";
                else if (i < 16)
                    cout << "\n0x0" << DecHex(i) << ":";
                else
                    cout << "\n0x" << DecHex(i) << ":";
            }
            cout << ram.at(i) << " ";
        }
        cout << endl;

    }
    string getBlock(int b, int addr) {
        string ret = "";
        int start = addr / b;
        start *= b;
        for (int i = start; i < start + b; i++) {
            ret = ret + ram.at(i);
        }
        return ret;
    }
    void setData(int addr, string data) {
        //cout <<addr<< "address before " << ram.at(addr) << endl;
        ram.at(addr) = data;
        
    }
    void Dump() {
        ofstream out("ram.txt");
        for (int i = 0; i < ram.size(); i++) {
            out << ram.at(i) <<"\n";
        }
        out.close();
    }
private:
    vector<string> ram;
     
    string DecHex(int dec)
    { 
        string ret;
        int n = 0, i;
        char hex[100]; 
        while (dec != 0)
        {
            i = dec % 16;
            if (i < 10){
                hex[n] = i + 48;
                n += 1;
            }
            else{
                hex[n] = i + 55;
                n += 1;
            }
            dec /= 16;
        }
        for (int j = n - 1; j >= 0; j--) {
            ret += hex[j];
        }
        return ret;
    }
};