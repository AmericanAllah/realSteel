Here's how to connect three MPU9250 IMUs to an Arduino Uno:

Common connections for all IMUs:

VCC: Connect the VCC pins of all three IMUs to the 3.3V pin on the Arduino.
GND: Connect the GND pins of all three IMUs to one of the GND pins on the Arduino.
SCL: Connect the SCL pins of all three IMUs to the A5 pin on the Arduino Uno (SCL pin for the Uno).
SDA: Connect the SDA pins of all three IMUs to the A4 pin on the Arduino Uno (SDA pin for the Uno).
Individual connections for each IMU to set different I2C addresses:

IMU 1 (Upper Arm): Leave the ADO pin unconnected or connect it to GND. The I2C address will be 0x68.
IMU 2 (Forearm): Connect the ADO pin to 3.3V. The I2C address will be 0x69.
IMU 3 (Hand): As the Arduino Uno only has two I2C addresses, you'll need to use an I2C multiplexer (e.g., TCA9548A) to create additional I2C channels for the third IMU.
Note that you'll need to update the provided code to work with an I2C multiplexer. Additionally, when reading the data from the third IMU, you'll need to select the appropriate I2C channel on the multiplexer.

To wire the MPU9250s to the TCA9548A I2C multiplexer and the Arduino, follow these steps:

TCA9548A multiplexer to Arduino Uno:

VIN: Connect this pin to the 5V pin on the Arduino.
GND: Connect this pin to one of the GND pins on the Arduino.
SCL: Connect this pin to the A5 pin on the Arduino Uno (SCL pin for the Uno).
SDA: Connect this pin to the A4 pin on the Arduino Uno (SDA pin for the Uno).
RST: Leave this pin unconnected or connect it to a digital pin on the Arduino if you need to reset the multiplexer via software. Otherwise, you can connect it to the 5V pin for a continuous normal operation.
A0, A1, A2: Leave these pins unconnected. They are used to set the I2C address of the TCA9548A, but the default address 0x70 should work fine in this case.
MPU9250s to TCA9548A multiplexer:

Connect the VCC pin of all three IMUs to the 3.3V pin on the Arduino.
Connect the GND pin of all three IMUs to one of the GND pins on the Arduino.
Connect the SCL pin of the first MPU9250 (Upper Arm) to the SC0 pin on the TCA9548A multiplexer.
Connect the SDA pin of the first MPU9250 (Upper Arm) to the SD0 pin on the TCA9548A multiplexer.
Connect the SCL pin of the second MPU9250 (Forearm) to the SC1 pin on the TCA9548A multiplexer.
Connect the SDA pin of the second MPU9250 (Forearm) to the SD1 pin on the TCA9548A multiplexer.
Connect the SCL pin of the third MPU9250 (Hand) to the SC2 pin on the TCA9548A multiplexer.
Connect the SDA pin of the third MPU9250 (Hand) to the SD2 pin on the TCA9548A multiplexer.
Leave the other pins (EDA, ECL, ADO, INT, NCS, FSYNC) on the MPU9250s unconnected, as they are not required for basic I2C communication and orientation tracking in this scenario.