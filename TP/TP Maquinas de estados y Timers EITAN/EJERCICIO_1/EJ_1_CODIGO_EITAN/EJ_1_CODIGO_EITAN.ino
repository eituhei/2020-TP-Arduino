#include <TimerOne.h>

#define VELOCIDAD_PUERTO_SERIE         9600
#define BTN_DELAY_MS                   25 // Tiempo para el antirrebote

//---- Maquina de estados boton 1 ----
#define PIN_BTN_PLAY_PAUSE             11
#define BTN_1_ESPERA                   0
#define BTN_1_CONFIRMACION             1
#define BTN_1_LIBERADO                 2

//---- Maquina de estados boton 2 ----
#define PIN_BTN_STOP_RESET             12
#define BTN_2_ESPERA                   3
#define BTN_2_CONFIRMACION             4
#define BTN_2_LIBERADO                 5

//---- Maquina de estados contadora ----
#define PLAY                           0
#define PAUSE                          1
#define STOP                           2
#define RESET                          3

//---- Textos guia ----
#define TXT_COMIENZO                   "Presione el boton 1 para comenzar o pausar el cronometro, y el 2 para frenar y reiniciar el tiempo: "
#define TXT_STOP_RESET                 "Volviste a poner el tiempo en 0, para volver a iniciar el cronometro oprima el boton 2."
#define TXT_PLAY_PAUSE                 "Pausaste el tiempo, presione el boton 1 para continuar la cuenta."

//---- Variables boton 1 ----
int mSegBtn1 = 0;
int flagBtn1;
int estadoBtn1 = BTN_1_ESPERA;

//---- Variables boton 2 ----
int mSegBtn2 = 0;
int flagBtn2;
int estadoBtn2 = BTN_2_ESPERA;

//---- Variables de tiempo ----
int mSeg;
int seg = 0;
int contadorSeg = 0;
int contadorMin = 0;

//---- Variable maquina de estados ----
int estadoMaquina = PAUSE; // Se iguala a PAUSE para que la primera vez que se oprima el boton empiece a contar en PLAY

void setup()
{
  Serial.begin(VELOCIDAD_PUERTO_SERIE);
  Timer1.initialize(1000);
  Timer1.attachInterrupt(TIMER);
  pinMode(PIN_BTN_PLAY_PAUSE, INPUT_PULLUP);
  pinMode(PIN_BTN_STOP_RESET, INPUT_PULLUP);
  Serial.println(TXT_COMIENZO);
  //Timer1_initialize();
}

void loop()
{
  maquinaBtn1();
  maquinaBtn2();
  maquinaEstadosCronometro();
}

void maquinaBtn1()
{
  boolean bot;

  switch (estadoBtn1)
  {
    case BTN_1_ESPERA:
      bot = digitalRead(PIN_BTN_PLAY_PAUSE);
      if (bot == 0)
      {
        mSegBtn1 = 0;
        estadoBtn1 = BTN_1_CONFIRMACION;
      }
      break;
    case BTN_1_CONFIRMACION:
      bot = digitalRead(PIN_BTN_PLAY_PAUSE);
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
      bot = digitalRead(PIN_BTN_PLAY_PAUSE);
      if (bot == 1)
      {
        flagBtn1 = true;
        estadoBtn1 = BTN_1_ESPERA;
      }
      break;
  }
}

void maquinaBtn2()
{
  boolean bot;

  switch (estadoBtn2)
  {
    case BTN_2_ESPERA:
      bot = digitalRead(PIN_BTN_STOP_RESET);
      if (bot == 0)
      {
        mSegBtn2 = 0;
        estadoBtn2 = BTN_2_CONFIRMACION;
      }
      break;
    case BTN_2_CONFIRMACION:
      bot = digitalRead(PIN_BTN_STOP_RESET);
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
      bot = digitalRead(PIN_BTN_STOP_RESET);
      if (bot == 1)
      {
        flagBtn2 = true;
        estadoBtn2 = BTN_2_ESPERA;
      }
      break;
  }
}

void maquinaEstadosCronometro()
{
  switch (estadoMaquina)
  {
    case PAUSE:
      if (flagBtn1 == true)
      {
        flagBtn1 = false;
        seg = 0;
        estadoMaquina = PLAY;
      }
      if (flagBtn2 == true)
      {
        flagBtn2 = false;
        Serial.println(TXT_STOP_RESET);
        estadoMaquina = STOP;
      }
      break;
    case PLAY:
      if (flagBtn1 == true)
      {
        flagBtn1 = false;
        Serial.println(TXT_PLAY_PAUSE);
        estadoMaquina = PAUSE;
      }
      if (flagBtn2 == true)
      {
        flagBtn2 = false;
        Serial.println(TXT_STOP_RESET);
        estadoMaquina = STOP;
      }
      if (seg >= 1)
      {
        Serial.print(contadorMin);
        Serial.print(":");
        Serial.println(contadorSeg);
        contadorSeg++;
        seg = 0;
      }
      if (contadorSeg == 60)
      {
        contadorMin++;
        contadorSeg = 0;
      }
      break;
    case STOP:
      if (flagBtn2 == true)
      {
        flagBtn2 = false;
        Serial.println(TXT_COMIENZO);
        estadoMaquina = RESET;
      }
      break;
    case RESET:
      contadorSeg = 0;
      contadorMin = 0;
      estadoMaquina = PAUSE;
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

    ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)
    //generates pulse wave of frequency 1kHz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)
    TIMER();
    }
 */
