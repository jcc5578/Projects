
// File: Driver.cpp
// Author(s): Joseph Chieng, Marcel Thio
// Date: 04/19/2020
// Section: 508, 509
// E-mail: jcc5578@tamu.edu 
// Description:
// e.g. The content of this file implements the driver that read inputs and runs program
#include <ostream>
#include <string>
#include "Ram.h"
#include "Cache.h"

using namespace std;

int main(int argc, char* argv[]) {

    int c, db, e, repPol, wHitPol, wMissPol;
    string cmd = "null";
    db = e = repPol = wHitPol = wMissPol = 0;
    Ram ram;
    if(argc!=2){
        cout<<"ERROR: No input file found. Pleas re-run with input file.\n";
        exit(1);
    }
    cout << "*** Welcome to the cache simulator ***\ninitialize the RAM:\ninit-ram 0x00 0xFF";
    ram.file(argv[1]);
    cout << "\nram successfully initialized!" << endl;
    
    do{
        cout<<"configure the cache\ncache size: ";
        cin>>c;
        c = (int) pow(2,ceil(log2(c)));
        if (c>256){
            cout<<"Cache size too big will scale back to 256"<<endl;
            c=256;
        }
        if (c<8){
            cout<<"Cache size too small will scale back to 256"<<endl;
            c=8;
        }
        cout<<"data block size: ";
        cin>>db;
        while ( db<=0){
            cout<<"Please write only option 1 or greater"<<endl;
            cout<<"data block size: ";
            cin>>db;
        }
        cout<<"associativity: ";
        cin>>e;
        while ( e!=1 &&e!=2&&e!=4){
            cout<<"Please write only option 1, 2, or 4"<<endl;
            cout<<"associativity: ";
            cin>>e;
        }
        if(c<e*db){
            cout<<"The combonation is not compatible"<<endl;
        }
    }while(c<e*db);// assume there wil only be one set


    cout<<"replacement policy: ";
    cin>>repPol;
    while(repPol!=1&&repPol!=2&&repPol!=3){
        cout<<"Please write only option 1, 2, or 3"<<endl;
        cout<<"replacement policy: ";
        cin>>repPol;
    }

    cout<<"write hit policy: ";
    cin>>wHitPol;
    while(wHitPol!=1&&wHitPol!=2){
        cout<<"Please write only option 1 or 2"<<endl;
        cout<<"write hit policy: ";
        cin>>wHitPol;
    }

    cout<<"write miss policy: ";
    cin>>wMissPol;
    while(wMissPol!=1&&wMissPol!=2){
        cout<<"Please write only option 1 or 2"<<endl;
        cout<<"write miss policy: ";
        cin>>wMissPol;
    }
    Cache cache(c,db,e,repPol,wHitPol,wMissPol,&ram);
    // clean
   getline(cin,cmd);
    //Cache cache(32, 8, 4, 1, 2, 1, &ram);//s
    cout << "\ncache successfully configured!" << endl;
    while (true) {
        cout << "\n\n*** Cache simulator menu ***\ntype one command:\n1. cache-read\n2. cache-write\n3. cache-flush\n4. cache-view\n5. memory-view\n6. cache-dump\n7. memory-dump\n8. quit\n****************************\n";
        getline(cin, cmd);
        if (cmd.find("cache-read") != string::npos) {
            //cout << cmd << endl;
            cache.read(cmd);
        }
        else if (cmd.find("cache-write") != string::npos) {
            //cout << cmd << endl;
            cache.write(cmd);
        }
        else if (cmd.find("cache-flush") != string::npos) {
            //cout << cmd << endl;
            cache.flush();
        }
        else if (cmd.find("cache-view") != string::npos) {
            //cout << cmd << endl;
            cache.view();
        }
        else if (cmd.find("memory-view") != string::npos) {
            //cout << cmd << endl;
            ram.view();
        }
        else if (cmd.find("cache-dump") != string::npos) {
            //cout << cmd << endl;
            cache.Dump();
        }
        else if (cmd.find("memory-dump") != string::npos) {
            //cout << cmd << endl;
            ram.Dump();
        }
        else if (cmd.find("quit") != string::npos) {
            return 1;
        }
        else {
            cout << "command not recognized, please type command as shown" << endl;
        }
    }
    return 0;
}