//
//  ShapeObject.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 25/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//


@interface ShapeObject : Particle
@property float size, rotation;
@property  GLKVector4 color;// = GLKVector4Make(1,1, 1, 10);
@property  bool isRotating;

@property  GLKVector3 rAxis;
- (float*)getColorfv;
@end

@implementation ShapeObject
    //GLKVector4 position;
@synthesize size, rotation, color, isRotating, rAxis;

    const float nill[4] = {0,0,0,0};



- (id)initWithName:(NSString*)name
{
    self = [super initWithName:name];
    if (self) {
         size =1;
        color = GLKVector4Make(1,1, 1, 10);
        rAxis = GLKVector3Make(0,0,1);
        rotation = 0;
        isRotating = false;
    }
    return self;
    
}

- (void)draw
{
    glPushMatrix();
    
    glRotatef(rotation, rAxis.x, rAxis.y, rAxis.z);
    
    glPushMatrix();
    
    glTranslatef(self.anchor.x,self.anchor.y, self.anchor.z);
    glTranslatef([self position].x,[self position].y,[self position].z);
    [self setMaterial];
    //drawMe(size);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    [self unsetMaterial];
    
    //glPopMatrix();
    glPopMatrix();
    glPopMatrix();
}
- (void)draw:(void(float size))drawMe{
        glPushMatrix();
       
        glRotatef(rotation, rAxis.x, rAxis.y, rAxis.z);
        
        glPushMatrix();
        
        glTranslatef(self.anchor.x,self.anchor.y, self.anchor.z);
        glTranslatef([self position].x,[self position].y,[self position].z);
    [self setMaterial];
        drawMe(size);
       // glDrawArrays(GL_TRIANGLES, 0, 36);
    [self unsetMaterial];
        
        //glPopMatrix();
        glPopMatrix();
        glPopMatrix();
    }


- (void)animate
{
    //if (temp) tester.checks[9] += "\nSHAPE:\n" + toString();
    if (isRotating) rotation += _dt;//*dift;// * 30;
    
    [super animate];
}

- (void)setMaterial
{
        //glMaterialfv(GL_FRONT,GL_EMISSION, color.v);
}
    
- (void)unsetMaterial
{
        //glMaterialfv(GL_FRONT, GL_EMISSION,nill);
}
    
- (float*)getColorfv
{
    return color.v;
}


- (void)setColorfv:(float*)c
{
    color = GLKVector4MakeWithArray(c);
}
    

@end