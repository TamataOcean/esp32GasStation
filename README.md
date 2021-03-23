# esp32GasStation using CCS811 & BME280
Tutorial to use ESP32 to send CO2 & TVOC information other Mqtt ( inpired by [RandomerTutorial](https://randomnerdtutorials.com/esp32-mqtt-publish-subscribe-arduino-ide/) )

# Install Arduino lib for ESP32
Follow this [link](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/)

# Fonctionnal Schema
![Sch_Fonctionnal](https://user-images.githubusercontent.com/25310798/73060571-6b0a2700-3e98-11ea-8de7-cf990ef746e2.jpg)
 
# Electrical Schema
![ESP32_BME280_bb](https://user-images.githubusercontent.com/25310798/86024869-d0f17080-ba2d-11ea-98a7-3ce7bb2fa018.png)

# CO2 Information 
[CO2 & ppm information](https://www.experts-environnement.fr/augmentation-du-co2-dans-les-logements-a-cause-dun-systeme-de-ventilation-defectueux/)

# Technical info 
[ESP32 Which GPIO pins should you use?](https://randomnerdtutorials.com/esp32-pinout-reference-gpios/)   
[ESP32 I2C Communication: Set Pins, Multiple Bus Interfaces and Peripherals](https://randomnerdtutorials.com/esp32-i2c-communication-arduino-ide/).  
[ESP32 Heltel with OLED Screen](https://robotzero.one/heltec-wifi-kit-32/)

# Safe levels of CO2 & TVOC:   
    CO2 (equivalent calculated carbon-dioxide)
    350-1,000ppm                   Concentrations typical of occupied indoor spaces with good air exchange
    1,000-2,000ppm                 Complaints of drowsiness and poor air.
    2,000-5,000 ppm                Headaches, sleepiness and stagnant, stale, stuffy air. Poor concentration, loss of attention, increased heart rate and slight nausea may also be present.

    _______________________________________________________________________________________________________________________________________________________________________
    TVOC (Total Volatile Organic Compound)
    If TVOCs are present, an overall concentration will be reported. While there are no exposure limits for TVOCs some guidelines have been recommended. Generally, TVOC concentrations between 50 parts per billion (ppb) and 325 ppb are thought to be acceptable

    Household product which emit TVOC:
    Paints, paint strippers and other solvents, wood preservatives, aerosol sprays, cleansers and disinfectants, moth repellents and air fresheners, stored fuels and automotive products, hobby supplies, dry-cleaned clothing, pesticide, other products, including:

    Building materials and furnishings which emit TVOC:
    Office equipment such as copiers and printers, correction fluids and carbonless copy paper, graphics and craft materials including glues and adhesives, permanent markers and photographic solutions.
    _______________________________________________________________________________________________________________________________________________________________________

new...
