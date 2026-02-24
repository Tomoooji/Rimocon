#include "Rimocon.h"
// ボタン,トグルスイッチ,可変抵抗,ジョイスティックの順に個数を指定
Rimocon<6,0,0,0> Sanaaase;
//<6,0,0,0>
const uint8_t Pins[6] = {6,7,8,9,10,11};

void setup() {
  Sanaaase.attachButton(Pins);//Pins,NULL,NULL,NULL
}

void loop() {
  Sanaaase.readAll();
  Sanaaase.detectAll();
  delay(1000);
}
