#ifndef RIMOCON_H
#define RIMOCON_H

#include <Arduino.h>
#include "Parts.h"

#ifndef BUTTON_NUM
  #define BUTTON_NUM 1
#endif
#ifndef TOGGLE_NUM
  #define TOGGLE_NUM 1
#endif
#ifndef VOLUME_NUM
  #define VOLUME_NUM 1
#endif
#ifndef JOYSTICK_NUM
  #define JOYSTICK_NUM 1
#endif

template<int BUTTON = BUTTON_NUM, int TOGGLE = TOGGLE_NUM, int VOLUME = VOLUME_NUM, int JOYSTICK = JOYSTICK_NUM>
class Rimocon{
  private:
    static constexpr int BTN = BUTTON;
    static constexpr int TGL = TOGGLE;
    static constexpr int VLM = VOLUME;
    static constexpr int JSTK = JOYSTICK;

  public:
    Rimocon(){}
    ~Rimocon(){}
    //bool attach(uint8_t pinAll[]); // やりたくないとは言わないがだるすぎる 
      bool attachButton(uint8_t pins[]);
      bool attachVolume(uint8_t pins[]);
      bool attachToggle(uint8_t pin1s[], uint8_t pin2s[]);
      bool attachJoystick(uint8_t pinXs[], uint8_t pinYs[], uint8_t pinBtns[]);

    void readAll();
      void readButtons();
      void readToggles();
      void readVolumes();
      void readJoysticks();

    void detectAll();
      void buttonPushed();
      void toggleFliped();
      void volumeMoved();
      void joystickTilted();
      void joystickPushed();

    Button buttons[BTN];
    Toggle toggles[TGL];
    Volume volumes[VLM];
    Joystick joysticks[JSTK];

    bool resultBtn[];
    int resultTgl[];
    int resultVlm[];
    Polar resultJstkTilte[];
    bool resultJstkPush[];

};

#endif