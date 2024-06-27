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
