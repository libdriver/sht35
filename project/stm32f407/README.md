### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

IIC Pin: SCL/SDA PB8/PB9.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. SHT35

#### 3.1 Command Instruction

1. Show sht35 chip and driver information.

   ```shell
   sht35 (-i | --information)
   ```

2. Show sht35 help.

   ```shell
   sht35 (-h | --help)
   ```

3. Show sht35 pin connections of the current board.

   ```shell
   sht35 (-p | --port)
   ```

4. Run sht35 register test.

   ```shell
   sht35 (-t reg | --test=reg) [--addr=<0 | 1>]
   ```

5. Run sht35 read test, num is test times.

   ```shell
   sht35 (-t read | --test=read) [--addr=<0 | 1>] [--times=<num>]
   ```

6. Run sht35 read function, num is read times.

   ```shell
   sht35 (-e read | --example=read) [--addr=<0 | 1>] [--times=<num>]
   ```

7. Run sht35 shot function, num is read times.

   ```shell
   sht35 (-e shot | --example=shot) [--addr=<0 | 1>] [--times=<num>]
   ```

#### 3.2 Command Example

```shell
sht35 -i

sht35: chip is Sensirion SHT35.
sht35: manufacturer is Sensirion.
sht35: interface is IIC.
sht35: driver version is 2.0.
sht35: min supply voltage is 2.4V.
sht35: max supply voltage is 5.5V.
sht35: max current is 1.50mA.
sht35: max temperature is 125.0C.
sht35: min temperature is -40.0C.
```

```shell
sht35 -p

sht35: SCL connected to GPIOB PIN8.
sht35: SDA connected to GPIOB PIN9.
```

```shell
sht35 -t reg --addr=0

sht35: chip is Sensirion SHT35.
sht35: manufacturer is Sensirion.
sht35: interface is IIC.
sht35: driver version is 2.0.
sht35: min supply voltage is 2.4V.
sht35: max supply voltage is 5.5V.
sht35: max current is 1.50mA.
sht35: max temperature is 125.0C.
sht35: min temperature is -40.0C.
sht35: start register test.
sht35: sht35_set_addr_pin/sht35_get_addr_pin test.
sht35: set address pin 0.
sht35: check addr pin ok.
sht35: set address pin 1.
sht35: check addr pin ok.
sht35: sht35_set_repeatability/sht35_get_repeatability test.
sht35: set repeatability high.
sht35: check repeatability pin ok.
sht35: set repeatability medium.
sht35: check repeatability pin ok.
sht35: set repeatability low.
sht35: check repeatability pin ok.
sht35: set art test.
sht35: check art ok.
sht35: set heater test.
sht35: enable heater.
sht35: check heater ok.
sht35: disable heater.
sht35: check heater ok.
sht35: get status test.
sht35: check status 0x8070.
sht35: clear status test.
sht35: check clear status ok.
sht35: finish register test.
```

