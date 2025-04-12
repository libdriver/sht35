### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

IIC Pin: SCL/SDA GPIO3/GPIO2.

GPIO Pin: INT GPIO17.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(sht35 REQUIRED)
```

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

6. Run sht35 alert test, ms is the timeout in ms, degree is the degree of limit, percentage is the percentage of limit.

   ```shell
   sht35 (-t alert | --test=alert) [--addr=<0 | 1>] [--timeout=<ms>] [--high-limit-temp=<degree>] [--high-limit-humi=<percentage>][--low-limit-temp=<degree>] [--low-limit-humi=<percentage>]
   ```

7. Run sht35 read function, num is read times.

   ```shell
   sht35 (-e read | --example=read) [--addr=<0 | 1>] [--times=<num>]
   ```

8. Run sht35 shot function, num is read times.

   ```shell
   sht35 (-e shot | --example=shot) [--addr=<0 | 1>] [--times=<num>]
   ```
9. Run sht35 alert function, ms is the timeout in ms, degree is the degree of limit, percentage is the percentage of limit.

   ```shell
   sht35 (-e alert | --example=alert) [--addr=<0 | 1>] [--timeout=<ms>] [--high-limit-temp=<degree>] [--high-limit-humi=<percentage>][--low-limit-temp=<degree>] [--low-limit-humi=<percentage>]
   ```
10. Run sht35 sn function.

   ```shell
   sht35 (-e sn | --example=sn) [--addr=<0 | 1>]
   ```

#### 3.2 Command Example

```shell
./sht35 -i

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
./sht35 -p

