
#include <SPI.h>
#include <RF24.h>

#define NRF_CE   27
#define NRF_CSN  13
#define NRF_SCK  33
#define NRF_MOSI 14
#define NRF_MISO 32

// Paket
struct __attribute__((packed)) Packet {
  uint32_t seq;
  int32_t  lat_e7;
  int32_t  lon_e7;
  uint16_t speed_dkmh;
  uint8_t  sats;
  uint8_t  fix;
};

RF24 radio(NRF_CE, NRF_CSN);
const uint8_t ADDR[6] = "FRIS1";

void setup() {
  Serial.begin(115200);
  SPI.begin(NRF_SCK, NRF_MISO, NRF_MOSI, NRF_CSN);
  if (!radio.begin(&SPI)) { Serial.println("nRF24 nicht gefunden!"); while (true) delay(1000); }
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(108);
  radio.openReadingPipe(1, ADDR);
  radio.startListening();
  Serial.println("# Receiver bereit");
  Serial.println("seq,fix,lat,lon,speed_kmh,sats");
}

void loop() {
  if (radio.available()) {
    Packet p;
    radio.read(&p, sizeof(p));
    Serial.printf("%lu,%u,%.7f,%.7f,%.1f,%u\n", p.seq, p.fix,
                  p.lat_e7 / 1e7, p.lon_e7 / 1e7, p.speed_dkmh / 10.0, p.sats);
  }
}
