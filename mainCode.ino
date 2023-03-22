#include <Wire.h>
#include <Adafruit_TCA9548A.h>
#include <MPU9250.h>
#include <Servo.h>

// I2C multiplexer object
Adafruit_TCA9548A mux = Adafruit_TCA9548A();

// IMU objects
MPU9250 imu_upper_arm(Wire, 0x68);
MPU9250 imu_forearm(Wire, 0x69);
MPU9250 imu_hand(Wire, 0x68); // The same address as imu_upper_arm since it will be on a different I2C channel

// Servo objects
Servo servo_shoulder_horizontal;
Servo servo_shoulder_vertical;
Servo servo_elbow;
Servo servo_wrist_pitch;
Servo servo_wrist_roll;

// Servo pins
const int shoulder_horizontal_pin = 3;
const int shoulder_vertical_pin = 5;
const int elbow_pin = 6;
const int wrist_pitch_pin = 9;
const int wrist_roll_pin = 10;

// Function to read and process IMU data
void read_imu(MPU9250 &imu, float &roll, float &pitch, float &yaw) {
  // Read and update IMU data
  imu.update();

  // Get roll, pitch, and yaw values
  roll = imu.getRoll();
  pitch = imu.getPitch();
  yaw = imu.getYaw();
}

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Initialize the I2C multiplexer
  if (!mux.begin()) {
    Serial.println("Failed to find TCA9548A chip");
    while (1);
  }

  // Initialize the IMUs
  mux.setChannel(0); // Set the multiplexer to channel 0
  imu_upper_arm.begin();

  mux.setChannel(1); // Set the multiplexer to channel 1
  imu_forearm.begin();

  mux.setChannel(2); // Set the multiplexer to channel 2
  imu_hand.begin();

  // Initialize servo motors
  servo_shoulder_horizontal.attach(shoulder_horizontal_pin);
  servo_shoulder_vertical.attach(shoulder_vertical_pin);
  servo_elbow.attach(elbow_pin);
  servo_wrist_pitch.attach(wrist_pitch_pin);
  servo_wrist_roll.attach(wrist_roll_pin);
}
void loop() {
  // Read IMU data
  float upper_arm_roll, upper_arm_pitch, upper_arm_yaw;
  float forearm_roll, forearm_pitch, forearm_yaw;
  float hand_roll, hand_pitch, hand_yaw;

  mux.setChannel(0); // Set the multiplexer to channel 0
  read_imu(imu_upper_arm, upper_arm_roll, upper_arm_pitch, upper_arm_yaw);

  mux.setChannel(1); // Set the multiplexer to channel 1
  read_imu(imu_forearm, forearm_roll, forearm_pitch, forearm_yaw);

  mux.setChannel(2); // Set the multiplexer to channel 2
  read_imu(imu_hand, hand_roll, hand_pitch, hand_yaw);

  // Calculate servo angles based on the relative orientation of the IMUs
  int shoulder_horizontal = upper_arm_yaw;
  int shoulder_vertical = upper_arm_pitch;
  int elbow = forearm_pitch - upper_arm_pitch;
  int wrist_pitch = hand_pitch - forearm_pitch;
  int wrist_roll = hand_roll - forearm_roll;

  // Set servo angles
  servo_shoulder_horizontal.write(constrain(shoulder_horizontal, 0, 180));
  servo_shoulder_vertical.write(constrain(shoulder_vertical, 0, 180));
  servo_elbow.write(constrain(elbow, 0, 180));
  servo_wrist_pitch.write(constrain(wrist_pitch, 0, 180));
  servo_wrist_roll.write(constrain(wrist_roll, 0, 180));

  // Optional: print the angles for debugging
  Serial.print("Upper Arm: "); Serial.print(upper_arm_roll); Serial.print(", "); Serial.print(upper_arm_pitch); Serial.print(", "); Serial.println(upper_arm_yaw);
  Serial.print("Forearm: "); Serial.print(forearm_roll); Serial.print(", "); Serial.print(forearm_pitch); Serial.print(", "); Serial.println(forearm_yaw);
  Serial.print("Hand: "); Serial.print(hand_roll); Serial.print(", "); Serial.print(hand_pitch); Serial.print(", "); Serial.println(hand_yaw);
  
  // Delay to avoid overwhelming the servos and IMUs
  delay(20);
}
