#include "RF24.h"
#include <SPI.h>
#include <ezButton.h>
#include "esp_bt.h"
#include "esp_wifi.h"

// Define radios for HSPI and VSPI
SPIClass *sp = nullptr;
SPIClass *hp = nullptr;

RF24 radio1(16, 15, 16000000);   // HSPI
RF24 radio2(22, 21, 16000000);  // VSPI

// Hopping array and variables
byte hopping_channel[] = {32, 34, 46, 48, 50, 52, 0, 1, 2, 4, 6, 8, 22, 24, 26, 28, 30, 74, 76, 78, 80, 82, 84, 86};
byte ptr_hop = 0;

unsigned int flag = 0;
unsigned int flagv = 0;
int ch = 45;
int ch1 = 45;

// Button setup
ezButton toggleSwitch(33);

void two() {
  if (flagv == 0) {
    ch1 += 4;
  } else {
    ch1 -= 4;
  }

  if (flag == 0) {
    ch += 2;
  } else {
    ch -= 2;
  }

  if ((ch1 > 79) && (flagv == 0)) {
    flagv = 1;
  } else if ((ch1 < 2) && (flagv == 1)) {
    flagv = 0;
  }

  if ((ch > 79) && (flag == 0)) {
    flag = 1;
  } else if ((ch < 2) && (flag == 1)) {
    flag = 0;
  }

  radio1.setChannel(ch);
  radio2.setChannel(ch1);
}

void one() {
  radio1.setChannel(random(80));
  radio2.setChannel(random(80));
  delayMicroseconds(random(60));
}

void RF() {
  radio2.begin();
  radio2.startConstCarrier(RF24_PA_MAX, 45);
  radio2.setDataRate(RF24_250KBPS);
}

void initSP() {
  sp = new SPIClass(VSPI);
  sp->begin();
  if (radio2.begin(sp)) {
    Serial.println("SP Started !!!");
    radio2.setAutoAck(false);
    radio2.stopListening();
    radio2.setRetries(0, 0);
    radio2.setPALevel(RF24_PA_MAX, true);
    radio2.setDataRate(RF24_250KBPS);
    radio2.setCRCLength(RF24_CRC_DISABLED);
    radio2.printPrettyDetails();
    radio2.startConstCarrier(RF24_PA_MAX, ch1);
  } else {
    Serial.println("SP couldn't start !!!");
  }
}

void initHP() {
  hp = new SPIClass(HSPI);
  hp->begin();
  if (radio1.begin(hp)) {
    Serial.println("HP Started !!!");
    radio1.setAutoAck(false);
    radio1.stopListening();
    radio1.setRetries(0, 0);
    radio1.setPALevel(RF24_PA_MAX, true);
    radio1.setDataRate(RF24_250KBPS);
    radio1.setCRCLength(RF24_CRC_DISABLED);
    radio1.printPrettyDetails();
    radio1.startConstCarrier(RF24_PA_MAX, ch);
  } else {
    Serial.println("HP couldn't start !!!");
  }
}

void setup() {
  Serial.begin(115200);

  // Disable unnecessary modules
  esp_bt_controller_deinit();
  esp_wifi_stop();
  esp_wifi_deinit();
  esp_wifi_disconnect();

  toggleSwitch.setDebounceTime(50);

  // Initialize radios
  initHP();
  initSP();
}

void loop() {
  toggleSwitch.loop();

  int state = toggleSwitch.getState();
  if (state == HIGH) {
    two(); // Perform channel hopping logic
  } else {
    one(); // Randomize channels
  }

  // Perform hopping for radio2
  ptr_hop++;
  if (ptr_hop >= sizeof(hopping_channel)) ptr_hop = 0;
  radio2.setChannel(hopping_channel[ptr_hop]);
}
