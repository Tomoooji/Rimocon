#include "Rimocon.h"

bool Rimocon::attachButton(uint8_t pins[]){
  uint8_t pinId = 0;
  for(Button& btn: this->buttons){
    btn.attach(pins[pinId]);
    pinId+=1;
  }
}

bool Rimocon::attachVolume(uint8_t pins[]){
  uint8_t pinId = 0;
  for(volume& vlm: this->volumes){
    vlm.attach(pins[pinId]);
    pinId+=1;
  }
}

bool Rimocon::attachToggle(uint8_t pin1s[], uint8_t pin2s[]){
  uint8_t pinId = 0;
  for(Toggle& tgl: this->toggles){
    tgl.attach(pin1s[pinId*2], pin2s[pinId*2+1]);
    pinId+=2;
  }
}

bool Rimocon::attachJoystick(uint8_t pinXs[], uint8_t pinYs[], uint8_t pinBtns[]){
  uint8_t pinId = 0;
  for(Joystick& : this->joystick){
    tgl.attach(pinXs[pinId*3], pinYs[pinId*3+1], pinBtns[pinId*3+1]);
    pinId+=3;
  }
}

void Rimocon::readAll(){
  this->readButtons();
  this->readToggles();
  this->readVolumes();
  this->readJoysticks();
}

void Rimocon::readButtons(){
  for(Button& btn: this->buttons){
  //for(int btn_id; btn_id < BTN; btn_id++){
    btn.readState();
  }
}
void Rimocon::readToggles(){
  for(Toggle& tgl: this->toggles){
  //for(int tgl_id; tgl_id < TGL*2; tgl_id++){
    tgl.readState();
  }
}
void Rimocon::readVolumes(){
  for(Volume& vlm: this->volumes){
  //for(int vlm_id; vlm_id < VLM; vlm_id++){
    vlm.readValue();
  }
}
void Rimocon::readJoysticks(){
  for(Joystick& jstk: this->joysticks){
  //for(int jstk_id; jstk_id < JSTK*3; jstk_id++){
    jstk.readAll();
  }
}


void Rimocon::detectAll(){
  this->buttonPushed();
  this->toggleFliped();
  this->volumeMoved();
  this->joystickTilted();
  this->joystickPushed();
};

void Rimocon::buttonPushed(){
  uint8_t btnId = 0;
  for(Button& btn: this->buttons){
    this->resultBtn[btnId] = btn.isPushed();
    btnId += 1;
  }
}

void Rimocon::toggleFliped(){
  uint8_t tglId = 0;
  for(Toggle& tgl: this->toggles){
    this->resultTgl[tglId] = tgl.isFliped();
    tglId += 1;
  }
}

void Rimocon::volumeMoved(){
  uint8_t vlmId = 0;
  for(Volume& vlm: this->volumes){
    this->resultVlm[vlmId] = vlm.isMoved();
    vlmId += 1;
  }
}

void Rimocon::joystickTilted(){
  uint8_t jstkId = 0;
  for(Joystick& jstk: this->joysticks){
    this->resultJstkTilte[jstkId] = jstk.isTilted();
    jstkId += 1;
  }
}

void Rimocon::joystickPushed(){
  uint8_t jstkId = 0;
  for(Joystick& jstk: this->joysticks){
    this->resultJstkPush[jstkId] = jstk.isPushed();
    jstkId += 1;
  }
}
