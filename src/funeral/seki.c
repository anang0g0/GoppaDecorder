unsigned long long int seki(unsigned long long int a ,unsigned long long int b){
unsigned long long int c=0;

while(a!=0){
if ((a & 1)==1)
c^=b;

b<<=1; a>>=1;
}

return c;
}

main(){
    unsigned long long int u=0;
    u=seki(0b101010101010101010101111111,0b111111111100000000001111111111);

    printf("f=%llu\n",u);
}


