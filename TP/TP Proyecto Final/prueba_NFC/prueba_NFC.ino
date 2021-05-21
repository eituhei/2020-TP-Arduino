#include <emulatetag.h>
#include <llcp.h>
#include <mac_link.h>
#include <PN532.h>
#include <PN532Interface.h>
#include <PN532_debug.h>
#include <snep.h>

#include <PN532_SWHSU.h>

#include <SoftwareSerial.h>

SoftwareSerial SWSerial( 10, 11 ); // RX, TX

PN532_SWHSU pn532swhsu( SWSerial );

PN532 nfc( pn532swhsu );


void setup(void) {

  Serial.begin(9600);

  Serial.println("Hola Maker!");

  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();

  if (! versiondata) {

    Serial.print("Modulo PN53x no encontrado");

    while (1); // Halt

  }

  // Got valid data, print it out!

  Serial.print("Encontrado chip PN5"); Serial.println((versiondata >> 24) & 0xFF, HEX);

  Serial.print("Firmware ver. "); Serial.print((versiondata >> 16) & 0xFF, DEC);

  Serial.print('.'); Serial.println((versiondata >> 8) & 0xFF, DEC);

  // Configure board to read RFID tags

  nfc.SAMConfig();

  Serial.println("Esperando a una tarjeta ISO14443A...");

}

void loop(void) {

  boolean success;

  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID

  uint8_t uidLength;                       // Length of the UID (4 or 7 bytes depending on ISO14443A card type)

  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);

  if (success) {

    Serial.println("Tarjeta encontrada");

    Serial.print("UID Length: "); Serial.print(uidLength, DEC); Serial.println(" bytes");

    Serial.print("UID Value: ");

    for (uint8_t i = 0; i < uidLength; i++)

    {

      Serial.print(" 0x"); Serial.print(uid[i], HEX);

    }

    Serial.println("");

    // 1 second halt

    delay(1000);

  }

  else

  {

    // PN532 probably timed out waiting for a card

    Serial.println("Tiempo expirado! Esperando otra tarjeta...");

  }

}