```shell
sht35 -t read --addr=0 --times=3

sht35: chip is Sensirion SHT35.
sht35: manufacturer is Sensirion.
sht35: interface is IIC.
sht35: driver version is 2.0.
sht35: min supply voltage is 2.4V.
sht35: max supply voltage is 5.5V.
sht35: max current is 1.50mA.
sht35: max temperature is 125.0C.
sht35: min temperature is -40.0C.
sht35: start read test.
sht35: continuous read.
sht35: set low repeatability.
sht35: set rate 0.5Hz.
sht35: temperature is 28.95C.
sht35: humidity is 29.02%.
sht35: temperature is 30.05C.
sht35: humidity is 28.77%.
sht35: temperature is 30.36C.
sht35: humidity is 28.13%.
sht35: set rate 1Hz.
sht35: temperature is 30.67C.
sht35: humidity is 25.99%.
sht35: temperature is 30.70C.
sht35: humidity is 25.56%.
sht35: temperature is 30.87C.
sht35: humidity is 25.04%.
sht35: set rate 2Hz.
sht35: temperature is 30.90C.
sht35: humidity is 25.20%.
sht35: temperature is 30.99C.
sht35: humidity is 25.27%.
sht35: temperature is 30.94C.
sht35: humidity is 25.27%.
sht35: set rate 4Hz.
sht35: temperature is 31.03C.
sht35: humidity is 25.30%.
sht35: temperature is 30.98C.
sht35: humidity is 25.22%.
sht35: temperature is 30.97C.
sht35: humidity is 25.41%.
sht35: set rate 10Hz.
sht35: temperature is 30.98C.
sht35: humidity is 25.40%.
sht35: temperature is 31.11C.
sht35: humidity is 25.48%.
sht35: temperature is 31.14C.
sht35: humidity is 25.51%.
sht35: set medium repeatability.
sht35: set rate 0.5Hz.
sht35: temperature is 31.08C.
sht35: humidity is 25.55%.
sht35: temperature is 31.12C.
sht35: humidity is 25.39%.
sht35: temperature is 31.21C.
sht35: humidity is 25.27%.
sht35: set rate 1Hz.
sht35: temperature is 31.22C.
sht35: humidity is 25.20%.
sht35: temperature is 31.29C.
sht35: humidity is 25.46%.
sht35: temperature is 31.33C.
sht35: humidity is 25.48%.
sht35: set rate 2Hz.
sht35: temperature is 31.32C.
sht35: humidity is 25.95%.
sht35: temperature is 31.39C.
sht35: humidity is 26.07%.
sht35: temperature is 31.36C.
sht35: humidity is 26.10%.
sht35: set rate 4Hz.
sht35: temperature is 31.43C.
sht35: humidity is 25.93%.
sht35: temperature is 31.45C.
sht35: humidity is 25.83%.
sht35: temperature is 31.45C.
sht35: humidity is 25.70%.
sht35: set rate 10Hz.
sht35: temperature is 31.45C.
sht35: humidity is 25.56%.
sht35: temperature is 31.43C.
sht35: humidity is 25.34%.
sht35: temperature is 31.46C.
sht35: humidity is 25.24%.
sht35: set high repeatability.
sht35: set rate 0.5Hz.
sht35: temperature is 31.54C.
sht35: humidity is 25.31%.
sht35: temperature is 31.49C.
sht35: humidity is 25.19%.
sht35: temperature is 31.52C.
sht35: humidity is 25.23%.
sht35: set rate 1Hz.
sht35: temperature is 31.62C.
sht35: humidity is 25.54%.
sht35: temperature is 31.59C.
sht35: humidity is 25.55%.
sht35: temperature is 31.62C.
sht35: humidity is 25.74%.
sht35: set rate 2Hz.
sht35: temperature is 31.63C.
sht35: humidity is 25.60%.
sht35: temperature is 31.65C.
sht35: humidity is 25.74%.
sht35: temperature is 31.65C.
sht35: humidity is 25.74%.
sht35: set rate 4Hz.
sht35: temperature is 31.69C.
sht35: humidity is 25.60%.
sht35: temperature is 31.67C.
sht35: humidity is 25.64%.
sht35: temperature is 31.67C.
sht35: humidity is 25.59%.
sht35: set rate 10Hz.
sht35: temperature is 31.76C.
sht35: humidity is 25.45%.
sht35: temperature is 31.72C.
sht35: humidity is 25.09%.
sht35: temperature is 31.75C.
sht35: humidity is 24.97%.
sht35: single read.
sht35: set low repeatability.
sht35: temperature is 31.83C.
sht35: humidity is 24.81%.
sht35: temperature is 31.75C.
sht35: humidity is 24.46%.
sht35: temperature is 31.72C.
sht35: humidity is 24.31%.
sht35: set medium repeatability.
sht35: temperature is 31.73C.
sht35: humidity is 24.23%.
sht35: temperature is 31.72C.
sht35: humidity is 24.02%.
sht35: temperature is 31.69C.
sht35: humidity is 23.95%.
sht35: set high repeatability.
sht35: temperature is 31.76C.
sht35: humidity is 23.81%.
sht35: temperature is 31.76C.
sht35: humidity is 23.75%.
sht35: temperature is 31.76C.
sht35: humidity is 23.62%.
sht35: disable clock stretching.
sht35: temperature is 31.76C.
sht35: humidity is 23.46%.
sht35: temperature is 31.81C.
sht35: humidity is 23.68%.
sht35: temperature is 31.77C.
sht35: humidity is 24.37%.
sht35: finish read test.
```

```shell
sht35 -e read --addr=0 --times=3

sht35: 1/3.
sht35: temperature is 31.29C.
sht35: humidity is 26.11%.
sht35: 2/3.
sht35: temperature is 30.98C.
sht35: humidity is 26.03%.
sht35: 3/3.
sht35: temperature is 30.80C.
sht35: humidity is 25.91%.
```

```shell
sht35 -e shot --addr=0 --times=3

sht35: 1/3.
sht35: temperature is 29.93C.
sht35: humidity is 27.01%.
sht35: 2/3.
sht35: temperature is 29.86C.
sht35: humidity is 26.91%.
sht35: 3/3.
sht35: temperature is 29.86C.
sht35: humidity is 27.07%.
```

```shell
sht35 -h

Usage:
  sht35 (-i | --information)
  sht35 (-h | --help)
  sht35 (-p | --port)
  sht35 (-t reg | --test=reg) [--addr=<0 | 1>]
  sht35 (-t read | --test=read) [--addr=<0 | 1>] [--times=<num>]
  sht35 (-e read | --example=read) [--addr=<0 | 1>] [--times=<num>]
  sht35 (-e shot | --example=shot) [--addr=<0 | 1>] [--times=<num>]

Options:
      --addr=<0 | 1>    Set the addr pin.([default: 0])
  -e <read | shot>, --example=<read | shot>
                        Run the driver example.
  -h, --help            Show the help.
  -i, --information     Show the chip information.
  -p, --port            Display the pin connections of the current board.
  -t <reg | read>, --test=<reg | read>
                        Run the driver test.
      --times=<num>     Set the running times.([default: 3])
```

