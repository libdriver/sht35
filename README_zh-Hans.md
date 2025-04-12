[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver SHT35

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/sht35/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

SHT35建立在全新和优化的CMOSens芯片之上，进一步提高了产品可靠性和精度规格。SHT35提供了一系列新功能，如增强信号处理、两个独特和用户可选IIC地址、一个可编程温湿度极限的报警模式，以及高达1 MHz的通信速度。DFN封装的面积为2.5 × 2.5 mm2，高度为0.9 mm。这有助于SHT35集成到多种应用。此外，2.15至5.5 V的宽电源电压范围和多种可选接口可保证与不同集成要求的兼容性。总之，SHT35湿度传感器系列融入了Sensirion作为行业领导者15年的经验和心血，是一款超高性价比的产品。

LibDriver SHT35是LibDriver推出的SHT35的全功能驱动，该驱动提供温湿度连续模式读取和温湿度单次模式读取等功能并且它符合MISRA标准。

### 目录

  - [说明](#说明)
  - [安装](#安装)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
    - [example alert](#example-alert)
  - [文档](#文档)
  - [贡献](#贡献)
  - [版权](#版权)
  - [联系我们](#联系我们)

### 说明

/src目录包含了LibDriver SHT35的源文件。

/interface目录包含了LibDriver SHT35与平台无关的IIC总线模板。

/test目录包含了LibDriver SHT35驱动测试程序，该程序可以简单的测试芯片必要功能。

/example目录包含了LibDriver SHT35编程范例。

/doc目录包含了LibDriver SHT35离线文档。

/datasheet目录包含了SHT35数据手册。

/project目录包含了常用Linux与单片机开发板的工程样例。所有工程均采用shell脚本作为调试方法，详细内容可参考每个工程里面的README.md。

/misra目录包含了LibDriver MISRA代码扫描结果。

### 安装

参考/interface目录下与平台无关的IIC总线模板，完成指定平台的IIC总线驱动。

将/src目录，您使用平台的接口驱动和您开发的驱动加入工程，如果您想要使用默认的范例驱动，可以将/example目录加入您的工程。

### 使用

您可以参考/example目录下的编程范例完成适合您的驱动，如果您想要使用默认的编程范例，以下是它们的使用方法。

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

### 文档

在线文档: [https://www.libdriver.com/docs/sht35/index.html](https://www.libdriver.com/docs/sht35/index.html)。

离线文档: /doc/html/index.html。

### 贡献

请参考CONTRIBUTING.md。

### 版权

版权 (c) 2015 - 现在 LibDriver 版权所有

MIT 许可证（MIT）

特此免费授予任何获得本软件副本和相关文档文件（下称“软件”）的人不受限制地处置该软件的权利，包括不受限制地使用、复制、修改、合并、发布、分发、转授许可和/或出售该软件副本，以及再授权被配发了本软件的人如上的权利，须在下列条件下：

上述版权声明和本许可声明应包含在该软件的所有副本或实质成分中。

本软件是“如此”提供的，没有任何形式的明示或暗示的保证，包括但不限于对适销性、特定用途的适用性和不侵权的保证。在任何情况下，作者或版权持有人都不对任何索赔、损害或其他责任负责，无论这些追责来自合同、侵权或其它行为中，还是产生于、源于或有关于本软件以及本软件的使用或其它处置。

### 联系我们

请联系lishifenging@outlook.com。