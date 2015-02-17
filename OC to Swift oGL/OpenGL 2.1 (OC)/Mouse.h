//
//  Mouse.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 31/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//


@interface Mouse : NSObject <RMXMouseOwner>
    //@property bool focus;
    @property int dx, dy;
    @property GLKVector2 pos;
@property (getter=hasFocus) bool focus;
- (void)mouse2view:(int)x y:(int)y owner:(id)owner;
@end

@implementation Mouse



@synthesize name = _name, dx, dy, pos, focus;

- (id)initWithName:(NSString*)name
{
    self = [super init];
    _name = name;
    focus = false;
    dx = 0;
    dy = 0;
    pos = GLKVector2Make(0,0);
    return self;
}


- (void)toggleFocus
{
    focus = !focus;
}

    
    
- (GLKVector2)getMouse
{
    //GLKVector2 pos = { this->pos.x - dx,this->pos.y - dy};
    return pos;
}

- (void)center:(void(int x, int y))center
{
    center(pos.x,pos.y);
}
- (void)setMousePos:(int)x y:(int)y
{
    pos.x = x;// + dx;
    pos.y = y;//;
}
- (void)mouse2view:(int)x y:(int)y{
    NSLog(@"ERROR: Mouse2View Called directly to Mouse!");
}

- (void)mouse2view:(int)x y:(int)y owner:(id)owner
{
        //dx = dy = 0;
        
        
        int DeltaX, DeltaY;// =
        
        
        CGGetLastMouseDelta(&DeltaX, &DeltaY);
//        pos.x += DeltaX;
//        pos.y += DeltaY;
        //cout<< "  dx " << "|" << DeltaX << "|" << DeltaY << endl;
    [rmxDebugger add:3 n:self t:[NSString stringWithFormat:@"Mousie diffX: %i, diffY: %i",DeltaX, DeltaY]];
       
        
        //DeltaX -= dx; DeltaY -= dy;
        //cout<< "  dx " << "|" << DeltaX << "|" << DeltaY << endl;
        int dir = focus ? 1 : -1;
        
        float theta = (float)(DeltaX)*dir;
        float phi = (float)(DeltaY)*dir;// / 20.0f;
        
    [owner plusAngle:theta up:phi];
        // cout<< "  Mouse Pos: " << "|" << pos.x << "|" << pos.y << endl;
        
        
    }
    
- (void)calibrateView:(int)x vert:(int)y
{//GLKVector2 pos){
    CGGetLastMouseDelta(&dx, &dy);
//        dx += x - CGDisplayPixelsWide(0)/2;
//        dy += y - CGDisplayPixelsHigh(0)/2;
    //setMousePos(pos.x-dx, pos.y-dy);
    //cout<< "  CALABRATING " << "|" << dx << "|" << dy << endl;    }
}
@end