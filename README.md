# Music Player - APS 1
Made By: Renato Falcão & Matheus Barros

## Documentation 

This was made as a project for the class "Computação Embarcado" - Insper, and it consists of making a Music Player using the Atmel SAME70-XPLD.

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
| BUZZER     |      PC19       |         |
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

### Estruturação do código

O código foi estruturado pensando na utilização de callbacks que alteram flags para pausar e tocar a música e para passar para as próximas músicas. A função que coordena a execução da música no buzzer é chamada de playsong() que, de acordo com a frequência das notas e de sua duração, ativa o buzzer através da função tone() que liga o buzzer pela duração determinada. Além disso, acende os LEDs do OLED de acordo com a frequência da nota tocada, mostrando visualmente quando algum som é tocado.

