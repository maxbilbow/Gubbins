//
//  Particle.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 23/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//


#include "SimpleParticle.h"
//#include "Mouse.h"

@interface Particle : SimpleParticle <RMXOrienrationProcessor>
@property GLKVector3 anchor;
@property Particle *origin;// = [[SimpleParticle alloc]init];

- (void)animate;
- (void)setVelocity:(GLKVector3)acceleration;
- (void)manipulate;
- (bool)translate;
- (void)addGravity:(float)g;
- (void)toggleGravity;
- (bool)hasGravity;
- (bool)isGrounded;
- (void)push:(GLKVector3)direction;
- (void)plusAngle:(float)theta up:(float)phi;
- (bool)isDrift;
- (void)setAnchor:(GLKVector3)vector;

@end
/*
 Provides basic movement attributes to any object
 */
@implementation Particle
@synthesize anchor, origin;//, public PointOfView, public Mouse{
    /* ATTRIBUTES 
     - Position
     - Velocity
     - (acceloration? Could be an external input)
     - LookAt
     - Up
     - Right
     */



    

- (id)initWithName:(NSString*)name
{
    self = [super initWithName:name];
    
    
    [self setAccelerationRate:0.01];
    [self setSpeedLimit:0.20];
    [self setLimitSpeed:true];
    [self setDrift:false];
    [self setGround:0];
    origin = nil;//[[Particle alloc]initWithName:@"Origin"];
    anchor = GLKVector3Make(0,0,0);
    [self setRotationSpeed:-0.1];
    [self setJumpStrength:2.0];
   // }
    return self;
    
}
- (bool)isDrift
{
    return !self.drift;
}
    
- (void)setPosition:(GLKVector3)v
{
    if (v.y < [self ground])
        v.y = [self ground];
    [super setPosition:v];
    //[rmxDebugger add:1 n:self.name t:[NSString stringWithFormat:@"x: %f, y: %f, z: %f, GROUND: %f",position.x,position.y,position.z,ground]];
}
    
- (bool)checkLimits:(GLKVector3)dV
{
    [rmxDebugger add:1 n:self.name t:@"Check Limits in Particle should be overriten"];
    return true;
}
    
- (bool)isZero:(GLKVector3)v
{
    return ((v.x==0)&&(v.y==0)&&(v.z==0));
}
    
   
- (bool)translate
{
    if ([self isZero:[self velocity]])
        return false;
    else
        [self setPosition:GLKVector3Add([self position],[self velocity])];
    return true;
}
    
-(void)animate
{

    [self accelerate];
    [self setLeftVector:GLKVector3CrossProduct([self forwardVector],[self upVector])];
    if (![self translate])
        [rmxDebugger add:2 n:self.name t:@"no movement!"];
    [self manipulate];
    [rmxDebugger add:2 n:self.name t:[NSString stringWithFormat:@"%@ POSITION: %p | PX: %f, PY: %f, PZ: %f",self.name,[self pMem],[self position].x,[self position].y,[self position].z ]];
    }

- (void)manipulate
{
    [rmxDebugger add:1 n:self.name t:@"'Manipulate' should be overridden"];
}
    //MOVEMENT

- (void)stop
{
    [self setVelocity: GLKVector3Make(0,0,0)];
        //setRotationalVelocity(GLKVector3Make(0,0,0));
}

    
    
- (void)plusAngle:(float)theta up:(float)phi
{
    theta *= PI_OVER_180*self.rotationSpeed;
    phi *= PI_OVER_180*self.rotationSpeed;
    [self rotateAroundVerticle:theta];
    [self rotateAroundHorizontal:phi];
    [rmxDebugger add:2 n:self.name t:[NSString stringWithFormat:@"plusAngle: THETA %f, PHY: %f",theta,phi]];
}
    
-(void)rotateAroundVerticle:(float)theta
{
    GLKMatrix4 rm = GLKMatrix4MakeRotation(theta, [self upVector].x, [self upVector].y, [self upVector].z);
        //GLKMatrix4RotateWithVector3(GLKMatrix4MakeYRotation(theta), theta, getUpVector());
    [self setForwardVector:GLKMatrix4MultiplyVector3WithTranslation(rm, [self forwardVector])];
        //leftVector = GLKMatrix4MultiplyVector3WithTranslation(rm, leftVector);
    //free(rm);
}
-(void)rotateAroundHorizontal:(float)phi
{
    // leftVector = GLKVector3CrossProduct(getForwardVector(), getUpVector()); // Set the Right Vector
    GLKMatrix4 rm = GLKMatrix4MakeRotation(phi, [self leftVector].x, [self leftVector].y, [self leftVector].z);
    
    //upVector = GLKMatrix4MultiplyVector3WithTranslation(rm, upVector);
    [self setForwardVector:GLKMatrix4MultiplyVector3WithTranslation(rm, [self forwardVector])];
    
}

- (void)setVelocity:(GLKVector3)acceleration
{
    float forward = acceleration.z;
    float left = -acceleration.x;
    float up = acceleration.y;
    [rmxDebugger add:1 n:self.name t:[NSString stringWithFormat:@"FV: %f, LV: %f, UV: %f",forward,left,up]];
    [self setForwardV:GLKVector3MultiplyScalar([self forwardVector], forward)];
    //forwardV = GLKVector3DivideScalar(forwardV, physics.friction);
    [self setUpV:GLKVector3MultiplyScalar([self upVector], up)];
    [self setLeftV:GLKVector3MultiplyScalar([self leftVector], left)];
    // GLKVector3 tm = GLKVector3Project(acceleration, forwardVector);
    //GLKVector3 tm
    
    [super setVelocity:GLKVector3Add([self velocity],GLKVector3Add([self forwardV],[self leftV]))];
    [super setVelocity:GLKVector3DivideScalar([self velocity],[self.physics getFriction])];
    [super setVelocity:GLKVector3Add([self upV],[self velocity])];
    
}

    

- (void)addGravity:(float)g
{
    [self.physics addGravity:g];
}
    
- (void)toggleGravity
{
    [self.physics toggleGravity];
}
    
- (bool)hasGravity{
    return ([self.physics gravity] > 0);
}
    
- (bool)isGrounded{
    return ([self position].y == self.ground);
}
    
- (void)push:(GLKVector3)direction
{
    [super setVelocity:GLKVector3Add([self velocity], direction)];
}
    

    

- (GLKVector3)getEye
{
    return [self position];
}

- (GLKVector3)getCenter
{
    return GLKVector3Add([self position],[self forwardVector]);
}

- (GLKVector3)getUp
{
    return [self upVector];
}

    
    
    
@end


