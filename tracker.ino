// FrisTracker - SENDER (ESP32-PICO-V3-02 + NEO-6M + nRF24L01+PA+LNA)
// Libraries: "RF24" (TMRh20), "TinyGPSPlus" (Mikal Hart)
#include <SPI.h>
#include <RF24.h>
#include <TinyGPSPlus.h>


#define NRF_CE   27
#define NRF_CSN  13
#define NRF_SCK  33
#define NRF_MOSI 14
#define NRF_MISO 32
#define GPS_RX   26   // GPS-TX  -> ESP RX
#define GPS_TX   25   // GPS-RX  <- ESP TX

// Paket
struct __attribute__((packed)) Packet {
  uint32_t seq;
  int32_t  lat_e7;     // Grad * 1e7
  int32_t  lon_e7;
  uint16_t speed_dkmh; // km/h * 10
  uint8_t  sats;
  uint8_t  fix;
};

RF24 radio(NRF_CE, NRF_CSN);
TinyGPSPlus gps;
const uint8_t ADDR[6] = "FRIS1";
uint32_t seq = 0, lastSend = 0;

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, GPS_RX, GPS_TX);
  SPI.begin(NRF_SCK, NRF_MISO, NRF_MOSI, NRF_CSN);
  if (!radio.begin(&SPI)) { Serial.println("nRF24 nicht gefunden!"); while (true) delay(1000); }
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(108);
  radio.setRetries(5, 5);
  radio.openWritingPipe(ADDR);
  radio.stopListening();
  Serial.println("Tracker bereit");
}

void loop() {
  while (Serial2.available()) gps.encode(Serial2.read());

  if (millis() - lastSend >= 1000) {   // 1 Hz (NEO-6M Standard)
    lastSend = millis();
    Packet p;
    p.seq = seq++;
    p.fix = gps.location.isValid() ? 1 : 0;
    p.lat_e7 = (int32_t)(gps.location.lat() * 1e7);
    p.lon_e7 = (int32_t)(gps.location.lng() * 1e7);
    p.speed_dkmh = (uint16_t)(gps.speed.kmph() * 10);
    p.sats = gps.satellites.isValid() ? gps.satellites.value() : 0;
    bool ok = radio.write(&p, sizeof(p));
    Serial.printf("seq=%lu fix=%u sats=%u %s\n", p.seq, p.fix, p.sats, ok ? "gesendet" : "kein ACK");
  }
}