sht35: SCL connected to GPIO3(BCM).
sht35: SDA connected to GPIO2(BCM).
sht35: ALERT connected to GPIO17(BCM).
```

```shell
./sht35 -t reg --addr=0

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
sht35: sht35_get_status test.
sht35: check status 0x8070.
sht35: sht35_clear_status test.
sht35: check clear status ok.
sht35: sht35_get_serial_number test.
sht35: serial number is 0x10 0xE2 0x41 0x1F.
sht35: sht35_set_high_alert_limit/sht35_get_high_alert_limit test.
sht35: set is 0xF6F7.
sht35: clear is 0x934B.
sht35: check high alert limit set ok.
sht35: check high alert limit clear ok.
sht35: sht35_set_low_alert_limit/sht35_get_low_alert_limit test.
sht35: set is 0xDADD.
sht35: clear is 0x5609.
sht35: check low alert limit set ok.
sht35: check low alert limit clear ok.
sht35: sht35_alert_limit_convert_to_register test.
sht35: 80.00% 60.00C converted 0xCD33.
sht35: 22.00% -9.00C converted 0x3869.
sht35: finish register test.
```

```shell
./sht35 -t read --addr=0 --times=3

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
sht35: temperature is 29.13C.
sht35: humidity is 27.53%.
sht35: temperature is 29.65C.
sht35: humidity is 27.32%.
sht35: temperature is 29.79C.
sht35: humidity is 26.81%.
sht35: set rate 1Hz.
sht35: temperature is 29.85C.
sht35: humidity is 26.40%.
sht35: temperature is 29.82C.
sht35: humidity is 26.19%.
sht35: temperature is 30.00C.
sht35: humidity is 26.09%.
sht35: set rate 2Hz.
sht35: temperature is 29.93C.
sht35: humidity is 26.09%.
sht35: temperature is 30.02C.
sht35: humidity is 26.05%.
sht35: temperature is 29.96C.
sht35: humidity is 26.00%.
sht35: set rate 4Hz.
sht35: temperature is 29.90C.
sht35: humidity is 25.89%.
sht35: temperature is 29.93C.
sht35: humidity is 26.05%.
sht35: temperature is 29.99C.
sht35: humidity is 25.94%.
sht35: set rate 10Hz.
sht35: temperature is 29.93C.
sht35: humidity is 25.95%.
sht35: temperature is 30.06C.
sht35: humidity is 25.98%.
sht35: temperature is 29.93C.
sht35: humidity is 25.98%.
sht35: set medium repeatability.
sht35: set rate 0.5Hz.
sht35: temperature is 30.02C.
sht35: humidity is 25.99%.
sht35: temperature is 29.96C.
sht35: humidity is 26.00%.
sht35: temperature is 30.03C.
sht35: humidity is 26.26%.
sht35: set rate 1Hz.
sht35: temperature is 30.09C.
sht35: humidity is 26.33%.
sht35: temperature is 30.03C.
sht35: humidity is 26.28%.
sht35: temperature is 30.04C.
sht35: humidity is 26.05%.
sht35: set rate 2Hz.
sht35: temperature is 30.06C.
sht35: humidity is 25.99%.
sht35: temperature is 30.06C.
sht35: humidity is 25.86%.
sht35: temperature is 30.00C.
sht35: humidity is 25.91%.
sht35: set rate 4Hz.
sht35: temperature is 30.09C.
sht35: humidity is 25.95%.
sht35: temperature is 30.07C.
sht35: humidity is 25.89%.
sht35: temperature is 30.09C.
sht35: humidity is 25.90%.
sht35: set rate 10Hz.
sht35: temperature is 30.07C.
sht35: humidity is 25.84%.
sht35: temperature is 30.04C.
sht35: humidity is 25.93%.
sht35: temperature is 30.06C.
sht35: humidity is 25.90%.
sht35: set high repeatability.
sht35: set rate 0.5Hz.
sht35: temperature is 30.06C.
sht35: humidity is 25.95%.
sht35: temperature is 30.07C.
sht35: humidity is 25.95%.
sht35: temperature is 30.07C.
sht35: humidity is 25.95%.
sht35: set rate 1Hz.
sht35: temperature is 30.10C.
sht35: humidity is 26.03%.
sht35: temperature is 30.10C.
sht35: humidity is 25.89%.
sht35: temperature is 30.12C.
sht35: humidity is 25.86%.
sht35: set rate 2Hz.
sht35: temperature is 30.13C.
sht35: humidity is 25.89%.
sht35: temperature is 30.12C.
sht35: humidity is 25.85%.
sht35: temperature is 30.13C.
sht35: humidity is 25.80%.
sht35: set rate 4Hz.
sht35: temperature is 30.14C.
sht35: humidity is 25.62%.
sht35: temperature is 30.12C.
sht35: humidity is 25.75%.
sht35: temperature is 30.12C.
sht35: humidity is 25.78%.
sht35: set rate 10Hz.
sht35: temperature is 30.14C.
sht35: humidity is 25.89%.
sht35: temperature is 30.14C.
sht35: humidity is 25.94%.
sht35: temperature is 30.16C.
sht35: humidity is 25.97%.
sht35: single read.
sht35: set low repeatability.
sht35: temperature is 30.17C.
sht35: humidity is 26.02%.
sht35: temperature is 30.17C.
sht35: humidity is 25.88%.
sht35: temperature is 30.10C.
sht35: humidity is 25.95%.
sht35: set medium repeatability.
sht35: temperature is 30.16C.
sht35: humidity is 25.86%.
sht35: temperature is 30.16C.
sht35: humidity is 25.89%.
sht35: temperature is 30.17C.
sht35: humidity is 25.88%.
sht35: set high repeatability.
sht35: temperature is 30.16C.
sht35: humidity is 25.89%.
sht35: temperature is 30.16C.
sht35: humidity is 25.91%.
sht35: temperature is 30.17C.
sht35: humidity is 25.91%.
sht35: disable clock stretching.
sht35: temperature is 30.16C.
sht35: humidity is 25.92%.
sht35: temperature is 30.20C.
sht35: humidity is 25.94%.
sht35: temperature is 30.17C.
sht35: humidity is 25.86%.
sht35: finish read test.
```

```shell
./sht35 -t alert --addr=0 --timeout=10000 --high-limit-temp=30.0 --high-limit-humi=50.0 --low-limit-temp=25.0 --low-limit-humi=30.0

