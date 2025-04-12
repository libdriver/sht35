[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver SHT35
[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/sht35/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

SHT35 ist die nächste Generation der Temperatur- und Feuchtigkeitssensoren von Sensirion. Es baut auf einem neuen CMOSens-Sensorchip auf, der das Herzstück der neuen Feuchtigkeits- und Temperaturplattform von Sensirion bildet. Der SHT35 hat im Vergleich zu seinem Vorgänger eine erhöhte Intelligenz, Zuverlässigkeit und verbesserte Genauigkeitsspezifikationen. Seine Funktionalität umfasst eine verbesserte Signalverarbeitung, zwei eindeutige und vom Benutzer wählbare IIC-Adressen und Kommunikationsgeschwindigkeiten von bis zu 1 MHz. Das DFN-Gehäuse hat eine Grundfläche von 2,5 x 2,5 mm2 bei einer Höhe von 0,9 mm. Dies ermöglicht die Integration des SHT35 in eine Vielzahl von Anwendungen. Zudem garantiert der weite Versorgungsspannungsbereich von 2,4 V bis 5,5 V die Kompatibilität mit unterschiedlichsten Einbausituationen. Alles in allem stecken im SHT35 15 Jahre Erfahrung von Sensirion, dem führenden Unternehmen in der Feuchtigkeitssensorbranche.

LibDriver SHT35 ist der voll funktionsfähige Treiber von SHT35, der von LibDriver gestartet wurde. Er bietet Funktionen zum kontinuierlichen Lesen von Temperatur und Feuchtigkeit sowie zum Lesen von Temperatur und Feuchtigkeit im Einzelmodus. LibDriver ist MISRA-konform.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
    - [example alert](#example-alert)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver SHT35-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver SHT35 IIC.

/test enthält den Testcode des LibDriver SHT35-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver SHT35-Beispielcode.

/doc enthält das LibDriver SHT35-Offlinedokument.

/Datenblatt enthält SHT35-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige IIC-Schnittstellenvorlage und stellen Sie Ihren Plattform-IIC-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

#### example basic

```C
#include "driver_sht35_basic.h"

uint8_t res;
uint8_t i;
uint8_t sn[4];
float temperature;
float humidity;

res = sht35_basic_init(SHT35_ADDRESS_0);
if (res != 0)
{
    return 1;
}

...

res = sht35_basic_get_serial_number(sn);
if (res != 0)
{
    sht35_basic_deinit();

    return 1;
}
sht35_interface_debug_print("sht35: serial number is 0x%02X 0x%02X 0x%02X 0x%02X.\n", sn[0], sn[1], sn[2], sn[3]);

...
    
for (i = 0; i < 3; i++)
{
    sht35_interface_delay_ms(1000);
    res = sht35_basic_read((float *)&temperature, (float *)&humidity);
    if (res != 0)
    {
        (void)sht35_basic_deinit();

        return 1;
    }
    sht35_interface_debug_print("sht35: temperature is %0.2fC.\n", temperature);
    sht35_interface_debug_print("sht35: humidity is %0.2f%%.\n", humidity);
    
    ...
    
}

...

(void)sht35_basic_deinit();

return 0;
```

#### example shot

```C
#include "driver_sht35_shot.h"

uint8_t res;
uint8_t i;
uint8_t sn[4];
float temperature;
float humidity;

res = sht35_shot_init(SHT35_ADDRESS_0);
if (res != 0)
{
    return 1;
}

...
    
res = sht35_shot_get_serial_number(sn);
if (res != 0)
{
    sht35_shot_deinit();

    return 1;
}
sht35_interface_debug_print("sht35: serial number is 0x%02X 0x%02X 0x%02X 0x%02X.\n", sn[0], sn[1], sn[2], sn[3]);

...
    
for (i = 0; i < 3; i++)
{
    sht35_interface_delay_ms(1000);
    res = sht35_shot_read((float *)&temperature, (float *)&humidity);
    if (res != 0)
    {
        (void)sht35_shot_deinit();

        return 1;
    }
    sht35_interface_debug_print("sht35: temperature is %0.2fC.\n", temperature);
    sht35_interface_debug_print("sht35: humidity is %0.2f%%.\n", humidity);
    
    ...
    
}

...

(void)sht35_shot_deinit();

return 0;
```

#### example alert

```C
#include "driver_sht35_alert.h"

uint8_t res;
uint32_t i;
uint8_t sn[4];
float high_limit_temperature = 30.0f;
float high_limit_humidity = 50.0f;
float low_limit_temperature = 25.0f;
float low_limit_humidity = 30.0f;

static void a_receive_callback(uint16_t type)
{
    switch (type)
    {
        case SHT35_STATUS_ALERT_PENDING_STATUS :
        {
            sht35_interface_debug_print("sht35: irq alert pending status.\n");
            
            break;
        }
        case SHT35_STATUS_HUMIDITY_ALERT :
        {
            sht35_interface_debug_print("sht35: irq humidity alert.\n");
            
            break;
        }
        case SHT35_STATUS_TEMPERATURE_ALERT :
        {
            sht35_interface_debug_print("sht35: irq temperature alert.\n");
            
            break;
        }
    }
}

g_gpio_irq = sht35_alert_irq_handler;
res = gpio_interrupt_init();
if (res != 0)
{
    g_gpio_irq = NULL;

    return 1;
}

...

res = sht35_alert_init(addr, a_receive_callback,
                       high_limit_temperature, high_limit_humidity,
                       high_limit_temperature - 1.0f, high_limit_humidity + 1.0f,
                       low_limit_temperature, low_limit_humidity,
                       low_limit_temperature - 1.0f, low_limit_humidity + 1.0f);
if (res != 0)
{
    gpio_interrupt_deinit();
    g_gpio_irq = NULL;

    return 1;
}

...
    
res = sht35_alert_get_serial_number(sn);
if (res != 0)
{
    sht35_alert_deinit();

    return 1;
}
sht35_interface_debug_print("sht35: serial number is 0x%02X 0x%02X 0x%02X 0x%02X.\n", sn[0], sn[1], sn[2], sn[3]);

...
    
/* loop */
for (i = 0; i < 10000; i++)
{
    /* delay 1ms */
    sht35_interface_delay_ms(1);
}

...
    
gpio_interrupt_deinit();
g_gpio_irq = NULL;
(void)sht35_alert_deinit();

return 0;
```

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/sht35/index.html](https://www.libdriver.com/docs/sht35/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.