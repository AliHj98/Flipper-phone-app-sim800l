#Phone App For sim800l module
[Flipper Zero](https://flipperzero.one/) app to control SIm800l via UART interface.

Check https://github.com/AlexKaut/flipperzero-flipperphone-sim800l-v0.1/tree/main for detailed pinup and info on how to make a module

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





## INFO:

~60% of the source code is taken from the [Wifi Marauder](https://github.com/0xchocolate/flipperzero-firmware-with-wifi-marauder-companion) project. Many thanks to the developers of the Wifi Marauder project.
