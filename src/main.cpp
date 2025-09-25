#include <WiFi.h>
#include <HTTPClient.h>

// ===== WiFi config =====
const char* ssid = "๋Jccp";
const char* password = "jccp2kxi";

// ===== Telegram Bot config =====
String BOT_TOKEN = "8211974993:AAFgalBzOGkYBRcfnX0f2XGzikDDSZKWK2o";  // จาก BotFather
String CHAT_ID  = "7336407311";     // ตัวเลข Chat ID


// ===== ข้อมูล sensor จำลอง =====
String device_id = "ESP32_001";
float temperature = 28.5;
float humidity = 72.1;
float voltage = 3.17;

// ประกาศฟังก์ชันก่อนใช้งาน
void sendTelegramMessage();

void setup() {
  Serial.begin(115200);
  
  // เชื่อม WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected!");
  
  // ส่งข้อความ Telegram
  sendTelegramMessage();
}

void loop() {
  // ส่งทุก 1 นาที
  delay(60000);
  // อัปเดตข้อมูล sensor จริงได้ตรงนี้
  temperature += 0.1; // ตัวอย่างจำลอง
  humidity += 0.2;
  voltage += 0.01;
  sendTelegramMessage();
}

void sendTelegramMessage() {
  if(WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String message = "Device: " + device_id + "\n" +
                     "Temperature: " + String(temperature) + " °C\n" +
                     "Humidity: " + String(humidity) + " %\n" +
                     "Voltage: " + String(voltage) + " V";
                     
    String url = "https://api.telegram.org/bot" + BOT_TOKEN + "/sendMessage?chat_id=" + CHAT_ID + "&text=" + message;

    http.begin(url);
    int httpResponseCode = http.GET();
    if(httpResponseCode > 0) {
      Serial.println("Message sent successfully!");
    } else {
      Serial.print("Error sending message: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("WiFi Disconnected");
    
  }//dsfdfdfdffd
}
