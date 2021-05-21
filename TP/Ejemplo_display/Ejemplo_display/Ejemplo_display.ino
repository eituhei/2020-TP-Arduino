#include <LiquidCrystal.h>

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

//---- Estados del Display ----
#define ESTADO_PANTALLA_1           0
#define ESTADO_PANTALLA_2           1
#define ESTADO_PANTALLA_3           2
#define ESTADO_PANTALLA_INICIAL     3

//---- Define del Antirrebote ----
#define BTN_DELAY_MS                25

// ---- Variables ----
int cambioDeEstado = ESTADO_PANTALLA_INICIAL;

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

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  lcd.begin(16, 2);
  //Timer1.initialize(1000);
  //Timer1.attachInterrupt(TIMER);
  pinMode(BTN_1, INPUT_PULLUP);
  pinMode(BTN_2, INPUT_PULLUP);
  Timer1_initialize();
}

void loop() {
  lcd.setCursor(0, 0);
  maquinaBtn1();
  maquinaBtn2();
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

void cambioDeDisplay (void)
{
  switch (cambioDeEstado)
  {
    case ESTADO_PANTALLA_1:
      lcd.autoscroll();
      lcd.print ("Milanesa con pure");
      lcd.setCursor(0, 1);
      lcd.print ("Hamburguesa con fritas");
      if (flagBtn1 == true)
      {
        flagBtn1 = false;
        lcd.clear();
        cambioDeEstado = ESTADO_PANTALLA_2;
      }
      if (flagBtn2 == true)
      {
        flagBtn2 = false;
        lcd.clear();
        cambioDeEstado = ESTADO_PANTALLA_3;
      }
      break;

    case ESTADO_PANTALLA_2:
      lcd.noAutoscroll();
      lcd.print ("Coca-Cola");
      lcd.setCursor(0, 1);
      lcd.print ("Manaos");
      if (flagBtn1 == true)
      {
        flagBtn1 = false;
        lcd.clear();
        cambioDeEstado = ESTADO_PANTALLA_3;
      }
      if (flagBtn2 == true)
      {
        flagBtn2 = false;
        lcd.clear();
        cambioDeEstado = ESTADO_PANTALLA_1;
      }

      break;
    case ESTADO_PANTALLA_3:
      lcd.noAutoscroll();
      lcd.print ("Flan con DDL");
      lcd.setCursor(0, 1);
      lcd.print ("Bombon suizo");
      if (flagBtn1 == true)
      {
        flagBtn1 = false;
        lcd.clear();
        cambioDeEstado = ESTADO_PANTALLA_1;
      }
      if (flagBtn2 == true)
      {
        flagBtn2 = false;
        lcd.clear();
        cambioDeEstado = ESTADO_PANTALLA_2;
      }
      break;
    case ESTADO_PANTALLA_INICIAL:
      
        lcd.autoscroll();
        lcd.print("Con el Btn 1 van hacia adelante");
        lcd.setCursor(0, 1);
        lcd.print("y con el 2 hacia atras");
      if (seg ==1)
      {
      lcd.clear();
      cambioDeEstado = ESTADO_PANTALLA_1;
      }
      break;
  }
}
void TIMER()
{
  mSegBtn1 = mSegBtn1 + 1;

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
