#include "Parts.h"

//Error message:
//"pin has not defined in both constracter and attach"
//////////////////////////////////////////////
Button::Button(uint8_t pin):_pin(pin){}

bool Button::attach(uint8_t pin){
  if(pin == UNDEFINEDPIN){
    if(this->_pin == UNDEFINEDPIN){
      return false;
    }
    else{
      return true;
    }
  }
  else{
    this->_pin = pin; // 初期化時とpinが違っても上書き
    return true;
  }
}

void Button::readState(){
  if(this-> _pin != UNDEFINEDPIN){
    this->_state = digitalRead(this->_pin);
  }
}

bool Button::isPushed(){
  if(this-> _pin != UNDEFINEDPIN){
    bool current = this->_state;
    this->readState();
    return !current && this->_state;
    /* push/release両方版(この場合はintを返す)
    switch(digitalRead(this->_pin)){
      case HIGH:
        return !this->_state
      case LOW:
        return -1*this->_state
    }
    */
  }
}

//////////////////////////////////////////////
Volume::Volume(uint8_t pin):_pin(pin){}

bool Volume::attach(uint8_t pin){
  if(pin == UNDEFINEDPIN){
    if(this->_pin == UNDEFINEDPIN){
      return false;
    }
    else{
      return true;
    }
  }
  else{
    this->_pin = pin; // 初期化時とpinが違っても上書き
    return true;
  }
}

void Volume::readValue(){
  if(this-> _pin != UNDEFINEDPIN){
    this->_value = analogRead(this->_pin);
  }
}

int Volume::isMoved(){
  if(this-> _pin != UNDEFINEDPIN){
    int current = this->_value;
    this->readValue();
    return this->_value - current;
  }
}

//////////////////////////////////////////
Toggle::Toggle(uint8_t pinL, uint8_t pinR){
  this->left.attach(pinL);
  this->right.attach(pinR);
}

bool Toggle::attach(uint8_t pinL, uint8_t pinR){
  return this->left.attach(pinL) && this->right.attach(pinR);
}

void Toggle::readState(){
  this->left.readState();
  this->right.readState();
}

int Toggle::isFliped(){
  return this->left.isPushed() - this->right.isPushed();
}

//////////////////////////////////////////
Joystick::Joystick(uint8_t pinBtn = UNDEFINEDPIN, uint8_t pinX = UNDEFINEDPIN, uint8_t pinY = UNDEFINEDPIN){
  this->button.attach(pinBtn);
  this->x.attach(pinX);
  this->y.attach(pinY);
}

bool Joystick::attach(uint8_t pinBtn = UNDEFINEDPIN, uint8_t pinX = UNDEFINEDPIN, uint8_t pinY = UNDEFINEDPIN){
  return this->button.attach(pinBtn) && this->x.attach(pinX) && this->y.attach(pinY);
}

void Joystick::readAll(){
  this->button.readState();
  this->x.readValue();
  this->y.readValue();
  this->_calcPolar();
}

Polar Joystick::isTilted(){
 this->_calcPolar(this->x.isMoved() && this->y.isMoved());
 return this->_polar;
}

void Joystick::_calcPolar(int x, int y){
  if(x < 0) x = this->x.value() - this->centerX;
  if(y < 0) y = this->y.value() - this->centerY;
  this->_polar.radius = sqrt(sq(abs(x)>this->rangeX ? x : 0) + sq(abs(y)>this->rangeY ? y : 0));
  this->_polar.theta = atan2((abs(y)>this->rangeY ? y : 0), (abs(x)>this->rangeX ? x : 0));
}