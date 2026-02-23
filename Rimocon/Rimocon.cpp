/*
#include "Rimocon.h"

bool Rimocon::attach(uint8_t pinBtn[], uint8_t pinTgl[], uint8_t pinVlm[], uint8_t pinJstk[]){
  bool is_succesed;
  if(pinBtn != NULL){
    for(int btn_id; btn_id < BTN; btn_id++){
      is_succesed = is_succesed && this->buttons[btn_id].attach(pinBtn[btn_id]);
    }
  }
  if(!is_succesed) return false; 
  if(pinTgl != NULL){
    for(int tgl_id; tgl_id < TGL*2; tgl_id++){
      is_succesed = is_succesed && this->toggles[tgl_id].attach(pinTgl[tgl_id*2], pinTgl[tgl_id*2+1]);
    }
  }
  if(!is_succesed) return false; 
  if(pinVlm != NULL){
    for(int vlm_id; vlm_id < VLM; vlm_id++){
      is_succesed = is_succesed && this->volumes[vlm_id].attach(pinVlm[vlm_id]);
    }
  }
  if(!is_succesed) return false; 
  if(pinJstk != NULL){
    for(int jstk_id; jstk_id < JSTK*3; jstk_id++){
      is_succesed = is_succesed && this->joysticks[jstk_id].attach(pinJstk[jstk_id*3], pinJstk[jstk_id*3+1], pinJstk[jstk_id*3+2]);
    }
  }
  return is_succesed; 
}

void Rimocon::readAll(){
  this->readButtons();
  this->readToggles();
  this->readVolumes();
  this->readJoysticks();
}

void Rimocon::readButtons(){
  for(int btn_id; btn_id < BTN; btn_id++){
    buttons[btn_id].readState();
  }
}
void Rimocon::readToggles(){
  for(int tgl_id; tgl_id < TGL*2; tgl_id++){
    this->toggles[tgl_id].readState();
  }
}
void Rimocon::readVolumes(){
  for(int vlm_id; vlm_id < VLM; vlm_id++){
    this->vloumes[vlm_id].readValue();
  }
}
void Rimocon::readJoysticks(){
  for(int jstk_id; jstk_id < JSTK*3; jstk_id++){
    this->joysticks[jstk_id].readAll();
  }
}

void Rimocon::detectAll(bool resultBtn[], int resultTgl[], int resultVlm[], Polar resultJstkTilte[], bool resultJstkPush[]){
  this->buttonPushed(resultBtn);
  this->toggleFliped(resultTgl);
  this->volumeMoved(resultVlm);
  this->joystickTilted(resultJstkTilte);
  this->joystickPushed(resultJstkPush);
}

void Rimocon::buttonPushed(bool resultBtn[]){
  if(!BTN || resultBtn == NULL) return;
  for(int btn_id; btn_id < BTN; btn_id++){
    resultBtn[btn_id] = this->buttons[btn_id].isPushed();
  }
}

void Rimocon::toggleFliped(bool resultTgl[]){
  if(!TGL || resultTgl == NULL) return;
  for(int tgl_id; tgl_id < TGL*2; tgl_id++){
    resultTgl[tgl_id] = this->toggles[tgl_id].isFliped();
  }
}

void Rimocon::volumeMoved(bool resultVlm[]){
  if(!VLM || resultVlm == NULL) return;
  for(int vlm_id; vlm_id < VLM; vlm_id++){
    resultVlm[vlm_id] = this->volumes[vlm_id].isMoved();
  }
}

void Rimocon::joystickTilted(bool resultJstkTilt[]){
  if(!JSTK || resultJstkTilt == NULL) return;
  for(int jstk_id; jstk_id < JSTK*3; jstk_id++){
    resultJstkTilt[jstk_id] = this->joysticks[jstk_id].isTilted();
  }
}

void Rimocon::joystickPushed(bool resultJstkPush[]){
  if(!JSTK || resultJstkPush == NULL) return;
  for(int jstk_id; jstk_id < JSTK*3; jstk_id++){
    resultJstkPush[jstk_id] = this->joysticks[jstk_id].isPushed();
  }
}
*/