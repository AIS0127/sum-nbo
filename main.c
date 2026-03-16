#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <arpa/inet.h>


int main(int argc, char * argv[]){
    FILE *f;
    if( argc < 2 ){
        printf("syntax : sum-nbo <file1> [<file2>...]\n");
        return -1;
    }

    uint32_t *data = (uint32_t *)malloc((argc - 1) * sizeof(uint32_t));
     
    for( int i = 1; i < argc; i++ ){
        f = fopen(argv[i], "r");
        if ( !f ){
            printf("error : failed to open %s\n", argv[i]);
            return -1;
        }
        
        if ( fseek(f, 0, SEEK_END) == -1){
            fclose(f);
            printf("error : failed to seek %s\n", argv[i]);
            return -1;
        }
        if( ftell(f) < 4 ){
            fclose(f);
            printf("error : size of file < 4\n");
            return -1;
        }else{
            if ( fseek(f, 0, SEEK_SET) == -1){
                fclose(f);
                printf("error : failed to seek %s\n", argv[i]);
                return -1;
            }
        }
        
        if( !fread(&data[i - 1], sizeof(uint32_t), 1,f) ){
            fclose(f);
            printf("error : failed to read %lu in %s\n",sizeof(uint32_t), argv[i]);
            return -1;
        }else{
            data[i - 1] = ntohl(data[i - 1]);
            fclose(f);
        }
    }

    uint32_t sum = 0;

    for( int i = 1; i < argc; i ++){
        printf("%d(0x%08x)", data[i - 1], data[i - 1]);        
        sum += data[i - 1];
        if ( i != argc-1 ){
            printf(" + ");
        }else{
            printf(" = ");
        }
    }
    printf("%d(0x%08x)", sum, sum);        
}