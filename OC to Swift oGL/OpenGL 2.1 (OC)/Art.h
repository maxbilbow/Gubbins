//
//  Art.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 23/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef OpenGL_2_0_Art_h
#define OpenGL_2_0_Art_h

//#define _INFINITY 9999
#endif

#include "Shapes.h"
#include "LightSource.h"

@interface Art : NSObject <RMXObject>
@property GLfloat x, y, z, d, r,g, b,k;
@property ShapeObject * sh, * sh2, * sh3, *sh4;
@end
ShapeObject * sh, * sh2, * sh3, *sh4;
void RenderObjects(void);


@implementation Art

@synthesize name = _name;

float colorBronzeDiff[4] = { 0.8, 0.6, 0.0, 1.0 };
float colorBronzeSpec[4] = { 1.0, 1.0, 0.4, 1.0 };
float colorBlue[4]       = { 0.0, 0.2, 1.0, 1.0 };
float colorNone[4]       = { 0.0, 0.0, 0.0, 0.0 };
float red[4]             = { 1.0, 0.0, 0.0, 1.0 };
float green[4]           = { 0.0, 0.0, 1.0, 1.0 };
float yellow[4]          = { 1.0, 0.0, 1.0, 1.0 };

    GLfloat x, y, z, d, r,g, b,k;
    enum{
        XY,
        XZ,
        YX,
        YZ,
        ZX,
        ZY
    };
    
- (id)initWithName:(NSString *)name
{
    self = [super init];
    _name = name;
    if (self) {
        self.x = 0;//45.0f;
        self.y = (GLfloat)250/(GLfloat)250;
        self.z = 0.1f;
        self.d = 100.0f;
        self.r = 0.5f;
        self.g = 0.2f;
        self.b = 0.2f;
        self.k = 0.0f;
    }

    sh = [[ShapeObject alloc]initWithName:@"Shape1"];
    sh2 = [[ShapeObject alloc]initWithName:@"Shape2"];
    sh3 = [[ShapeObject alloc]initWithName:@"Shape3"];
    sh4 = [[ShapeObject alloc]initWithName:@"Shape4"];
    sun = [[LightSource alloc]initWithName:@"SUN"];
    
    //sh = &world.getShapes()[World::Objects::BOX1];
    [sh setPosition:GLKVector3Make(6,0,0)];
    [sh setColor:GLKVector4MakeWithArray(yellow)];
    sh.rAxis = GLKVector3Make(0,1,0);
    
    
    //sh2 = &world.getShapes()[1];
    [sh2 setPosition:GLKVector3Make(-3,0,0)];
    [sh2 setColor:GLKVector4MakeWithArray(red)];
    sh2.rAxis = GLKVector3Make(0,1,0);
    
    //sh3 = &world.getShapes()[2];
    [sh3 setPosition:GLKVector3Make(3,0,0)];
    [sh3 setColor:GLKVector4MakeWithArray(colorBlue)];
    sh3.rAxis = GLKVector3Make(0,1,0);
    
    [sh4 setPosition:GLKVector3Make(0,0,-3)];
    [sh4 setColor:GLKVector4MakeWithArray(green)];
    sh4.rAxis = GLKVector3Make(0,1,0);
    
    [world insertSprite: sh];
    [world insertSprite: sh2];
    [world insertSprite: sh3];
    [world insertSprite: sh4];
    [world insertSprite: sun];
    
    [self randomObjects];
    return self;
    
    
}

- (void)drawThings
{
    for (ShapeObject* sprite in [world sprites]){
        if ([sprite class]==[ShapeObject class]) {
    glMaterialfv(GL_FRONT, GL_SPECULAR, [sprite getColorfv]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, [sprite getColorfv]);
    glPushMatrix();
    //glTranslatef(3, 0, 0);
    [sprite draw:DrawCubeWithTextureCoords];
    glPopMatrix();
                                                  }
    }
}



