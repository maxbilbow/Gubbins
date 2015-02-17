//
//  ActionProcessor.h
//  OpenGL 2.1 (OC)
//
//  Created by Max Bilbow on 15/02/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

#ifndef OpenGL_2_1__OC__ActionProcessor_h
#define OpenGL_2_1__OC__ActionProcessor_h


#endif

@protocol RMXAnyInput <RMXObject>

- (void)toggleFocus;
- (void)center:(void(int x, int y))center;
- (void)calibrateView:(int)x vert:(int)y;
- (bool)hasFocus;

@end

@protocol RMXMouseOwner <RMXObject, RMXAnyInput>
- (void)setMousePos:(int)x y:(int)y;
- (void)mouse2view:(int)x y:(int)y;
//- (void)setPos:(int)x v:(int)y;
- (GLKVector2)getMouse;
@end

@protocol RMXOrienrationProcessor

//- (void)rotate;
- (void)rotateAroundVerticle:(float)theta;
- (void)rotateAroundHorizontal:(float)phi;
- (void)plusAngle:(float)theta up:(float)phi;
@end
