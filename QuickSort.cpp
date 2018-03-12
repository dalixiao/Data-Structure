//
//  quick_sort.cpp
//  quick sort
//
//  Created by dali on 11/4/17.
//  Copyright © 2017 dali. All rights reserved.
//
#include <string>
#include <iostream>

using namespace std;

int partition(int a[], int n, int pivotIndex){
    int pivot = a[pivotIndex];
    int LB=1;
    int Unknown=1;
    while(Unknown < n){
        if(a[Unknown] <= pivot){
            swap(a[Unknown],a[LB]);
            LB++;
        }
        Unknown++;
    }
    swap(a[0],a[LB-1]);
    return LB-1;
}

void quicksort(int a[], int n){
    if(n==1 || n==0)
        return;
    int M = partition(a,n,0);
    quicksort(a,M+1);
    quicksort(&a[M+1],n-(M+1));
}

int main() {
    int n=7;
    int a[10] = {10, 80, 30, 90, 40, 50, 70};
    quicksort(a, n);
    for(int i=0; i<n; i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
}
