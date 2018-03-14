//
//  TwoFiveTree.h
//  234 Tree
//
//  Created by dali on 2/23/18.
//  Copyright © 2018 dali. All rights reserved.
//
//#include <string>
#include <algorithm>    // std::swap
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>
#ifndef TwoFiveTree_h
#define TwoFiveTree_h
using namespace std;

template<class T>
class TwoFiveTree{
public:
    struct Node{
        Node(T E[], int  C[], int Oc, Node* p0, Node* p1, Node* p2, Node* p3, Node* p4){
            for(int i=0; i<4; i++){
                element[i] = E[i];
                counter[i] = C[i];
            }
            occupied = Oc;
            ptr[0] = p0;
            ptr[1] = p1;
            ptr[2] = p2;
            ptr[3] = p3;
            ptr[4] = p4;
            
        }
        Node(){
            for(int i=0; i<5; i++)
                ptr[i] = nullptr;
            for(int i=0; i<4; i++)
                counter[i] = 0;
        }
        
        T element[4];
        int occupied=0;
        int counter[4];
        Node* ptr[5];
    };
//-----------------------------------------------------------------------------------------------------------------------------------------------
    TwoFiveTree(){ root = new Node();}
    ~TwoFiveTree() { destroy(root); }
    void destroy(Node* root){
        if(root){
            for(int i=0 ; i< (root->occupied) + 1 ; i++){
                if(root->ptr[i])
                    delete root->ptr[i];
            }
        }
    }
//-----------------------------------------------------------------------------------------------------------------------------------------------
    void rangesearch(T LB, T UB){
        rangesearch_(LB,UB,root);
    }
    void rangesearch_(T LB, T UB, Node* root){
        if(root){
            int i=0;
            while(i < root -> occupied){
                rangesearch_(LB,UB,root->ptr[i]);
                if(root->element[i] >= LB && root->element[i] <= UB)
                    cout<<root->element[i]<<endl;
                i++;
            }
            rangesearch_(LB,UB,root->ptr[i]);
        }
    }
    void outputall(ofstream& OUT){
        outputall_(OUT, root);
    }
    void outputall_(ofstream& OUT, Node* root){
        if(root){
            int i=0;
            while(i < root -> occupied){
                outputall_(OUT,root->ptr[i]);
                OUT << root->element[i] <<"\n";
                i++;
            }
            outputall_(OUT,root->ptr[i]);
        }
    }
    void Traversal(Node* root){
        if(root){
            int i=0;
            while(i < root -> occupied){
                Traversal(root->ptr[i]);
                cout<< root->element[i] <<"   "<<root->counter[i]<<endl;
                i++;
            }
            Traversal(root->ptr[i]);
        }
    }
//-----------------------------------------------------------------------------------------------------------------------------------------------
    void remove(T e){
        Node* result = remove_(e, root);
        if(result == NULL){
            root = NULL;
        }
        else if(result -> occupied >= 1){
            root = result;
        }
        else
            root = result->ptr[0];
    }
    Node* remove_(T e,Node* root){
        if(root == NULL){
            return NULL;
        }
        int i=0;
        while(i<root->occupied){
            if(e == root->element[i])
            {
                root->counter[i]--;
                if(root->counter[i] > 0)
                    return root;
                if(root->ptr[0]){ // element is in internall node
                    Node* predecessor = root->ptr[i];
                    while(predecessor->ptr[0] != 0){
                        predecessor = predecessor->ptr[predecessor->occupied];
                    }
                    swap(root->element[i],predecessor->element[predecessor->occupied-1]);
                    swap(root->counter[i],predecessor->counter[predecessor->occupied-1]);
                    Node* returningPtr = remove_(e, root->ptr[i]);
                    if( returningPtr != root->ptr[i] ){    //说明 pointer field 的 ith pointer 降了一个层
                        root = Sink_Down_Fill_The_Hole(root,i,returningPtr);
                        return root;
                    }
                    else{
                        root->ptr[i] = returningPtr;
                        return root;
                    }
                }
                else{    //element is in the leaf
                    if(root->occupied>1){
                        for(int j=i+1; j<= root->occupied-1; j++){
                            root->element[j-1] = root->element[j];
                            root->counter[j-1] = root->counter[j];
                        }
                        root->occupied--;
                        return root;
                    }
                    else{  //if(root->occupied==1)
                        return NULL;
                    }
                }
            }
            else if( e < root->element[i]){
                Node* returningPtr = remove_(e, root->ptr[i]);
                if( returningPtr != root->ptr[i] ){    //说明 pointer field 的 ith pointer 降了一个层
                    root = Sink_Down_Fill_The_Hole(root,i,returningPtr);
                    return root;
                }
                else{
                    root->ptr[i] = returningPtr;
                    return root;
                }
            }
            i++;
        }
        Node* returningPtr = remove_(e, root->ptr[i]);
        if( returningPtr != root->ptr[i] ){    //说明 pointer field 的 ith pointer 降了一个层
            root = Sink_Down_Fill_The_Hole(root,i,returningPtr);
            return root;
        }
        else{
            root->ptr[i] = returningPtr;
            return root;
        }

    }
    
