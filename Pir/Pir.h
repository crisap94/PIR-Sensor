#ifndef PIR_H
#define PIR_H

#include <Arduino.h>

//#define DEBUGGIN

class Pir {

private:
  uint8_t pin;
  bool state;
  bool previus_state;
  uint16_t sensingInterval;
  uint64_t previusMillis;

  void (*callBackFunction)(void);
  bool check_CallBackFunction();

  inline void Execute_CallBackFunction() {
    if (callBackFunction) {
      (*callBackFunction)();
    }
  }

public:
  // Constructor
  Pir(uint8_t _pin, void (*_callBackFunction)(void) = 0,
      uint16_t _sensingInterval = 1000);

  void begin();
  void handle();
  // Destructor
  virtual ~Pir();

  // Setters
  inline void setInterval(uint16_t _sensingInterval) {
    this->sensingInterval = _sensingInterval;
  }

  inline void setPin(uint8_t _pin) { this->pin = _pin; }

  // Getters
  inline bool getState() { return this->state; }
};

#endif
