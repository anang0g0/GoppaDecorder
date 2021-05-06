#include "global.h"
#include "struct.h"
#include "chash.c"




void main(){
    arrayul aa={0};

    while(1){
        aa=chash();
        printf("%d\n",aa.t[0]);
    }

}