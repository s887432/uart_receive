# uart_receive
UART test tool<br>
## Usage
<b>compile</b><br>
$ git clone https://github.com/s887432/uart_receive<br>
$ cd uart_receive<br>
$ mkdir build<br>
$ cd build<br>
$ cmake .. -DARCH=arm9<br>
where arm9 is built for sam9x60, sam9x75<br>
cortex is built for SAMA5, SAMA7 series<br>
$ make<br>
<br>
The output will be placed at project folder.<br>
If built for ARM9, the output folder will be arm9_bin<br>
If built for CORTEX, the output folder will be cortex_bin<br>
<br>
Have fun!!!<br>
Patrick @ Taipei
