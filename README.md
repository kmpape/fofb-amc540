# fofb-amc540

Fast orbit feedback implementation on the TI C6678 DSP / AMC540. Must be built using Code Composer Studio and the AMC540 patch provided by Vadatech.

- Recommended compiler options: -O3 -pm -op2 -mt
- Remove from compiler options: -g -ss

Note: The clock speed of the C6678 can be set to 1.4 GHz. To do so, modify the PLL setup in the corresponding GEL file.
