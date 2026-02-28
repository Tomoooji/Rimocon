#include "Rimocon.h"
// ボタン,トグルスイッチ,可変抵抗,ジョイスティックの順に個数を指定
Rimocon<6,0,0,0> Sanaaase;
//Array<Button, bool, 1> oneButton;
//Array<Volume, int, 1> oneButton;

//const uint8_t Pins[6] = {6,7,8,9,10,11};

void setup() {
  oneButton.attachAll({6});//Pins,NULL,NULL,NULL
}

void loop() {
  oneButton.readAll();
  oneButton.detectAll();
  delay(1000);
}
