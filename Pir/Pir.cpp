#include <Pir.h>

#ifdef DEBUGGIN
#define PIR_DEBUG(String) (Serial.println(String))
#endif

#ifndef DEBUGGIN
#define PIR_DEBUG(String)
#endif

Pir::Pir(uint8_t _pin, void (*_callBackFunction)(void),
         uint16_t _sensingInterval) {

  this->pin = _pin;
  this->previus_state = false;
  this->callBackFunction = _callBackFunction;
  this->sensingInterval = _sensingInterval;
  this->previusMillis = 0;
}

Pir::~Pir() { PIR_DEBUG("Deleting Pir Object"); }

void Pir::begin() {
  pinMode(pin, INPUT);
  PIR_DEBUG("Initializing Pin ");
  check_CallBackFunction();
}

bool Pir::check_CallBackFunction() {
  if (!this->callBackFunction) {
    PIR_DEBUG("The Pir Obj does not have a Call-Back-Function");
    return false;
  }
  PIR_DEBUG("Function exist");
  return true;
}

void Pir::handle() {
  state = digitalRead(this->pin);

  if (previus_state == LOW && state == HIGH) {
    PIR_DEBUG("PIR State: " + String(state));
    if (check_CallBackFunction()) {
      Execute_CallBackFunction();
    }
    previus_state = HIGH;
  }
  if (state == LOW) {
    previus_state = LOW;
  }
}
