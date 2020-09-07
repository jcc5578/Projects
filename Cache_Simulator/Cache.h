// File: Cache.h
// Author(s): Joseph Chieng, Marcel Thio
// Date: 04/19/2020
// Section: 508, 509
// E-mail: jcc5578@tamu.edu 
// Description:
// e.g. The content of this file implements functions to configure and interacts with a cache vector
#include <fstream>
#include <math.h>
#include <map>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Frequency.h"

//include "Ram.h"
using namespace std;
class Cache {
public:
    Cache(int c, int db, int e, int rp, int hp, int mp, Ram* nram) {
        hits = misses = 0;
        C = c;
        B = db;
        lines = e;
        this->rp = rp;
        this->hp = hp;
        this->mp = mp;
        ram = nram;
        S = C / (B * lines);
        s = (int)log2(S);
        b = (int)log2(B);
        t = 8 - (s + b);
        countHits = countMisses = 0;
        int counter = 0;

        // create cache
        for (int i = 0; i < S * lines; i++) {
            string input="00";
            // add tag bits
            for (int j = 0; j < (int)ceil((double) t/4.0); j++) {
                input += "0";
                //input += "T";
                //cout << "+";
            }
            // add blocks
            for (int j = 0; j < B; j++) {
                input += "00";
            }
            //cout << input << endl;
            cache.push_back(input);
        }
        //last access
        for (int i = 0; i < S; i++) {
            lastAccess.push_back("0");
            for (int j = 1; j < lines; j++) {
                lastAccess.at(i) += to_string(j);
           }
        }
        //Least Frequently used
        for (int i = 0; i < S * lines; i++)
        {
            freqAccess.push_back(frequency(0, 0));
            freqAccess.at(i).blockline = counter;
            counter++;
        }
        //checkLA();
    }
    ~Cache() {
        ram = nullptr;
        cache.empty();
    }
    void checkLA() {
        for (int i = 0; i < lastAccess.size(); i++) {
            cout << lastAccess.at(i)<<endl;
        }
    }
    void checkFA()
    {
        for (int i = 0; i < freqAccess.size(); i++)
        {
            cout << freqAccess.at(i).blockline << " " << freqAccess.at(i).freq << endl;
        }
    }
    void Dump() {
        ofstream out("cache.txt");
        string line = "";
        for (int i = 0; i < cache.size(); i++) {
            line = cache.at(i);
            // valid and dirty
            //cout << line[0] << " " << line[1] << " ";
            line = line.substr(2);
            // make it cap

            // tag 
            //cout << line.substr(0, ceil((double)t / 4.0)) << " ";
            line = line.substr((int)ceil((double)t / 4.0));
            // data
            for (int i = 0; i < line.length(); i += 2) {
                out << line[i] << line[i + 1] << " ";
            }
            out << endl;
        }
        out.close();
    }
    void read(string cmd) {// noaddress
        string tagbits, sbits, bbits, addr, addr1, tag;
        int sb, bb, hit = -1;
        static int fill = 0;
            if (cmd.find(" ") != string::npos && cmd.find("0x") != string::npos) {
                
                cmd = cmd.substr(cmd.find(" ")+1);
               //cout<<"|"<<cmd<<"|"<<endl;
                if(cmd.length()<=4 && !( int(cmd[2])>=103|| int(cmd[3])>=103 || (int(cmd[2])>=71&&int(cmd[2])<=90)|| (int(cmd[3])>=71&&int(cmd[3])<=90) )){
                cmd = cmd.substr(cmd.find("0x") + 2, 2);
                // get address
                addr = cmd;
                // if they just put 1 assume a zero is infront 
                if(cmd.length()==1){
                    cmd = "0"+cmd;
                }
                if(int(cmd[0])>=97 && int(cmd[0])<=102){
                    cmd[0] = static_cast<char>(int(cmd[0])-32); 
                }
                if(int(cmd[1])>=97 && int(cmd[1])<=102){
                    cmd[1] = static_cast<char>(int(cmd[1])-32); 
                }
                addr=cmd;
                cmd = HexBin(cmd[0]) + HexBin(cmd[1]);
                addr1 = cmd;
                for (int i = 0; i < t; i++)
                    tagbits += cmd[i];
                cmd = cmd.substr(t);
                for (int i = 0; i < s; i++)
                    sbits += cmd[i];
                bbits = cmd.substr(s);
                //cout << tagbits << " | " << sbits << " | " << bbits << endl;
                if (t % 4 == 1)
                    tagbits = "000" + tagbits;
                if (t % 4 == 2)
                    tagbits = "00" + tagbits;
                if (t % 4 == 3)
                    tagbits = "0" + tagbits;
                if (tagbits.length() == 8) {
                    tagbits = binHex.find(tagbits.substr(0, 4))->second + binHex.find(tagbits.substr(4))->second;
                }
                else {
                    tagbits = binHex.find(tagbits.substr(0, 4))->second;
                }
                //cout << tagbits << endl;
                bb = BinDec(stoi(bbits));
                if (sbits != "") {
                    sb = BinDec(stoi(sbits));
                }
                else{
                    sb=0;
                    //cout<<"-----------------------------------------"<<endl;
                }
                for (int i = sb * lines; i < (sb + 1) * lines; i++) {
                    string tagon;
                    // to check length of tag
                    if (tagbits.length() >=2) {
                        tagon = cache.at(i).substr(2, 2);
                    }
                    else {
                        tagon = cache.at(i)[2];
                    }
                    // if hit store where
                    //cout<<"i: "<<i<<"| tagon: "<< tagon<<"|tagbits: "<<tagbits.length()<<endl;
                    if (cache.at(i)[0] == '1' && tagon == tagbits) {
                        hit = i;
                    }
                }
                
                //hit
                if (hit != -1) {
                    countHits+=1;
                    cout << "set:" << sb << endl;
                    cout << "tag:" << tagbits << endl;
                    cout << "hit:yes" << endl;
                    cout << "eviction_line:-1" << endl;
                    cout << "ram_address:" << addr << endl;
                    //cout << "bb is " << bb << endl;
                    if (bb == 0) {
                        cout << "data:0x" << cache.at(hit).substr(2 + tagbits.length() + (bb * 2), 2);
                    }
                    else {
                        cout << "data:0x" << cache.at(hit).substr(2+tagbits.length()+(bb * 2), 2); //check +1 or not
                    }
                    cout << endl;
                    string holder = lastAccess.at(sb).substr(hit - (sb * lines));
                    lastAccess.at(sb) = lastAccess.at(sb).substr(0, lastAccess.at(sb).find(holder)) + lastAccess.at(sb).substr(lastAccess.at(sb).find(holder) + 1) + holder;
                    //cout << "HIT IS: " << hit << endl;
                    for(int i = 0; i < freqAccess.size(); i++)
                    {
                        if (hit == freqAccess.at(i).blockline)
                        {
                            freqAccess.at(i).freq+=1;
                        }
                    }
                    //freqAccess.at(freqAccess.size()-1-hit).freq += 1;
                    //checkFA();
                }
                //miss
                else {
                    //checkLA();
                    string newblock = ram->getBlock(B, BinDec(stoi(addr1)));
                    countMisses+=1;
                    cout << "set:" << sb << endl;
                    cout << "tag:" << tagbits << endl;
                    cout << "hit:no" << endl;

                    if (rp == 1) {
                        // check if there is an extra block first
                        for (int i = sb * lines; i < (sb + 1) * lines; i++) {
                            // if hit store where
                            if (cache.at(i)[0] == '0') {
                                hit = i;
                                break;
                            }
                        }
                        if (hit != -1) {
                            cout << "eviction_line:" << hit - (sb * lines) << endl;
                            cache.at(hit) = "10" + tagbits + newblock;
                            string holder = lastAccess.at(sb).substr(hit - (sb * lines));
                            lastAccess.at(sb) = lastAccess.at(sb).substr(0, lastAccess.at(sb).find(holder)) + lastAccess.at(sb).substr(lastAccess.at(sb).find(holder) + 1) + holder;
                        }
                        else {
                            srand(time(0));
                            int n = rand() % lines;
                            cout << "eviction_line:" << n << endl;
                            cache.at((sb * lines) + n) = "10" + tagbits + newblock;
                            string holder = lastAccess.at(sb).substr(lastAccess.at(sb).find(to_string(n)));
                            lastAccess.at(sb) = lastAccess.at(sb).substr(0, lastAccess.at(sb).find(holder)) + lastAccess.at(sb).substr(lastAccess.at(sb).find(holder) + 1) + holder;
                        }
                    }
                    else if(rp == 2){
                        string lol = lastAccess.at(sb);
                        //cout << "LOL IS: " << lol << endl;
                        lol = lol.substr(0, 1);
                        int n =  stoi(lol);
                        cout << "eviction_line:"<< n << endl;
                        cache.at((sb * lines) + n) = "10" + tagbits + newblock;
                        lastAccess.at(sb) = lastAccess.at(sb).substr(1) + lastAccess.at(sb).substr(0,1);

                    }
                    else
                    {
                        freqAccess.at(sb).freq += 1;
                        int lol = freqAccess.at(sb).blockline;
                        if (fill < 4) 
                        {
                            frequency move = freqAccess.at(0);
                            for(int i = 0; i < freqAccess.size()-1; i++)
                            {
                                freqAccess.at(i) = freqAccess.at(i+1);
                            }
                            freqAccess.at(freqAccess.size()-1) = move;
                            fill++;
                            cache.at((sb* lines) + lol) = "10" + tagbits + newblock;
                            //cout << "fill is: " << fill << endl;
                        }
                        else{
                            //cout << "HELLO WORLD???" << endl;
                            int minindex = 9999999;
                            int indexvalue = 9999;
                            for (int i = 0; i < freqAccess.size(); i++)
                            {
                                if (freqAccess.at(i).freq < minindex)
                                {
                                    minindex = freqAccess.at(i).freq;
                                    indexvalue = i;
                                }
                            }
                            //cout << "INDEX IS: " << indexvalue << endl;
                            cache.at((sb* lines) + indexvalue) = "10" + tagbits + newblock;
                            freqAccess.at((sb*lines)+indexvalue).freq = 0;
                        }
                        cout << "eviction_line:" << lol << endl;
                        //checkFA();
                    }
                    cout << "ram_address:0x" << addr << endl;
                    //cout << tagbits.length() << " " << bb << " " << B << endl;
                    cout << "data:0x" << newblock.substr((bb * 2), 2) << endl;

                }
                //view();
                }else{
                    cout<<"ERROR: Data Invalid"<<endl;
                }

            }
            else {
                cout << "invalid command :: make sure that address starts with '0x'" << endl;
            }
        
        
    }
    void write(string cmd) {
        string addr, data;
        string tagbits, sbits, bbits, addrB, tag;
        int sb, bb, hit = -1;
        int dirtyBit = -1;
        static int fill = 0;
        if (cmd.find(" ") != string::npos && cmd.substr(cmd.find(" ") + 4).find(" ") != string::npos &&cmd.find("0x") != string::npos && cmd.substr(cmd.find("0x") + 4).find("0x") != string::npos) {
            string str1, str2;
            str1= cmd.substr(cmd.find(" ")+1);
            //cout<<str1<<endl;
            str2= str1.substr(str1.find(" ")+1);
            str1= str1.substr(0,str1.find(" "));
            //cout<<"|"<<str1<<"|"<<str2<<"|"<<endl;
            //cout<<"gohere1"<<endl;
            if(!(int(str1[2])>=103|| int(str1[3])>=103 || int(str2[2])>=103|| int(str2[3])>=103 ||(int(str1[2])>=71&&int(str1[2])<=90)|| (int(str1[3])>=71&&int(str1[3])<=90)|| (int(str2[2])>=71&&int(str2[2])<=90)|| (int(str2[3])>=71&&int(str2[3])<=90))){
           // cout<<"gohere2"<<endl;
            if(((str1.length()<=4&&str2.length()<=4))){
                //cout<<"gohere3"<<endl;
                addr = cmd.substr(cmd.find("0x") + 2, 2);
                cmd = cmd.substr(cmd.find("0x") + 4);
                data = cmd.substr(cmd.find("0x") + 2, 2);
                cmd = addr;
                
                // if the addr only has one value
                if(!( (int(addr[1])>=65 && int(addr[1])<=70) || (int(addr[1])>=48 && int(addr[1])<=57))){
                    cmd = "0"+ cmd;
                }
                if(!( (int(data[1])>=65 && int(data[1])<=70) || (int(data[1])>=48 && int(data[1])<=57))){
                    data = "0"+ data;
                }
                if(int(cmd[0])>=97 && int(cmd[0])<=102){
                    cmd[0] = static_cast<char>(int(cmd[0])-32); 
                }
                if(int(cmd[1])>=97 && int(cmd[1])<=102){
                    cmd[1] = static_cast<char>(int(cmd[1])-32); 
                }
                addr=cmd;
                if(int(data[0])>=97 && int(data[0])<=102){
                    data[0] = static_cast<char>(int(data[0])-32); 
                }
                if(int(data[1])>=97 && int(data[1])<=102){
                    data[1] = static_cast<char>(int(data[1])-32); 
                }

                //cout << "addr/data" << addr << data << endl;
                //-----------------same code ish
                cmd = HexBin(cmd[0]) + HexBin(cmd[1]);
                addrB = cmd;
                for (int i = 0; i < t; i++)
                    tagbits += cmd[i];
                cmd = cmd.substr(t);
                for (int i = 0; i < s; i++)
                    sbits += cmd[i];
                bbits = cmd.substr(s);
                //cout << tagbits << " | " << sbits << " | " << bbits << endl;
                if (t % 4 == 1)
                    tagbits = "000" + tagbits;
                if (t % 4 == 2)
                    tagbits = "00" + tagbits;
                if (t % 4 == 3)
                    tagbits = "0" + tagbits;
                if (tagbits.length() == 8) {
                    tagbits = binHex.find(tagbits.substr(0, 4))->second + binHex.find(tagbits.substr(4))->second;
                }
                else {
                    tagbits = binHex.find(tagbits.substr(0, 4))->second;
                }
                //cout << tagbits << endl;
                bb = BinDec(stoi(bbits));
                if (sbits != "") {
                    sb = BinDec(stoi(sbits));
                }
                else{
                    sb=0;
                }
                for (int i = sb * lines; i < (sb + 1) * lines; i++) {
                    string tagon;
                    // to check length of tag
                    if (tagbits.length() >=2) {
                        tagon = cache.at(i).substr(2, 2);
                    }
                    else {
                        tagon = cache.at(i)[2];
                    }
                    // if hit store where
                    //cout<<"i: "<<i<<"| tagon: "<< tagon<<"|tagbits: "<<tagbits.length()<<endl;
                    if (cache.at(i)[0] == '1' && tagon == tagbits) {
                        hit = i;
                    }
                    
                }
                //cout << "\t\t\t\t" << hit << endl;





                if (hit !=-1) {
                    countHits+=1;
                    cout << "set:" << sb << endl;
                    cout << "tag:" << tagbits << endl;
                    cout << "write_hit:yes" << endl;
                    cout << "eviction_line:-1" << endl;
                    cout << "ram_address:0x" << addr << endl;
                    //cout << "bb is " << bb << endl;
                    cout << "data:0x" << data<<endl;
                    string holder = lastAccess.at(sb).substr(hit - (sb * lines));
                    lastAccess.at(sb) = lastAccess.at(sb).substr(0, lastAccess.at(sb).find(holder)) + lastAccess.at(sb).substr(lastAccess.at(sb).find(holder) + 1) + holder;
                    if (hp == 1) {
                        //cout << "hit,b,bb" << hit << " " << B << " " << bb << endl;
                        ram->setData(BinDec(stoi(addrB)), data);
                        cache.at(hit) = "10" + tagbits + ram->getBlock(B, BinDec(stoi(addrB)));
                        //cout << cache.at(hit) << endl;
                    }
                    else {
                        cache.at(hit) = "11" + tagbits + cache.at(hit).substr(2 + tagbits.length(), bb * 2) + data + cache.at(hit).substr(4 + tagbits.length() + (bb * 2));
                    }
                    dirtyBit =int(cache.at(hit)[1])-48;
                     for(int i = 0; i < freqAccess.size(); i++)
                    {
                        if (hit == freqAccess.at(i).blockline)
                        {
                            freqAccess.at(i).freq+=1;
                        }
                    }
                }
                //miss
                else {
                    countMisses+=1;
                    cout << "set:" << sb << endl;
                    cout << "tag:" << tagbits << endl;
                    cout << "write_hit:no" << endl;
                    if (mp == 1) {
                        //checkLA();
                        string newblock = ram->getBlock(B, BinDec(stoi(addrB)));
                        // rp policy
                        if (rp == 1) {
                            // check if there is an extra block first
                            for (int i = sb * lines; i < (sb + 1) * lines; i++) {
                                // if hit store where
                                if (cache.at(i)[0] == '0') {
                                    hit = i;
                                    break;
                                }
                            }
                            if (hit != -1) {
                                cout << "eviction_line:" << hit - (sb * lines) << endl;
                                cache.at(hit) = "10" + tagbits + newblock;
                                cache.at(hit) = "11" + tagbits + cache.at(hit).substr(2 + tagbits.length(), bb * 2) + data + cache.at(hit).substr(4 + tagbits.length() + (bb * 2));
                                dirtyBit =int(cache.at(hit)[1])-48;
                                string holder = lastAccess.at(sb).substr(hit - (sb * lines));
                                lastAccess.at(sb) = lastAccess.at(sb).substr(0, lastAccess.at(sb).find(holder)) + lastAccess.at(sb).substr(lastAccess.at(sb).find(holder) + 1) + holder;
                            }
                            else {
                                srand(time(0));
                                int n = rand() % lines;
                                cout << "eviction_line:" << n << endl;
                                cache.at((sb * lines) + n) = "10" + tagbits + newblock;
                                cache.at((sb * lines) + n) = "11" + tagbits + cache.at((sb * lines) + n).substr(2 + tagbits.length(), bb * 2) + data + cache.at((sb * lines) + n).substr(4 + tagbits.length() + (bb * 2));
                                dirtyBit = int(cache.at((sb * lines) + n)[1])-48;
                                string holder = lastAccess.at(sb).substr(lastAccess.at(sb).find(to_string(n)));
                                lastAccess.at(sb) = lastAccess.at(sb).substr(0, lastAccess.at(sb).find(holder)) + lastAccess.at(sb).substr(lastAccess.at(sb).find(holder) + 1) + holder;
                            }
                        }
                        else if (rp == 2){
                            string lol = lastAccess.at(sb);
                            lol = lol.substr(0, 1);
                            int n = stoi(lol);
                            cache.at((sb * lines) + n) = "10" + tagbits + newblock;
                            cout << "eviction_line:" << n << endl;
                            cache.at((sb * lines) + n) = "11" + tagbits + cache.at((sb * lines) + n).substr(2 + tagbits.length(), bb * 2) + data + cache.at((sb * lines) + n).substr(4 + tagbits.length() + (bb * 2));
                            dirtyBit =int(cache.at((sb * lines) + n)[1])-48;
                            lastAccess.at(sb) = lastAccess.at(sb).substr(1) + lastAccess.at(sb).substr(0, 1);

                        }
                        else{
                            freqAccess.at(sb).freq += 1;
                            int lol = freqAccess.at(sb).blockline;
                            if (fill < 4) 
                            {
                                frequency move = freqAccess.at(0);
                                for(int i = 0; i < freqAccess.size()-1; i++)
                                {
                                    freqAccess.at(i) = freqAccess.at(i+1);
                                }
                                freqAccess.at(freqAccess.size()-1) = move;
                                fill++;
                                cache.at((sb * lines) + lol) = "10" + tagbits + newblock;
                                cache.at((sb* lines) + lol) = "11" + tagbits + cache.at((sb * lines) + lol).substr(2 + tagbits.length(), bb * 2) + data + cache.at((sb * lines) + lol).substr(4 + tagbits.length() + (bb * 2));
                                dirtyBit = int(cache.at((sb*lines) + lol)[1])-48;
                                //cout << "fill is: " << fill << endl;
                            }
                            else{
                                //cout << "HELLO WORLD???" << endl;
                                int minindex = 9999999;
                                int indexvalue = 9999;
                                for (int i = 0; i < freqAccess.size(); i++)
                                {
                                    if (freqAccess.at(i).freq < minindex)
                                    {
                                        minindex = freqAccess.at(i).freq;
                                        indexvalue = i;
                                    }
                                }
                                //cout << "INDEX IS: " << indexvalue << endl;
                                cache.at((sb * lines) + indexvalue) = "10" + tagbits + newblock;
                                cache.at((sb* lines) + indexvalue) = "11" + tagbits + cache.at((sb * lines) + indexvalue).substr(2 + tagbits.length(), bb * 2) + data + cache.at((sb * lines) + indexvalue).substr(4 + tagbits.length() + (bb * 2));
                                freqAccess.at((sb*lines)+indexvalue).freq = 0;
                                dirtyBit = int(cache.at((sb*lines) + indexvalue)[1])-48;
                            }
                            cout << "eviction_line:" << lol << endl;
                        }
                    }
                    else {//mp
                        ram->setData(BinDec(stoi(addrB)), data);
                        cout << "eviction_line:0" << endl;
                    }
                    cout << "ram_address:0x" << addr << endl;
                    //cout << tagbits.length() << " " << bb << " " << B << endl;
                    cout << "data:0x" << data << endl;
                    
                }
                cout<<"dirty_bit:"<<dirtyBit<<endl;
            //view();
            }
            else {
                cout<<"ERROR: read in too many values after 0x"<<endl;
                cout<<str1<<"|"<<str2<<"|"<<endl;
            }
            }
            else{
                cout<<"ERROR: data invalid"<<endl;
            }


        }
        else {
            cout << "invalid command :: make sure that address starts with '0x' and has Data" << endl;
        }
    }
    void flush() {
        // check if there is a dirty bit to write back
        int set_im_on = 0;
        
        for(unsigned int i = 0; i< cache.size(); i++){
            if(cache.at(i)[1] == '1'){
                string cline = cache.at(i).substr(2);
                set_im_on = i / lines;
                int big_block_offset = B * set_im_on;
                int tag, taglength = (int)ceil((double) t/4.0);
                string hb;
                if( taglength == 2){
                    hb = HexBin(cline[0]) + HexBin(cline[1]);
                    cline = cline.substr(2);
                    tag = BinDec(stoi(hb));
                }
                else{
                    hb = HexBin(cline[0]);
                    cline = cline.substr(1);
                    tag = BinDec(stoi(hb));
                }
                int bigger_block_offset = S * B * tag;
                int start = bigger_block_offset+big_block_offset;
                for(int i = 0; i < B; i++){
                    ram->setData(start,cline.substr(0,2));
                    cline = cline.substr(2);
                    start++;
                }
            }
        }
        int newcounter = 0;
        for (int i = 0; i < S * lines; i++)
        {
            freqAccess.at(i) = frequency(newcounter, 0);
            newcounter++;
        }
        // create cache
        for (int i = 0; i < S * lines; i++) {
            string input="00";
            // add tag bits
            for (int j = 0; j < (int)ceil((double) t/4.0); j++) {
                input += "0";
                //input += "T";
                //cout << "+";
            }
            // add blocks
            for (int j = 0; j < B; j++) {
                input += "00";
            }
            //cout << input << endl;
            cache.at(i)=input;
        }
        // create lastAccess
        for (int i = 0; i < S; i++) {
            lastAccess.at(i)="0";
            for (int j = 1; j < lines; j++) {
                lastAccess.at(i) += to_string(j);
           }
        }
    }
    void view() {
        

        // general info
        //cout << "cache-view" << endl;
        cout << "cache_size:" << C;
        cout << "\ndata_block_size:" << B;
        cout << "\nassociativity:" << lines;
        if (rp == 1) {
            cout << "\nreplacement_policy:1";
        }
        else if(rp == 2)
        {
            cout << "\nreplacement_policy:2";
        }
        else
        {
            cout << "\nreplacement_policy:3";
        }
        if (hp == 1)
        {
            cout << "\nwrite_hit_policy:1";
        }
        else
        {
            cout << "\nwrite_hit_policy:2";
        }
        //cout << "\nwrite_hit_policy:" << (hp == 1) ? "write_through" : "no_write_allocate";
        if(mp == 1)
        {
            cout << "\nwrite_miss_policy:1";
        }
        else
        {
            cout << "\nwrite_miss_policy:2";
        }
        //cout << "\nwrite_miss_policy:" << (mp == 1) ? "write_allocate" : "no_write_allocate";
        cout << "\nnumber_of_cache_hits:" << countHits;
        cout << "\nnumber_of_cache_misses:" << countMisses << endl;
        cout << "cache_content:" << endl;
        
        string line="";
        for (int i = 0; i < cache.size(); i++) {
            line = cache.at(i);
            // valid and dirty
            cout << line[0] << " " << line[1] << " ";
            line = line.substr(2);
            // make it cap

            // tag 
            cout << line.substr(0, ceil((double)t / 4.0)) << " ";
            line = line.substr((int)ceil((double)t / 4.0));
            // data
            for (int i = 0; i < line.length(); i += 2) {
                cout << line[i] << line[i + 1] << " ";
            }
            cout << endl;
        }

    }
private:
    int C, B, lines, rp, hp, mp, S, t, s, b, countHits, countMisses;
    int hits, misses;
    Ram* ram;
    vector<string> cache;
    vector<string> lastAccess;
    vector<frequency> freqAccess;
    map<string, string> binHex = { {"0000","0"},{"0001","1"},{"0010","2"},{"0011","3"},{"0100","4"},{"0101","5"},{"0110","6"},{"0111","7"},{"1000","8"},
        {"1001","9"},{"1010","A"},{"1011","B"},{"1100","C"},{"1101","D"},{"1110","E"},{"1111","F"}, };
    
    int BinDec(int n){
        int r, ret, i;
        ret = i = 0;
        while (n != 0){
            r = n % 10;
            n /= 10;
            ret += r * pow(2, i);
            i++;
        }
        return ret;
    }

    string HexBin(char hex){
        switch (hex) {
        case '0':
            return "0000";
            break;
        case '1':
            return "0001";
            break;
        case '2':
            return "0010";
            break;
        case '3':
            return "0011";
            break;
        case '4':
            return "0100";
            break;
        case '5':
            return "0101";
            break;
        case '6':
            return "0110";
            break;
        case '7':
            return "0111";
            break;
        case '8':
            return "1000";
            break;
        case '9':
            return "1001";
            break;
        case 'A':
        case 'a':
            return "1010";
            break;
        case 'B':
        case 'b':
            return "1011";
            break;
        case 'C':
        case 'c':
            return "1100";
            break;
        case 'D':
        case 'd':
            return "1101";
            break;
        case 'E':
        case 'e':
            return "1110";
            break;
        case 'F':
        case 'f':
            return "1111";
            break;
        default:
            cout << hex;
        }
    }
};