#ifndef PARTS_FOR_RIMOCON_H
#define PARTS_FOR_RIMOCON_H
#include <Arduino.h>

constexpr uint8_t UNDEFINEDPIN = 255;

///////////////////////////////////

template <typename Valtype>
class InputDevice{
  protected:
    Valtype _value;
  public:
    virtual void read() = 0;
    virtual Valtype get() = 0;
    virtual Valtype detect() = 0;
};

///////////////////////////////////

class Button : public InputDevice<bool>{
  private:
    uint8_t _pin;
    //bool _value;
  public:
    Button(uint8_t pin = UNDEFINEDPIN):_pin(pin){}
     // allows attaching pin number at constructor
    void read() override {return this->readPlessed();}
    bool detect() override {return this->detectPushed();}
    bool get() override {return this->getPlessed();}
    bool attach(uint8_t pin = UNDEFINEDPIN){
     // return false if any pin wasn't attached
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
    void readPlessed(){
     // just update inner state
      if(this-> _pin != UNDEFINEDPIN){
        this->_value = digitalRead(this->_pin);
      }
    }
    bool detectPushed(){
     // detect when it pushed (or/and released)
      if(this-> _pin != UNDEFINEDPIN){
        bool current = this->_value;
        this->read();
        return !current && this->_value;
        /* push/release両方版(この場合はintを返す)
        switch(digitalRead(this->_pin)){
          case HIGH:
            return !this->_value
          case LOW:
            return -1*this->_value
        }
        */
      }
    }
    bool getPlessed(){return this->_value;} // getter to inner state
};

//////////////////////////////////

class Volume : public InputDevice<int>{
  private:
    uint8_t _pin;
    //int _value;
  public:
    static const int MAX = 1023; // staticない方がいいかもしれない
    static const int MIN = 0;
    Volume(uint8_t pin = UNDEFINEDPIN):_pin(pin){}
    void read() override {return this->readPosition();}
    int detect() override {return this->detectMoved();}
    int get() override {return this->getPosition();}
    bool attach(uint8_t pin = UNDEFINEDPIN){
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
    void readPosition(){
      if(this-> _pin != UNDEFINEDPIN){
        this->_value = analogRead(this->_pin);
      }
    }
    int detectMoved(){
      if(this-> _pin != UNDEFINEDPIN){
        int current = this->_value;
        this->readPosition();
        return this->_value - current;
      }
    }
    int getPosition(){return this->_value;};
    int getParsent(){return map(this->_value,MIN,MAX,0,100);};
};

////////////////////////////////////////

struct Toggle : public InputDevice<int>{
  private:
    //int _state;
  public:
    Button left, right;
    Toggle(uint8_t pinL = UNDEFINEDPIN, uint8_t pinR = UNDEFINEDPIN){
      this->left.attach(pinL); this->right.attach(pinR);}
    void read() override {return this->readState();}
    int detect() override {return this->detectFliped();}
    int get() override {return this->getState();}
    bool attach(uint8_t pinL = UNDEFINEDPIN, uint8_t pinR = UNDEFINEDPIN){
      return this->left.attach(pinL) && this->right.attach(pinR);
    }
    bool attach(uint8_t pins[]){return this->attach(pins[0], pins[1]);}
    void readState(){
      this->left.readPlessed();
      this->right.readPlessed();
    }
    int detectFliped(){
      return this->left.detectPushed() - this->right.detectPushed();
    }
    bool detectFlipedRight(){return this->right.detectPushed();}
    bool detectFlipedLeft(){return this->left.detectPushed();}
    int getState(){return this->_value;}
};

////////////////////////////////////////

struct Polar{
  float radius;
  float theta;
};

constexpr int InitIgnoreRange = 10;

struct Joystick : InputDevice<Polar>{
  private:
    //Polar _polar;
    int centerX; // initaliy setuped in constranter
    int centerY;
    int rangeX; // ignore Xinput -rangeX~+rangeX from centerX
    int rangeY; // ignore Yinput -rangeY~+rangeY from centerY
  protected:
    void _calcPolar(int x = -1, int y = -1){
      if(x < 0) x = this->x.getPosition() - this->centerX;
      if(y < 0) y = this->y.getPosition() - this->centerY;
      this->_value.radius = sqrt(sq(abs(x)>this->rangeX ? x : 0) + sq(abs(y)>this->rangeY ? y : 0));
      this->_value.theta = atan2((abs(y)>this->rangeY ? y : 0), (abs(x)>this->rangeX ? x : 0));
    }
  public:
    Button button;
    Volume x, y;
    Joystick(uint8_t pinBtn = UNDEFINEDPIN, uint8_t pinX = UNDEFINEDPIN, uint8_t pinY = UNDEFINEDPIN){
      this->button.attach(pinBtn); this->x.attach(pinX); this->y.attach(pinY);}
    void read() override {return this->readAll();}
    Polar detect() override {return this->detectTilted();}
    //int detect() {return this->detectPushed();}
    Polar get() override {return this->getPolar();}
    bool attach(uint8_t pinBtn = UNDEFINEDPIN, uint8_t pinX = UNDEFINEDPIN, uint8_t pinY = UNDEFINEDPIN){
      return this->button.attach(pinBtn) && this->x.attach(pinX) && this->y.attach(pinY);
    }
    bool attach(uint8_t pins[]){return this->attach(pins[0], pins[1], pins[2]);}
    void readAll(){
      this->button.readPlessed();
      this->x.readPosition();
      this->y.readPosition();
      this->_calcPolar();
    }
    Polar detectTilted(){
      this->_calcPolar(this->x.detectMoved() && this->y.detectMoved());
      return this->_value;
    }
    bool detectPushed(){return this->button.detectPushed();}
    void setCenter(int x = -1, int y = -1, int xrange = InitIgnoreRange, int yrange = InitIgnoreRange){
      this->centerX = (x>=0 ? x : this->x.MIN + (this->x.MAX - this->x.MIN) / 2);
      this->centerY = (y>=0 ? y : this->y.MIN + (this->y.MAX - this->y.MIN) / 2);
      this->rangeX = xrange;  
      this->rangeY = yrange;  
    }
    Polar getPolar(){return this->_value;}
};

////////////////////////////////////////

#endif