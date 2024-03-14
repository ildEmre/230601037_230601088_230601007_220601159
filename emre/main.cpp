#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// XOR şifreleme veya şifre çözme fonksiyonu
void encryptDecrypt(const vector<char>& input, const vector<char>& key, vector<char>& output){
    output.resize(input.size());
    for (size_t i = 0; i < input.size(); ++i) {
        output[i] = input[i] ^ key[i % key.size()]; 
    }
}

int main(){
    int secim = 0;
    while(secim != 1 && secim != 2 && secim != 3){
        cout << "1. Dosya sifrele." << endl;
        cout << "2. Sifrelenmis dosyayi coz." << endl;
        cout << "3. Girilecek metni sifrele." << endl;
        cout << "Seciminizi giriniz: ";
        cin >> secim;
        if(secim != 1 && secim != 2 && secim != 3){
            cout << "Gecersiz secim. Lutfen tekrar deneyiniz." << endl;
        }
        else
            break;
    }
    if(secim == 1){
        // metin şifreleme
        string dosyaIsim;
        cout << "Sifrelemek istediginiz dosyanin ismini giriniz: (orn: text.txt): ";
        cin >> dosyaIsim;
        ifstream inputDosya(dosyaIsim);
        if (!inputDosya.is_open()) {
            cout << "Dosya bulunamadi." << endl;
            return 0;
        }

        // tüm text dosyasını okuyup vektör dizisine ata
        vector<char> normalMetin(istreambuf_iterator<char>(inputDosya), {});

        inputDosya.close();
        vector<char> key = {'a', 'n', 'a', 'h', 't', 'a', 'r'}; // şifreleme işlemi için anahtar oluştur

        // XOR şifrelemesi kullanarak dosya'yı şifreleme
        vector<char> sifrelenmisMetin;
        encryptDecrypt(normalMetin, key, sifrelenmisMetin);

        //şifrelenmiş dosyayı aktarmak için bir output file oluştur
        string sifrelenmisDosyaIsim;
        cout << "Sifrelenmis metni aktarmak icin bir dosya ismi giriniz(Ornek: dosya.txt): ";
        cin >> sifrelenmisDosyaIsim;
        ofstream outputDosya(sifrelenmisDosyaIsim);
        if (!outputDosya.is_open()) {
            cout << "Output dosyasi acilamadi." << endl;
            return 0;
        }

        // şifrelenmiş dosyayı output dosyasına yaz
        outputDosya.write(sifrelenmisMetin.data(), sifrelenmisMetin.size());

        outputDosya.close();

        cout << "Sifreleme basarili. Sifrelenmis metin " << dosyaIsim << " dosyasina yazildi." << endl;
    } else if(secim == 2){
        // şifrelenmiş txt dosyasını çözme
        string sifrelenmis;
        cout << "Cozmek istediginiz dosyanin ismini giriniz(Ornek: dosya.txt): ";
        cin >> sifrelenmis;
        ifstream inputDosya(sifrelenmis);
        if (!inputDosya.is_open()) {
            cout << "Cozmek istediginiz metin bulunamadi veya acilamadi." << endl;
            return 0;
        }

        // tüm dosyayı okuyup vektör dizisine ata
        vector<char> sifrelenmisMetin(istreambuf_iterator<char>(inputDosya), {});
        
        inputDosya.close();

        vector<char> key = {'a', 'n', 'a', 'h', 't', 'a', 'r'}; // şifre çözme anahtarını belirle

        // XOR şifrelemesi kullanarak şifrelenmiş metni çöz
        vector<char> cozulmusMetin;
        encryptDecrypt(sifrelenmisMetin, key, cozulmusMetin);

        // cozulmus metni yazmak için bir output file oluştur veya bul
        string outputDosyaIsim;
        cout << "Cozulmus metni yazmak icin bir dosya adi giriniz(Ornek: dosya.txt):";
        cin >> outputDosyaIsim;
        ofstream outputDosya(outputDosyaIsim);
        if(!outputDosya.is_open()){
            cout << "Dosya acilamadi." << endl;
            return 0;
        }

        // çözülmüş metni output file'a yaz
        outputDosya.write(cozulmusMetin.data(), cozulmusMetin.size());
        outputDosya.close();

        cout << "Sifre cozme basarili. Cozulmus metin " << outputDosyaIsim << " dosyasina yazildi." << endl;
    } 
    else if(secim == 3){
        string input;
        cout << "Sifrelemek istediginiz metni giriniz: ";
        cin.ignore();
        getline(cin, input);
        vector <char> normalMetin(input.begin(), input.end());
        vector<char> key = {'a', 'n', 'a', 'h', 't', 'a', 'r'};
        vector<char> sifrelenmisMetin;
        encryptDecrypt(normalMetin, key, sifrelenmisMetin);
        cout << "Sifreleme basarili. Sifrelenmis veriyi saklamak icin dosya ismi giriniz(Ornek: Dosya.txt): ";
        string dosyaIsim;
        cin >> dosyaIsim;
        ofstream outputDosya(dosyaIsim);
        if(!outputDosya.is_open()){
            cout << "Dosya acilamadi." << endl;
            return 0;
        }
        outputDosya.write(sifrelenmisMetin.data(), sifrelenmisMetin.size());
        outputDosya.close();
        cout << "Basarili. Sifrelenmis veri " << dosyaIsim << " dosyasina yazildi." << endl;
    }
    else{
        cout << "Gecersiz secim." << endl;
    }

    return 0;
}
