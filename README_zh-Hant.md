[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver SHT35

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/sht35/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

SHT35建立在全新和優化的CMOSens芯片之上，進一步提高了產品可靠性和精度規格。 SHT35提供了一系列新功能，如增強信號處理、兩個獨特和用戶可選IIC地址、一個可編程溫濕度極限的報警模式，以及高達1 MHz的通信速度。 DFN封裝的面積為2.5 × 2.5 mm2，高度為0.9 mm。這有助於SHT35集成到多種應用。此外，2.15至5.5 V的寬電源電壓範圍和多種可選接口可保證與不同集成要求的兼容性。總之，SHT35濕度傳感器系列融入了Sensirion作為行業領導者15年的經驗和心血，是一款超高性價比的產品。

LibDriver SHT35是LibDriver推出的SHT35的全功能驅動，該驅動提供溫濕度連續模式讀取和溫濕度單次模式讀取等功能並且它符合MISRA標準。

### 目錄

  - [說明](#說明)
  - [安裝](#安裝)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
    - [example alert](#example-alert)
  - [文檔](#文檔)
  - [貢獻](#貢獻)
  - [版權](#版權)
  - [聯繫我們](#聯繫我們)

### 說明

/src目錄包含了LibDriver SHT35的源文件。

/interface目錄包含了LibDriver SHT35與平台無關的IIC總線模板。

/test目錄包含了LibDriver SHT35驅動測試程序，該程序可以簡單的測試芯片必要功能。

/example目錄包含了LibDriver SHT35編程範例。

/doc目錄包含了LibDriver SHT35離線文檔。

/datasheet目錄包含了SHT35數據手冊。

/project目錄包含了常用Linux與單片機開發板的工程樣例。所有工程均採用shell腳本作為調試方法，詳細內容可參考每個工程裡面的README.md。

/misra目錄包含了LibDriver MISRA程式碼掃描結果。

### 安裝

參考/interface目錄下與平台無關的IIC總線模板，完成指定平台的IIC總線驅動。

將/src目錄，您使用平臺的介面驅動和您開發的驅動加入工程，如果您想要使用默認的範例驅動，可以將/example目錄加入您的工程。

### 使用

您可以參考/example目錄下的程式設計範例完成適合您的驅動，如果您想要使用默認的程式設計範例，以下是它們的使用方法。

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

### 文檔

在線文檔: [https://www.libdriver.com/docs/sht35/index.html](https://www.libdriver.com/docs/sht35/index.html)。

離線文檔: /doc/html/index.html。

### 貢獻

請參攷CONTRIBUTING.md。

### 版權

版權 (c) 2015 - 現在 LibDriver 版權所有

MIT 許可證（MIT）

特此免費授予任何獲得本軟件副本和相關文檔文件（下稱“軟件”）的人不受限制地處置該軟件的權利，包括不受限制地使用、複製、修改、合併、發布、分發、轉授許可和/或出售該軟件副本，以及再授權被配發了本軟件的人如上的權利，須在下列條件下：

上述版權聲明和本許可聲明應包含在該軟件的所有副本或實質成分中。

本軟件是“如此”提供的，沒有任何形式的明示或暗示的保證，包括但不限於對適銷性、特定用途的適用性和不侵權的保證。在任何情況下，作者或版權持有人都不對任何索賠、損害或其他責任負責，無論這些追責來自合同、侵權或其它行為中，還是產生於、源於或有關於本軟件以及本軟件的使用或其它處置。

### 聯繫我們

請聯繫lishifenging@outlook.com。