sht35: chip is Sensirion SHT35.
sht35: manufacturer is Sensirion.
sht35: interface is IIC.
sht35: driver version is 2.0.
sht35: min supply voltage is 2.4V.
sht35: max supply voltage is 5.5V.
sht35: max current is 1.50mA.
sht35: max temperature is 125.0C.
sht35: min temperature is -40.0C.
sht35: start alert test.
sht35: high limit temperature is 30.00C.
sht35: high limit humidity is 50.00%.
sht35: low limit temperature is 25.00C.
sht35: low limit humidity is 30.00%.
sht35: irq alert pending status.
sht35: irq humidity alert.
sht35: irq temperature alert.
sht35: finish alert test.
```

```shell
./sht35 -e read --addr=0 --times=3

sht35: 1/3.
sht35: temperature is 29.59C.
sht35: humidity is 25.88%.
sht35: 2/3.
sht35: temperature is 29.44C.
sht35: humidity is 26.00%.
sht35: 3/3.
sht35: temperature is 29.35C.
sht35: humidity is 26.11%.
```

```shell
./sht35 -e shot --addr=0 --times=3

sht35: 1/3.
sht35: temperature is 29.14C.
sht35: humidity is 26.40%.
sht35: 2/3.
sht35: temperature is 29.13C.
sht35: humidity is 26.43%.
sht35: 3/3.
sht35: temperature is 29.13C.
sht35: humidity is 26.47%.
```

```shell
./sht35 -e alert --addr=0 --timeout=10000 --high-limit-temp=30.0 --high-limit-humi=50.0 --low-limit-temp=25.0 --low-limit-humi=30.0

sht35: high limit temperature is 30.00C.
sht35: high limit humidity is 50.00%.
sht35: low limit temperature is 25.00C.
sht35: low limit humidity is 30.00%.
sht35: irq alert pending status.
sht35: irq humidity alert.
sht35: irq temperature alert.
sht35: finish.
```

```shell
./sht35 -e sn --addr=0

sht35: serial number is 0x10 0xE2 0x41 0x1F.
```

```shell
./sht35 -h

Usage:
  sht35 (-i | --information)
  sht35 (-h | --help)
  sht35 (-p | --port)
  sht35 (-t reg | --test=reg) [--addr=<0 | 1>]
  sht35 (-t read | --test=read) [--addr=<0 | 1>] [--times=<num>]
  sht35 (-t alert | --test=alert) [--addr=<0 | 1>] [--timeout=<ms>] [--high-limit-temp=<degree>] [--high-limit-humi=<percentage>]
        [--low-limit-temp=<degree>] [--low-limit-humi=<percentage>]
  sht35 (-e read | --example=read) [--addr=<0 | 1>] [--times=<num>]
  sht35 (-e shot | --example=shot) [--addr=<0 | 1>] [--times=<num>]
  sht35 (-e alert | --example=alert) [--addr=<0 | 1>] [--timeout=<ms>] [--high-limit-temp=<degree>] [--high-limit-humi=<percentage>]
        [--low-limit-temp=<degree>] [--low-limit-humi=<percentage>]

Options:
      --addr=<0 | 1>    Set the addr pin.([default: 0])
  -e <read | shot | alert | sn>, --example=<read | shot | alert | sn>
                        Run the driver example.
      --low-limit-temp  Low limit temperature in degress.([default: 25.0])
      --low-limit-humi  Low limit humidity in percentage.([default: 30.0])
  -h, --help            Show the help.
      --high-limit-temp High limit temperature in degress.([default: 30.0])
      --high-limit-humi High limit humidity in percentage.([default: 50.0])
  -i, --information     Show the chip information.
  -p, --port            Display the pin connections of the current board.
  -t <reg | read | alert>, --test=<reg | read | alert>
                        Run the driver test.
      --times=<num>     Set the running times.([default: 3])
      --timeout=<ms>    Set timeout in ms.([default: 10000])
```

