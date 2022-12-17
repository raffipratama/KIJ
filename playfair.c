#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void choice_fill();
char encryption(char []);
void decryption(char []);
void play_fair();
char key[100], play[5][5], ct[255], msg[255], plain_text[255], c_text[255];
int main(){
    int i, choice, flag=0, j, k, size;
    printf("\n --- play Fair Cipher ---\n");
    printf("Enter plain text :");
    scanf("%[^\n]", msg);
    size=strlen(msg);
    size=strlen(msg);
    int count = 0;
    for (i=0; msg[i]; i++)
    if (msg[i]!=' ')
        msg[count++]==msg[i];
    msg[count]='\0';
    for (i=0; i<size; i+=2){
        if(msg[i]==msg[i+1])
        {
            for(j=size; j>i; j--)
            {
                msg[j]=msg[size-1];
                size--;
            }
            msg[j+1]='x';
        }
    }
    size=strlen(msg);
    if(size%2!=0)
    {
        msg[size]='x';
        msg[size+1]='\0';
    }
    printf("\n plaintext after space remove : %s", msg);
    printf("\n message for enryption is : ");
    for(i=0,j=0; msg[i];i++){
        putchar(msg[i]);
        if(i%2!=0)
        printf(" ");
    }
    encryption(msg);
}

char encryption(char pt[]){
    int i, j, k, l, r1,r2, c1, c2, p, q;
    printf("\n Plain text : %s",pt);
    play_fair();
    j=1;
    for(i=0; i<strlen(pt);){
        r1=0;r2=0;c1=0;c2=0;p=0;q=0;
        p=pt[i]; q=pt[j]; printf("\t ");
        putchar(pt[i]); putchar(pt[j]);
        printf("=");
        if(p=='j')
            pt[i]='i';
        if(q=='j')
            pt[i]='i';
        for(k=0; k<5;k++){
            for(l=0; l<5;l++){
                if(play[k][l]==p)
                    r1=k;c1=l;
                if(play[k][l]==q)
                    r2=k;c2=l;
            }
        }
        if(r1==r2){
            ct[i]=play[r1][(c1+1)%5];
            ct[j]=play[r2][(c2+1)%5];
            putchar(ct[i]);
            putchar(ct[j]);
        }
        else if(c1==c2){
            ct[i]=play[(r1+1)%5][c1];
            ct[j]=play[(r2+1)%5][c2];
            putchar(ct[i]);
            putchar(ct[j]);
        }
        else{
            ct[i]=play[r1][c2];
            ct[j]=play[r2][c1];
            putchar(ct[i]);putchar(ct[j]);
        }
        i=i+2;
        j=j+2;
    }
    printf("\n\n \tEncrypted msg is : %s\n",ct);
    return ct;
}

void play_fair(){
    int i, k, j,x, y, size;
    printf("\n enter key: ");
    scanf("%s", key);
    strcat(key,"abcdefghiklmnopqrstuvwxyz");
    size=strlen(key);
    for(i=0; i<size; i++){
        if(key[i]=='j'){key[i]='i';}
        for(j=i+1; j<size;){
            if(key[j]==key[i]){
                for(k=j; k<size; k++){
                    key[k]=key[k+1];}
                size--;
            }
            else j++;}
    }
        for(i=0,k=0; i<5;i++){
            for(j=0; j<5;j++){
                play[i][j]=key[k];
                k++;
            }
        }
        for(x=0;x<5;x++){
            for(y=0;y<5;y++){
                printf(" ");
                putchar(play[x][y]);
            }
            printf("\n");
        }
} 
