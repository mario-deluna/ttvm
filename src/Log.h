//
//  Log.h
//
//  Created by Mario Döring on 12.03.18.
//

#ifndef Log_h
#define Log_h

/**
 * Remove for release or find out how go
 * pass this dynamically in xcode...
 */
#ifndef _DEBUG
#define _DEBUG
#endif

#include <iostream>

#define WARN(x) (std::cerr << "[WARNING] -> " << x << std::endl);
#define ERR(x) (std::cerr << "[ERROR] -> " << x << std::endl);

#ifdef _DEBUG
#define LOG(x) (std::cout << "" << x << std::endl);
#else
#define LOG(x) ;
#endif

#endif /* Log_h */
