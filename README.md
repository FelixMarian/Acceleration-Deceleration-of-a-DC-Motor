# Acceleration and deceleration of a DC Motor

This project demonstrates controlling a DC motor using an Arduino and a push-button. The motor's speed increases and decreases gradually when the button is pressed. If the button is held for 2 seconds, the motor shuts down if running or starts up if stopped.

## Table of Contents
- [Components Used](#components-used)
- [Circuit Diagram](#circuit-diagram)
- [Installation](#installation)
- [Usage](#usage)
- [Acceleration and Deceleration Cycles](#acceleration-and-deceleration-cycles)
- [Arduino Code Explanation](#arduino-code-explanation)
- [License](#license)
- [Credits](#credits)

## Components Used
- Arduino UNO
- Breadboard
- TIP120 transistor
- 3V DC motor
- Push-button
- 886 Ω Resistor
- 1 kΩ Resistor
- 250 kΩ Potentiometer
- 2 AAA 1.5V batteries
- LCD 16x2

## Circuit Diagram
![Tinkercad-assembly](https://github.com/FelixMarian/Acceleration-Deceleration-of-a-DC-Motor/assets/118266856/ac392b53-2e15-4e96-b46d-f089c91c19f3)

## Installation
1. **Connect the Components**: Wire up the components according to the provided circuit diagram. Ensure a proper connection between the components.
2. **Upload Arduino Code**: Upload the provided Arduino code (`Acceleration-Deceleration-DC-Motor.ino`) to your Arduino board using the Arduino IDE or any other suitable software.

## Usage
1. **Pressing the Button**: Press the button to control the motor's speed.
   - If the motor is off and the button is pressed for 2 seconds, it will start.
   - If the motor is running and the button is pressed for 2 seconds, it will stop.
   - Each press of the button (not holding it) changes the motor speed in one direction.
2. **Observing Duty Cycle**: Duty cycle information will be displayed on a 16x2 LCD screen connected to the Arduino.


## Acceleration and Deceleration Cycles

When the circuit is initially powered on, it enters the acceleration cycle. In this cycle, each press of the button (not holding it) increases the motor's speed gradually. The duty cycle, which determines the motor's speed, increases by 10% with each press of the button. Once the duty cycle reaches 100%, the motor enters the deceleration cycle.

In the deceleration cycle, each press of the button decreases the motor's speed gradually. Similarly, the duty cycle decreases by 10% with each press of the button. Once the duty cycle reaches 0% the motor enters the acceleration cycle.

These cycles provide a smooth and controlled way to adjust the motor's speed.


## Arduino Code Explanation
- **Setup Function**: Initializes the necessary pins for input and output, sets up the LCD display, and starts serial communication.
- **Loop Function**:
  - Detects when the push-button is pressed and starts a timer.
  - Increases or decreases the motor's speed gradually by adjusting the duty cycle, depending on the duration of the button press.
  - Checks if the timer exceeds 2 seconds, and if it does, it starts/stops the motor.
  - Controls the motor using PWM signals.
- **Helper Functions**:
  - `dutyCycleWrite()`: Prints the current duty cycle on the LCD screen.
  - `cycleState()`: Modifies the cycle state (acceleration or deceleration).
  - `changeState()`: Prints a countdown prompt for starting up or shutting down the motor.

## License
This project is licensed under the [MIT License](LICENSE).

## Credits
- **Author**: STOENOIU Felix-Marian
- **Email**: Stoenoiu.Felix1@gmail.com
- **GitHub**: [My GitHub profile]([https://github.com/yourusername](https://github.com/FelixMarian))

