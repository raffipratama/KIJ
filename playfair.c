#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char encryption(char []);
void play_fair();
char key[100], play[5][5], ct[255], msg[255], plain_text[255], c_text[255];
int main(){
    int i, choice, flag=0, j, k, size;
    printf("\n --- Playfair Cipher Encryption ---\n");
    printf(" Masukkan Plain Text : ");
    scanf("%[^\n]", msg);

    //menghilangkan spasi pada msg
    size=strlen(msg);
    int count = 0;
    for (i = 0; i < size; i++)
	if (msg[i] != ' ')//menyimpan string yang tidak menganding spasi ' '
		msg[count++] = msg[i];
	msg[count] = '\0';
    printf("\n  Plain text setelah dihapus spasi : %s", msg);
    
    //menginputka aturan playfair pada msg
    for (i=0; i<size; i+=2){
        if(msg[i]==msg[i+1])
        {
            for(j=size; j>i; j--)
            {
                msg[j]=msg[size-1];
                size--;
            }
            msg[j+1]='x'; //x untuk huruf kembar
        }
    }
    size=strlen(msg);
    if(size%2!=0)
    {
        msg[size]='z';//z untuk huruf terakhir dengan jumlah kata ganjil
        msg[size+1]='\0';
    }
    printf("\n Plaintext setelah dikenai aturan playfair : %s", msg);
    
    printf("\n Pasangan huruf yang akan dienkripsikan : ");
    for(i=0,j=0; msg[i];i++){
        putchar(msg[i]);
        if(i%2!=0)
        printf(" ");
    }
    encryption(msg);
}

char encryption(char pt[]){
    int i, j, k, l, r1,r2, c1, c2, p, q;

    //membuat matriks key
    play_fair();
    j=1;
    for(i=0; i<strlen(pt);){
        r1=0;r2=0;c1=0;c2=0;p=0;q=0;

        //menyimpan huruf pertama pada p dan huruf kedua pada q
        p=pt[i]; q=pt[j]; printf("\t ");
        putchar(pt[i]); putchar(pt[j]);
        printf("=");
        
        //membandingkan p dengan q

        //apabila salah satu huruf = j maka dijadikan huruf i
        if(p=='j')
            pt[i]='i';
        if(q=='j')
            pt[i]='i';

        //mencari huruf pada key
        for(k=0; k<5;k++){
            for(l=0; l<5;l++){
                if(play[k][l]==p)
                    {r1=k;c1=l;}
                if(play[k][l]==q)
                    {r2=k;c2=l;}
            }
        }

        //apabila koordinat r1==r2 maka lokasi ciphertext adalah ((c1&c2)+1)%5
        if(r1==r2){
            ct[i]=play[r1][(c1+1)%5];
            ct[j]=play[r2][(c2+1)%5];
            putchar(ct[i]);
            putchar(ct[j]);
        }
        //apabila koordinat c1==c2 maka lokasi ciphertext adalah ((r1&r2)+1)%5
        else if(c1==c2){
            ct[i]=play[(r1+1)%5][c1];
            ct[j]=play[(r2+1)%5][c2];
            putchar(ct[i]);
            putchar(ct[j]);   
        }
        //sisanya menukar lokasi c1 dengan c2 dan r1 dengan r2
        else{
            ct[i]=play[r1][c2];
            ct[j]=play[r2][c1];
            putchar(ct[i]);
            putchar(ct[j]);
        }
        //melanjutkan huruf berikutnya
        i=i+2;
        j=j+2;
    }
    //print keseluruhan encryption text
    printf("\n\n \tPesan yang dienkripsikan : %s\n",ct);
    return ct;
}

void play_fair(){
    //algoritma untuk menyiapkan key
    int i, k, j,x, y, size;

    //menginputkan key
    printf("\n Masukkan kunci : ");
    scanf("%s", key);

    //dasar huruf key yang digunakan (pengecualian huruf j)
    strcat(key,"abcdefghiklmnopqrstuvwxyz");
    size=strlen(key);

    //pembuatan key
    for(i=0; i<size; i++){

        //menyimpan key j menjadi i
        if(key[i]=='j'){
        key[i]='i';}

        //menyimpan satu key apabila key yang ditemukan sama
        for(j=i+1; j<size;){
            if(key[j]==key[i]){
                for(k=j; k<size; k++){
                    key[k]=key[k+1];}
                size--;
            }
            else j++;}
    }
        //menyimpan key pada matriks play
        for(i=0,k=0; i<5;i++){
            for(j=0; j<5;j++){
                play[i][j]=key[k];
                k++;
            }
        }
        //print matriks key
        for(x=0;x<5;x++){
            for(y=0;y<5;y++){
                printf(" ");
                putchar(play[x][y]);
            }
            printf("\n");
        }
} 
