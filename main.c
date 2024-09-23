#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(){

    

    int p1[2];  //pipe p0 -> p1
    int p2[2];  //pipe p0 -> p2
    if(pipe(p1) == -1 || pipe(p2) == -1){
        printf("create pipe error");
        return 2;
    }

    int pid1, pid2, pid3; 
    
    //child 1
    pid1 = fork();
    
    //child 2
    if(pid1 != 0){
        pid2 = fork();
    }
    
    //child 3
    if(pid1 != 0 && pid2 != 0){
        pid3 = fork();
    }

    if(pid1 == -1 || pid2 == -1 || pid3 == -1){
        printf("fork error \n");
        return 1;
    }

    if(pid1 == 0){  //Child 1
        
        close(p2[0]);
        close(p1[1]);
        close(p2[1]);

        //Recebendo Numero de P0
        int number1;
        if(read(p1[0], &number1, sizeof(number1)) == -1){
            printf("read number ERROR !!!\n");
            return 2;
        }
        printf("this number (x) is %d \n", number1);
        
        //Recebendo string de P0
        int tamanho =0;
        char str[200];
        if(read(p1[0], &tamanho, sizeof(int)) == -1){
            printf("read str ERROR !!!\n");
            return 2;
        }
        if(read(p1[0], str , sizeof(char)*tamanho ) == -1){
            printf("read str ERROR !!!\n");
            return 2;
        }
        printf("String received in Child 1:%s\n", str);






        close(p1[0]);




    }else if(pid2 == 0){    //child 2
        close(p1[0]);
        close(p1[1]);
        close(p2[1]);
        
        int number1;
        if(read(p2[0], &number1, sizeof(number1)) == -1){
            printf("read number ERROR !!!\n");
            return 2;
        }
        printf("this number (y) is %d \n", number1);

        //Recebendo string de P0
        int tamanho =0;
        char str[200];
        if(read(p2[0], &tamanho, sizeof(int)) == -1){
            printf("read str ERROR !!!\n");
            return 2;
        }
        if(read(p2[0], str , sizeof(char)*tamanho ) == -1){
            printf("read str ERROR !!!\n");
            return 2;
        }
        printf("String received in Child 2:%s\n", str);



        close(p2[0]);


    }else if(pid3 == 0){    //Child 3
        close(p2[0]);
        close(p1[1]);
        close(p2[1]);
        close(p1[0]);




    }else{                      //parent
        close(p1[0]);
        close(p2[0]);
        
        char x[3];
        char y[3];
        int number1;  //x
        int number2;  //y

    
        printf("Digite um numero entre 1-5\n");
        scanf("%s",x);
        number1 = atoi(x);
        if( number1 < 1 || number1 > 5 ) {
            printf("invalid input number:%d\n", number1);
            exit(1);
        }

        printf("Digite um numero entre 6-10\n");
        scanf("%s",y);
        number2 = atoi(y);
        if( number2 < 6 || number2 > 10 ) {
            printf("invalid input number:%d\n", number2);
            exit(1);
        }

        //enviando valor de x (P0 -> P1)
        if(write(p1[1], &number1, sizeof(number1)) == -1){
            printf("write x for p1 ERROR!!! \n");
            return 2;
        }
        
        //enviando valor de y (P0 -> P2)
        if(write(p2[1], &number2, sizeof(number2)) == -1){
            printf("write y for p1 ERROR!!! \n");
            return 2;
        }

        //enviando string (P0 -> P1)
        char str[] = "Meu filho, crie e envie para o seu irmão P3 um array de tamanho randômico entre 100 e 200, preenchido completamente com o valor X";
        str[strlen(str) - 1] = x[0];
        //printf("%s\n", str);

        int tamanho = strlen(str) +1;
        if(write(p1[1], &tamanho, sizeof(int)) == -1){
            printf("write str for p1 ERROR!!! \n");
            return 2;
        }
        if(write(p1[1], str, sizeof(char) *tamanho ) == -1){
            printf("write str for p1 ERROR!!! \n");
            return 2;
        }

        //enviando string (P0 -> P2)
        str[strlen(str) - 1] = y[0];
        //printf("%s\n", str);

        if(write(p2[1], &tamanho, sizeof(int)) == -1){
            printf("write str for p1 ERROR!!! \n");
            return 2;
        }
        if(write(p2[1], str, sizeof(char) *tamanho ) == -1){
            printf("write str for p1 ERROR!!! \n");
            return 2;
        }


        close(p1[1]);
        close(p2[1]);
        wait(NULL);

    }
    

    return 0;
}