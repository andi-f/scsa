# scsa
Simple tool for capture the data from a spectrum analyser via Linux-GPIB. You can set some parameter remotely and capture  the screen. 
The Screen capture can exported as pdf or png,

Supported spectrum analyser:
Advantest 4131

Compile and install:

The program is written in C and uses GTK-2. Just compile it with make.

Additional software: You need linux-gpib and a gpib interface.

The gpib-functions.h and gpib-functions.h were written by Frank Mori Hess.

ToDo:

Add spectrum analyser TEK 492

Add marker read out and setting

Add setting GPIB interface and address
