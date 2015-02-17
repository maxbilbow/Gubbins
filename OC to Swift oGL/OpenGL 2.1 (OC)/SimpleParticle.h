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
#include "Physics.h"


@interface SimpleParticle : NSObject <RMXObject>
@property GLKVector3 position, velocity,acceleration, forwardVector, upVector, leftVector, forwardV, upV, leftV;
@property Physics * physics, *externalPhysics, *localPhysics;
@property float accelerationRate, speedLimit,ground,rotationSpeed,jumpStrength;
@property bool limitSpeed, drift;
- (id)initWithName:(NSString*)name;
- (void)setVelocity:(GLKVector3)acceleration;
//- (float)getForwardVelocity;
//- (float)getUpVelocity;
//- (float)getLeftVelocity;
- (GLKVector3)getEye;
- (GLKVector3)getCenter;
- (GLKVector3)getUp;

- (void)setPosition:(GLKVector3)v;
- (void)accelerateForward:(float)velocity;
- (void)accelerateUp:(float)velocity;
- (void)accelerateLeft:(float)velocity;
- (void)forwardStop;
- (void)upStop;
- (void)leftStop;

//- (GLKVector3)getVelocity;
@end

@implementation SimpleParticle
    /* ATTRIBUTES
     - Position
     - Velocity
     - (acceloration? Could be an external input)
     - LookAt
     - Up
     - Right
     */
@synthesize name = _name;

@synthesize position = _position, velocity,acceleration, forwardVector, upVector, leftVector, forwardV, upV, leftV, physics, externalPhysics, localPhysics, accelerationRate, speedLimit,ground,rotationSpeed,jumpStrength,limitSpeed, drift;
    //float * dift = &dt;
   // @synthesize position = _position;



- (id)initWithName:(NSString*)name
{
    //self = [super init];
    _name = name;
   

    //if (self) {
   // position=malloc(sizeof(GLKVector3));
    
//    position = malloc(sizeof(GLKVector3));
//    velocity =malloc(sizeof(GLKVector3));
//    acceleration =malloc(sizeof(GLKVector3));
//    forwardVector = malloc(sizeof(GLKVector3));
//    upVector = malloc(sizeof(GLKVector3));
//    leftVector =malloc(sizeof(GLKVector3));
//    forwardV = malloc(sizeof(GLKVector3));
//    upV = malloc(sizeof(GLKVector3));
//    leftV = GLKVector3Make(0, 0, 0);
    GLKVector3 p = GLKVector3Make(0, 0, 0);
    _position = p;//GLKVector3Make(0, 0, 0);
    //position = GLKVector3Make(0, 0, 0);
    velocity = GLKVector3Make(0, 0, 0);
    acceleration = GLKVector3Make(0, 0, 0);
    forwardVector = GLKVector3Make(0, 0, 1);
    upVector = GLKVector3Make(0, 1, 0);
    leftVector = GLKVector3Make(1, 0, 0);
    forwardV = GLKVector3Make(0, 0, 0);
    upV = GLKVector3Make(0, 0, 0);
    leftV = GLKVector3Make(0, 0, 0);

    localPhysics = [[Physics alloc] initWithName:name];
        physics = localPhysics;
        externalPhysics = [[Physics alloc] initWithName:name];
        NSLog(@"init: %@ at:%p",name,&_position);
    //}
    
    return self;
    
}

// Dealloc method should always follow init method
- (void)dealloc
{
    // Remove any observers or free any necessary cache, etc.
    

}



- (void)useExternalPhysics
{
    physics = externalPhysics;
}
    
- (void)useLocalPhysics
{
    physics = localPhysics;
}


- (GLKVector3)getLeftVector
{
    return leftVector;
}
- (GLKVector3*)pMem{
    return &_position;
}


- (GLKVector3)getEye
{
    return _position;
}
    
- (GLKVector3)getCenter
{
    return GLKVector3Add(_position,forwardVector);
}
    
- (GLKVector3)getUp
{
    return upVector;
}
- (void)accelerateForward:(float)v
{
    acceleration.z = v * accelerationRate;
    
}

- (void)accelerateUp:(float)v
{
    acceleration.y = v * accelerationRate;
    //  accelerate();
    //       accelerate(GLKVector3Make(0,velocity*accelerationRate,0));
}

- (void)accelerateLeft:(float)v
{
    acceleration.x = v * accelerationRate;
    //accelerate();//accelerate(GLKVector3Make(velocity*accelerationRate,0,0));
}


- (void)forwardStop
{
    if (!drift) {
        acceleration.z = 0;
        //            if(getForwardVelocity()>0)
        //                acceleration.z = -physics.friction;
        //            else if (getForwardVelocity()<0)
        //                acceleration.z = physics.friction;
        //            else
        //                acceleration.z = 0;//-velocity.z;
    }
}

- (void)upStop
{
    if (!drift) {
        acceleration.y = 0;// -velocity.y;
        //accelerate();
    }
}

- (void)leftStop
{
    if (!drift) {
        acceleration.x = 0;// -velocity.x;
        //accelerate();
    }
    
}

- (void)accelerate
{
    //acceleration.z =
    [rmxDebugger add:3 n:self.name t:[NSString stringWithFormat:@"FV: %f, LV: %f, UV: %f",[self velocity].x,[self velocity].y,[self velocity].z]];
    acceleration.y -= [physics gravity];
    [self setVelocity:[self acceleration]]; //Need to calculate this
    
    if (limitSpeed){
        for (int i=0;i<3;++i)
            if ([self velocity].v[i] > speedLimit){
                [rmxDebugger add:3 n:self.name t:[NSString stringWithFormat:@"speed%i = %f",i,[self velocity].v[i]]];
                [self velocity].v[i] = speedLimit;
            } else if ([self velocity].v[i] < -speedLimit){
                [rmxDebugger add:3 n:self.name t:[NSString stringWithFormat:@"speed%i = %f",i,[self velocity].v[i]]];
                [self velocity].v[i] = -speedLimit;
            } else
                [rmxDebugger add:3 n:self.name t:[NSString stringWithFormat:@"speed%i OK: %f",i,[self velocity].v[i]]];
    }
    
    
    [rmxDebugger add:6 n:self t:[NSString stringWithFormat:@"accZ: %f, velZ: %f",[self acceleration].z,[self velocity].z]];
    
    
}

@end