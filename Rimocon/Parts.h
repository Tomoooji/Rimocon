#ifndef PARTS_RIMOCON_H
#define PARTS_RIMOCON_H
#include <Arduino.h>

constexpr uint8_t UNDEFINEDPIN = 255;

class Button{
  private:
    uint8_t _pin;
    bool _state;
  public:
    Button(uint8_t pin = UNDEFINEDPIN);
    bool attach(uint8_t pin = UNDEFINEDPIN);
    void readState();
    bool isPushed();
    bool state(){return this->_state;}
};

class Volume{
  private:
    uint8_t _pin;
    int _value;
  public:
    static const int MAX = 1023; // staticない方がいいかもしれない
    static const int MIN = 0;
    Volume(uint8_t pin = UNDEFINEDPIN);
    bool attach(uint8_t pin = UNDEFINEDPIN);
    void readValue();
    int isMoved();
    int value(){return this->_value;};
    int parsent(){return map(this->_value,MIN,MAX,0,100);};
};

struct Toggle{
  private:
    int _state;
  public:
    Button left, right;
    Toggle(
      uint8_t pinL = UNDEFINEDPIN,
      uint8_t pinR = UNDEFINEDPIN
      );
    bool attach(uint8_t pinL = UNDEFINEDPIN,
                uint8_t pinR = UNDEFINEDPIN);
    void readState();
    int isFliped();
    bool isFlipedRight(){return this->right.isPushed();}
    bool isFlipedLeft(){return this->left.isPushed();}
    int state(){return this->_state;}
};

struct Polar{
  float radius;
  float theta;
};

constexpr int InitIgnoreRange = 10;

struct Joystick{
  private:
    Polar _polar;
    int centerX; // initaliy setuped in constranter
    int centerY;
    int rangeX; // ignore Xinput -rangeX~+rangeX from centerX
    int rangeY; // ignore Yinput -rangeY~+rangeY from centerY
  protected:
    void _calcPolar(int x = -1, int y = -1);
  public:
    Button button;
    Volume x, y;
    Joystick(
      uint8_t pinBtn = UNDEFINEDPIN,
      uint8_t pinX = UNDEFINEDPIN,
      uint8_t pinY = UNDEFINEDPIN
    );
    bool attach(uint8_t pinBtn = UNDEFINEDPIN,
                uint8_t pinX = UNDEFINEDPIN,
                uint8_t pinY = UNDEFINEDPIN);
    void readAll();
    Polar isTilted();
    bool isPushed(){return this->button.isPushed();}
    void setCenter(int x = -1, int y = -1, int xrange = InitIgnoreRange, int yrange = InitIgnoreRange){
      this->centerX = (x>=0 ? x : this->x.MIN + (this->x.MAX - this->x.MIN) / 2);
      this->centerY = (y>=0 ? y : this->y.MIN + (this->y.MAX - this->y.MIN) / 2);
      this->rangeX = xrange;  
      this->rangeY = yrange;  
    }
    Polar polar(){return this->_polar;}
};


#endif