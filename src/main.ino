#include <esp_now.h>
#include <WiFi.h>

// Callback für den Empfang von Daten
void onDataReceived(const uint8_t *mac_addr, const uint8_t *data, int data_len)
{
    Serial.print("Nachricht empfangen von ");
    for (int i = 0; i < 6; i++)
    {
        Serial.printf("%02X", mac_addr[i]);
        if (i < 5)
            Serial.print(":");
    }
    Serial.println();

    // Empfangene Daten anzeigen
    Serial.print("Daten: ");
    for (int i = 0; i < data_len; i++)
    {
        Serial.print((char)data[i]);
    }
    Serial.println();

    // Quittung senden
    String acknowledgment = "Quittung erhalten für UID";
    esp_now_send(mac_addr, (uint8_t *)acknowledgment.c_str(), acknowledgment.length());
}

void setup()
{
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    Serial.println("Slave wird initialisiert...");

    if (esp_now_init() != ESP_OK)
    {
        Serial.println("Fehler beim Initialisieren von ESP-NOW!");
        return;
    }

    esp_now_register_recv_cb(onDataReceived);
    Serial.println("Slave ist bereit, Nachrichten zu empfangen.");
}

void loop()
{
    delay(1000); // Warteschleife, Slave wartet auf Nachrichten
}
