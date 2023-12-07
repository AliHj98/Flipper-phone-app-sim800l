#Phone App For sim800l module
[Flipper Zero](https://flipperzero.one/) app to control SIm800l via UART interface.

Companion app for this module:
https://github.com/AlexKaut/flipperzero-flipperphone-sim800l-v0.1/tree/main 

Check for detailed pinup and info on how to make a module

you can also make your own module, the sim800 V2 is much easier to set up and use but has no speaker and mic I/O.
## Download fap
|  **FW RougeMaster** |

| (https://flipc.org/AliHj98/Flipper-phone-app-sim800l?firmware=roguemaster) |

## Capabilities
- Read SIM card number
- Check Simcard status
- Check signal strength
- Set baud rate <9600> for sim800l
- Fast commands

## Connecting
| Flipper Zero pin |Sim800l interface|
| ---------------- | --------------- |
| 1 (5V)           | 5V              |
| 13 TX            | RX              |
| 14 RX            | TX              |
|8, 18 GND         | GND             |

## Phone status
Sends AT+CPAS Command
module status: 0 - ready to work, 2 - unknown (command execution is not guaranteed), 
3 - incoming call, 4 - voice connection

## Signal Quality
Sends AT+CSQ Command
signal quality: 0 -115 dBm or less, 1 - 111 dBm, 2-30 -110..-54 dBm, 31 -52 dBm or more,
99 -unknown or no signal.

## Phone Call
Sends ATD commant that starts a phone call to a specific phone number

<ATD+XXXXXXXXXXXX;> (Do not forget ";" in the end)

![image](https://github.com/AliHj98/Flipper-phone-app-sim800l/assets/99630322/9dffe2c1-a272-4ab1-8879-be632e0f2351)


## Keyboard
Phone App uses its own special keyboard for work, which has all the symbols necessary for working in the console.

To accommodate more characters on a small display, some characters are called up by holding.

![kbf](https://user-images.githubusercontent.com/122148894/212286637-7063f1ee-c6ff-46b9-8dc5-79a5f367fab1.png)

## Supported send AT commands
In the "Send AT command" mode, the keyboard settings are changed for the convenience of entering AT commands.

![AT](https://user-images.githubusercontent.com/122148894/230785072-319fe5c9-deca-49f9-bfe4-5ace89d38d53.png)


## How to install
Copy the contents of the repository to the applications_user/uart_terminal_phone folder Flipper Zero firmware and build app with the command ./fbt fap_uart_terminal.

Or use the tool [uFBT](https://github.com/flipperdevices/flipperzero-ufbt) for building applications for Flipper Zero.

Download ready [fap][https://flipc.org/AliHj98/Flipper-phone-app-sim800l?firmware=roguemaster]

## How it works


![1f](https://github.com/AliHj98/Flipper-phone-app-sim800l/blob/main/photos/Screenshot%202023-12-07%20182019.png)


##

RoadMap:
- Sending text messages through flipper
- reading text messages
- recieving calls
- connecting to data and getting https request
- viewing, adding removing and saving contacts list on sim


## INFO:
This is a UART TERMINAL fork, Thanks to https://github.com/cool4uma
