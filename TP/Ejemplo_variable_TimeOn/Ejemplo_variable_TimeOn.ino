//#include <TimerOne.h>
#define SERIAL               9600
#define PIN_BOTON     12
#define PRESIONADO    0
#define NO_PRESIONADO 1
#define PAUSA     1
#define PLAY      2
boolean contador;
void maquinaContadora(void);
char estadoMaquinaLED;
char estadoMaquinaContadora = PAUSA;
//---- VARIABLES LIBRERIAS ----
int seg; //Variable conatdor de segundo
int mSeg; //Variable contador de miliseg


void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_BOTON, INPUT_PULLUP);
  //Timer1.initialize(1000); //Configuro timer para que interrumpa cada 1000 uSeg (1000 micro Seg = 1 mili Seg)
  //Timer1.attachInterrupt(timer);//Configuro que funcion ejecuta la interrupcion del Timer 1
 Timer1_initialize();
  Serial.begin(SERIAL);
  Serial.print("hola");
}

void loop() {
  // put your main code here, to run repeatedly:
  maquinaContadora();
 
}

void maquinaContadora(void)
{
  boolean estadoBoton;
  
  switch (estadoMaquinaContadora)
  {
    case PAUSA:

      estadoBoton = digitalRead(PIN_BOTON);
      if (estadoBoton == PRESIONADO) //si precciono el boton hago el cambio de estado y hago las acciones que corresponda
      {
        while (estadoBoton == PRESIONADO)
        {
          estadoBoton = digitalRead(PIN_BOTON);
        }

        
        contador = true;
        estadoMaquinaContadora = PLAY; //Cambio de estado
      }
      break;
      
    case PLAY:

      estadoBoton = digitalRead(PIN_BOTON);
      if (estadoBoton == PRESIONADO) //si precciono el boton hago el cambio de estado y hago las acciones que corresponda
      {
        while (estadoBoton == PRESIONADO)
        {
          estadoBoton = digitalRead(PIN_BOTON);
        }
        Serial.print ("Van:");
        Serial.println(seg);
        Serial.print ("Ahora pasa al estado de pause");
        contador = false;
        estadoMaquinaContadora = PAUSA; //Cambio de estado
      }
      break;

  }
  
  }
  void timer (void) //Interrumpe cada 1mSeg
  {
    if (contador == true)
    {
      mSeg = mSeg + 1; //Incremento la variable contadora de mili seg

      if (mSeg >= 1000) //Si pasan 1000ms incremento la variable seg
      {
        mSeg = 0; //Reseteo mSeg
        seg++;    //incremeto en 1 la variable seg
      }
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

    ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)
    //generates pulse wave of frequency 1kHz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)
    timer();
    }
  
