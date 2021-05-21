//---- Definiciones ----
#define CANTIDAD_DESEADA 20

//---- Varibles ----
int numero;
int numeroMaximo;
int numeroMinimo;
int numeroContador = 0 ;
float numeroPromedio = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.println("Ingresar 20 números");

  for (numeroContador = 0; numeroContador < CANTIDAD_DESEADA; numeroContador = numeroContador + 1)
  {

    Serial.print("Vas por el número:");
    Serial.println(numeroContador + 1);

    while (Serial.available () == 0)
    {
    }

    numero = Serial.parseInt ();

    while (Serial.available())
    {
      Serial.read();
    }

    Serial.println(numero);

    if ( numeroContador == 0) 
    {
      numeroMaximo = numero;
      numeroMinimo = numero;
    }
    
    numeroPromedio = numeroPromedio + numero;
    
    if (numero > numeroMaximo)
    {
      numeroMaximo = numero;
    }
    
    if (numero < numeroMinimo)
    {
      numeroMinimo = numero;
    }
  }

  Serial.print("El número mayor es ");
  Serial.println(numeroMaximo);
  Serial.print("El número menor es ");
  Serial.println(numeroMinimo);
  Serial.print("El promedio es ");
  Serial.println( numeroPromedio / CANTIDAD_DESEADA);
}
