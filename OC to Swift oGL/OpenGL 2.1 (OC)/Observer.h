//
//  Particle.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 23/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef OpenGL_2_0_Particle_h
#define OpenGL_2_0_Particle_h


#endif

#include "Particle.h"
//#include "RMXEventProcessor.h"
#include "Mouse.h"
#include "PointOfView.h"

@interface Observer : Particle <RMXMouseOwner,RMXPointOfView>
@property Mouse *mouse;
@property Particle * item;
@property GLKVector3 itemPosition;
@property float armLength, reach, rotationSpeed; //return 1?;
- (void)jump;
- (void)setView;
@end
/*
 Provides basic movement attributes to any object
 */
@implementation Observer
    /* ATTRIBUTES 
     - Position
     - Velocity
     - (acceloration? Could be an external input)
     - LookAt
     - Up
     - Right
     */
@synthesize mouse, item, itemPosition, armLength, reach;


    
- (id)initWithName:(NSString*)name
{
    self = [super initWithName:name];
    if (self) {
        mouse = [[Mouse alloc]initWithName:name];
        self.item = self.origin;
        itemPosition = item.position;
        armLength = 2;
        reach = 6;
        self.ground=1;
    }
    return self;
}
    


- (void)jump
{
    if ([self hasGravity]&&[self isGrounded])
        [self accelerateUp:self.jumpStrength];
}
    
    
- (void)grabObject:(Particle*)i
{
        if ((self.item == i)||(GLKVector3Distance(self.position, i.position)>reach))
            [self releaseObject];
        else {
            self.item = i;
            itemPosition = i.position;
            armLength = GLKVector3Distance([self getCenter], itemPosition);
            
        }
        
    }

-(void)releaseObject
{
        //origin.setPosition(anchor->getCenter());
    self.item = self.origin;//[[Particle alloc]init];
}
    
-(void)manipulate
{
        //item->setAnchor(this->getPosition());
    [item setPosition:GLKVector3Add([self getCenter],
                                    GLKVector3MultiplyScalar(self.forwardVector,armLength))];
}
    
- (void)extendArmLength:(float)i
{
    if (armLength+i>1)
        armLength += i;
        
}

- (GLKMatrix4)makeLookAt:(GLKMatrix4(float eyeX,float eyeY, float eyeZ, float cx,float cy, float cz, float ux,float uy, float uz ))lookAt
{
    return (GLKMatrix4)lookAt(
                              [self getEye].x,   [self getEye].y,     [self getEye].z,
                              [self getCenter].x, [self getCenter].y, [self getCenter].z,
                              [self getUp].x,     [self getUp].y,     [self getUp].z
                              );

}

- (void)makeLookAtGl:(void(double eyeX,double eyeY, double eyeZ, double cx,double cy, double cz, double ux,double uy, double uz ))lookAt
{
     lookAt(
                              [self getEye].x,   [self getEye].y,     [self getEye].z,
                              [self getCenter].x, [self getCenter].y, [self getCenter].z,
                              [self getUp].x,     [self getUp].y,     [self getUp].z
                              );
    
}

- (GLKMatrix4)makePerspective:(GLKMatrix4(float fovyRadians, float aspect, float nearZ, float farZ))make
                            m:(float)m width:(int)width height:(int)height
{//, Number fovyRadians, Number aspect, Number nearZ, Number farZ){
    
    return (GLKMatrix4)make(60*m ,width / height, 1.0, 1000.0);
}
- (void)setView
{
    [rmxDebugger add:1 n:self.name t:@"SetView in Observer not implemented"];
}


- (void)setMousePos:(int)x y:(int)y{
    [mouse setMousePos:x y:y];
}
- (void)mouse2view:(int)x y:(int)y{
    [mouse mouse2view:x y:y owner:self];
}

- (GLKVector2)getMouse {
    return [mouse getMouse];
}


- (void)toggleFocus {
    [mouse toggleFocus];
}
- (void)center:(void(int x, int y))center {
    [mouse center:center];
}
- (void)calibrateView:(int)x vert:(int)y {
    [mouse calibrateView:x vert:y];
}
- (bool)hasFocus{
    return [mouse hasFocus];
}


- (NSString*)viewDescription{
    return [NSString stringWithFormat:
    @"\n      EYE x%f, y%f, z%f\n   CENTRE x%f, y%f, z%f\n      UP: x%f, y%f, z%f\n",
            [self getEye].x,[self getEye].y,[self getEye].z,
            [self getCenter].x,[self getCenter].y,[self getCenter].z,
            [self getUp].x,[self getUp].y,[self getUp].z];
}


@end
