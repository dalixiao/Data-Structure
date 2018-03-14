//
//  quicksort.h
//  Binary Search Tree
//
//  Created by dali on 2/8/18.
//  Copyright © 2018 dali. All rights reserved.
//

#ifndef quicksort_h
#define quicksort_h
#include <string>
#include <vector>

int partition(vector<string>& arr, int L, int R){
    string pivot=arr[L];
    int j=L;
    for(int i=L+1; i<=R;i++){
        if(arr[i]<pivot){
            swap(arr[j+1],arr[i]);
            j++;
        }
    }
    swap(arr[L],arr[j]);
    return j;
}


void __quicksort(vector<string>& arr,int L,int R){
    if(L<R){
        int a = partition(arr,L,R);
        __quicksort(arr, L, a-1);
        __quicksort(arr, a+1, R);
    }
}


void quicksort(vector<string>& arr){
    __quicksort(arr,0,arr.size()-1);
}

#endif /* quicksort_h */
