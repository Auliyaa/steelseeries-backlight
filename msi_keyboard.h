#ifndef MSI_CONSTANTS_H
#define MSI_CONSTANTS_H

#include <hidapi/hidapi.h>
#include <string>
#include <vector>

namespace msi
{

// Defines an enum that can be converted to/built from a std::string
#define STR_ENUM(NAME,ENUM,...)\
class NAME\
{\
  ENUM _val;\
public:\
  NAME(ENUM val) : _val(val) {}\
  NAME(int val) : _val((ENUM)val) {}\
  NAME(const std::string& s)\
    : _val((ENUM)-1)\
  {\
    const std::vector<std::string> _str = std::vector<std::string>({ __VA_ARGS__ });\
    for(size_t i=0; i < _str.size(); ++i)\
    {\
      if (_str[i].compare(s) == 0) { _val = (ENUM)i; break; }\
    }\
  }\
  NAME operator+(int v) const { return NAME(_val+v); }\
  operator unsigned char() const { return (unsigned char)_val; }\
  operator ENUM() const { return _val; }\
  operator std::string() const\
  {\
    const std::vector<std::string> _str = std::vector<std::string>({ __VA_ARGS__ });\
    return _str[(size_t)_val];\
  }\
  bool operator<(const NAME& other) const { return _val < other._val; }\
  static std::vector<std::string> values() { return std::vector<std::string>({ __VA_ARGS__ }); }\
}

// regions
enum __regions__
{
  all,
  left,
  middle,
  right
};
STR_ENUM(region,
         __regions__,
         "all",
         "left",
         "middle",
         "right");

// colors
enum __colors__
{
  off,
  red,
  orange,
  yellow,
  green,
  sky,
  blue,
  purple,
  white
};
STR_ENUM(color,
         __colors__,
         "off",
         "red",
         "orange",
         "yellow",
         "green",
         "sky",
         "blue",
         "purple",
         "white");

// levels
enum __levels__
{
  high,
  medium,
  low,
  light
};
STR_ENUM(level,
         __levels__,
         "high",
         "medium",
         "low",
         "light");

// modes
enum __modes__
{
  normal,
  gaming,
  breathe,
  demo,
  wave
};
STR_ENUM(mode,
         __modes__,
         "normal",
         "gaming",
         "breathe",
         "demo",
         "wave");

extern bool setColor(hid_device* dev, msi::color c, msi::region r, msi::level l);
extern bool setMode(hid_device* dev, msi::mode m);

} // namespace msi

#endif // MSI_CONSTANTS_H

