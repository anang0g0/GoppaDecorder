#include "global.h"
#include "struct.h"
#include "chash.c"




void main(){
    arrayul aa={0};
    int count=0;

    while(1){
        aa=chash();
        printf("%llu\n",aa.z);
        count++;
        if(count==10000)
        break;
    }

}