# iot-arduino-rotary-encoder

use of lcd 16x2 through i2c adapter and rotary encoder to retrieve current position and hit btn

:warning: upload sketch before to connect to avoid ports burn ( if previous sketch may used D2,D3,D4 as output )

![](data/img/schematics.png)

- rotary clockwise

<img width=400 src="data/img/rotary-scope-cw.png"></img>

- rotary counter clockwise

<img width=400 src="data/img/rotary-scope-ccw.png"></img>

## prerequisites

- [vscode arduino](https://github.com/devel0/knowledge/blob/master/doc/vscode-arduino.md)

## config i2c address

- if unsure about your lcd i2c adapter address uncomment [I2C_DEVICE_SCAN]() macro in the config and hit a run to see on the serial terminal which address detected then set it to `LCD_ADDR`

output example:

```
Scanning...                                                                                                           
I2C device found at address 0x3F  !                                                                                   
done
```

## build

- tune `.vscode/c_cpp_properties.json` according to your paths
- `ctrl+shift+p arduino board config` : Arduno Nano / ATmega328P (Old Bootloader)
- `ctrl+alt+u` to upload

## stm32 notes

- the sketch can uploaded to stm32 core
- automatically detect [stm32duino](https://github.com/stm32duino/Arduino_Core_STM32) environment through the [ARDUINO_ARCH_STM32](https://github.com/devel0/iot-arduino-rotary-encoder/blob/9ee53babf17a031f300dfa9b695dd7a5f4d7e601/iot-arduino-rotary-encoder/config.h#L11) macro in order to use `digitalPinToInterrupt` and Wire.setSDA and Wire.setSCL to use custom bus between availables

## libraries

- included a DebouncedButton and DebouncedRotary to manage signal debouncing (default 50ms for button and 1500micros for rotary) ; these values used through millis() and macros() inside interrupt function that still valid even millis() value not changes during the interrupt itself