# (物理)リモコン用ライブラリ
ユニバーサル基板などの上にスイッチや可変抵抗を配置して作成した物理リモコンからの入力をまとめて管理するためのライブラリです(個々のパーツのみでも使用可能)。
## 対応機器
タクトスイッチ、2接点トグルスイッチ、可変抵抗、ジョイスティック
## 使い方
1. 自作物理リモコンの制御に使う場合
``` Arduino
#include <Rimocon>

// 各パーツの数は明記することを推奨します
int num_button = 2;
int num_toggle = 2;
int num_volume = 2;
int num_joysitck = 1;
// ピン配列は1つが複数ピン使う場合も一次元の配列としてください
uint8_t pins_button[num_button];
uint8_t pins_toggle[num_toggle];
uint8_t pins_volume[num_volume];
uint8_t pins_joysitck[num_joysitck];

//<>のところの改行は必須ではないです(データ型の一部みたいなもんです)。
Rimocon<num_button,
        num_toggle,
        num_volume,
        num_joysitck> myRimocon;

//使えないピン使ってたりしたらわかるようにしとくと良いと思います。
bool attachFlag = true;

void setup(){
    // 複数形なのでs付けるのをお忘れなく
  attachFlag = attachFlag && myRimocon.buttons.attach(pins_button);
  attachFlag = attachFlag && myRimocon.toggles.attach(pins_toggle);
  attachFlag = attachFlag && myRimocon.volumes.attach(pins_volume);
  attachFlag = attachFlag && myRimocon.joysitcks.attach(pins_joysitck);

}

void loop(){
}
```
2. 各パーツ単体で使う場合
``` Arduino
#include <Parts>

Button myButton;
Toggle myToggle;
Volume myVolume;
Joystick myJstk;

void setup(){

}

void loop(){

}
```

3. 1種類のパーツのみを複数扱う場合 (1.のリモコンを用いた運用も可能)
``` Arduino
#include <Rimocon>

void setup(){

}

void loop(){

}
```

#
### memos:
- I want to add "mode" (includes switchMode function) to buttons
- should be 0 if it isn't used

- Maybe I shoud choose making another class from button... (because of readAll/getAll/detectAll functions)

- swithch from constructor of Toggle and Joystick

---
- I also need to make Timer class (or something like that)...