#include "Rimocon.h"
// ボタン,トグルスイッチ,可変抵抗,ジョイスティックの順に個数を指定
Rimocon<> Sanaaase;
//<6,0,0,0>
//const uint8_t Pins[6] = {6,7,8,9,10,11};
//bool results[6];
bool result[1];

const uint8_t btn[]={10};
const uint8_t tgl[]={9,11};
const uint8_t vlm[]={A0};
const uint8_t jstk[]={A1,A2,12};

void setup() {
  Sanaaase.attach(btn, tgl, vlm, jstk);//Pins,NULL,NULL,NULL
}

void loop() {
  Sanaaase.readAll();
  Sanaaase.detectAll(result,NULL,NULL,NULL,NULL);
}
