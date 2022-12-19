# Tugas Kelompok KIJ E 
1. Muhammad Nevin - 05111940000079
2. Muhammad Rayhan Rafii Pratama - 05111940000110
3. Aflah Hilmy - 05111940000177

# Enkripsi Playfair Cipher
## A. Penjelasan Soal
Playfair cipher merupakan teknik enkripsi simetris dengan menggunakan grid huruf 5x5.
Berikut peraturan yang digunakan pada playfair cipher : 
Key matriks tidak boleh memiliki huruf yang sama. Key berbentuk matriks 5x5. Dimana pada awal huruf diinputkan kata atau telah ditentukan kata sebelumnya.

Plaintext di enkripsikan berdasarkan 2 kelompok huruf. Spasi dihapuskan pada text. Apabila terdapat kedua huruf yang sama maka ditambahkan huruf bogus’X’, contoh: (RAFFI, maka menjadi paket huruf (RA FX FI)). Apabila kata memiliki jumlah huruf ganjil maka ditambahkan huruf bogus ‘Z’ di akhir, contoh: (API, maka menjadi (AP IZ).
Berikutnya adalah cara mengenkripsikan plaintext : apabila terdapat pasangan huruf yang memiliki koordinat x atau y yang sama maka ditambahkan 1 posisi mod 5 (pada koordinat yang tidak sama). Contoh DZ menjadi MF dan OS menjadi QT. Lalu apabila berbeda maka menukar lokasi koordinat x dan y masing2 pasangan huruf plaintext. Contoh BT menjadi DQ, dan KL menjadi GY.
## 2. Code dan Comment
Dimulai pada main dimana disini diinputkan plaintext, menyesuaikan plaintext dengan playfair rule, dan membagi plaintext menjadi pasangan huruf.

```c
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
  
   //menginputkan aturan playfair pada msg
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
```

Berikutnya terdapat fungsi encryption untuk mengenkripsikan plaintext. Pada fungsi ini pertama direquestkan kunci matriks pada fungsi play_fair dan mengenkripsikan text. 
```c
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
```

Lalu yang terakhir merupakan fungsi play_fair untuk membuat key matriks 5x5
```c
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
```

## 3. Operasional
1. Jalankan code pada compiler

2. Inputkan plaintext

3. Inputkan key

# Enkripsi dan Dekripsi AES-EBC
## 1. Penjelasan Soal
AES (Advanced Encryption Standard) adalah standar enkripsi simetris ditetapkan oleh US NIST (National Institute of Standards and Technology) pada 2001. Enkripsi ini menggantikan DES (Data Encryption Standard) yang dikenalkan pada 1977. Enkripsi ini menggunakan key yang sama untuk proses enkripsi dan dekripsi. Pada tahap awal enkripsi, key yang digunakan akan dilakukan transformasi KeyExpansion, yaitu proses penurunan key yang berukuran 16 bytes menjadi berukuran 176 bytes. Hal ini untuk menyediakan key yang cukup untuk setiap tahapan transformasi.
AES bekerja dengan menggunakan 4 jenis transformasi:
1. SubBytes, berfungsi untuk menukar isi dari byte dengan menggunakan tabel substitusi.
2. ShiftRows, merupakan proses pergeseran blok per baris pada state array.
3. MixColumns, proses pengacakan di masing-masing state array
4. AddRoundKey, mengkombinasikan state array dan round key dengan bitwise XOR.
Proses transformasi diatas dilakukan secara berulang. Perulangan dilakukan 10 kali untuk key 16 bytes, 12 kali untuk 24 bytes dan 14 kali untuk key 32 bytes. Khusus pada perulangan terakhir transformasi MixColumns tidak dilakukan

ECB (Electronic codebook) merupakan salah satu mode operasi block cipher yang paling simpel. Metode ini membagi isi pesan menjadi beberapa blok dan mengenkripsi blok-blok tersebut secara terpisah


## 2. Code dan Comment
1. Code diawali dengan validasi nilai key yang harus memiliki panjang bytes senilai 16, 24, atau 32. Bila tidak valid, maka program berhenti. Bila valid, maka akan dilanjutkan ke tahap key expansion.
[](snapcode/code.png)
[](snapcode/1.png)
	

2. Tahap ekspansi key diawali dengan konversi nilai key ke dalam bentuk matrix untuk membentuk four-word round key (16 byte) menggunakan function text2matrix. Selanjutnya dihasilkan linear array lainnya sejumlah 4 * jumlah ronde sesuai pada pemetaan dict round_number. Word pada index kelipatan 4, dihasilkan linear array dari operasi xor nilai atasnya (index-4), nilai sbox, dan nilai rcon. Sedangkan pada index lainnya dihasilkan dari operasi xor nilai atasnya dan nilai sebelumnya (index-1). Terus dilakukan hingga didapatkan nilai round key dengan panjang 4 + (4 * round_number)
[](snapcode/2.png)
[](snapcode/2_1.png)

3. Pada tahap enkripsi, nilai plaintext dilakukan konversi ke matrix untuk membentuk four-word round key (16 byte) menggunakan function text2matrix. Plain text yang terlah dikonversi selanjutnya dilakukan operasi __add_round_key. Lalu dilakukan operasi iterasi __round_encrypt yang terdiri dari __sub_bytes, __shift_rows, __mix_columns, __add_round_key. Begitu pula bila akan melakukan dekripsi, yang pada iterasi __round_decrypt nya terdiri dari __add_round_key, __inv_mix_columns, __inv_shift_rows, dan __inv_sub_bytes yang memiliki operasi yang sama namun terbalik.
[]("snapcode/3_1.png")
[](snapcode/3_2.png)
[](snapcode/3_3.png)


4. Pada tahap round_encrypt, dilakukan perulangan sebanyak 10/12/14 kali bergantung pada ukuran dari key untuk proses transformasi sub_bytes, shift_rows, add_round_key, dan mix_columns
[](snapcode/4_1.png)
[](snapcode/4_2.png)

5. Pada tahap sub_bytes, dilakukan subtitusi pada setiap bytes dengan nilai pada S-box pada baris x dan kolom y yang sama
[](snapcode/4_3.png)

6. Pada tahap shift_rows, dilakukan pergeseran posisi bit menjadi ke kirinya, untuk bit paling kiri digeser ke posisi paling kanan
[](snapcode/4_4.png)

7. Pada tahap add_round_key, dilakukan proses pengoperasian bitwise XOR pada round key dengan plaintext
[](snapcode/4_5.png)

8. Pada tahap mix_columns dilakukan tranformasi untuk mengubah nilai pada tiap matriks dengan operasi XOR pada nilai dirinya dan pada nilai indeks kanannya (index+1)%4. Formula mix_columns adalah dengan menggunakan metode xtime. Xtime adalah fungsi yang melakukan shift left lalu melakukan operasi XOR dengan nilai 27 dan selanjutnya dioperasikan AND dengan nilai 255. Pada operasi xtime dilakukan apabila nilai plaintext memiliki panjang 16 bytes, jika tidak maka nilai plaintext akan di shift left satu bit.
[](snapcode/4_6.png)





## 3. Operasional
Ganti key yang digunakan pada variabel master_key

Ganti plaintext yang ingin dienkripsi pada variabel plaintext

Jalankan code pada compiler


