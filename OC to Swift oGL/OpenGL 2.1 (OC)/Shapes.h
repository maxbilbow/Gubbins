//
//  shapes.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 23/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef OpenGL_2_0_shapes_h
#define OpenGL_2_0_shapes_h


#endif



#define VIEWING_DISTANCE_MIN  3.0
#define TEXTURE_ID_CUBE 1
enum {
    MENU_LIGHTING = 1,
    MENU_POLYMODE,
    MENU_TEXTURING,
    MENU_EXIT
};

#define TRUE 1
#define FALSE 0
static BOOL g_bLightingEnabled = TRUE;
static BOOL g_bFillPolygons = TRUE;
static BOOL g_bTexture = FALSE;
static BOOL g_bButton1Down = FALSE;
static GLfloat g_fTeapotAngle = 0.0;
static GLfloat g_fTeapotAngle2 = 0.0;
//static GLfloat g_fViewDistance = 3 * VIEWING_DISTANCE_MIN;
//static GLfloat g_nearPlane = 1;
//static GLfloat g_farPlane = 1000;
//    int g_Width = 600;                          // Initial window width
//    int g_Height = 600;                         // Initial window height
static int g_yClick = 0;


void DrawCubeFace(float fSize)
{
    fSize /= 2.0;
    NSLog(@"glBegin(GL_QUADS); IN METAL?");
    /*glVertex3f(-fSize, -fSize, fSize);    glTexCoord2f (0, 0);
    glVertex3f(fSize, -fSize, fSize);     glTexCoord2f (1, 0);
    glVertex3f(fSize, fSize, fSize);      glTexCoord2f (1, 1);
    glVertex3f(-fSize, fSize, fSize);     glTexCoord2f (0, 1);
    glEnd(); */
}
void DrawCubeWithTextureCoords (float fSize)
{
    glPushMatrix();
    DrawCubeFace (fSize);
    glRotatef (90, 1, 0, 0);
    DrawCubeFace (fSize);
    glRotatef (90, 1, 0, 0);
    DrawCubeFace (fSize);
    glRotatef (90, 1, 0, 0);
    DrawCubeFace (fSize);
    glRotatef (90, 0, 1, 0);
    DrawCubeFace (fSize);
    glRotatef (180, 0, 1, 0);
    DrawCubeFace (fSize);
    glPopMatrix();
}


void DrawSpheree(double r, int lats, int longs)
{

          int i, j;
          for(i = 0; i <= lats; i++) {
                  double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
                  double z0  = sin(lat0);
                  double zr0 =  cos(lat0);
        
                  double lat1 = M_PI * (-0.5 + (double) i / lats);
                  double z1 = sin(lat1);
                  double zr1 = cos(lat1);
        
              NSLog(@"glBegin(GL_QUAD_STRIP) in metal?");
                  for(j = 0; j <= longs; j++) {
                        double lng = 2 * M_PI * (double) (j - 1) / longs;
                          double x = cos(lng);
                          double y = sin(lng);
            
                       /*   glNormal3f(x * zr0, y * zr0, z0);
                         glVertex3f(x * zr0, y * zr0, z0);
                          glNormal3f(x * zr1, y * zr1, z1);
                          glVertex3f(x * zr1, y * zr1, z1); */
                      }
                 // glEnd();
        }
    }

void DrawSphere(float size){
    DrawSpheree(size,10,10);
}



