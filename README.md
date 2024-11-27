# Backend

Der Code des Mikrocontrollers welcher die Stadt interaktiv macht
___

## Components and technologies

### Microcontroller

We use the NodeMCU 32S
It has all feature we need:

- Wifi Connection
- UART
- USB-C

It works on 3.3V

### Sensors and other hardware

To create a interactive SmartCity we use different sensors to track:

- temperature
- position
- counts
- time
- and other

### Dashboard

See the other repo: [Frontend](https://github.com/FHAC-IP-SmartCity/frontend)

### Lego

The City will be built with Lego

___

## Get started

1. Installiere PlatformIO
Stelle sicher, dass PlatformIO auf dem neuen PC installiert ist. Wenn es noch nicht installiert ist, kannst du es mit folgenden Schritten tun:

Installiere VSCode (falls noch nicht geschehen).
Installiere die PlatformIO IDE-Erweiterung für VSCode:
Öffne VSCode und gehe zu "Extensions" (Erweiterungen) und suche nach PlatformIO.
Installiere die PlatformIO IDE-Erweiterung.

2. Übertrage das Projekt
Kopiere den gesamten Projektordner auf den neuen PC. Das bedeutet, du musst den gesamten Ordner, der die PlatformIO-Projektdatei (platformio.ini), den Code und die Bibliotheken enthält, auf den neuen PC übertragen.

3. Konfiguriere die Abhängigkeiten
In der platformio.ini-Datei sind bereits einige Abhängigkeiten konfiguriert, z. B. MFRC522 und libCBOR. PlatformIO wird diese Abhängigkeiten automatisch herunterladen, wenn das Projekt auf dem neuen PC geöffnet wird, solange du eine Internetverbindung hast.

Wenn du zusätzliche Abhängigkeiten verwendest (wie dotenv in deinem Beispiel), musst du sicherstellen, dass diese ebenfalls auf dem neuen PC installiert sind. Du kannst dies durch den Befehl in der PlatformIO-CLI tun:

`pio lib install`
Der lib_deps Abschnitt in der platformio.ini-Datei listet bereits die benötigten Bibliotheken auf.

4. Überprüfe den Pfad zu den Bibliotheken
In der platformio.ini wird der Pfad zu den zusätzlichen Bibliotheken (lib_extra_dirs) angegeben:

`lib_extra_dirs = ~/Documents/Arduino/libraries`
Achte darauf, dass der Pfad korrekt auf das Verzeichnis der Arduino-Bibliotheken auf dem neuen PC verweist. Wenn der Pfad unterschiedlich ist, musst du den Pfad zu den Bibliotheken in der platformio.ini anpassen.

Alternativ kannst du diese Bibliotheken direkt im Projektordner ablegen, um diese Abhängigkeit zu vermeiden.
5. Installiere die benötigten Node.js-Abhängigkeiten (falls erforderlich)
Deine package.json-Datei enthält die dotenv-Abhängigkeit, die in deinem Projekt verwendet wird. Auf dem neuen PC musst du sicherstellen, dass Node.js und npm (Node Package Manager) installiert sind.

Installiere Node.js, falls noch nicht geschehen (über nodejs.org).

Installiere die Abhängigkeiten:

`npm install`
Dadurch wird die dotenv-Abhängigkeit und alle weiteren Abhängigkeiten aus der package.json installiert.

6. Komponenten und Bibliotheken
Wenn dein Projekt spezielle Hardwarekomponenten wie den ESP32 oder einen RFID-Reader verwendet, stelle sicher, dass du die entsprechenden Treiber und Tools für diese Geräte installiert hast.

Der ESP32-Treiber wird in PlatformIO bereits mit der platform = espressif32-Zeile konfiguriert, aber stelle sicher, dass du die entsprechenden USB-Treiber für den ESP32 auf dem neuen PC installiert hast, falls dies erforderlich ist.
7. Projekt in PlatformIO öffnen
Öffne das Projekt im VSCode mit PlatformIO.

PlatformIO sollte die platformio.ini-Datei automatisch erkennen und alle Abhängigkeiten herunterladen.

Du kannst das Projekt auch über die PlatformIO CLI mit dem folgenden Befehl öffnen:

`pio project init`
8. Upload und Serial Monitor
Wenn alles eingerichtet ist, kannst du dein Projekt auf das Zielgerät hochladen und den Serial Monitor öffnen:

Lade das Projekt hoch:

`pio run --target upload`
(Müsste auch über die Extension funktioniern, wenn du oben rechts auf das Icon klickst.

Öffne den Serial Monitor:

`pio device monitor`
Damit solltest du dein Projekt problemlos auf einem anderen PC zum Laufen bringen können. Stelle sicher, dass alle Bibliotheken und Abhängigkeiten korrekt installiert sind und dass alle Hardwarekomponenten ordnungsgemäß angeschlossen sind.

Library von PlatformIO
libCBOR  und MFRC522
___
