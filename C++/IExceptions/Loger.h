//
//  Loger.h
//  RNN
//
//  Created by Daniel Solovich on 1/11/18.
//  Copyright © 2018 Daniel Solovich. All rights reserved.
//

#ifndef Loger_h
#define Loger_h



#define DEBUGGER_MODE 1

#if DEBUGGER_MODE == 1
#define LOG(x) std::cout << x << std::endl
#else
#define LOG(x) 
#endif

#endif /* Loger_h */
