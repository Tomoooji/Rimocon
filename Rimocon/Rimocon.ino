#include "Rimocon.h"
// ボタン,トグルスイッチ,可変抵抗,ジョイスティックの順に個数を指定
Rimocon<6,0,0,0> Sanaaase;

const uint8_t Pins[6] = {6,7,8,9,10,11};

void setup() {
  Sanaaase.buttons.attachAll(Pins);//Pins,NULL,NULL,NULL
}

void loop() {
  Sanaaase.buttons.readAll();
  Sanaaase.buttons.detectAll();
  delay(1000);
}
