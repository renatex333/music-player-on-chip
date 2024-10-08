# Music Player

Authors: Renato Falcão & Matheus Barros

## Documentation 

This was made as a project for the class "Computação Embarcada" - Insper, and it consists of making a Music Player using the Atmel SAME70-XPLD.

For more information access:

https://insper.github.io/ComputacaoEmbarcada/APS-1-Musical/

### Componenets used
- Atmel SAME70-XPLD
- OLED1 Xplained Pro
- Protoboard
- Jumpers
- Buzzer

### Pins & Functionalities

| Funtion    |      PINS       | BUTTONS |
|------------|-----------------|---------|
| BUZZER +   |      PC19       |         |
| BUZZER -   |      GND        |         |
| Start/Stop |      PC31       |Button 2 |
| SELECTION  |      PD28       |Button 1 |
| LED1       |      PA0        |         |
| LED2       |      PC30       |         |
| LED3       |      PB2        |         |

- The start/stop button can play or pause.
- Use the Selection to change Songs.
- The 3 leds will flash according to the notes duration giving it a cool adition to the project.

### Setup
<img src="https://user-images.githubusercontent.com/15271557/189542702-80d9a59f-aff5-4ff8-8af1-4542a70b7887.jpeg" width="500">


### Working Project Video [Link](https://youtu.be/iDsRo0B9OPo)

[<img src="https://user-images.githubusercontent.com/15271557/189547261-e3931e12-78fd-4dad-9f83-431e1b579b9b.jpeg" width="500">](https://youtu.be/iDsRo0B9OPo)


### Music List

All Songs chosen were made by Robson Couto, you can access his Arduino Songs clicking this [Link](https://github.com/robsoncouto/arduino-songs)

**Songs**

They are in this order:

- [Jigglypuff Song](https://github.com/robsoncouto/arduino-songs/blob/master/jigglypuffsong/jigglypuffsong.ino)
- [Never Gonna Give You Up Song](https://github.com/robsoncouto/arduino-songs/blob/master/nevergonnagiveyouup/nevergonnagiveyouup.ino)
- [Game Of Thrones Theme Song](https://github.com/robsoncouto/arduino-songs/blob/master/gameofthrones/gameofthrones.ino)
- [Zelda Theme Song](https://github.com/robsoncouto/arduino-songs/blob/master/zeldatheme/zeldatheme.ino)
- [Doom](https://github.com/robsoncouto/arduino-songs/blob/master/doom/doom.ino)
- [Star Wars](https://github.com/robsoncouto/arduino-songs/blob/master/starwars/starwars.ino)

### Code Structure

The code was organized into the following files:

- `Songs.h` &rarr; file where the notes and their respective durations were defined.
- `defines.h` &rarr; file where the pins assigned to each peripheral, such as the buzzer, buttons, and LEDs, were defined.
- `jigglypuff.h`, `nevergonnagiveyouup.h`, `gameofthrones.h`, `zelda.h`, `doom.h`, `starwars.h` &rarr; files where the arrays with the melodies of the songs were defined.
- `main.c` &rarr; file containing all the necessary functions for the software's execution. This includes functions for initializing peripherals and the structs for each song, callback functions that handle state changes of the flags when buttons are pressed, functions that return the states of certain pins, functions that activate or deactivate the pin controlling the buzzer, as well as the main functions that control the buzzer to turn on/off for the specified durations, thus playing the desired song.