    Node* Sink_Down_Fill_The_Hole(Node* root,int i,Node* returningPtr){       //root 这个node 的 ith pointer 降了一个层
        if( i>=1 && i<= root->occupied){        //左边多， 挪到右边
            if( root->ptr[i-1]->occupied >1 ){    //siblings has more than two element: Rotation
                root->ptr[i]->element[0] = root->element[i-1];
                root->ptr[i]->counter[0] = root->counter[i-1];
                root->element[i-1] = root->ptr[i-1]->element[root->ptr[i-1]->occupied-1];
                root->counter[i-1] = root->ptr[i-1]->counter[root->ptr[i-1]->occupied-1];
                
                root->ptr[i]->ptr[1] = returningPtr;
                root->ptr[i]->ptr[0] = root->ptr[i-1]->ptr[ root->ptr[i-1] -> occupied ];
                root->ptr[i]->occupied = 1;
                root->ptr[i-1]->ptr[ root->ptr[i-1] -> occupied ] = NULL;
                root->ptr[i-1]->occupied--;
                return root;
            }
            else{   //i=0      //siblings has only one element, merge!
                root->ptr[i-1]->element[1] = root->element[i-1];
                root->ptr[i-1]->counter[1] = root->counter[i-1];
                root->ptr[i-1]->ptr[2] = returningPtr;
                for(int j=i-1; j >= 0 && j < root->occupied-1;j++){
                    root->element[j] = root->element[j+1];
                    root->counter[j] = root->counter[j+1];
                }
                for(int j=i; j <= root->occupied-1; j++){
                    root->ptr[j] = root->ptr[j+1];
                }
                root->ptr[root->occupied] = NULL;
                root->occupied--;
                root->ptr[i-1]->occupied++;
                if(root->occupied >= 1){
                    return root;
                }
                else{
                    root = root->ptr[0];
                    return root;
                }
            }
        }
        else{ // i=0
            if( root->ptr[1]->occupied > 1 ){    //siblings has more than two element: Rotation
                root->ptr[0]->element[0] = root->element[0];
                root->ptr[0]->counter[0] = root->counter[0];
                root->element[0] = root->ptr[1]->element[0];
                root->counter[0] = root->ptr[1]->counter[0];
                
                root->ptr[0]->ptr[0] = returningPtr;
                root->ptr[0]->ptr[1] = root->ptr[1]->ptr[0];
                for(int j=0; j<=root->ptr[1]->occupied-1; j++){
                    root->ptr[1]->element[j] = root->ptr[1]->element[j+1];
                    root->ptr[1]->counter[j] = root->ptr[1]->counter[j+1];
                    root->ptr[1]->ptr[j] = root->ptr[1]->ptr[j+1];
                }
                root->ptr[1]->ptr[ root->ptr[1] -> occupied ] = NULL;
                root->ptr[0]->occupied=1;
                root->ptr[1]->occupied--;
                return root;
            }
            else{    //sibling has one element merge!
                root->ptr[1]->element[1] = root->ptr[1]->element[0];
                root->ptr[1]->counter[1] = root->ptr[1]->counter[0];
                root->ptr[1]->element[0] = root->element[0];
                root->ptr[1]->counter[0] = root->counter[0];
                root->ptr[1]->occupied++;

                root->ptr[1]->ptr[2]=root->ptr[1]->ptr[1];
                root->ptr[1]->ptr[1]=root->ptr[1]->ptr[0];
                root->ptr[1]->ptr[0]=returningPtr;
                
                for(int i = 0; i < root->occupied; i++){
                    root->element[i] = root->element[i+1];
                    root->counter[i] = root->counter[i+1];
                    root->ptr[i] = root->ptr[i+1];
                }
                root->ptr[root->occupied] = NULL;
                root->occupied--;
                if(root->occupied >= 1){
                    return root;
                }
                else{
                    root = root->ptr[0];
                    return root;
                }
            }
        }
        
    }
//-----------------------------------------------------------------------------------------------------------------------------------------------
    bool search(T e){
        if(search_(e,root))
            return true;
        else
            return false;
    }
    
