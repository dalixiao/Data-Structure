//
//  FolderTraversal.h
//  Binary Search Tree
//
//  Created by dali on 2/7/18.
//  Copyright © 2018 dali. All rights reserved.
//
#include<string>
#include<stdio.h>
#include<cstdlib>
#include<iostream>
#include<string.h>
#include<fstream>
#include<dirent.h>
#include<ctime>
#ifndef FolderTraversal_h
#define FolderTraversal_h


using namespace std;

string stopwords[127] = { "i", "me", "my", "myself", "we", "our", "ours", "ourselves", "you", "your", "yours", "yourself", "yourselves", "he", "him", "his", "himself", "she", "her", "hers", "herself", "it", "its", "itself", "they", "them", "their", "theirs", "themselves", "what", "which", "who", "whom", "this", "that", "these", "those", "am", "is", "are", "was", "were", "be", "been", "being", "have", "has", "had", "having", "do", "does", "did", "doing", "a", "an", "the", "and", "but", "if", "or", "because", "as", "until", "while", "of", "at", "by", "for", "with", "about", "against", "between", "into", "through", "during", "before", "after", "above", "below", "to", "from", "up", "down", "in", "out", "on", "off", "over", "under", "again", "further", "then", "once", "here", "there", "when", "where", "why", "how", "all", "any", "both", "each", "few", "more", "most", "other", "some", "such", "no", "nor", "not", "only", "own", "same", "so", "than", "too", "very", "s", "t", "can", "will", "just", "don", "should", "now" };

bool validWord(string& str){
    bool flag = false;
    for(int i=0; i<str.size();i++){
        if(isalpha(str[i]))
            flag = true;
        if  ( !(isalpha(str[i]) || str[i]=='_' || str[i] == '-' ||  ispunct(str[i]) ) )
            return false;
        if(isupper(str[i]))
            str[i]=tolower(str[i]);
    }
    for(int i=0; i<127; i++){
        if(str == stopwords[i]){
            //cout<<"fuck"<<endl;
            return false;
        }
    }
    if(flag == true)
        return true;
    else
        return false;
}
void FindTxt(char* path, char* OutputPath, unsigned long long &count){
    ofstream outFile(OutputPath);
    DIR *pDIR;
    struct dirent *entry;
    if( (pDIR=opendir(path)) ){
        while( (entry = readdir(pDIR)) != NULL){
            if( strcmp(entry->d_name,".")==0 || strcmp(entry->d_name,"..")==0 || strcmp(entry->d_name,".DS_Store")==0 )
                continue;
            
            if(entry->d_type == DT_REG){
                char * subpath = (char *) malloc(2 + strlen(path)+ strlen(entry->d_name) );
                strcpy(subpath, path);
                strcat(subpath,"/");
                strcat(subpath, entry->d_name);
                //cout<<subpath<<endl;
                ifstream inFile;
                inFile.open(subpath);
                string x;
                while(inFile >> x){
                    if(validWord(x)){
                        count++;
                        outFile<<x;
                        outFile<<" ";
                    }
                }
                
                
            }
            if(entry->d_type == DT_DIR){
                char * subpath = (char *) malloc(2 + strlen(path)+ strlen(entry->d_name) );
                strcpy(subpath, path);
                strcat(subpath,"/");
                strcat(subpath, entry->d_name);
                //cout<<subpath<<endl;
                FindTxt(subpath,OutputPath,count);
            }
        }
    }
}



#endif /* FolderTraversal_h */
