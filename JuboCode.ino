// NFC Libraries

#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>

// DFPlayer Libraries

#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

// NFC Objects

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);

// DFPlayer Objects

SoftwareSerial DFPlayerSerial(10, 11); // RX, TX

String lastDiskID;

void playDisk(NfcTag disk);

void setup(void) {
  Serial.begin(9600);

  // NFC
  nfc.begin(true);
  delay(1000);
  // DFP
  
  DFPlayerSerial.begin(9600);
  mp3_set_serial(DFPlayerSerial);
  mp3_set_volume(30);
  mp3_set_EQ(0);
  delay(1000);
}

void loop(void) {
  // Serial.println("\nScan a NFC tag\n");
  if (nfc.tagPresent()) {
    NfcTag disk = nfc.read();
    if (disk.getUidString() != lastDiskID) {
      lastDiskID = disk.getUidString();
      if (disk.hasNdefMessage()) {
        NdefMessage message = disk.getNdefMessage();
        NdefRecord record = message.getRecord(0);
      
        int payloadLength = record.getPayloadLength();
        byte payload[payloadLength];
        record.getPayload(payload);
      
      
        String payloadAsString = ""; // Processes the message as a string vs as a HEX value
        for (int c = 3; c < payloadLength; c++) {
          payloadAsString += (char)payload[c];  
        }
          
      
        int diskNumber = payloadAsString.toInt();
        Serial.println("PUTO");
        Serial.println(diskNumber);
        //mp3_play(diskNumber);
      }
    }
    delay(5000);
  }
}