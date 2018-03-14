//
//  main.cpp
//  Binary Search Tree
//
//  Created by dali on 1/27/18.
//  Copyright © 2018 dali. All rights reserved.
//
#include <unistd.h>
#include <stdio.h>
#include<ctime>
#include<fstream>
#include <iostream>
#include "BST.h"
#include "HashTable.h"
#include "FolderTraversal.h"
using namespace std;
void execute(string input, BST BST, HashTable HT);

string S[100]={
 "trail","study","declaration","outer","agree","launch","criticism","slab","slam","blue","delay","lobby","survival","column","know","design","salvation","maze","student","iron","packet","cause","mole","block","arm","technology","refer","bar","carrot","mosquito","generate","laboratory","password","privacy","include","credit","ant","sensitive","branch","bomber","care","displace","weave","hesitate","hurt","edge","node","enlarge","arrogant","obstacle","accident","systematic","wage","idea","sequence","planet","defendant","spoil","magnetic","hold","gown","boom","lemon","mold","frequency","fling","constitution","likely","prejudice","period","character","carry","facility","fisherman","term","fascinate","glow","swell","offend","system","culture","cute","sulphur","voucher","gem","reveal","glacier","restrict","exclude","compartment","flight","grateful","bald","answer","finger","line","wave","pull","chief","flower"
};

int main(int argc, const char * argv[]) {
    char CWD[1024];
    getcwd(CWD, sizeof(CWD));
    //puts(CWD);
    char InputPath[1024];
    strcpy(InputPath,CWD);
    strcat(InputPath,"/");
    strcat(InputPath,"hotels-small");
    
    char OutputPath[1024];
    strcpy(OutputPath,CWD);
    strcat(OutputPath,"/");
    strcat(OutputPath,"dataset.txt");
    
    clock_t startTime = clock();
    unsigned long long size;
    FindTxt(InputPath, OutputPath,size);
    clock_t endTime = clock();
    double time = double(endTime - startTime)/CLOCKS_PER_SEC;
    //cout<<time<<endl;
    //cout<<"size is "<<size<<endl;

    BST BST;
    HashTable HT(size);
    ifstream inFile;
    inFile.open(OutputPath);
    if(!inFile){
        cout<<"Unable to open file";
        exit(1);
    }
    string x;
    clock_t start=clock();
    while( inFile >> x ){
        HT.insert(x);
        BST.insert(x);
    }
    clock_t end = clock();
    double time2 = double(end - start)/CLOCKS_PER_SEC;
    cout<<time2<<endl;
    inFile.close();
    cout<<"please enter instruction: "<<endl;
    while(1){
        string input;
        cin>>input;
        int n=0;
        for(int i=0; i<input.size(); i++)
            n = n + input[i] - '0';
        switch(n){
            case 1:{
                cout<<"find"<<endl;
                string s;
                cin>>s;
                clock_t startTime = clock();
                bool a=BST.search(s);
                clock_t endTime = clock();
                double time1 = double(endTime - startTime)/CLOCKS_PER_SEC;
                startTime = clock();
                bool b=HT.find(s);
                endTime = clock();
                double time2 = double(endTime - startTime)/CLOCKS_PER_SEC;
                if( a==1 && b==1)
                    cout<<"true"<<endl;
                else
                    cout<<"false"<<endl;
                cout<<"BST: "<<time1<<endl;
                cout<<"HashTable: "<<time2<<endl;
            }break;
            case 2:{
                cout<<"insert"<<endl;
                string s;
                cin>>s;
                clock_t startTime = clock();
                BST.insert(s);
                clock_t endTime = clock();
                double time1 = double(endTime - startTime)/CLOCKS_PER_SEC;
                startTime = clock();
                HT.insert(s);
                endTime = clock();
                double time2 = double(endTime - startTime)/CLOCKS_PER_SEC;
                cout<<"BST: "<<time1<<endl;
                cout<<"HashTable: "<<time2<<endl;
            }break;
            case 3:{
                cout<<"remove"<<endl;
                string s;
                cin>>s;
                clock_t startTime = clock();
                BST.deleteNode(s);
                clock_t endTime = clock();
                double time1 = double(endTime - startTime)/CLOCKS_PER_SEC;
                startTime = clock();
                HT.remove(s);
                endTime = clock();
                double time2 = double(endTime - startTime)/CLOCKS_PER_SEC;
                cout<<"BST: "<<time1<<endl;
                cout<<"HashTable: "<<time2<<endl;
            }break;
            case 4:{
                cout<<"sort"<<endl;
                string s;
                cin>>s;
                
                ofstream outfile;
                outfile.open(s);
                
                clock_t startTime = clock();
                BST.outputall(outfile);
                clock_t endTime = clock();
                double time1 = double(endTime - startTime)/CLOCKS_PER_SEC;
                
                outfile << endl;
                outfile << endl;
                
                startTime = clock();
                HT.outputall(outfile);
                endTime = clock();
                double time2 = double(endTime - startTime)/CLOCKS_PER_SEC;
                
                cout<<"BST: "<<time1<<endl;
                cout<<"HashTable: "<<time2<<endl;
            }break;
            case 5:{
                cout<<"range search"<<endl;
                string LB,UB;
                cin>>LB;
                cin>>UB;
                
                clock_t startTime = clock();
                BST.rangesearch(LB, UB);
                clock_t endTime = clock();
                double time1 = double(endTime - startTime)/CLOCKS_PER_SEC;
                
                cout<<endl<<endl;
                
                startTime = clock();
                HT.rangesearch(LB, UB);
                endTime = clock();
                double time2 = double(endTime - startTime)/CLOCKS_PER_SEC;
                
                cout<<"BST: "<<time1<<endl;
                cout<<"HashTable: "<<time2<<endl;
            }break;
            case 6:{
                cout<<"100 remove "<<endl;
                clock_t start = clock();
                for(int i=0; i<100; i++){
                    BST.deleteNode(S[i]);
                }
                clock_t end = clock();
                cout <<"BST: "<<double(end-start)/CLOCKS_PER_SEC<<endl;
                start = clock();
                for(int i=0; i<100; i++){
                    HT.remove(S[i]);
                }
                end = clock();
                cout <<"HT: "<<double(end-start)/CLOCKS_PER_SEC<<endl;
                
            }break;
            default:
                cout << "not valid! Reenter"<<endl<<endl;
        }
    }
}



