# Acelerometro + Display STM

## Archivos agregados:

* **adxl345.c**
* **fonts.c**
* **i2c-lcd.c**
* **ssd1306.c**

* **adxl345.h**
* **fonts.h**
* **i2c-lcd.h**
* **ssd1306.h**

## Esquema de conexión:

``` c
Esquema de conexion:

  ADXL345
  SCL: A5
  SDA: A7
  SDO: A6
  CS : B6
  
  Oled Display: I2C
  SCK: B8
  SDA: B9
  ```
## Configuraciones a realizar:
``` c
  SPI1:
  -Full duplex master
  -Preescaler /64
  -CPOL High
  -CPHA 2 Edge
  
  I2C1:
  -Fast mode 
  -400KHz
  -GPIO OUT CS

```
## Modificaciones en el main:

### Linea 30
```
#include "i2c-lcd.h"
#include "fonts.h"
#include "ssd1306.h"
#include "adxl345.h"
```
### Linea 128
```
  lcd_init();
  lcd_send_string("SPI_TEST");
  HAL_Delay(2000);

  adxl_init();

  SSD1306_Init();
```
### Linea 146
```
   lectura_acelerometro();
   acelerometro_a_display();
```

