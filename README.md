# Auto Medicine Dispensing System

![Project Image](https://i.imgur.com/your-image-url.png) 
A smart automatic medicine dispensing system project built using the **ESP32** microcontroller. It features a **4x4 Keypad** for input, an **IR Sensor** for accurately counting dispensed medication, a **Servo Motor** to control the dispensing mechanism, and an **OLED** display for status updates.

## 🌟 Features

* **Medication Selection:** Users can select the type of medicine via the 4x4 keypad.
* **Quantity Input:** Users can enter the desired quantity (e.g., 5 pills).
* **Automated Dispensing:** The Servo Motor automatically opens/closes the dispensing gate.
* **Accurate Counting:** Uses an IR Sensor to detect and count each pill as it passes.
* **Real-time Feedback:** The OLED display shows the current status, such as "Please select medicine," "Enter amount," and "Dispensing: 3/5."

---

## 🛠️ Hardware Required

* **ESP32** (Main control board)
* **OLED Display** (e.g., SSD1306 I2C 128x64)
* **4x4 Matrix Keypad** (For user input)
* **IR Sensor Module** (For pill counting)
* **Servo Motor** (e.g., SG90, for opening/closing the gate)
* Jumper Wires
* Breadboard
* Power Supply

---

## ⚙️ Workflow

1.  **Initialization:** The system boots up. The OLED displays a welcome message or "Please select medicine."
2.  **Select Medicine:** The user presses a button on the Keypad (e.g., 'A', 'B', '1', '2') to choose the medicine type.
3.  **Enter Quantity:** The OLED prompts "Enter amount." The user enters a number (e.g., '5') and presses a confirmation key (e.g., '#').
4.  **Dispensing Starts:** The system commands the Servo Motor to rotate to the "open" position.
5.  **Counting:** Pills begin to fall past the IR Sensor.
    * Each time a pill breaks the sensor's beam (e.g., state changes from `LOW` to `HIGH`), the system increments the count (`count + 1`).
    * The OLED provides a real-time update (e.g., "Dispensed: 1/5", "Dispensed: 2/5", ...).
6.  **Count Reached:** When the dispensed count (`count`) equals the requested amount (`amount`).
7.  **Dispensing Stops:** The system commands the Servo Motor to return to the "closed" position.
8.  **Completion:** The OLED displays "Dispensing Complete" and the system returns to the initial state, ready for the next request.

---

## 🚀 Setup

1.  **Hardware Connection:**
    * Connect the Keypad, OLED (SDA, SCL), IR Sensor (Digital Pin), and Servo (PWM Pin) to the ESP32 according to the pinout defined in your code.

2.  **Arduino IDE Setup:**
    * Install the ESP32 Board Manager in the Arduino IDE.
    * Go to **Tools > Manage Libraries...** and install the necessary libraries:
        * `Keypad` (by Mark Stanley, Alexander Brevig)
        * `Adafruit_GFX`
        * `Adafruit_SSD1306` (or your specific OLED library)
        * `ESP32Servo` (Specifically for ESP32)

3.  **Compile and Upload:**
    * Open your `.ino` project file.
    * Select your board (e.g., "ESP32 Dev Module").
    * Select the correct COM Port.
    * Upload the code to your board.

---

## 📊 System Diagram
+---------------+ +----------+ +---------------+ | | ---> | | ---> | | | Keypad 4x4 | | ESP32 | | OLED Display | | (Input) | | (Control)| | (Output) | | | <--- | | | | +---------------+ | | <--- +---------------+ ^ | | ^ | +----------+ | | | | +-------------------+------------------+ | (Detects Pill) | (Counts) v +---------------+ +----------+ | | | | | IR Sensor | | Servo | | | <--- | Motor | | | | (Action) | +---------------+ +----------+ ^ | (Controls Gate)