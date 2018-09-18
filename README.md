# IOT_box
Integration of various sensors for data acquisition, buffer management and socket programming for packet transfer.
Module definations

SPI:
- Defining of SPI library for interfacing with MCP3008 ADC to provide analo Sensor inputs to raspberry pi.
- ADC_in: function used for reading data in, setting polling time using delay function and time stamping inputs.
- Time_inp: fucntion used for obtaining current time from mraspberry pi internal clock.
- ADC_package: function used for packaging of sensor data and returning this packaged data to main function.

Buffer:
- Used for storing of data passed from SPI packaging, buffer length, timer duration and overwrite activating is configurable using the
  config file.
- FIFO buffer implementation with owerwirte and timer flushing functionalites.
- Passing of data from buffer to UDP client when either condition of timer overflow or size overflow is encountered.

Encrypt:
- Used for providing a Message Digest (MD5) encryption of buffer contents and appended at the end of datagram for checksum capabilites.
- encrypt_MD5 : function used for taking in contents from buffer and creating an MD5 checksum for respective data.
- encrypt_package: function used for packaging the buffer data with MD5 checksum and appending message length for decryption ease.
- encrypt: used for transfering data to and from the buffer.

Client:
- UDP socket implementation for transfering encrypted sensor data to specific ports.
- UDP_client_init: function used for intializing UDP client parameters.
- client: function used for sending data to specific server and creating a configurable log of recent outputs.

Main:
Used for syncronising all the above process and initializing parameters.
