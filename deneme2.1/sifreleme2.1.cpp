#include <stdio.h>
#include <stdlib.h>

#define KEY 10 //Sifremede kullanilacak kaydirma miktari sabit bir deger olarak KEY=10 olarak belirlenmis oldu

void encryptFile(FILE *inputFile, FILE *outputFile) { //sifreleme fonksiyonu
    char ch;
    while ((ch = fgetc(inputFile)) != EOF) {
        ch = ch + KEY; //her karakter 10 art?r?ld?
        fputc(ch, outputFile); 
    }
}

void decryptFile(FILE *inputFile, FILE *outputFile) { //sifre cozme fonksiyonu
    char ch;
    while ((ch = fgetc(inputFile)) != EOF) {
        ch = ch - KEY;
        fputc(ch, outputFile);
    }
}

int main() {
    FILE *inputFile, *outputFile;
    char inputFileName[100], outputFileName[100];
    int secim; //kullan?c?n?n yaomak istedigi islem icin

    printf("Dosya adini girin: ");
    scanf("%s", inputFileName);

    inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        printf("Dosya acilamadi!");
        exit(1);
    }

    printf("Sifrelenmis dosya adini girin: ");
    scanf("%s", outputFileName); //inputFileName orjinal dosyamiz ve yaptigimiz degisikliklerden etkilenmesini istemedigimiz icin 
								// bburda girilen degeri yeni bir dosyaya atamis olduk
    outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        printf("Dosya acilamadi!");
        fclose(inputFile);
        exit(1);
    }

    printf("1- Sifrele \n2- Sifreyi Coz \n Seciminizi yapin: ");
    scanf("%d", &secim);

    switch (secim) { //secime g?re yap?lacak islemler tan?mland?
        case 1:
            encryptFile(inputFile, outputFile);
            printf("Dosya sifrelendi.\n");
            printf("SIFRE--> %d/n",KEY);
            break;
        case 2:
            decryptFile(inputFile, outputFile);
            printf("Dosya cozuldu.\n");
            break;
        default:
            printf("Gecersiz secim!\n");
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
