#include "global.h"
#include "struct.h"
#include "chash.c"




int main(){
    arrayul aa={0};
    int count=0,i;

    while(1){
        aa=chash();
        for(i=0;i<NN/16;i++){
        print_uint128(aa.z[i]);
        printf(" ");
    }
        printf("\n");
        //printf("%llu %llu\n",aa.u[0],aa.u[1]);
        count++;
        if(count==10000)
        break;
    }

return 0;
}