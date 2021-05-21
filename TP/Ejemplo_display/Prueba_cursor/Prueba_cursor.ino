//---- Librerias ----
//#include <TimerOne.h>
#include <LiquidCrystal.h>

//---- Lineas para poner el cursor ----
#define LINEA_1                     0,0
#define LINEA_2                     0,1

//---- Nombre de las lineas para la variable ----
#define NOMBRE_LINEA_1              0
#define NOMBRE_LINEA_2              1

//---- Antirrebote boton 1 ----
#define BTN_1                       8
#define BTN_1_ESPERA                0
#define BTN_1_CONFIRMACION          1
#define BTN_1_LIBERADO              2

//---- Antirrebote boton 2 ----
#define BTN_2                       9
#define BTN_2_ESPERA                3
#define BTN_2_CONFIRMACION          4
#define BTN_2_LIBERADO              5

//---- Antirrebote boton 2 ----
#define BTN_3                       10
#define BTN_3_ESPERA                6
#define BTN_3_CONFIRMACION          7
#define BTN_3_LIBERADO              8

//---- Estados del Display ----
#define ESTADO_PANTALLA_1           9
#define ESTADO_PANTALLA_2           10
#define ESTADO_PANTALLA_3           11
#define ESTADO_PANTALLA_4           12

//---- Define del Antirrebote ----
#define BTN_DELAY_MS                5

// ---- Variable maquina de estados menu ----
int cambioDeEstado = ESTADO_PANTALLA_1;

//---- Variables de tiempo ----
int mSeg;
int seg = 0;

//---- Variables antirrebote boton 1 ----
int mSegBtn1 = 0;
int flagBtn1;
int estadoBtn1 = BTN_1_ESPERA;

//---- Variables antirrebote boton 2 ----
int mSegBtn2 = 0;
int flagBtn2;
int estadoBtn2 = BTN_2_ESPERA;

//---- Variables antirrebote boton 3 ----
int mSegBtn3 = 0;
int flagBtn3;
int estadoBtn3 = BTN_3_ESPERA;

//---- Variable para el nombre de la linea ----
int posicionCursor;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  //Timer1.initialize(1000);
  //Timer1.attachInterrupt(TIMER);
  pinMode(BTN_1, INPUT_PULLUP);
  pinMode(BTN_2, INPUT_PULLUP);
  pinMode(BTN_3, INPUT_PULLUP);
  Timer1_initialize();
}

void loop() {
  maquinaBtn1();
  maquinaBtn2();
  maquinaBtn3();
  cambioDeDisplay();
}

void maquinaBtn1()
{
  boolean bot;

  switch (estadoBtn1)
  {
    case BTN_1_ESPERA:
      bot = digitalRead(BTN_1);
      if (bot == 0)
      {
        mSegBtn1 = 0;
        estadoBtn1 = BTN_1_CONFIRMACION;
      }
      break;
    case BTN_1_CONFIRMACION:
      bot = digitalRead(BTN_1);
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
      bot = digitalRead(BTN_1);
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
      bot = digitalRead(BTN_2);
      if (bot == 0)
      {
        mSegBtn2 = 0;
        estadoBtn2 = BTN_2_CONFIRMACION;
      }
      break;
    case BTN_2_CONFIRMACION:
      bot = digitalRead(BTN_2);
      if (bot == 0 && mSegBtn1 >= BTN_DELAY_MS)
      {
        estadoBtn2 = BTN_2_LIBERADO;
      }
      if (bot == 2 && mSegBtn2 < BTN_DELAY_MS)
      {
        estadoBtn2 = BTN_2_ESPERA;
      }
      break;
    case BTN_2_LIBERADO:
      bot = digitalRead(BTN_2);
      if (bot == 1)
      {
        flagBtn2 = true;
        estadoBtn2 = BTN_2_ESPERA;
      }
      break;
  }
}

void maquinaBtn3()
{
  boolean bot;

  switch (estadoBtn3)
  {
    case BTN_3_ESPERA:
      bot = digitalRead(BTN_3);
      if (bot == 0)
      {
        mSegBtn3 = 0;
        estadoBtn3 = BTN_3_CONFIRMACION;
      }
      break;
    case BTN_3_CONFIRMACION:
      bot = digitalRead(BTN_3);
      if (bot == 0 && mSegBtn3 >= BTN_DELAY_MS)
      {
        estadoBtn3 = BTN_3_LIBERADO;
      }
      if (bot == 1 && mSegBtn3 < BTN_DELAY_MS)
      {
        estadoBtn3 = BTN_3_ESPERA;
      }
      break;
    case BTN_3_LIBERADO:
      bot = digitalRead(BTN_3);
      if (bot == 1)
      {
        flagBtn3 = true;
        estadoBtn3 = BTN_3_ESPERA;
      }
      break;
  }
}

void cambioDeDisplay (void)
{
  switch (cambioDeEstado)
  {
    case ESTADO_PANTALLA_1:
      lcd.setCursor(LINEA_1);
      lcd.print ("P1L1");
      lcd.setCursor(LINEA_2);
      lcd.print ("P1L2");
      cambioDeEstado = ESTADO_PANTALLA_2;
      break;

    case ESTADO_PANTALLA_2:
      if (flagBtn1 == true)
      {
        flagBtn1 = false;
        lcd.noCursor();
        lcd.setCursor(LINEA_1);
        lcd.cursor();
        posicionCursor = NOMBRE_LINEA_1;
      }
      if (flagBtn2 == true)
      {
        flagBtn2 = false;
        lcd.noCursor();
        lcd.setCursor(LINEA_2);
        lcd.cursor();
        posicionCursor = NOMBRE_LINEA_2;
      }
      if (posicionCursor == NOMBRE_LINEA_1)
      {
        if (flagBtn3 == true)
        {
          Serial.println("Linea 1 boton apretado");
          flagBtn3 = false;
          lcd.setCursor(LINEA_1);
          lcd.noCursor();
          lcd.clear();
          lcd.print("BIEN3");
          cambioDeEstado = ESTADO_PANTALLA_3;
        }
      }
      if (posicionCursor == NOMBRE_LINEA_2)
      {
        if (flagBtn3 == true)
        {
          lcd.setCursor(LINEA_1);
          lcd.noCursor();
          lcd.clear();
          lcd.print("BIEN4");
          flagBtn3 = false;
          cambioDeEstado = ESTADO_PANTALLA_4;
        }
      }
      break;
    case ESTADO_PANTALLA_3:
      if (flagBtn3 == true)
      {
        flagBtn3 = false;
        cambioDeEstado = ESTADO_PANTALLA_1;
      }
      break;

    case ESTADO_PANTALLA_4:
      if (flagBtn3 == true)
      {
        flagBtn3 = false;
        cambioDeEstado = ESTADO_PANTALLA_1;
      }
      break;
  }
}

void TIMER()
{
  mSegBtn1 = mSegBtn1 + 1;
  mSegBtn2 = mSegBtn2 + 1;
  mSegBtn3 = mSegBtn3 + 1;
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
