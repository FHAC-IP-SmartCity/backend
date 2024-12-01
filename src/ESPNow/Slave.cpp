#include "ESPNow/Slave.h"

// Initialisierung des statischen Instanzzeigers
ESPNowSlave *ESPNowSlave::instance = nullptr;

ESPNowSlave::ESPNowSlave(const uint8_t *masterMac) : device(masterMac) {}

void ESPNowSlave::init()
{
    // Instanzzeiger setzen
    instance = this;

    // Statische Callback-Funktion registrieren
    device.init(onReceiveStatic);
    pipeline.println("Slave: Initialisiert.");

    esp_now_register_recv_cb(onReceiveStatic);
}

void ESPNowSlave::loop()
{

    delay(1000);
}

// Statische Callback-Funktion
void ESPNowSlave::onReceiveStatic(const uint8_t *mac, const uint8_t *data, int len)
{
    if (mac == nullptr || data == nullptr || len == 0)
    {
        pipeline.println("Received empty data or invalid MAC address.");
        return;
    }

    // Process the received data
    pipeline.println("Data received from master:");

    // Send the received data using the pipeline
    std::string message = std::string("Received data: ") + std::string((char *)data, len);
    // TODO: Send the message using the pipeline to frontend

    // Split the message into two parts
    std::string delimiter = "ID: ";
    size_t pos = message.find(delimiter);
    if (pos != std::string::npos)
    {
        std::string data = message.substr(0, pos);
        std::string id = message.substr(pos + delimiter.length());
        pipeline.println((data).c_str());
        pipeline.println(("ID: " + id).c_str());
    }
    else
    {
        pipeline.println("ID not found in the message.");
    }
}

// Nicht-statische Methode für die eigentliche Verarbeitung
void ESPNowSlave::onReceive(const uint8_t *mac, const uint8_t *data, int len)
{
    pipeline.println("Slave: Daten empfangen.");
    pipeline.println(("Empfangene Daten: " + std::string((char *)data, len)).c_str());

    // Quittung senden
    std::string acknowledgment = "Quittung erhalten";
    if (device.send(acknowledgment))
    {
        pipeline.println("Slave: Quittung gesendet.");
    }
    else
    {
        pipeline.println("Slave: Fehler beim Senden der Quittung.");
    }
}