    Node* search_(T e, Node* root){
        if(root == NULL)
            return NULL;
        for(int i=0; i< root->occupied; i++){
            if( e == root->element[i] )
                return root;
        }
        int i=0;
        while( i < root->occupied ){
            if( e < root->element[i] ){
                break;
            }
            i++;
        }
        return search_(e, root->ptr[i]);
    }
//-----------------------------------------------------------------------------------------------------------------------------------------------
    void insert(T e){
        root = insert_(e, root);
    }

    Node* insert_(T e, Node* root){
        //1 say we recurse down to the deepest level then we pop back
        //2 We climb up the first level and get a returning pointer, if returning pointer is same as before, we are done;
        //3 If the returning pointer is different, we merge the returning pointer and the orignal pointer, and see if it will result in a change in upper level
        //4 It might produce a ripper effect: If the ripper effect does not reach root, we can still return root, if it does, we return it
        
        for(int i=0; i< root->occupied; i++){
            if(e == root->element[i]){
                root->counter[i]++;
                return root;
            }
        }
        if(root->ptr[0] == nullptr){   // inserting into a leaf
            T E[4];
            int C[4];
            E[0] = e;
            C[0] = 1;
            int OC = 1;
            Node* InsertingNode = new Node(E, C, OC, nullptr, nullptr, nullptr, nullptr, nullptr);
            Node* result = Merge_Split_If_Rich(root, InsertingNode);
            return result;
        }
        else{   // it is not a leaf
            int i=0;
            while(i<root->occupied){
                if(e < root->element[i])
                    break;
                i++;
            }
            Node* temp = insert_(e, root->ptr[i]);
            if(temp == root->ptr[i])
                return root;
            else
                return Merge_Split_If_Rich(root, temp);
            
        }
        
    }
    
    Node* Merge_Split_If_Rich(Node* Root_Original,Node* Root_Returning){
        T TempElement[5];            //for element
        int TempCounter[5];            //for count
        Node* TempPtr[6];          //storing pointer
        for(int i=0; i< 6; i++)
            TempPtr[i] = NULL;
        for(int i=0; i<= Root_Original->occupied; i++)
            TempPtr[i] = Root_Original->ptr[i];
        int TempOccupied = Root_Original->occupied + Root_Returning->occupied;
        T InsertingElement = Root_Returning->element[0];
        int InsertingCounter = Root_Returning->counter[0];
        for(int i=0; i<Root_Original->occupied; i++){
            TempElement[i] = Root_Original->element[i];
            TempCounter[i] = Root_Original->counter[i];
        }
        TempElement[Root_Original->occupied] = InsertingElement;
        TempCounter[Root_Original->occupied] = InsertingCounter;
        
        int i;//InsertingElementIndex
        for( i=TempOccupied-1; i>0 && TempElement[i] < TempElement[i-1]; i--){
            swap(TempElement[i-1],TempElement[i]);
            swap(TempCounter[i-1],TempCounter[i]);
        }
        for(int j=TempOccupied; j>i  ; j--){
            TempPtr[j] = TempPtr[j-1];
        }
        for(int j=0; j<i; j++){
        
        }
        TempPtr[i] = Root_Returning->ptr[0];
        TempPtr[i+1] = Root_Returning->ptr[1];
        
        if(TempOccupied == 5){
            T left1[4];
            int left2[4];
            T right1[4];
            int right2[4];
            for(int i=0; i<2; i++){
                left1[i] = TempElement[i];
                left2[i] = TempCounter[i];
            }
            for(int i=3; i<=4; i++){
                right1[i-3] = TempElement[i];
                right2[i-3] = TempCounter[i];
            }
            int OC=2;
            Node* L = new Node(left1,left2,OC,TempPtr[0],TempPtr[1],TempPtr[2],nullptr,nullptr);
            Node* R = new Node(right1,right2,OC,TempPtr[3],TempPtr[4],TempPtr[5],nullptr,nullptr);
            T parent1[4];
            int parent2[4];
            parent1[0]=TempElement[2];
            parent2[0]=TempCounter[2];
            OC=1;
            Node* parent = new Node(parent1, parent2, OC, L, R, nullptr, nullptr, nullptr);
            delete Root_Original;
            return parent;
        }
        else{
            for(int i=0; i<TempOccupied; i++){
                Root_Original->element[i] = TempElement[i];
                Root_Original->counter[i] = TempCounter[i];
                Root_Original->ptr[i] = TempPtr[i];
            }
            Root_Original->ptr[TempOccupied] = TempPtr[TempOccupied];
            Root_Original->occupied++;
            return Root_Original;
        }
    }
//-----------------------------------------------------------------------------------------------------------------------------------------------

    

    Node* root;
    
};

#endif /* TwoFiveTree_h */
