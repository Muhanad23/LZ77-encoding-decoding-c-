// Your includes here
#include "lz77.h"
#include <iostream>
#include "cmath"
using namespace std;
// Your implementations here

int LZ77::encode(const vector<unsigned char>& msg,int S, int T, int A,
vector<Triplet>* encoded_msg) {
    //if msg was empty
    if (!msg.size()) {
        return 0;
    }
    unsigned char const *s,*l,*lptr,*sptr;
    int k,j,mk,c,bits;
    bool encode=false,match=false;
    encoded_msg->push_back({0,0,msg[0]});
    bits=ceil(log2(S))+ceil(log2(S)+T)+ceil(log2(A));
    int i=1;
    //loop on msg
    while (i<msg.size()) {
        encode=false;
        match=false;
        s=&msg[i-1];
        l=&msg[i];
        j=mk=0;
        k=0;
        int z=1;
        lptr=l;
        sptr=s;
        //to check all elemnts in the search buffer to get the longest path
        while (z<=S && i-z>=0) {
            if (msg[i-z]!=*l) {
                z++;
            }
            else {
                match=true;
                mk=0;
                lptr=l;
                for (int ii=i-z;ii<msg.size();ii++) {
                    if (msg[ii]==*lptr) {
                        lptr++;
                        mk++;
                    }
                    else {
                         break;
                    }
                }
                if (k<mk) {
                    j=z;
                    k=mk;
                    encode=true;
                }
                z++;
            }
        }
        if (k)
            i+=k;
        i++;
        if (encode || !match) {
            c=*lptr;
            encoded_msg->push_back({j,k,c});
            bits+=ceil(log2(S))+ceil(log2(S)+T)+ceil(log2(A));
        }          
    }
    return bits;
}

void LZ77::decode(const vector<Triplet>& encoded_msg,vector<unsigned char>* decoded_msg) {
    int j,k,c;
    if (!encoded_msg.size())
        return;
    decoded_msg->push_back(encoded_msg[0].c);
    for (int i=1;i<encoded_msg.size();i++) {
        j=encoded_msg[i].j;
        k=encoded_msg[i].k;
        c=encoded_msg[i].c;
        int f=decoded_msg->size()-j;
        for (int n=f;n<f+k;n++) {
            decoded_msg->push_back(decoded_msg->at(n));
        }
        decoded_msg->push_back(c);
    }
}