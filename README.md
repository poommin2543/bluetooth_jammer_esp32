# bluetooth_jammer_esp32
# Dual NRF24L01+ Frequency Hopping on ESP32

This project implements dual NRF24L01+ radios on an ESP32 using both VSPI and HSPI interfaces. It provides frequency hopping and constant carrier transmission for radio testing and analysis.

## Features
- Utilizes two NRF24L01+ modules
- Implements frequency hopping for interference mitigation
- Supports channel randomization and fixed hopping sequences
- Uses SPI communication with VSPI and HSPI on ESP32
- Implements a button (connected to GPIO 33) to switch between hopping modes
- Disables Bluetooth and WiFi to reduce interference

## Hardware Requirements
- ESP32 board
- Two NRF24L01+ modules
- Push button (connected to GPIO 33)

## Wiring
| NRF24L01+ (HSPI) | ESP32 | NRF24L01+ (VSPI) | ESP32 |
|------------------|-------|------------------|-------|
| MISO            | 12    | MISO            | 19    |
| MOSI            | 13    | MOSI            | 23    |
| SCK             | 14    | SCK             | 18    |
| CSN             | 15    | CSN             | 21    |
| CE              | 16    | CE              | 22    |
| VCC             | 3.3V  | VCC             | 3.3V  |
| GND             | GND   | GND             | GND   |

## Software Requirements
- Arduino IDE with ESP32 board support
- RF24 library
- ezButton library

## Installation
1. Clone this repository:
   ```sh
   git clone https://github.com/poommin2543/bluetooth_jammer_esp3.git
   ```
2. Install the required libraries in Arduino IDE:
   - [RF24 Library](https://github.com/nRF24/RF24)
   - [ezButton Library](https://github.com/ArduinoGetStarted/ezButton)
3. Open the `main.ino` file in Arduino IDE.
4. Select the ESP32 board and the correct COM port.
5. Upload the code to your ESP32.

## Usage
- The device starts with frequency hopping enabled.
- Pressing the button (GPIO 33) toggles between:
  - **Hopping Mode**: Alternates between predefined channels.
  - **Random Mode**: Randomly selects a channel at intervals.
- Monitor serial output for debug messages.

## Functions Explained
- `two()`: Implements channel hopping logic.
- `one()`: Randomizes channels.
- `RF()`: Starts constant carrier transmission.
- `initSP()`: Initializes VSPI radio.
- `initHP()`: Initializes HSPI radio.

## License
This project is licensed under the MIT License.

## Contributing
Feel free to fork and submit pull requests. Any contributions are welcome!

## Author
- Poommin Phinphimai 
- GitHub: [Your GitHub Profile](https://github.com/poommin2543)

