//---- Cases ----
#define CASE_ROJO     'r'
#define CASE_VERDE    'g'
#define CASE_AZUL     'b'
 
//---- Salidas ----
#define PIN_LED_ROJO   3
#define PIN_LED_VERDE  4
#define PIN_LED_AZUL   5

//---- Variables ----
char letra;
 
void setup() 
{
    Serial.begin(9600);  
   
    pinMode(PIN_LED_ROJO,OUTPUT);
    pinMode(PIN_LED_VERDE,OUTPUT);
    pinMode(PIN_LED_AZUL,OUTPUT);
}
 
void loop()
{
 Serial.println("Ingresa una letra");
 delay(3000);
 
 if(Serial.available()>0)
 {
 letra=Serial.read();
 Serial.println(letra); 
 }
 
 if(letra!=CASE_VERDE && letra!=CASE_AZUL)
 {
  letra==CASE_ROJO;
 }
  
 switch(letra)
 {
  case CASE_ROJO:
            digitalWrite(PIN_LED_ROJO,HIGH);
            digitalWrite(PIN_LED_VERDE,LOW);
            digitalWrite(PIN_LED_AZUL,LOW);
            break;
 
  case CASE_VERDE:
            digitalWrite(PIN_LED_ROJO,LOW);
            digitalWrite(PIN_LED_VERDE,HIGH);
            digitalWrite(PIN_LED_AZUL,LOW);
            break;  
 
   case CASE_AZUL:
            digitalWrite(PIN_LED_ROJO,LOW);
            digitalWrite(PIN_LED_VERDE,LOW);
            digitalWrite(PIN_LED_AZUL,HIGH);
            break;                            
 }
}
 
