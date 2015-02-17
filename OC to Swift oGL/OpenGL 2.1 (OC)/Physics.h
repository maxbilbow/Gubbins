//
//  Physics.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 25/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//




@interface Physics : NSObject <RMXObject>
@property NSString* name;
@property float gravity, friction;
@end

@implementation Physics
const float U_GRAVITY = (0.01/50);
const float  U_FRICTION = 1.1;



@synthesize name = _name, gravity, friction;;
- (id)initWithName:(NSString*)name
{
    
    self = [super init];
    if (self) {
        _name = name;
        gravity = U_GRAVITY;
        friction = U_FRICTION;
        NSLog(@"init Physics");
    }
    return self;
}

- (void)toggleGravity
{
    gravity = (gravity == U_GRAVITY) ? 0 : U_GRAVITY;
}

- (void)addGravity:(float) g
{
    gravity += g;
    if (gravity<0)
        gravity = 0;
    [rmxDebugger add:4 n:self t:[NSString stringWithFormat:@" / Gravity: %f", gravity]];// +=  + to_string(gravity);
}
    
- (float)getFriction
{
    return friction;
}
    
- (void)toggleFriction
{
    friction = (friction == U_FRICTION) ? 0 : U_FRICTION;
}
    
- (void)addFriction:(float)f
{
    friction += f;
    if (friction<0)
        friction = 0;
    [rmxDebugger add:4 n:self t:[NSString stringWithFormat:@" / Friction: %f",friction]];
}
    
    
@end;