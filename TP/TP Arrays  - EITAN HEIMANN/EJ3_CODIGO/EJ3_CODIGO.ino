#include <string.h>

//---- DEFINES ----
#define BAUDIOS 9600

//---- VECTORES ----
char texto [11];

//---- VARIABLES ----
int elementos;

//---- FUNCIONES ----
void toUpper (char vector [], int cant_elem);

void setup() {
  Serial.begin(BAUDIOS);

  strcpy(texto, "coronavirus");
  Serial.println(texto);

  elementos = sizeof(texto) / sizeof(texto[0]);
  
  toUpper (texto, elementos);
  Serial.println(texto);
}

void loop() 
{
  
}

void toUpper (char vector [], int cant_elem)
{
  int indice;
  
  for (indice = 0; indice < cant_elem; indice = indice + 1)
  {
    if (vector[indice] >= 'a' && vector[indice] <= 'z')
    {
      vector[indice] = vector[indice] - 32;
    }
  }
}
