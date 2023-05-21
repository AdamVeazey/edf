EDF
===

Embedded Development Framework (EDF) is a collection of libraries intended for use in embedded systems.

The structure of the framework itself shown below. 

```bash      tree --dirsfirst -I 'build|CMakeFiles' src/
src/
├── EDF
│   ├── Drivers
│   │   └── src
│   ├── MCU
│   │   ├── ATmega328
│   │   ├── ESP32
│   │   ├── LPC845
│   │   ├── MSP430
│   │   └── nRF5340
│   ├── Peripherals
│   │   └── src
│   ├── src
│   ├── Array.hpp
│   ├── Assert.hpp
│   └── Stack.hpp
└── CMakeLists.txt
```

EDF
===

This is for MISC building blocks commonly used in embedded systems projects. 
- STL like containers with a fixed max size.
  1. Array
  2. Stack
  3. Vector
  4. Queue
  5. Heap
  6. BinarySearchTree
- Assert
- Math
  1. isPow2
  2. min
  3. max
  4. voltageDividerCalcVin
  5. voltageDividerCalcVout
  6. nElements
- String
- UnixTimestamp
- BitField
- Version
- Color

TODO: What about RTOS related things?
- Semaphore
- Mutex
- EventGroup
- Lock
- MessageQueue


Peripherals
===========

Dependencies:
- EDF

This contains base classes for common peripherals used by Drivers. None of these contain platform specific information within them, but do provide the interfaces you need in order to write a portable driver. 

- GPIO
- SPI
- I2C
- UART
- PWM
- Timer
- ADC
- DAC
- WDT
- RTC

Drivers
=======

Dependencies:
- EDF
- Peripherals

This contains drivers for specific ICs, as well as 'higher level' generic uses of Peripherals. Relies on Peripherals and EDF
- RGB LED
- SoftTimer
- EEPROM IC drivers
- IMU IC drivers
- ADC IC drivers
- Flash memory IC drivers


MCU
====

Dependencies:
- EDF
- Peripherals

This contains peripheral implementations for specific MCUs. Also may provide more MCU specific code that is project independent. EX: BLE central/peripheral related code, MQTT, WiFi, etc... Things that can be reused if another project uses the same MCU, but stuff that's too different between MCUs to really be turned into something completely generic that's still useful. 

- GPIO implementation (GPIOFast + GPIO)
- PWM implementation (PWMFast + PWM)
- I2C implementation (I2CFast + I2C)
- BLE central 
- BLE peripheral
- MQTT client
- WiFi STA
- WiFi AP

---
**NOTE**

"Fast" versions are the real implementation, but without directly deriving from the generic peripheral type. This is to allow you to avoid the vtable penalty if the difference legitimately matters.
```
EDF::Peripherals::I2C           EDF::MCU::LPC845::I2CFast
         |_________________________________|
                          |
                 EDF::MCU::LPC845::I2C
```
---


