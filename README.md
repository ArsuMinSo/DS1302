# DS1302 Arduino Library  

This library provides an interface for controlling the **DS1302 Real-Time Clock (RTC)** module using an **Arduino** or compatible microcontroller.  

## **Features**
- Set and retrieve **time** (hours, minutes, seconds).  
- Set and retrieve **date** (day, month, year).  
- Enable or disable the RTC clock.  
- Configure the **trickle charge** circuit for battery backup.  


## **Wiring (ESP/Arduino)**
| DS1302 Pin | Arduino Pin |
|------------|------------|
| **VCC**    | 5V         |
| **GND**    | GND        |
| **CLK**    | Any GPIO (e.g., `2`) |
| **DAT**    | Any GPIO (e.g., `3`) |
| **RST**    | Any GPIO (e.g., `4`) |

> **Important:**  
> - **VCC should be connected to 5V**, not 3.3V!  
> - **A CR2032 battery** should be installed to retain time after power loss.  

---

## **Installation**
1. Download the `DS1302.h` and `DS1302.cpp` files.  
2. Place them inside your Arduino project folder.  
3. Include the header file in your Arduino sketch:  

```cpp
#include "DS1302.h"
```

---

## **Usage**
### **1. Initialize the RTC module**
```cpp
#include <Arduino.h>
#include "DS1302.h"

#define DS1302_CLK 2
#define DS1302_IO  3
#define DS1302_RST 4

DS1302 rtc(DS1302_CLK, DS1302_IO, DS1302_RST);

void setup() {
    Serial.begin(9600);
    rtc.begin();
}
```

---

### **Set the Time and Date**
```cpp
rtc.setTime(14, 30, 45);  // Set time to 14:30:45
rtc.setDate(27, 3, 2025); // Set date to 27th March 2025
```

---

### **Read the Current Time and Date**
```cpp
uint8_t hour, minute, second;
uint8_t day, month;
uint16_t year;

rtc.getTime(hour, minute, second);
rtc.getDate(day, month, year);

Serial.printf("Time: %02d:%02d:%02d\n", hour, minute, second);
Serial.printf("Date: %02d/%02d/%d\n", day, month, year);
```

---

### **Enable or Disable Clock**
```cpp
rtc.enableClock();   // Start the RTC
rtc.disableClock();  // Stop the RTC
```

---

### **Configure Trickle Charge**
This function allows the trickle charge circuit to charge the backup battery.

```cpp
rtc.setTrickleCharge(true, 1, 2);  // Enable with 1 diode, 2KΩ resistor
rtc.setTrickleCharge(false, 0, 0); // Disable charging
```
> **Warning:** Use trickle charge carefully to avoid damaging your battery!  

---

## **License**
This library is open-source and available under the MIT License.

---

## **Troubleshooting**
**Problem: RTC always shows `00:00:00 00/00/2000`**  
✔ Check if the **battery is installed** correctly.  
✔ Ensure **VCC is connected to 5V**, not 3.3V.  
✔ Try setting the time manually after power-up.  

---

## **Contributing**
If you find any issues or want to improve the library, feel free to submit a pull request or report an issue.

---

## **Author**
Developed by Šimon Raus.  
```  