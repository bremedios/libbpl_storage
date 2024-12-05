//
// Created by Bradley Remedios on 11/24/24.
//
#ifndef DEBUG_H
#define DEBUG_H

//#define __ENABLE_STORAGE_DEBUG    1

#define ERROR_MSG(msg)  { std::cerr << "ERROR: " << __PRETTY_FUNCTION__ << ":" << msg << std::endl; }

#if defined(__ENABLE_STORAGE_DEBUG)
    #define DEBUG_MSG(msg)  { std::cout << "DEBUG: " << __PRETTY_FUNCTION__ << ":" << msg << std::endl; }
#else
    #define DEBUG_MSG(cmd)
#endif // __ENABLE_STORAGE_DEBUG

#endif //DEBUG_H