//
//  main.cpp
//  Binary Search Tree
//
//  Created by dali on 1/27/18.
//  CopyrigTFTree © 2018 dali. All rigTFTrees reserved.
//
#include <unistd.h>
#include <stdio.h>
#include<ctime>
#include<fstream>
#include <iostream>
#include "TwoFiveTree.h"
#include "FolderTraversal.h"
#include "AvlTree.h"
using namespace std;
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
    cout<<time<<endl;

    TwoFiveTree<string> TFTree;
    AVLTree<string> AVLTree;
    ifstream  inFile;
    inFile.open(OutputPath);
    if(!inFile){
        cout<<"Unable to open file";
        exit(1);
    }
    string x;
    clock_t start=clock();
    while( inFile >> x ){
        TFTree.insert(x);
        AVLTree.insert(x);
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
                bool a=AVLTree.search(s);
                clock_t endTime = clock();
                double time1 = double(endTime - startTime)/CLOCKS_PER_SEC;
                startTime = clock();
                bool b=TFTree.search(s);
                endTime = clock();
                double time2 = double(endTime - startTime)/CLOCKS_PER_SEC;
                if( a==1 && b==1)
                    cout<<"true"<<endl;
                else
                    cout<<"false"<<endl;
                cout<<"AVLTree: "<<time1<<endl;
                cout<<"TFTree: "<<time2<<endl;
            }break;
            case 2:{
                cout<<"insert"<<endl;
                string s;
                cin>>s;
                clock_t startTime = clock();
                AVLTree.insert(s);
                clock_t endTime = clock();
                double time1 = double(endTime - startTime)/CLOCKS_PER_SEC;
                startTime = clock();
                TFTree.insert(s);
                endTime = clock();
                double time2 = double(endTime - startTime)/CLOCKS_PER_SEC;
                cout<<"AVLTree: "<<time1<<endl;
                cout<<"TFTree: "<<time2<<endl;
            }break;
            case 3:{
                cout<<"remove"<<endl;
                string s;
                cin>>s;
                clock_t startTime = clock();
                AVLTree.remove(s);
                clock_t endTime = clock();
                double time1 = double(endTime - startTime)/CLOCKS_PER_SEC;
                startTime = clock();
                TFTree.remove(s);
                endTime = clock();
                double time2 = double(endTime - startTime)/CLOCKS_PER_SEC;
                cout<<"AVLTree: "<<time1<<endl;
                cout<<"TFTree: "<<time2<<endl;
            }break;
            case 4:{
                cout<<"sort"<<endl;
                string s;
                cin>>s;
                
                ofstream outfile;
                outfile.open(s);
                
                clock_t startTime = clock();
                AVLTree.outputall(outfile);
                clock_t endTime = clock();
                double time1 = double(endTime - startTime)/CLOCKS_PER_SEC;
                
                outfile << endl;
                outfile << endl;
                
                startTime = clock();
                TFTree.outputall(outfile);
                endTime = clock();
                double time2 = double(endTime - startTime)/CLOCKS_PER_SEC;
                
                cout<<"AVLTree: "<<time1<<endl;
                cout<<"TFTree: "<<time2<<endl;
            }break;
            case 5:{
                cout<<"range search"<<endl;
                string LB,UB;
                cin>>LB;
                cin>>UB;
                
                clock_t startTime = clock();
                AVLTree.rangesearch(LB, UB);
                clock_t endTime = clock();
                double time1 = double(endTime - startTime)/CLOCKS_PER_SEC;
                
                cout<<endl<<endl;
                
                startTime = clock();
                TFTree.rangesearch(LB, UB);
                endTime = clock();
                double time2 = double(endTime - startTime)/CLOCKS_PER_SEC;
                
                cout<<"AVLTree: "<<time1<<endl;
                cout<<"TFTree: "<<time2<<endl;
            }break;
            case 6:{
                cout<<"100 remove "<<endl;
                clock_t start = clock();
                for(int i=0; i<100; i++){
                    AVLTree.remove(S[i]);
                }
                clock_t end = clock();
                cout <<"AVL: "<<double(end-start)/CLOCKS_PER_SEC<<endl;
                start = clock();
                for(int i=0; i<100; i++){
                    TFTree.remove(S[i]);
                }
                end = clock();
                cout <<"TF: "<<double(end-start)/CLOCKS_PER_SEC<<endl;
                
            }break;
            default:
                cout << "not valid! Reenter"<<endl;
        }
    }
}



