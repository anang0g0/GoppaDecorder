#include "global.h"
#include "struct.h"
#include "chash.c"




void main(){
    arrayul aa={0};
    int count=0;

    while(1){
        aa=chash();
        print_uint128(aa.z);
        //printf("%llu %llu\n",aa.u[0],aa.u[1]);
        count++;
        if(count==10000)
        break;
    }

}