- (void)randomObjects
{
    int max =100, min = -100;
    
               
    for(int i=0;i<10;++i){
        float r[3] = {(rand() % (max+1-min))+min, (rand() % (max+1-min))+min, (rand() % (max+1-min))+min};
        float c[4] ={ rand() ,rand() ,rand(),rand() };
        ShapeObject *shape = [[ShapeObject alloc]initWithName:[NSString stringWithFormat:@"Shape: %i",i ]];
        [shape setPosition:GLKVector3MakeWithArray(r)];
        [shape setColor:GLKVector4MakeWithArray(c)];
        //shape.rAxis = GLKVector3Make(0,1,0);
        [world insertSprite:shape];
        //free(&shape);

    }
}
- (void)drawPlane
{
    /* glPushMatrix();
    //glColor4fv(colorBlue);
    
    glTranslatef(0, -1, 0);
    glBegin(GL_QUADS);
    glVertex3f( -_INFINITY,-0.001, -_INFINITY);
    glVertex3f( -_INFINITY,-0.001,_INFINITY);
    glVertex3f(_INFINITY,-0.001,_INFINITY);
    glVertex3f(_INFINITY,-0.001, -_INFINITY);
    glEnd();
    glPopMatrix(); */

    
    }
    
- (void)animate
{
    // shanimate();
    // We don't use bias in the shader, but instead we draw back faces,
    // which are already separated from the front faces by a small distance
    // (if your geometry is made this way)
    //glCullFace(GL_FRONT);
    glClearColor(r, g, b, y);
    
    [self drawThings];
    
    glPushMatrix();
    
    RenderObjects();
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, GLKVector4Make(0.8,0.8,0.8,1).v);
    [self drawPlane];
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorNone);
    
    /*
    glMaterialfv(GL_FRONT, GL_SPECULAR, colorBlue);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colorBlue);
    glColor4fv(colorBlue);
    glPushMatrix();
    glTranslatef(0, 0, 3);
    //glMaterialf(GL_FRONT, GL_SHININESS, 50.0);
    DrawCubeWithTextureCoords(1.0);//drawCube();
    glPopMatrix();
    
    
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_SPECULAR, [sh4 getColorfv]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, [sh4 getColorfv]);
    glTranslatef(0, sin(g_fTeapotAngle2/100)+0.5, -3);
    glPushMatrix();
    //glRotatef(g_fTeapotAngle2,0, 1, 0);
    [sh4 draw:DrawCubeWithTextureCoords];
    
    glPopMatrix();
    glPopMatrix();
    
    
    
    glMaterialfv(GL_FRONT, GL_SPECULAR, [sh3 getColorfv]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, [sh3 getColorfv]);
    glPushMatrix();
    //glTranslatef(3, 0, 0);
    [sh3 draw:DrawCubeWithTextureCoords];
    glPopMatrix();
    
    
    glMaterialfv(GL_FRONT, GL_SPECULAR, [sh2 getColorfv]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, [sh2 getColorfv]);
    glPushMatrix();
    [sh2 draw:DrawCubeWithTextureCoords];
    glPopMatrix();
    
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colorNone);
    glMaterialfv(GL_FRONT, GL_SPECULAR, colorNone);
    
    glMaterialfv(GL_FRONT, GL_DIFFUSE, [sh getColorfv]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, [sh getColorfv]);
    [sh draw:DrawCubeWithTextureCoords];
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colorNone);
    glMaterialfv(GL_FRONT, GL_SPECULAR, colorNone);
    
    //        for(int i=0;i<sizeof(shape);++i){
    //            glMaterialfv(GL_FRONT, GL_DIFFUSE, shape[i].getColorfv());
    //            glMaterialfv(GL_FRONT, GL_SPECULAR, shape[i].getColorfv());
    //            shape[i].draw(DrawCubeFace);
    //            glMaterialfv(GL_FRONT, GL_DIFFUSE, colorNone);
    //            glMaterialfv(GL_FRONT, GL_SPECULAR, colorNone);
    //        } */
    glPopMatrix();
    
        }


@end

//Particle pCube = Particle();
void RenderObjects(void)
{
    
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    // Main object (cube) ... transform to its coordinates, and render
    glRotatef(15, 1, 0, 0);
    glRotatef(45, 0, 1, 0);
    glRotatef(g_fTeapotAngle, 0, 0, 1);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colorBlue);
    glMaterialfv(GL_FRONT, GL_SPECULAR, colorNone);
    glColor4fv(colorBlue);
    glBindTexture(GL_TEXTURE_2D, TEXTURE_ID_CUBE);
    DrawCubeWithTextureCoords(1.0);
    // Child object (teapot) ... relative transform, and render
    glPushMatrix();
    glTranslatef(2, 0, 0);
    glRotatef(g_fTeapotAngle2, 1, 1, 0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colorBronzeDiff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, colorBronzeSpec);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0);
    glColor4fv(colorBronzeDiff);
    glBindTexture(GL_TEXTURE_2D, 0);
    glutSolidTeapot(0.3);
    glPopMatrix();
    glPopMatrix();
    
    
}


Art *art;// = Art();


