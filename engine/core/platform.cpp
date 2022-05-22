#include "platform.hpp"

hid::Platform hid::getCurrentPlatform()
{

#ifdef WIN32
    return hid::Platform::windows;
#elif __APPLE__
#if TARGET_OS_IPHONE
    return hid::Platform::ios;
#else
    return hid::Platform::mac;
#endif
#endif
}