#define hallEffectPin 2
#define outputPin 3
#define pulseTime_ms 50
#define speed_mph 10
#define wheelDiameter_mm 700

#define mph_to_mmpms 0.44704
enum Speed
{
  Mirror = 1,
  Regulated = 6,
  Fast = 8,
  VFast = 10,
  FFast = 12,
};


Speed speed = Speed::FFast;
unsigned long timer = 0;


void hallEffectISR()
{
  static uint16_t count = 0;
  count++;
  if(count == speed)
  {
    digitalWrite(outputPin, LOW);
    timer = millis();
    count = 0;
  }
  else
    digitalWrite(outputPin, HIGH);
}


void outputHandler()
{
  if((digitalRead(outputPin) == LOW) && (millis() - timer >= pulseTime_ms))
  {
    digitalWrite(outputPin, HIGH);
  }

  // unsigned short dutyCycle_ms = (wheelDiameter_mm*3.14159) / (speed_mph * mph_to_mmpms);
  // digitalWrite(outputPin, LOW);
  // delay(pulseTime_ms);
  // digitalWrite(outputPin, HIGH);
  // delay(dutyCycle_ms - pulseTime_ms);

}


void setup()
{
  Serial.begin(9600);
  pinMode(hallEffectPin, INPUT);
  pinMode(outputPin, OUTPUT);
  digitalWrite(outputPin,HIGH);

  attachInterrupt(digitalPinToInterrupt(hallEffectPin), hallEffectISR, FALLING);
}

void loop() 
{
  outputHandler();
}
