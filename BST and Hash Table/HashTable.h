#include <string>
#ifndef Header_h
#define Header_h
#include "quicksort.h"
#include <fstream>
using namespace std;
class HashTable{
public:
    struct entry{
        string mystring;
        int count;
        entry(){mystring=""; count = 0;}
        entry(string s, int c): mystring(s), count(c) {};
    };
    
    HashTable(){
        occupied = 0;
        size = 10;
        arr = new entry[size];
    }
    
    HashTable(unsigned long long inputsize){
        occupied = 0;
        size = (3/2)*inputsize;
        cout<<"constructing a HashTable of "<<size<<" entries"<<endl;
        arr = new entry[size];
    }
    
    ~HashTable(){
        delete [] arr;
    }
    
    unsigned long long hashFunction(string mystring){
        unsigned long long key=0;
        int g = 37;
        for( long i=mystring.size()-1; i >= 0; i--){
            key = g*key + mystring[i];
        }
        return key % size;
    }
    
    void insert(string str){
        unsigned long long key = hashFunction(str);
        unsigned long long offset1 = key % size;
        unsigned long long offset2 = 1 + key % (size-1);
        int i=0;
        unsigned long long index;
        while(1){
            index = (offset1 + i*offset2) % size;
            if( arr[index].count == 0 ){
                arr[index].mystring = str;
                arr[index].count = 1;
                break;
                occupied++;
            }
            if( arr[index].mystring == str && arr[index].count != -1){
                (arr[index].count)++;
                break;
            }
            i++;
        }
    }
    
    bool find(string str){
        unsigned long long key = hashFunction(str);
        unsigned long long offset1 = key % size;
        unsigned long long offset2 = 1 + key % (size-1);
        unsigned long long i=0;
        unsigned long long index = (offset1 + i*offset2) % size;
        while( arr[index].count != 0 ){
            if( arr[index].mystring == str && arr[index].count != -1){
                //cout<<"HT: The word "<<str<<" with count "<<arr[index].count<<endl;
                return true;
            }
            i++;
            index = (offset1 + i*offset2) % size;
        }
        return false;
    }
    
    void remove(string str){
        unsigned long long key = hashFunction(str);
        unsigned long long offset1 = key % size;
        unsigned long long offset2 = 1 + key % (size-1);
        unsigned long long i=0;
        unsigned long long index = (offset1 + i*offset2) % size;
        while( arr[index].count != 0 ){
            if( arr[index].mystring == str && arr[index].count != -1 ){
                if( arr[index].count == 1 ){
                    occupied--;
                    arr[index].count = -1;
                }
                else{
                    (arr[index].count)--;
                }
                break;
            }
            i++;
            index = (offset1 + i*offset2) % size;
        }
    }
    
    vector<string> rangesearch(string LB,string UP){
        int count = 0;
        vector<string> myvector;
        for(int i=0; i<size; i++){
            if(arr[i].mystring >= LB && arr[i].mystring <= UP && arr[i].count != -1){
                myvector.push_back(arr[i].mystring);
                cout<<arr[i].mystring<<endl;
                count++;
            }
        }
        //cout<<count<<endl;
        return myvector;
    }
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //scan through the Hash table, input each non empty index string
    void outputall(ofstream& outfile){
        vector<string> mystring = sort();
        for(int i=0; i<mystring.size(); i++){
            outfile << mystring[i];
            outfile << endl;
        }
    }
    vector<string> read(){
        vector<string> result;
        for(int i=0; i<size; i++){
            if(arr[i].count != 0 && arr[i].count != -1){
                result.push_back(arr[i].mystring);
            }
        }
        return result;
    }
    vector<string> sort(){
        vector<string> answer;
        answer = read();
        quicksort(answer);
        return answer;
    }
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
    entry* arr;
    unsigned long long size;
    int occupied;
};

#endif /* Header_h */

