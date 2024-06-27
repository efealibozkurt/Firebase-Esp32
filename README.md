# ESP32 ile Firebase Kullanımı

Bu proje, ESP32 mikrodenetleyicisini kullanarak sensör verilerini Firebase Realtime Database'e göndermeyi ve Firebase'den veri almayı gösterir. Proje, temel olarak ESP32 ve Firebase entegrasyonunu anlamaya ve kullanmaya yöneliktir.

## Gereksinimler

- ESP32 Geliştirme Kartı
- Arduino IDE
- Firebase Hesabı
- Firebase Realtime Database

## Kurulum

### Arduino IDE'nin Ayarlanması

1. **ESP32 Kartını Arduino IDE'ye Ekleyin:**
   - Arduino IDE'yi açın.
   - `Dosya` > `Tercihler` yolunu izleyin.
   - "Ekstra Kart Yöneticisi URL'leri" alanına şu URL'yi ekleyin: `https://dl.espressif.com/dl/package_esp32_index.json`
   - `Araçlar` > `Kart` > `Kart Yöneticisi` yolunu izleyin.
   - "esp32"yi arayın ve ESP32 kartlarını yükleyin.

2. **Gerekli Kütüphaneleri Yükleyin:**
   - `Araçlar` > `Kütüphane Yöneticisi` yolunu izleyin.
   - "FirebaseESP32" ve "ArduinoJson" kütüphanelerini arayın ve yükleyin.

### Firebase'in Ayarlanması

1. **Firebase Projesi Oluşturun:**
   - [Firebase Console](https://console.firebase.google.com/) adresine gidin.
   - Yeni bir proje oluşturun ve proje yapılandırmasını tamamlayın.

2. **Realtime Database Ayarları:**
   - Firebase Console'da `Database` sekmesine gidin.
   - `Realtime Database`'i etkinleştirin ve veritabanı URL'sini not edin.

3. **ESP32 için API Anahtarı ve Veritabanı URL'si:**
   - Firebase Console'da `Project Settings` > `Service accounts` > `Database secrets` yolunu izleyin.
   - Bir API anahtarı oluşturun ve not edin.

## Kod

```cpp
#include <WiFi.h>
#include <FirebaseESP32.h>

// WiFi Ayarları
#define WIFI_SSID "your_wifi_ssid"
#define WIFI_PASSWORD "your_wifi_password"

// Firebase Ayarları
#define FIREBASE_HOST "your_firebase_database_url"
#define FIREBASE_AUTH "your_firebase_database_secret"

FirebaseData firebaseData;

void setup() {
  Serial.begin(115200);

  // WiFi Bağlantısı
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("WiFi'ye bağlanılıyor...");
  }
  Serial.println("WiFi'ye bağlandı!");

  // Firebase Bağlantısı
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

void loop() {
  // Veri Gönderme
  if (Firebase.setInt(firebaseData, "/sensor/temperature", 25)) {
    Serial.println("Veri gönderildi!");
  } else {
    Serial.println("Veri gönderilemedi!");
    Serial.println(firebaseData.errorReason());
  }

  delay(2000);
}
