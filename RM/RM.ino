#define BRAKEVCC 0
#define CW   1
#define CCW  2
#define BRAKEGND 3
#define CS_THRESHOLD 100
//////////////////////////////////////////////////
// G04
#define Min_CH1    830 
#define Center_CH1 1200 
#define Max_CH1    1610 

#define Min_CH2    810 
#define Center_CH2 1200 
#define Max_CH2    1570 

#define Error 100
/////////////////////////////////////////////////
int inApin[2] = {7, 4};  
int inBpin[2] = {8, 9}; 
int pwmpin[2] = {5, 6}; 

int cspin[2] = {2, 3}; 
int enpin[2] = {0, 1};  

int statpin = 13;
int ch1 = 11 ;
int ch2 = 10;

void setup()
{
  Serial.begin(9600);
  
  pinMode(statpin, OUTPUT);

  for (int i=0; i<2; i++)
  {
    pinMode(inApin[i], OUTPUT);
    pinMode(inBpin[i], OUTPUT);
    pinMode(pwmpin[i], OUTPUT);
  }
  
  for (int i=0; i<2; i++)
  {
    digitalWrite(inApin[i], LOW);
    digitalWrite(inBpin[i], LOW);
  }
  
  pinMode(ch1, INPUT_PULLUP);
  pinMode(ch2, INPUT_PULLUP);
}

void loop()
{ int CH1 = pulseIn(ch1,HIGH);
  int CH2 = pulseIn(ch2,HIGH);
int PWM_Speed; //  = 0
if((CH2 > ((Center_CH2 + Error)&&(CH2 < (Center_CH2 - Error)))))
{
  if((CH1 > ((Center_CH1 + Error)&&(CH1 < (Center_CH1 - Error)))))
  {
  motorOff(0);
  motorOff(1);
  }
}
if (CH2 > (Center_CH2 + Error))
{
  PWM_Speed = map(CH2, Center_CH2 + Error, Max_CH2, 0, 255);// map(¤èÒ´Ôº,¤èÒÍÂÙèã¹ªèÇ§·Õè¡´,¤èÒÊÙ§ÊØ´¢Í§¤èÒ´Ôº,¤èÒµèÓÊØ´·ÕèµéÍ§¡ÒÃ (MIN),¤èÒÊÙ§ÊØ´·ÕèµéÍ§¡ÒÃ (MAX));
  Backword(PWM_Speed,100);
}
if (CH2 < (Center_CH2 - Error))
  { 
    PWM_Speed = map(CH2, Center_CH2 - Error, Min_CH2, 0, 255);
    Forword(PWM_Speed,100);
  }
if (CH1 > (Center_CH1 + Error))
{
  PWM_Speed = map(CH1, Center_CH1 + Error, Max_CH1, 0, 150);
  Right(PWM_Speed,100);
}
if (CH1 < (Center_CH1 - Error))
  { 
    PWM_Speed = map(CH1, Center_CH1 - Error, Min_CH1, 0, 150);
    Left(PWM_Speed,100);
  }

  if ((analogRead(cspin[0]) < CS_THRESHOLD) && (analogRead(cspin[1]) < CS_THRESHOLD))
    digitalWrite(statpin, HIGH);    
}

void motorOff(int motor)
{
  // Initialize braked
  for (int i=0; i<2; i++)
  {
    digitalWrite(inApin[i], LOW);
    digitalWrite(inBpin[i], LOW);
  }
  analogWrite(pwmpin[motor], 0);
}


void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm)
{
  if (motor <= 1)
  {
    if (direct <=4)
    {
      // Set inA[motor]
      if (direct <=1)
        digitalWrite(inApin[motor], HIGH);
      else
        digitalWrite(inApin[motor], LOW);

      // Set inB[motor]
      if ((direct==0)||(direct==2))
        digitalWrite(inBpin[motor], HIGH);
      else
        digitalWrite(inBpin[motor], LOW);

      analogWrite(pwmpin[motor], pwm);
    }
}
}
void Forword(int Speed,int Time)
{
    motorGo(0, CW, Speed);
    motorGo(1, CW, Speed);
    delay(Time);
}
void Backword(int Speed,int Time)
{
    motorGo(0, CCW, Speed);
    motorGo(1, CCW, Speed);
    delay(Time);
}
void Right(int Speed,int Time)
{
    motorGo(0, CW, Speed);
    motorGo(1, CCW, Speed);
    delay(Time);
}
void Left(int Speed,int Time)
{
    motorGo(0, CCW, Speed);
    motorGo(1, CW, Speed);
    delay(Time);
}
