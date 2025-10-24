#include <Arduino.h>
#include <ESP32Servo.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <Keypad.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define ROW_NUM 4        // four rows
#define COLUMN_NUM 4     // four columns
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)

const int servoPin = 4; // กำหนดขาเชื่อมต่อเซอร์โว
const int irSensorPin = 2; // กำหนดขาเชื่อมต่อเซ็นเซอร์ IR
const int dispenseAngle = 90; // มุมที่ใช้ในการจ่ายยา
const int restAngle = 0; // มุมพักของเซอร์โว
const int timegapMed = 100; // เวลาหน่วงระหว่างเม็ดยา

    char keys[ROW_NUM][COLUMN_NUM] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}};

byte pin_rows[ROW_NUM] = {13, 12, 14, 27};    
byte pin_column[COLUMN_NUM] = {26, 25, 33, 32};

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Servo myServo;

void displayMessage(const String &message, int x = 0, int y = 0)
{
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(x, y);
    display.print(message);
    display.display();
}

bool dispensingMed(int amount) {
    int count_med = 0;
    const int MedCountToClose = amount - 3; // กำหนดจำนวนยาสำหรับสั่งปิด servo ก่อนครบตามจำนวน

    myServo.write(dispenseAngle); // หมุนเซอร์โวเพื่อเตรียมจ่ายยา
    while (count_med < amount) {
        Serial.println(count_med);
        displayMessage("Total pills: " + String(amount));

        if (digitalRead(irSensorPin) == LOW) {
            count_med++;
            display.clearDisplay();
            displayMessage("Total pills: " + String(amount));
            displayMessage("Dispensed: " + String(count_med), 0, 16);
            delay(timegapMed);
        }

        if (count_med == MedCountToClose){
            myServo.write(restAngle); // หมุนเซอร์โวกลับสู่มุมพัก
        }
    }

    display.clearDisplay();
    displayMessage("Total pills: " + String(amount));
    displayMessage("Dispensed: " + String(count_med), 0, 16);
    return true;
}

void medicine_process(const String &medName){
    display.clearDisplay();
    displayMessage(medName);
    displayMessage("Enter the amount", 0, 16);

    String amountStr = "";
    while (true)
    {
        char key = keypad.getKey();

        if (key == '#')
        {
            if (amountStr.length() == 0)
            {
                continue;
            }
            display.clearDisplay();
            if (dispensingMed(amountStr.toInt()))
            {
                displayMessage("Dispensing done", 0, 32);
                delay(5000);
                break;
            }
        }
        else if (key == NO_KEY || key == 'A' || key == 'B' || key == 'C' || key == 'D')
        {
            continue;
        }
        else if (key == 'D')
        {
            amountStr = "";
            continue;
        }
        else if (key == '*')
        {
            amountStr = "";
            display.clearDisplay();
            displayMessage(medName);
            displayMessage("Enter the amount", 0, 16);
            displayMessage(amountStr, 0, 32);
        }
        else
        {
            amountStr += key;
            displayMessage(amountStr, 0, 32);
        }
    }
}

    void setup()
{
    Serial.begin(115200);

    pinMode(irSensorPin, INPUT);
    myServo.attach(servoPin);
    display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
}

void loop() {
    display.clearDisplay();
    displayMessage("Please select medicine");

    char key = keypad.getKey();
    if (key == 'A')
    {
        medicine_process("Paracetamol");
    }
}