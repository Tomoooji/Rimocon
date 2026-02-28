#ifndef RIMOCON_H
#define RIMOCON_H

#include <Arduino.h>
#include "Parts.h"

/////////////////////////////////

template <class Objtype, typename Valtype, int NUM = 1>
struct Array{
  Array(){}
  Objtype objects[NUM];
  Valtype states[NUM];
  Valtype changes[NUM];

  bool attachAll(uint8_t pins[], int pinnum = 1){
    bool is_succesed;
    if(pinnum>1){
      for(int i; i<NUM; i++){
        uint8_t pins_[pinnum];
        for(int j; j<pinnum; j++) {pins_[j] = pins[i*pinnum+j];}
        is_succesed = is_succesed && objects[i].attach(pins_);
      }
    }
    else{
      for(int i; i<NUM; i++){
        is_succesed = is_succesed && objects[i].attach(pins[i]);
      }
    }
    return is_succesed;
  }
  void readAll(){
    for(int i=0; i<NUM; i++) this->objects[i].read();
  }
  const Valtype (&getAll() const)[NUM]{
    for(int i=0; i<NUM; i++){
      this->states[i] = this->objects[i].get();
    }
    return this->states;
  }
  const Valtype (&detectAll())[NUM]{
    for(int i=0; i<NUM; i++){
      this->changes[i] = this->objects[i].detect();
    }
    return this->changes;
  }
};

/////////////////////////////////

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

/////////////////////////////////

template<int BUTTON = BUTTON_NUM, int TOGGLE = TOGGLE_NUM, int VOLUME = VOLUME_NUM, int JOYSTICK = JOYSTICK_NUM>
struct Rimocon{
  private:
    static constexpr int BTN = BUTTON;
    static constexpr int TGL = TOGGLE;
    static constexpr int VLM = VOLUME;
    static constexpr int JSTK = JOYSTICK;
  public:
    Rimocon(){}
    Array<Button,bool,BTN> buttons;
    Array<Volume,int,VLM> volumes;
    Array<Toggle,int,TGL> toggles;
    Array<Joystick,Polar,JSTK> joysticks;
};

#endif