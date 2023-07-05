#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(){
    char buf[1024];
    printf("Nhap vao Chuoi ki tu\n");
    fgets(buf, sizeof(buf), stdin);
    unsigned int len=strlen(buf)-1;
    
    if(len<1024) 
    buf[len]=0;
    
    for(int i = 0; buf[i]; i++){
    buf[i] = tolower(buf[i]);
}

    float *prob=calloc(128, sizeof(float));

    for (int i = 0; buf[i]; i++){
        int j = (int) buf[i];
        prob[j]+=(1.0/len);
    }

    for (int i = 97; i<128; i++){
        printf("%f\n",prob[i]);
}

    

}