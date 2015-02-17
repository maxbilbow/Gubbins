//
//  World.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 25/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef OpenGL_2_0_World_h
#define OpenGL_2_0_World_h


#endif
#define W_GRAVITY (0.01/50);
#define W_FRICTION 1.1;


#define VIEWING_DISTANCE_MIN  3.0
#define TEXTURE_ID_CUBE 1

@interface RMXWorld : UIViewController <RMXObject>
@property NSMutableArray* sprites;
@property NSString* observerName;
@property float dt;
- (id)closestObject;
- (void)animate;
- (void)insertSprite:(Particle*)sprite;
- (id)objectWithName:(NSString*)name;
- (void)setObserverWithId:(Particle*)object;
@end


@implementation RMXWorld
@synthesize name = _name, sprites = _sprites, observerName, dt;//, mainObserver = _mainObserver;
    const float _g = W_GRAVITY;
    const float _f = W_FRICTION;


- (id)initWithName:(NSString*)name
{
    self = [super init];
    _name = name;
    observerName = @"Main Observer";
    _sprites = [[NSMutableArray alloc]initWithCapacity:10];
    [_sprites addObject:[[Observer alloc]initWithName:observerName]];// inPropertyWithKey:observerName];
    return self;
}

- (Observer*)observer {
    return [_sprites firstObject];
}

- (void)setObserverWithName:(NSString*)name {
    if ([_sprites valueForKey:name])
        observerName = name;
    else
        NSLog(@"ERROR: Object '%@' not found in sprites array",name);
    
}

- (void)setObserverWithId:(Particle*)object {
    observerName = [object name];
    //if (![_sprites doesContain:object])
        [self insertSprite:object];
}


- (id)objectWithName:(NSString*)name{
    return [_sprites valueForKeyPath:name];
}
    
- (void)insertSprite:(id)sprite
{
    [_sprites addObject:sprite];
//        _sprites = (Observer*)shape;
}

    
- (void)animate
{
    for (Particle* sprite in _sprites) {
        [sprite animate];
    }
}
    
- (id)closestObject
{
    id closest = [_sprites objectAtIndex:1];
    float dista=GLKVector3Distance([self observer].position, ((Particle*)[_sprites objectAtIndex:1]).position);
        for (Particle* sprite in _sprites){
            float distb = GLKVector3Distance([self observer].position, sprite.position);
            NSString *lt = @" < ";
            if(distb<dista&&distb!=0){
                closest = sprite;
                //shapes[i];
                lt = @" > ";
                // cout << i-1 << ": "<< dista << lt << (i) <<": "<< distb << endl;
                dista = distb;
            }
           
        }
        //cout << "closest: "<< closest << ", dist:" << dista << endl;
    return closest;//shapes[closest];
    }


@end

RMXWorld *world;