# q3-EB-plot

This code takes the input from a selection of electron data, and creates a q3 vs Eb plot which shows the issue with the factorisation approach. 


## Building the code

### Prerequisites

- ROOT6 ([https://root.cern/install/](https://root.cern/install/))
- GCC 4.8.5 ([https://gcc.gnu.org/install/](https://gcc.gnu.org/install/))


### Build 

A simple compilation will build the code. Personally I prefer:

g++ {/path/to/install}/src/*.cc -o *executable* $(root-config --cflags --libs)


## Running the code 

### Flags

- [**-d**] Change the saving directory. Default is ./plots. *Argument required.*
- [**-n**] Plots the NuWro output and choose between with and with Optical Potential. Default is without. *Argument required.*
- [**-g**] Plots NEUT+GENIE output.
- [**-R**] Plots the RFG output.
- [**-q**] Plots CCQE instead of NC.
- [**-S**] Plots the SF, though this is default. Can be used to plot multiple graphs. *Argument required.*
- [**-c**] Plots the corrected file instead of the normal one.  
- [**-h**] Print help function.


