//---- LIBRERIAS ----
//#include <TimerOne.h>

//---- Define del Antirrebote ----
#define BTN_DELAY_MS                3

//---- ENTRADAS DEL TECLADO -----
#define PIN_COLUMNA_1 7
#define PIN_COLUMNA_2 6
#define PIN_COLUMNA_3 5
#define PIN_COLUMNA_4 4

//---- SALIDAS DEL TECLADO ----
#define PIN_FILA_1 11
#define PIN_FILA_2 10
#define PIN_FILA_3 9
#define PIN_FILA_4 8

//---- ESTADOS DEL TECLADO ----
#define ESTADO_FILA_1  0
#define ESTADO_FILA_2  1
#define ESTADO_FILA_3  3
#define ESTADO_FILA_4  4

//---- ESTADO DEL ANTIRREBOTE 1 ----
#define ESTADO_BOTON_ESPERA 4
#define ESTADO_BOTON_CONFIRMACION 5
#define ESTADO_BOTON_LIBERACION 6



//---- Variables de tiempo ----
int mSeg;
int seg = 0;

//---- Variables antirrebote ----
int PIN_BOT[4] = {PIN_COLUMNA_1, PIN_COLUMNA_2, PIN_COLUMNA_3, PIN_COLUMNA_4}; //Botones que queres usar *Tenes que declararlos en el setup igual
int estado_FSM_boton[4] = {1, 2, 3, 4};
int ms_boton;
int flag_boton[4] = {1, 2, 3, 4};

//---- Variable maquina de estados del teclado ----
int cambioDeEstado = ESTADO_FILA_1;


void setup()
{
  Serial.begin(9600);
  //Timer1.initialize(1000);
  //Timer1.attachInterrupt(TIMER);

  pinMode(PIN_BOT[0], INPUT_PULLUP);
  pinMode(PIN_BOT[1], INPUT_PULLUP);
  pinMode(PIN_BOT[2], INPUT_PULLUP);
  pinMode(PIN_BOT[3], INPUT_PULLUP);

  pinMode(PIN_FILA_1, OUTPUT);
  pinMode(PIN_FILA_2, OUTPUT);
  pinMode(PIN_FILA_3, OUTPUT);
  pinMode(PIN_FILA_4, OUTPUT);

  estado_FSM_boton[0] = ESTADO_BOTON_ESPERA;
  estado_FSM_boton[1] = ESTADO_BOTON_ESPERA;
  estado_FSM_boton[2] = ESTADO_BOTON_ESPERA;
  estado_FSM_boton[3] = ESTADO_BOTON_ESPERA;

  Timer1_initialize();
}

void loop()
{
  cambioDeFila();
  maquinaEstadosBoton(0);
  maquinaEstadosBoton(1);
  maquinaEstadosBoton(2);
  maquinaEstadosBoton(3);
}

void cambioDeFila (void)
{
  switch (cambioDeEstado)
  {
    case ESTADO_FILA_1:
      pinMode(PIN_FILA_1, HIGH);
      if (flag_boton[0] == true)
      {
        flag_boton[0] = false;
        Serial.println("1");
      }
      if (flag_boton[1] == true)
      {
        flag_boton[1] = false;
        Serial.println("2");
      }
      if (flag_boton[2] == true)
      {
        flag_boton[2] = false;
        Serial.println("3");
      }
      if (flag_boton[3] == true)
      {
        flag_boton[3] = false;
        Serial.println("A");
      }
      pinMode(PIN_FILA_1, LOW);
      cambioDeEstado = ESTADO_FILA_2;
      break;

    case ESTADO_FILA_2:
      pinMode(PIN_FILA_2, HIGH);
      if (flag_boton[0] == true)
      {
        flag_boton[0] = false;
        Serial.println("4");
      }
      if (flag_boton[1] == true)
      {
        flag_boton[1] = false;
        Serial.println("5");
      }
      if (flag_boton[2] == true)
      {
        flag_boton[2] = false;
        Serial.println("6");
      }
      if (flag_boton[3] == true)
      {
        flag_boton[3] = false;
        Serial.println("B");
      }
      pinMode(PIN_FILA_2, LOW);
      cambioDeEstado = ESTADO_FILA_3;
      break;

    case ESTADO_FILA_3:
      pinMode(PIN_FILA_3, HIGH);
      if (flag_boton[0] == true)
      {
        flag_boton[0] = false;
        Serial.println("7");
      }
      if (flag_boton[1] == true)
      {
        flag_boton[1] = false;
        Serial.println("8");
      }
      if (flag_boton[2] == true)
      {
        flag_boton[2] = false;
        Serial.println("9");
      }
      if (flag_boton[3] == true)
      {
        flag_boton[3] = false;
        Serial.println("C");
      }
      pinMode(PIN_FILA_3, LOW);
      cambioDeEstado = ESTADO_FILA_4;
      break;

    case ESTADO_FILA_4:
      pinMode(PIN_FILA_4, HIGH);
      if (flag_boton[0] == true)
      {
        flag_boton[0] = false;
        Serial.println("*");
      }
      if (flag_boton[1] == true)
      {
        flag_boton[1] = false;
        Serial.println("0");
      }
      if (flag_boton[2] == true)
      {
        flag_boton[2] = false;
        Serial.println("#");
      }
      if (flag_boton[3] == true)
      {
        flag_boton[3] = false;
        Serial.println("D");
      }
      pinMode(PIN_FILA_4, LOW);
      cambioDeEstado = ESTADO_FILA_1;
      break;
  }
}
void maquinaEstadosBoton(int numeroBot) {
  int estado_boton[numeroBot];

  switch (estado_FSM_boton[numeroBot]) {
    case ESTADO_BOTON_ESPERA:
      estado_boton[numeroBot] = digitalRead(PIN_BOT[numeroBot]);
      if ( estado_boton[numeroBot] == 0) {
        ms_boton = 0;
        estado_FSM_boton[numeroBot] = ESTADO_BOTON_CONFIRMACION;
      }
      break;

    case ESTADO_BOTON_CONFIRMACION:
      estado_boton[numeroBot] = digitalRead(PIN_BOT[numeroBot]);

      // Si se da la condicion, se considera el boton como presionado
      if ( estado_boton[numeroBot] == 0 && ms_boton >= BTN_DELAY_MS) {
        estado_FSM_boton[numeroBot] = ESTADO_BOTON_LIBERACION;
      }

      // Si se da la condicion, se considera ruido
      if ( estado_boton[numeroBot] == 1 && ms_boton < BTN_DELAY_MS) {
        estado_FSM_boton[numeroBot] = ESTADO_BOTON_ESPERA;
      }
      break;

    case ESTADO_BOTON_LIBERACION:
      estado_boton[numeroBot] = digitalRead(PIN_BOT[numeroBot]);

      // Si se da la condicion, se considera el boton como presionado
      if ( estado_boton[numeroBot] == 1) {
        flag_boton[numeroBot] = true;
        Serial.println("Boton presionado!");
        Serial.println(numeroBot + 1);
        estado_FSM_boton[numeroBot] = ESTADO_BOTON_ESPERA;
      }
      break;
  }
}

void TIMER()
{
  ms_boton = ms_boton + 1;
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
