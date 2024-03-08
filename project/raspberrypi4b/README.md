### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

IIC Pin: SCL/SDA GPIO3/GPIO2.

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
sht35: get status test.
sht35: check status 0x8070.
sht35: clear status test.
sht35: check clear status ok.
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
sht35: temperature is 28.17C.
sht35: humidity is 27.32%.
sht35: temperature is 29.21C.
sht35: humidity is 27.32%.
sht35: temperature is 29.57C.
sht35: humidity is 27.50%.
sht35: set rate 1Hz.
sht35: temperature is 29.85C.
sht35: humidity is 26.48%.
sht35: temperature is 29.93C.
sht35: humidity is 26.46%.
sht35: temperature is 29.96C.
sht35: humidity is 25.87%.
sht35: set rate 2Hz.
sht35: temperature is 29.98C.
sht35: humidity is 25.83%.
sht35: temperature is 29.99C.
sht35: humidity is 25.95%.
sht35: temperature is 30.12C.
sht35: humidity is 25.71%.
sht35: set rate 4Hz.
sht35: temperature is 30.09C.
sht35: humidity is 25.91%.
sht35: temperature is 30.08C.
sht35: humidity is 25.95%.
sht35: temperature is 30.06C.
sht35: humidity is 25.86%.
sht35: set rate 10Hz.
sht35: temperature is 30.19C.
sht35: humidity is 25.69%.
sht35: temperature is 30.23C.
sht35: humidity is 25.74%.
sht35: temperature is 30.22C.
sht35: humidity is 25.70%.
sht35: set medium repeatability.
sht35: set rate 0.5Hz.
sht35: temperature is 30.20C.
sht35: humidity is 25.63%.
sht35: temperature is 30.23C.
sht35: humidity is 25.58%.
sht35: temperature is 30.29C.
sht35: humidity is 25.75%.
sht35: set rate 1Hz.
sht35: temperature is 30.34C.
sht35: humidity is 26.13%.
sht35: temperature is 30.36C.
sht35: humidity is 26.09%.
sht35: temperature is 30.46C.
sht35: humidity is 25.92%.
sht35: set rate 2Hz.
sht35: temperature is 30.46C.
sht35: humidity is 26.08%.
sht35: temperature is 30.48C.
sht35: humidity is 26.11%.
sht35: temperature is 30.51C.
sht35: humidity is 25.74%.
sht35: set rate 4Hz.
sht35: temperature is 30.54C.
sht35: humidity is 25.53%.
sht35: temperature is 30.54C.
sht35: humidity is 25.40%.
sht35: temperature is 30.53C.
sht35: humidity is 25.28%.
sht35: set rate 10Hz.
sht35: temperature is 30.61C.
sht35: humidity is 25.14%.
sht35: temperature is 30.56C.
sht35: humidity is 25.10%.
sht35: temperature is 30.59C.
sht35: humidity is 24.94%.
sht35: set high repeatability.
sht35: set rate 0.5Hz.
sht35: temperature is 30.73C.
sht35: humidity is 24.78%.
sht35: temperature is 30.61C.
sht35: humidity is 24.45%.
sht35: temperature is 30.66C.
sht35: humidity is 24.36%.
sht35: set rate 1Hz.
sht35: temperature is 30.69C.
sht35: humidity is 24.24%.
sht35: temperature is 30.74C.
sht35: humidity is 24.26%.
sht35: temperature is 30.77C.
sht35: humidity is 24.25%.
sht35: set rate 2Hz.
sht35: temperature is 30.85C.
sht35: humidity is 24.31%.
sht35: temperature is 30.82C.
sht35: humidity is 24.80%.
sht35: temperature is 30.81C.
sht35: humidity is 25.30%.
sht35: set rate 4Hz.
sht35: temperature is 30.81C.
sht35: humidity is 25.56%.
sht35: temperature is 30.85C.
sht35: humidity is 25.67%.
sht35: temperature is 30.85C.
sht35: humidity is 25.69%.
sht35: set rate 10Hz.
sht35: temperature is 30.84C.
sht35: humidity is 25.52%.
sht35: temperature is 30.87C.
sht35: humidity is 25.49%.
sht35: temperature is 30.87C.
sht35: humidity is 25.37%.
sht35: single read.
sht35: set low repeatability.
sht35: temperature is 30.90C.
sht35: humidity is 25.20%.
sht35: temperature is 30.94C.
sht35: humidity is 25.22%.
sht35: temperature is 30.90C.
sht35: humidity is 24.86%.
sht35: set medium repeatability.
sht35: temperature is 30.91C.
sht35: humidity is 24.72%.
sht35: temperature is 30.87C.
sht35: humidity is 24.53%.
sht35: temperature is 30.94C.
sht35: humidity is 24.25%.
sht35: set high repeatability.
sht35: temperature is 30.94C.
sht35: humidity is 24.15%.
sht35: temperature is 30.94C.
sht35: humidity is 24.00%.
sht35: temperature is 30.97C.
sht35: humidity is 23.89%.
sht35: disable clock stretching.
sht35: temperature is 30.98C.
sht35: humidity is 23.82%.
sht35: temperature is 30.99C.
sht35: humidity is 23.79%.
sht35: temperature is 30.99C.
sht35: humidity is 23.73%.
sht35: finish read test.
```

```shell
./sht35 -e read --addr=0 --times=3

sht35: 1/3.
sht35: temperature is 31.50C.
sht35: humidity is 23.11%.
sht35: 2/3.
sht35: temperature is 31.17C.
sht35: humidity is 23.14%.
sht35: 3/3.
sht35: temperature is 30.98C.
sht35: humidity is 23.28%.
```

```shell
./sht35 -e shot --addr=0 --times=3

sht35: 1/3.
sht35: temperature is 30.02C.
sht35: humidity is 24.66%.
sht35: 2/3.
sht35: temperature is 29.99C.
sht35: humidity is 24.66%.
sht35: 3/3.
sht35: temperature is 29.96C.
sht35: humidity is 24.63%.
```

```shell
./sht35 -h

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

