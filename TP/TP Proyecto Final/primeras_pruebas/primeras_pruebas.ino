//#include <TimerOne.h>

#define PIN_IR 9
#define PIN_LED 7

#define VELOCIDAD_PUERTO_SERIE         9600
#define BTN_DELAY_MS                   25 // Tiempo para el antirrebote

//---- Maquina de estados boton presencia ----
#define BTN_IR_ESPERA                   3
#define BTN_IR_CONFIRMACION             4
#define BTN_IR_LIBERADO                 5

//---- Variables boton presencia ----
int mSegIR = 0;
int flagIR;
int estadoIR = BTN_IR_ESPERA;

//---- Variables de tiempo ----
int mSeg;
int seg = 0;

void setup()
{
  pinMode(PIN_IR, INPUT);
  Serial.begin(9600);
  pinMode(PIN_LED, OUTPUT);
  //Timer1.initialize(1000);
  //Timer1.attachInterrupt(TIMER);
  Timer1_initialize();

}


void loop()
{
  maquinaIR();
  if (flagIR == true)
  {
    flag = false;
    digitalWrite(PIN_LED, LOW);
  }
  else {
    digitalWrite(PIN_LED, HIGH);
  }
}
void maquinaIR()
{
  boolean bot;

  switch (estadoIR)
  {
    case BTN_IR_ESPERA:
      bot = digitalRead(PIN_IR);
      if (bot == 0)
      {
        mSegIR = 0;
        estadoIR = BTN_IR_CONFIRMACION;
      }
      break;
    case BTN_IR_CONFIRMACION:
      bot = digitalRead(PIN_IR);
      if (bot == 0 && mSegIR >= BTN_DELAY_MS)
      {
        estadoIR = BTN_IR_LIBERADO;
      }
      if (bot == 1 && mSegIR < BTN_DELAY_MS)
      {
        estadoIR = BTN_IR_ESPERA;
      }
      break;
    case BTN_IR_LIBERADO:
      bot = digitalRead(PIN_IR);
      flagIR = true;
      if (bot == 1)
      {
        estadoIR = BTN_IR_ESPERA;
      }
      break;
  }
}
void TIMER()
{
  mSegIR = mSegIR + 1;
  mSeg = mSeg + 1;
  if (mSeg == 1000)
  {
    seg = seg + 1;
    mSeg = 0;
  }
}

void Timer1_initialize()
{
  // Stop interrupts
  cli();

  // Set Timer1 interrupt at 1kHz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 1999;// = (16*10^6) / (1000*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS21 bit for 8 prescaler
  TCCR1B |= (1 << CS21);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  // Allow interrupts
  sei();
}

ISR(TIMER1_COMPA_vect) { //timer1 interrupt 1Hz toggles pin 13 (LED)
  //generates pulse wave of frequency 1kHz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)
  TIMER();
}
