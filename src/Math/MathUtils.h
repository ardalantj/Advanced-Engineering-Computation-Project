//
//  MathUtils.h
//  AirViz
//
//  Created by Ardalan TJ on 3/24/20.
//  Copyright © 2020 Ardalan TJ. All rights reserved.
//

 #pragma once

 #ifndef MAX
 #define MAX(a,b) (((a)>(b))?(a):(b))
 #endif

 #ifndef MIN
 #define MIN(a,b) (((a)<(b))?(a):(b))
 #endif

 #ifndef CONSTRAIN
 #define CONSTRAIN(a,low,high) MAX((low),MIN((a),(high)))
 #endif /* MathUtils_h */
