# (物理)リモコン用ライブラリ
ユニバーサル基板などの上にスイッチや可変抵抗を配置して作成した物理リモコンからの入力をまとめて管理するためのライブラリです(個々のパーツのみでも使用可能)。
## 対応機器
タクトスイッチ、2接点トグルスイッチ、可変抵抗、ジョイスティック
## 使い方
1. 自作物理リモコンの制御に使う場合
``` Arduino
#include <Rimocon>

int num_button = 2;
int num_toggle = 2;
int num_volume = 2;
int num_joysitck = 1;

Rimocon<num_button,
        num_toggle,
        num_volume,
        num_joysitck> MyRimocon;

bool attachFlag = true;

void setup(){
  attachFlag = attachFlag && Rimocon.buttons.attach(

  );
  attachFlag = attachFlag && Rimocon.toggles.attach(

  );
  attachFlag = attachFlag && Rimocon.volumes.attach(

  );
  attachFlag = attachFlag && Rimocon.joysitcks.attach(
    
  );

}

void loop(){
}
```
2. 各パーツ単体で使う場合
``` Arduino
#include <Parts>

Button Botan1;
Toggle Toguru1;
Volume KahenTeikou1;
Joystick YougiBou1;

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