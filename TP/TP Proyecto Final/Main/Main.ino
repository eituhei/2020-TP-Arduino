#include <TimerOne.h>
#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>
#include <SPI.h>

#define VELOCIDAD_PUERTO_SERIE         9600
#define PIN_BOCINA                     8
#define PIN_LED                        7
#define BTN_DELAY_MS                   25

//---- Maquina de estados IR ----
#define PIN_BTN_IR                      3

//---- Maquina de estados boton activar ----
#define PIN_BTN_ACTIVAR                4
#define BTN_ACTIVAR_ESPERA             3
#define BTN_ACTIVAR_CONFIRMACION       4
#define BTN_ACTIVAR_LIBERADO           5

//---- Maquina de estados general ----
#define ESTADO_IR                      6 //Estado para que el IR esté activado, si se interrumpe, ALARMA, si se activa con NFC, va al estado ABIERTO
#define ESTADO_ALARMA                  7
#define ESTADO_ABIERTO                 8 //Estado para cuando se activa el NFC y apaga el IR y hay un if para el btn reset e ir a estado IR

//---- Variables boton activar ----
int mSegBtnActivar = 0;
int flagBtnActivar;
int estadoBtnActivar = BTN_ACTIVAR_ESPERA;

//---- Variable maquina de estados ----
int estadoMaquina = ESTADO_IR;

//---- Variables de tiempo ----
int mSeg = 0;
int seg = 0;

//---- Informacion del NFC ----
#define SS_PIN 10
#define RST_PIN 9
MFRC522 rfid(SS_PIN, RST_PIN);
#define PASS 472
boolean acceso = 0;
boolean acceso2 = 0;

void setup()
{
  Serial.begin(VELOCIDAD_PUERTO_SERIE);
  Timer1.initialize(1000);
  Timer1.attachInterrupt(TIMER);
  pinMode(PIN_BTN_IR, INPUT_PULLUP);
  pinMode(PIN_BTN_ACTIVAR, INPUT_PULLUP);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BOCINA, OUTPUT);
  SPI.begin(); // init SPI bus
  rfid.PCD_Init(); // init MFRC522
  Serial.println("Tap RFID/NFC Tag on reader");
}

void loop() {
  // put your main code here, to run repeatedly:
  maquinaBtnActivar();
  sistemaSeguridad();
  lecturaNFC();
}



void maquinaBtnActivar()
{
  boolean bot;

  switch (estadoBtnActivar)
  {
    case BTN_ACTIVAR_ESPERA:
      bot = digitalRead(PIN_BTN_ACTIVAR);
      if (bot == 0)
      {
        mSegBtnActivar = 0;
        estadoBtnActivar = BTN_ACTIVAR_CONFIRMACION;
      }
      break;
    case BTN_ACTIVAR_CONFIRMACION:
      bot = digitalRead(PIN_BTN_ACTIVAR);
      if (bot == 0 && mSegBtnActivar >= BTN_DELAY_MS)
      {
        estadoBtnActivar = BTN_ACTIVAR_LIBERADO;
      }
      if (bot == 1 && mSegBtnActivar < BTN_DELAY_MS)
      {
        estadoBtnActivar = BTN_ACTIVAR_ESPERA;
      }
      break;
    case BTN_ACTIVAR_LIBERADO:
      bot = digitalRead(PIN_BTN_ACTIVAR);
      if (bot == 1)
      {
        flagBtnActivar = true;
        estadoBtnActivar = BTN_ACTIVAR_ESPERA;
      }
      break;
  }
}

void sistemaSeguridad()
{
  switch (estadoMaquina)
  {
    case ESTADO_IR:
      boolean estadoIR;
      Serial.println("Estado IR");
      estadoIR = digitalRead(PIN_BTN_IR);
      noTone(PIN_BOCINA);
      digitalWrite(PIN_LED, LOW);
      if (estadoIR == true)
      {
        seg = 0;
        estadoMaquina = ESTADO_ALARMA;
      }

      if (acceso == true)
      {
        acceso = false;
        estadoMaquina = ESTADO_ABIERTO;
      }

      break;
    case ESTADO_ABIERTO:
      Serial.println("Estado Abierto");
      if (flagBtnActivar == true)
      {
        flagBtnActivar = false;
        estadoMaquina = ESTADO_IR;
      }
      break;
    case ESTADO_ALARMA:
      Serial.println("Estado Alarma");

      sonidoAlarma();
      balizaLed ();
      if (flagBtnActivar == true)
      {
        flagBtnActivar = false;
        estadoMaquina = ESTADO_IR;
      }
      if (acceso2 == true)
      {
        acceso2 = false;
        estadoMaquina = ESTADO_IR;
      }
      break;
  }
}
void sonidoAlarma ()
{
  int duracion = 250;
  int frecmin = 2000;
  int frecmax = 4000;
  int i;
  for (i = frecmin; i <= frecmax; i++) {
    tone(PIN_BOCINA, i, duracion);
  }
  for (i = frecmax; i >= frecmin; i--) {
    tone(PIN_BOCINA, i, duracion);
  }
}

void balizaLed ()
{
  digitalWrite(PIN_LED, HIGH);
  if (seg == 1)
  {
    digitalWrite(PIN_LED, LOW);
  }
  if (seg == 2)
  {
    digitalWrite(PIN_LED, HIGH);
  }
  if (seg == 3)
  {
    digitalWrite(PIN_LED, LOW);
    seg = 0;
  }
}


void lecturaNFC()
{
  short codigo = 0;
  if (rfid.PICC_IsNewCardPresent()) { // new tag is available
    if (rfid.PICC_ReadCardSerial()) { // NUID has been readed
      MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
      Serial.print("RFID/NFC Tag Type: ");
      Serial.println(rfid.PICC_GetTypeName(piccType));

      // print NUID in Serial Monitor in the hex format
      Serial.print("UID:");
      for (int i = 0; i < rfid.uid.size; i++) {
        Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(rfid.uid.uidByte[i], HEX);
        codigo = codigo + rfid.uid.uidByte[i];
      }
      Serial.println(codigo);
      if (codigo == PASS)
      {
        Serial.println("Tarjeta valida");
        codigo = 0;
        acceso = true;
        acceso2 = true;
      }
      else {
        Serial.println("Tarjeta invalida");
        codigo = 0;
      }
      Serial.println();

      rfid.PICC_HaltA(); // halt PICC
      rfid.PCD_StopCrypto1(); // stop encryption on PCD
    }
  }
}

void TIMER()
{
  mSegBtnActivar = mSegBtnActivar + 1;
  mSeg = mSeg + 1;
  if (mSeg == 1000)
  {
    seg = seg + 1;
    mSeg = 0;
  }
}
