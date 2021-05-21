#include <TimerOne.h>

#define VELOCIDAD_PUERTO_SERIE         9600
#define BTN_DELAY_MS                   25 // Tiempo para el antirrebote
#define PIN_LED                        10

//---- Tipos de cafes ----
#define CAFE_CORTO "corto"
#define CAFE_LARGO "largo"

//---- Maquina de estados boton servir ----
#define PIN_BTN_SERVIR                 11
#define BTN_1_ESPERA                   0
#define BTN_1_CONFIRMACION             1
#define BTN_1_LIBERADO                 2

//---- Maquina de estados boton presencia ----
#define PIN_BTN_PRESENCIA              12
#define BTN_2_ESPERA                   3
#define BTN_2_CONFIRMACION             4
#define BTN_2_LIBERADO                 5

//---- Maquina de estados cafe ----
#define ESPERA                         0
#define CORTO                          1
#define LARGO                          2
#define PRESENCIA                      3

//---- Textos guia ----
#define TXT_ELECCION                   "Aprete el boton SERVIR y despues escriba que tipo de cafe quiere"
#define TXT_ENTREGA                    "Aqui tiene su cafe"
#define TXT_PRESENCIA                  "Tome el cafe y libere el area"


//---- Variables boton servir ----
int mSegBtn1 = 0;
int flagBtn1;
int estadoBtn1 = BTN_1_ESPERA;

//---- Variables boton presencia ----
int mSegBtn2 = 0;
int flagBtn2;
int estadoBtn2 = BTN_2_ESPERA;

//---- Variables de tiempo ----
int mSeg;
int seg = 0;


//---- Variable maquina de estados ----
int estadoMaquina = ESPERA;

void setup()
{
  Serial.begin(VELOCIDAD_PUERTO_SERIE);
  Timer1.initialize(1000);
  Timer1.attachInterrupt(TIMER);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BTN_SERVIR, INPUT_PULLUP);
  pinMode(PIN_BTN_PRESENCIA, INPUT_PULLUP);
  Serial.println(TXT_ELECCION);
  //Timer1_initialize();
}

void loop()
{
  maquinaBtnServir();
  maquinaCafe();
  maquinaBtnPresencia();
}

void maquinaBtnServir()
{
  boolean bot;

  switch (estadoBtn1)
  {
    case BTN_1_ESPERA:
      bot = digitalRead(PIN_BTN_SERVIR);
      if (bot == 0)
      {
        mSegBtn1 = 0;
        estadoBtn1 = BTN_1_CONFIRMACION;
      }
      break;
    case BTN_1_CONFIRMACION:
      bot = digitalRead(PIN_BTN_SERVIR);
      if (bot == 0 && mSegBtn1 >= BTN_DELAY_MS)
      {
        estadoBtn1 = BTN_1_LIBERADO;
      }
      if (bot == 1 && mSegBtn1 < BTN_DELAY_MS)
      {
        estadoBtn1 = BTN_1_ESPERA;
      }
      break;
    case BTN_1_LIBERADO:
      bot = digitalRead(PIN_BTN_SERVIR);
      if (bot == 1)
      {
        flagBtn1 = true;
        estadoBtn1 = BTN_1_ESPERA;
      }
      break;
  }
}


void maquinaBtnPresencia()
{
  boolean bot;

  switch (estadoBtn2)
  {
    case BTN_2_ESPERA:
      bot = digitalRead(PIN_BTN_PRESENCIA);
      if (bot == 0)
      {
        mSegBtn2 = 0;
        estadoBtn2 = BTN_2_CONFIRMACION;
      }
      break;
    case BTN_2_CONFIRMACION:
      bot = digitalRead(PIN_BTN_PRESENCIA);
      if (bot == 0 && mSegBtn2 >= BTN_DELAY_MS)
      {
        estadoBtn2 = BTN_2_LIBERADO;
      }
      if (bot == 1 && mSegBtn2 < BTN_DELAY_MS)
      {
        estadoBtn2 = BTN_2_ESPERA;
      }
      break;
    case BTN_2_LIBERADO:
      bot = digitalRead(PIN_BTN_PRESENCIA);
      flagBtn2 = true;
      if (bot == 1)
      {
        estadoBtn2 = BTN_2_ESPERA;
      }
      break;
  }
}


void maquinaCafe()
{
  String cafeLeido;
  switch (estadoMaquina)
  {
    case ESPERA:

      if (flagBtn1 == true)
      {
        flagBtn1 = false;
        while (Serial.available() == 0);
        while (Serial.available())
        {
          cafeLeido = Serial.readString();
          Serial.println(cafeLeido);
        }
        if (cafeLeido == CAFE_CORTO)
        {
          seg = 0;
          estadoMaquina = CORTO;
        }
        if (cafeLeido == CAFE_LARGO)
        {
          seg = 0;
          estadoMaquina = LARGO;
        }
      }
      break;
    case CORTO:
      digitalWrite(PIN_LED, HIGH);
      if (seg == 3)
      {
        digitalWrite(PIN_LED, LOW);
        Serial.println(TXT_ENTREGA);
        estadoMaquina = PRESENCIA;
      }
      break;

    case LARGO:
      digitalWrite(PIN_LED, HIGH);
      if (seg == 5)
      {
        digitalWrite(PIN_LED, LOW);
        Serial.println (TXT_ENTREGA);
        estadoMaquina = PRESENCIA;
      }
      break;

    case PRESENCIA:
      if (flagBtn2 == true)
      {
        flagBtn2 = false;
        Serial.println(TXT_PRESENCIA);
      }
      else
      {
        Serial.println (TXT_ELECCION);
        estadoMaquina = ESPERA;
      }
      break;
  }
}

void TIMER()
{
  mSegBtn1 = mSegBtn1 + 1;
  mSegBtn2 = mSegBtn2 + 1;
  mSeg = mSeg + 1;
  if (mSeg == 1000)
  {
    seg = seg + 1;
    mSeg = 0;
  }
}
/*
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
*/
