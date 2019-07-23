// includes here
#include "lz77.h"
#include <iostream>
#include <fstream>
#include "string.h"
#include "cmath"
using namespace std;
int main(int argc, char* argv[]) {
  LZ77 L;
  vector <Triplet> encoded;
  vector <unsigned char> decoded;
  string b;
  int a;
  int depth;
  int x,y;
  ofstream myfile;
  vector<unsigned char> msg;
  //to input msg as pgm
  if (strcmp(argv[1],"-encode")==0) {
    cin>>b;
    //handling comments in pgm files 
    while (1) {
    cin>>b;
      if (b[0]!='#')
        break;
      else 
        cin.ignore(5000,'\n');
    }
    x=stoi(b);
    cin>>y;
    b=argv[1];
    cin>>depth;
    //get the msg
    vector<int> file;
    while (cin>>a)
      file.push_back(a);
    //converting msg to unsigned char
    for (int i=0;i<file.size();i++) {
      msg.push_back((unsigned char)file[i]);
  }
  }
  else 
    b=argv[1];
  // perform the required operation ...
  if (b.compare("-encode")==0) 
      a=0;
  if (b.compare("-decode")==0)
      a=1;
  vector<unsigned char> difference =msg;
  int bits;
  // write output ...
  switch (a)
  {
  case 0:
    //Uncomment the next commented lines to see the difference then comment them to be able to use decoding
  /* for (int i=0;i<difference.size();i++) {
    if (i%x!=0)
    //get the difference from the left neighbour
      difference[i]=(unsigned char)((int)difference[i]-(int)msg[i-1]);
  }
    bits=L.encode(difference,stoi(argv[2]),stoi(argv[3]),stoi(argv[4]),&encoded);
    cout<<"# of bits (difference)= "<<bits<<endl;
    cout<<"# of bytes (difference)= "<<bits/8<<endl;
    cout<<"Compression ratio (difference) = "<<ceil(log2(depth))*x*y/(float)bits<<endl<<endl; */
    bits=L.encode(msg,stoi(argv[2]),stoi(argv[3]),stoi(argv[4]),&encoded); 
    cout<<"# of bits= "<<bits<<endl;
    cout<<"# of bytes= "<<bits/8<<endl;
    cout<<"Compression ratio = "<<ceil(log2(depth))*x*y/(float)bits<<endl;
    for (int i=0;i<encoded.size();i++) {
        cout<<encoded[i].j<<" "<<encoded[i].k<<" "<<(int)encoded[i].c<<"\n";
    }
    break;
  case 1:
    myfile.open("decoded.pgm");
    myfile.clear();
    myfile<<"P2"<<endl<<stoi(argv[2])<<" "<<stoi(argv[3])<<endl<<stoi(argv[4])<<endl;
    cin.ignore(5000,'\n');
    cin.ignore(5000,'\n');
    cin.ignore(5000,'\n');
    int j,k,c;
    while (cin>>j>>k>>c) 
      encoded.push_back({j,k,c});
    L.decode(encoded,&decoded);
    for (int i=0;i<decoded.size();i++)
      myfile<<(int)decoded[i]<<" ";
    myfile.close();
    break;
  default:
    break;
  }
  return 0;
}