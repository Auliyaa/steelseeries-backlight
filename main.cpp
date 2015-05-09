#include <iostream>

#include <tclap/CmdLine.h>
#include "msi_keyboard.h"

#define MAP_CONSTANT(NAME,SHORT,DESC,MANDATORY)\
std::vector<std::string> NAME##Values = msi::NAME::values();\
TCLAP::ValuesConstraint<std::string> NAME##Constraint(NAME##Values);\
TCLAP::ValueArg<std::string> NAME##Arg(SHORT,#NAME,DESC,MANDATORY,NAME##Values[0],&NAME##Constraint);\
cmd.add(NAME##Arg);

int main(int argc,char** argv)
{
  try
  {
    // Command description
    TCLAP::CmdLine cmd("Changes the color and light mode of a MSI keyboard.", ' ', "0.1");

    // Arguments definition
    TCLAP::SwitchArg offArg("o","off","Turns the light off. This parameter excludes all other options that may be passed alongside", cmd, false);
    MAP_CONSTANT(region,"r","Sets the region where the color is applied. This parameter may be ignored if --mode is set.",false);
    MAP_CONSTANT(color,"c","Sets the backlight color. This parameter may be combined to a region to specify where the color is set (see --region).",false);
    MAP_CONSTANT(level,"l","Sets the light intensity. This parameter may be ignored if --mode is set.",false);
    MAP_CONSTANT(mode,"m","Sets the keyboard mode. Some mode may ignore other parameters like --color, --level or --region.",false);

    // Parse the cmd line for available arguments
    cmd.parse(argc,argv);

    // Fetch arguments value
    bool off = offArg.getValue();
    msi::region reg = regionArg.getValue();
    msi::color col = colorArg.getValue();
    msi::level lvl = levelArg.getValue();
    msi::mode mod = modeArg.getValue();
    if (off)
    {
      mod = msi::normal;
      col = msi::off;
      reg = msi::all;
    }

    // Init the hid interface
    if (hid_init() != 0)
    {
      std::cerr << "Failed to initialize hid interfaces." << std::endl;
      exit(1);
    }

    // Open the keyboard device
    hid_device* keyboard = hid_open(0x1770, 0xff00, NULL);
    if (keyboard == nullptr)
    {
      std::cerr << "Could not find a compatible keyword. Make sure this program has root privileges and the device is plugged in." << std::endl;
      exit(1);
    }

    // Apply mode and color
    if (!msi::setMode(keyboard,mod))
    {
      std::cerr << "Failed to apply mode." << std::endl;
      exit(1);
    }
    if (!msi::setColor(keyboard,col,reg,lvl))
    {
      std::cerr << "Failed to apply color." << std::endl;
      exit(1);
    }

    // Close device
    hid_close(keyboard);
  }
  catch (TCLAP::ArgException &e)
  {
    std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
  }
}
