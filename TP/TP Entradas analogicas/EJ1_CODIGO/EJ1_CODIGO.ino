//---- Delay ----
#define TIEMPO_DELAY 50 

//---- LEDS ----
#define PIN_LED_A0 4
#define PIN_LED_A1 5

//---- Entradas analogicas ----
#define SENSOR_ANALOGICO_0 A0
#define SENSOR_ANALOGICO_1 A1

//---- Variables ----
float sensorValor1 = 0;
float sensorVoltaje1;
float sensorValor2 = 0;
float sensorVoltaje2;

void setup()
{
  pinMode (PIN_LED_A0, OUTPUT);
  pinMode (PIN_LED_A1, OUTPUT);
  Serial.begin (9600);
}

void loop()
{
  sensorValor1 = analogRead(A0);
  sensorVoltaje1 = (sensorValor1 * 5) / 1023;

  sensorValor2 = analogRead(A1);
  sensorVoltaje2 = (sensorValor2 * 5) / 1023;

  Serial.print("Sensor A0 =  ");
  Serial.print(sensorVoltaje1);
  Serial.println("V");
  Serial.print("Sensor A1 =  ");
  Serial.print(sensorVoltaje2);
  Serial.println("V");

  delay (TIEMPO_DELAY);

  if(sensorVoltaje1 > sensorVoltaje2)
  {
    digitalWrite(PIN_LED_A1, LOW);
    digitalWrite(PIN_LED_A0, HIGH);
  }
  
   if(sensorVoltaje1 < sensorVoltaje2)
  {
    digitalWrite(PIN_LED_A0, LOW);
    digitalWrite(PIN_LED_A1, HIGH);
  }
  
  if(sensorVoltaje1 == sensorVoltaje2)
  {
    digitalWrite(PIN_LED_A0, HIGH);
    digitalWrite(PIN_LED_A1, HIGH);
  }
}
