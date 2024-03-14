#include <stdio.h>
// Lineer sifreleme icin sifreleme algoritmasi fonksiyonu
void sifrele(char *metin, int anahtar)
{
    int i;
    for (i = 0; metin[i] != '\0'; ++i)
    {
        if (metin[i] >= 'a' && metin[i] <= 'z')
        {
            metin[i] = 'a' + (metin[i] - 'a' + anahtar) % 26;
        }
        else if (metin[i] >= 'A' && metin[i] <= 'Z')
        {
            metin[i] = 'A' + (metin[i] - 'A' + anahtar) % 26;
        }
    }
}
// Lİneer sifreleme icin sifre cozme algoritması fonksiyonu
void sif_coz(char *metin, int anahtar)
{
    int i;
    for (i = 0; metin[i] != '\0'; ++i)
    {
        if (metin[i] >= 'a' && metin[i] <= 'z')
        {
            metin[i] = 'a' + (metin[i] - 'a' - anahtar + 26) % 26;
        }
        else if (metin[i] >= 'A' && metin[i] <= 'Z')
        {
            metin[i] = 'A' + (metin[i] - 'A' - anahtar + 26) % 26;
        }
    }
}

int main()
{
    FILE *nor_dos, *sif_dos; // Dosya isimleri pointer ile tanimlanmis
    char nor_dos_ad[100], sif_dos_ad[100], bilgi[1000];
    int anahtar, secim;

    printf("Lutfen sifrelenecek txt dosyasinin adi: ");
    scanf("%s", nor_dos_ad);

    printf("Lutfen sifreleme anatarini girin: ");
    scanf("%d", &anahtar);

    // Sifrelenecek metnin alinacaği dosya aciliyor
    nor_dos = fopen(nor_dos_ad, "r");
    if (nor_dos == NULL)
    {
        printf("Hata: Dosya acilamadi.\n");
        return 1;
    }

    // Metin dosyadan okunuyor
    int i = 0;
    while ((bilgi[i] = fgetc(nor_dos)) != EOF)
    {
        i++;
    }
    bilgi[i] = '\0'; // Stringin sonuna Null terminator

    // Dosya kapa
    fclose(nor_dos);

    // Dosyanın icindeki metin sifreleniyor
    sifrele(bilgi, anahtar);

    printf("Sifrelenmis metnin yazilacagi dosya adini girin: ");
    scanf("%s", sif_dos_ad);

    // Sifreli metnin yazılacagı dosya aciliyor
    sif_dos = fopen(sif_dos_ad, "w");
    if (sif_dos == NULL)
    {
        printf("Hata: Dosya acilamadi.\n");
        return 1;
    }

    // Sifreli metin dosyaya yaziliyor
    fprintf(sif_dos, "%s", bilgi);

    // Dosya kapaniyor
    fclose(sif_dos);

    printf("Sifrelenmis metin '%s' adli dosyaya yazildi.\n", sif_dos_ad);

    // Kullanici sifreli metni cozmek isityor mu?
    printf("Sifrelenmis metni cozmek isityor musunuz? (Evet: 1 / Hayir: 0): ");
    scanf("%d", &secim);

    if (secim == 1)
    {
        // Sifrelenmis metni coz
        sif_coz(bilgi, anahtar);

        // Cozulmus metni yazdir
        printf("Metin:\n%s\n", bilgi);
    }

    return 0;
}