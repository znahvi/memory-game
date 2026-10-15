# Memory Game with Arduino
This is a memory game developed using Arduino! For each round, four LEDs will light up, and the player will enter the combination by pressing the corresponding buttons. Try to beat the highscore!

## Components Needed
- 1 Arduino Uno R3
- 4 Light-Emitting Diodes (LEDs)
- 4 220 Ohm Resistors
- 5 Pushbuttons
- 1 Liquid Crystal Display (LCD)
- 1 Positional Servo Motor
- 1 Mini-Breadboard
- A lot of wires!
- Optional: Carboard box, paint, soldering iron, and solder

## Tinkercad Circuit
<img width="1361" height="670" alt="image" src="https://github.com/user-attachments/assets/24464526-4070-4c4a-a639-0d818ff906e2" />

## Schematic
<img width="947" height="728" alt="image" src="https://github.com/user-attachments/assets/bdaaf148-a2d7-44df-a8c5-8d5bc724bef5" />

## Steps

1. Create your circuit according to the schematic below.
2. Upload the code to the Arduino microcontroller from the Arduino IDE.
3. Once you've created your first prototype, you can then put the LEDs, pushbuttons, and LCD on top of a cardboard box with the wiring and microcontroller inside the box.

# Troubleshooting

- The LCD uses an I2C module, so you have to download the library LiquidCrystal I2C so that the code can run properly.
- Make sure that you don't connect an LED without a resistor! The LED will burn out if you forget!
