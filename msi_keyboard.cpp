#include "msi_keyboard.h"

bool msi::setColor(hid_device *dev, msi::color c, msi::region r, msi::level l)
{
  if (r == msi::all)
  {
    return setColor(dev,c,msi::right,l) &&
           setColor(dev,c,msi::middle,l) &&
           setColor(dev,c,msi::left,l);
  }
  unsigned char buffer[8] = {
    1,
    2,
    66, // set
    (unsigned char)r, // region (starting from 0 due to the extra region "all")
    (unsigned char)c, // color (starting from 0)
    (unsigned char)l, // level (starting from 0)
    0,
    236 // EOR (end of request)
  };

  return hid_send_feature_report(dev,buffer,8) == 8;
}

bool msi::setMode(hid_device *dev, msi::mode m)
{
  unsigned char buffer[8] = {
    1,
    2,
    65, // commit
    (unsigned char)(m+1),  // mode (starting from 1)
    0,
    0,
    0,
    236 // EOR (end of request)
  };

  return hid_send_feature_report(dev,buffer,8) == 8;
}
