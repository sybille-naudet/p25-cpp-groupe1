#include <iostream>
#include chrono

int fibo_rec(int n){
if (n==0)
    return 0;

if (n==1)
    return 1;
return fibo_rec()+fibo_rec()

}