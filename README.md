# Kinematic clock

This repository showcases how Singapore Polytechnic's kinematic clock was made.  

Background info about the kinetic clock?

Design followed from?

## 3D Design

## Clock assembly
Each clock is made up of: 

![Clock parts](https://github.com/allen-michael-tan/Kinematic-clock/blob/main/Images/Clock%20parts.jpg)

1. Clock body [1]
2. Servo gear [2]
3. M2x12 pan head self-tapping screw [4]
4. M2x8 flanged pan head self-tapping screw [2]
5. Minute hand gear [1]
6. Hour hand gear [1]
7. Hour hand shaft [1]
8. Minute hand [1]
9. Hour hand [1]
10. Continuous servo motor [2]
11. M3 plain washer [3]
12. Bamboo skewer [1]
13. Retaining ring [1]  

### Parts manufacturing

The components of each clock were created using 3D printers, laser cutters and vinyl stickers.

#### 3D print

![3D printed part 1](https://github.com/allen-michael-tan/Kinematic-clock/blob/main/Images/3D%20printed%20part%201.jpeg)

![3D printed part 2 (clock body)]()

#### Laser cut

![Laser cut parts](https://github.com/allen-michael-tan/Kinematic-clock/blob/main/Images/Laser%20cut%20parts.jpeg)

Flat parts such as clock hands and 

#### Vinyl sticker

![Vinyl sticker]()

### Pre-assembly preparation

Before each clocks were put together, some components of the clock had to be prepared first.

#### Coating of 3D printed parts

![Spray coating](https://github.com/allen-michael-tan/Kinematic-clock/blob/main/Images/Spray%20coating.jpeg)

The material used for all 3D printed parts was PLA. This material has the tendency to disintigrate after a period of time, so a clear coat was applied on all the printed parts to increase their longevity. 

#### Hour hand assembly

![Hour hand assembly](https://github.com/allen-michael-tan/Kinematic-clock/blob/main/Images/Hour%20hand%20assembly.jpg)

The laser cut hour hand (blue arrow) was superglued to the tip of the hour hand shaft as shown above.

#### Minute hand assembly

![Minute hand assembly 1](https://github.com/allen-michael-tan/Kinematic-clock/blob/main/Images/Minute%20hand%20assembly%201.jpeg)

**XX**mm thick bamboo skewers were cut into lengths of 60mm.

![Minute hand assembly 2](https://github.com/allen-michael-tan/Kinematic-clock/blob/main/Images/Minute%20hand%20assembly%202.jpg)

M3 plain washer was superglued to the underside of the laser cut minute hand (blue arrow), this is done so to minimize friction between the minute and hour hand as they rotate. 

After which, a bamboo skewer was inserted to the minute hand and superglued (green arrow).

![Minute hand assembly 3](https://github.com/allen-michael-tan/Kinematic-clock/blob/main/Images/Minute%20hand%20assembly%203.jpg)

Lastly, on the other side of the minute hand where the bamboo skewer was inserted, black paint is applied onto the exposed side of the skewer (blue arrow). 

### Assembly

#### Step 1

![Clock assembly 1](https://github.com/allen-michael-tan/Kinematic-clock/blob/main/Images/Clock%20assembly%201.jpg)

The colour theme of the clock was black and white - black board and clock hands, white clock face. As the clock bodies were printed in different colours, white vinyl stickers were cut out and pasted onto the outside face of the clock body (blue arrow). 

*****

#### Step 2

![Clock assembly 2](https://github.com/allen-michael-tan/Kinematic-clock/blob/main/Images/Clock%20assembly%202.jpg)

Next, two continuous servo motors were installed onto the clock body as shown above and secured using 4 screws (blue arrows).

*****

#### Step 3

![Clock assembly 3](https://github.com/allen-michael-tan/Kinematic-clock/blob/main/Images/Clock%20assembly%203.jpeg)

Before inserting the hour hand, the shaft hub was lubricated using WD 40 to reduce friction between the hour hand shaft and the clock body.

*****

#### Step 4

![Clock assembly 4](https://github.com/allen-michael-tan/Kinematic-clock/blob/main/Images/Clock%20assembly%204.jpg)

The hour hand was inserted as shown (blue arrow). 

*****

#### Step 5

![Clock assembly 5](https://github.com/allen-michael-tan/Kinematic-clock/blob/main/Images/Clock%20assembly%205.jpg)

After the hour hand has been inserted, a retaining ring (blue arrow) was inserted as shown to prevent he hour hand from falling off. 

Following that, the hour hand gear (yellow arrow) and a servo gear (green arrow) was assembled accordingly. Then, a screw is used to secure the servo gear to the servo motor. 

*****

#### Step 6

![Clock assembly 6](https://github.com/allen-michael-tan/Kinematic-clock/blob/main/Images/Clock%20assembly%206.jpg)

In this final step, the minute hand (yellow arrow) was inserted into the hour hand shaft, followed by two washers (green arrow) and minute hand gear (blue arrow).

It is important to note that, the before inserting the minute hand gear, the bamboo skewer should rotate freely with little friction whilst inserted in the hour hand shaft. This is because if there was too much friction, when the hour hand rotates, the minute hand will rotate along it which is undesired. 

The purpose of the washer is to prevent the bamboo skewer from jiggling in and out the hour hand shaft.

Lastly, a second servo gear (red arrow) is secured to the second servo motor with a screw as shown.  

*****

## Board

The main board was made out of 15mm thick plywood. The parts were cut using a 2D CNC router. 

![CNC cutting 1]()

![CNC cutting 2]()

## Wiring

To control the 48 servo motors, three PWM servo motor drivers were used. Modifications to the two of the three drivers were done before they could all be daisy-chained together.

![Servo boards connection](https://github.com/allen-michael-tan/Kinematic-clock/blob/main/Images/Servo%20boards%20connection.jpg)

For board two, A0 was bridged; while for board three, A1 was bridged. The boards were then connected as shown.

![Servos to board 1](https://github.com/allen-michael-tan/Kinematic-clock/blob/main/Images/Servos%20to%20board%201.jpg)

Each driver board will control 16 individual motors, its wiring to the board is as shown. The remaining motors were wired exactly the same way as this board.

![Wiring of clock hands 1](https://github.com/allen-michael-tan/Kinematic-clock/blob/main/Images/Wiring%20of%20clock%20hands%201.jpg)

The servo motors of each individual minute and hour hands were wired to each resepctive boards with reference to the table above. "M" refers to minute hand while "H" refers to hour hand. 

![Wiring of clock hands 2](https://github.com/allen-michael-tan/Kinematic-clock/blob/main/Images/Wiring%20of%20clock%20hands%202.jpg)

The above shows how the clocks are grouped from the front view. 

![Boards connection](https://github.com/allen-michael-tan/Kinematic-clock/blob/main/Images/Boards%20connection.jpg)

A real time clock (RTC) module, DS3231 was used to accurately calculate the time displayed by the servo motors. 

The wiring connection of all the different boards is as of above.

![Full schematic](https://github.com/allen-michael-tan/Kinematic-clock/blob/main/Images/Full%20schematic.jpg)

This is the full schematic diagram of the kinematic clock.

![Circuit board]()

A circuit board was made to make the system modular should any replacement work is needed.

![Mounting of boards]()

All the different circuit boards were adhered onto the back of the board with double-sided foam tape. 

![Final wiring]()

This is how the back of the clock looked like after everything is wired and assembled. 

## Programming

### Calibration

### Code

#### RTC Code

#### Full Code

## Final product

![Final product]()

<a href="https://www.youtube.com/watch?v=qirl-tjCUZg"><img src="http://img.youtube.com/vi/YOUTUBE_VIDEO_ID_HERE/0.jpg" 
alt="Kinetic clock" width="240" height="180" border="10" /></a> 