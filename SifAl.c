#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// DEgisiklik deneme

// Sifreleme islevi
void encrypt(char *text, int key)
{
    int i;
    for (i = 0; i < strlen(text); i++)
    {
        text[i] += key;
    }
}

// Sifre cozme islevi
void decrypt(char *text, int key)
{
    int i;
    for (i = 0; i < strlen(text); i++)
    {
        text[i] -= key;
    }
}

int main()
{
    FILE *input_file, *output_file;
    char input_filename[50], output_filename[50], buffer[1000];
    int key, choice;

    printf("Lutfen sifrelemek istediginiz metin dosyasinin adini girin: ");
    scanf("%s", input_filename);

    printf("Sifreli metni yazmak istediginiz dosyanin adini girin: ");
    scanf("%s", output_filename);

    printf("Sifreleme anahtarini girin: ");
    scanf("%d", &key);

    // Dosyayi okuma modunda ac
    input_file = fopen(input_filename, "r");
    if (input_file == NULL)
    {
        printf("Hata: Girdi dosyasi acilamadi!\n");
        return 1;
    }

    // Dosyayi yazma modunda ac
    output_file = fopen(output_filename, "w");
    if (output_file == NULL)
    {
        printf("Hata: Cikis dosyasi acilamadi!\n");
        fclose(input_file);
        return 1;
    }

    // Dosyadan oku, sifrele ve diger dosyaya yaz
    while (fgets(buffer, sizeof(buffer), input_file) != NULL)
    {
        encrypt(buffer, key);
        fprintf(output_file, "%s", buffer);
    }

    // Dosyalari kapat
    fclose(input_file);
    fclose(output_file);

    printf("Dosya basariyla sifrelendi ve '%s' adli dosyaya yazildi.\n", output_filename);

    printf("Sifreli metni cozmek istiyor musunuz? (Evet: 1 / Hayir: 0): ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        // Dosyayi okuma modunda tekrar ac
        output_file = fopen(output_filename, "r");
        if (output_file == NULL)
        {
            printf("Hata: Dosya acilamadi!\n");
            return 1;
        }

        printf("Sifreleme anahtarini girin: ");
        scanf("%d", &key);

        // Dosyayi oku, coz ve ekrana yaz
        printf("Cozulen metin:\n");
        while (fgets(buffer, sizeof(buffer), output_file) != NULL)
        {
            decrypt(buffer, key);
            printf("%s", buffer);
        }

        // Dosyayi kapat
        fclose(output_file);
    }

    return 0;
}