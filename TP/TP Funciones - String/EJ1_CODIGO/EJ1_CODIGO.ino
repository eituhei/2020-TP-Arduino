//---- DEFINES ----
#define SERIAL               9600
#define CONTRASEnA_CORRECTA  "invitado"
#define MAIL_CORRECTO        "hola@chau.com"

//---- VARIABLES ----
String mailLeido;
String contrasenaLeida;
boolean validado;

//---- FUNCIONES ----
boolean checkUserPassword (String Correo, String Clave);
String mailRecibido ();
String contrasenaRecibida ();

void setup()
{
  Serial.begin(SERIAL);
}

void loop()
{
  mailLeido = ingresoPuertoSerie ("Mail recibido");
  contrasenaLeida = ingresoPuertoSerie ("Contrasena recibida");
  validado = checkUserPassword (mailLeido, contrasenaLeida);
    if (validado == true)
  {
    Serial.println("Bienvenidx");
  }
  else
  {
    Serial.println("Error en el mail o en la contrasena");
  }
}

String ingresoPuertoSerie (String informacionIngresada)
{
  String datoIngresado;
  while (Serial.available() == 0);
  while (Serial.available())
  {
    datoIngresado = Serial.readString();
    Serial.println(informacionIngresada);
    return datoIngresado;
  }


}
/* String mailRecibido ()
  {
  String mailIngresado;
  while (Serial.available() == 0);
  while (Serial.available())
  {
    mailIngresado = Serial.readString();
    Serial.println("Mail recibido");
    return mailIngresado;
  }
  }

  String contrasenaRecibida ()
  {
  String contrasenaIngresada;
  while (Serial.available() == 0);
  while (Serial.available())
  {
    contrasenaIngresada = Serial.readString();
    Serial.println("Contrasena recibida");
    return contrasenaIngresada;
  }
  }
*/
boolean checkUserPassword (String Correo, String Clave)
{
  if (Correo == MAIL_CORRECTO && Clave == CONTRASEnA_CORRECTA)
  {
    return true;
  }
  else
  {
    return false;
  }
}
