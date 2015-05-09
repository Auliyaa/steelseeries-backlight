# steelseeries-backlight
A very thin command-line utility to switch the light configuration of your MSI keyboard. 

This program controls a MSI keyboard with backlight functionality (Vendor id: 0x1770, Product id: 0xff00)

# Usage
```
./kbd-light  [-m <normal|gaming|breathe|demo|wave>] [-l <high|medium|low
                |light>] [-c <off|red|orange|yellow|green|sky|blue|purple
                |white>] [-r <all|left|middle|right>] [-o] [--] [--version]
                [-h]


Where: 

   -m <normal|gaming|breathe|demo|wave>,  --mode <normal|gaming|breathe
      |demo|wave>
     Sets the keyboard mode. Some mode may ignore other parameters like
     --color, --level or --region.

   -l <high|medium|low|light>,  --level <high|medium|low|light>
     Sets the light intensity. This parameter may be ignored if --mode is
     set.

   -c <off|red|orange|yellow|green|sky|blue|purple|white>,  --color <off
      |red|orange|yellow|green|sky|blue|purple|white>
     Sets the backlight color. This parameter may be combined to a region
     to specify where the color is set (see --region).

   -r <all|left|middle|right>,  --region <all|left|middle|right>
     Sets the region where the color is applied. This parameter may be
     ignored if --mode is set.

   -o,  --off
     Turns the light off. This parameter excludes all other options that
     may be passed alongside

   --,  --ignore_rest
     Ignores the rest of the labeled arguments following this flag.

   --version
     Displays version information and exits.

   -h,  --help
     Displays usage information and exits.


   Changes the color and light mode of a MSI keyboard.
```

# Requirements
## Build
* A C++11 capable compiler (tested with GCC 4.9.2)
* CMake (tested with CMake 3.2.2)
* TCLAP (http://tclap.sourceforge.net/, tested with TCLAP 1.2.1-3)
* libhidapi (http://www.signal11.us/oss/hidapi/, tested with libhidapi 0.8.0rc1-2)

## Runtime
kbd-light requires libhidapi-libusb to be installed and must be run with administrative privileges.

# Thanks
The code is mainly based over the work of wearefractal/msi-keyboard (https://github.com/wearefractal/msi-keyboard).