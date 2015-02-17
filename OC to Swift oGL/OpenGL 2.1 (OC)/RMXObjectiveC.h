//
//  Header.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 23/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//



#	include <sys/time.h>

//#include <iostream>

float _dt;
//using namespace std;
//#include <ApplicationServices/ApplicationServices.h>
//#include <ApplicationServices/ApplicationServices.h>
#include <math.h>
#include <GLKit/GLKMatrix4.h>
#import <GLKit/GLKit.h>
//#include <GLUT/glut.h>
//#import <OpenGLES/ES1/gl.h>

@protocol RMXObject
@property (readonly) NSString * name;
- (id)initWithName:(NSString*)name;
- (void)animate;
@end

union GLKVector3 {
    struct{
    
    };
    
}RMXVector3;

#include "RMXDebugger.h"


#include "RMXEventProcessor.h"
#include "Observer.h"

#include "World.h"
#include "Art.h"


#include "Window.h"






