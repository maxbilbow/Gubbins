//
//  main.cpp
//  OpenGL 2.0
//
//  Created by Max Bilbow on 23/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//


#include "Header.h"


void InitGraphics(void)
{
    int width, height;
    int nComponents;
    void* pTextureImage;
    
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHT1);
    // Create texture for cube; load marble texture from file and bind it
    //pTextureImage = read_texture("marble.rgb", &width, &height, &nComponents);
    glBindTexture(GL_TEXTURE_2D, TEXTURE_ID_CUBE);
    gluBuild2DMipmaps(GL_TEXTURE_2D,     // texture to specify
                      GL_RGBA,           // internal texture storage format
                      width,             // texture width
                      height,            // texture height
                      GL_RGBA,           // pixel format
                      GL_UNSIGNED_BYTE,	// color component format
                      pTextureImage);    // pointer to texture image
    glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                     GL_LINEAR_MIPMAP_LINEAR);
    glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}


int init()
{
    
    
    window.init(glutInitWindowSize,//glutInitDisplayMode,
                glutDisplayFunc,glutReshapeFunc,
                glutKeyboardFunc,glutKeyboardUpFunc,glutSpecialFunc,glutSpecialUpFunc,
                glutMouseFunc,glutMotionFunc,glutPassiveMotionFunc,
                glutIdleFunc
                );
    
    glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    

    if (window.isFullscreen()){//&&glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)){
        glutEnterGameMode();
    }else {
        cout << glutGameModeGet(GLUT_GAME_MODE_POSSIBLE);
         //window.create(glutCreateWindow);
        window.create(glutCreateWindow);
//        glutInitWindowPosition(100,100);
//        glutInitWindowSize(640,360);
//        glutCreateWindow("SnowMen from Lighthouse3D");
    }

    
        
    // Register callbacks:
    window.display (display,reshape);
    window.keyboard(keyPressed,keyUp,keySpecial,keySpecialUp);
    window.mouse(MouseButton,MouseMotion,mouseFree);
    window.idle(AnimateScene);
    
    // Create our popup menu
    BuildPopupMenu ();
InitGraphics();
    glutAttachMenu (GLUT_RIGHT_BUTTON);
    // Get the initial time, for use by animation
#ifdef _WIN32
    last_idle_time = GetTickCount();
#else
    gettimeofday (&last_idle_time, NULL);
#endif
    
    //mouse.center();
    
    if (window.isFullscreen()) {
        observer->toggleFocus();
        glutSetCursor(GLUT_CURSOR_NONE);
        observer->calibrateMouse(0,0);//observer->getMouse().x,observer->getMouse().y);
        observer->mouse2view(0, 0);
    }
    glutMainLoop ();
    return 0;
}





//using namespace World;
//World world = World();
int main (int argc, char **argv) {
   
    sh = &world.getShapes()[World::Objects::BOX1];
    sh->setPosition(GLKVector3Make(6,0,0));
    sh->setColor(yellow);
    sh->setrAxis(GLKVector3Make(0,1,0));
    
    
    //sh2 = &world.getShapes()[1];
    sh2 = new ShapeObject;
    sh2->setPosition(GLKVector3Make(-3,0,0));
    sh2->setColor(red);
    sh2->setrAxis(GLKVector3Make(0,1,0));
    world.setShape(World::Objects::BOX2, sh2);
    
    //sh3 = &world.getShapes()[2];
    sh3 = new ShapeObject;
    sh3->setPosition(GLKVector3Make(3,0,0));
    sh3->setColor(colorBlue);
    sh3->setrAxis(GLKVector3Make(0,1,0));
    world.setShape(World::Objects::BOX3, sh3);
    
    sh4 = new ShapeObject;
    sh4->setPosition(GLKVector3Make(0,0,-3));
    sh4->setColor(green);
    sh4->setrAxis(GLKVector3Make(0,1,0));
    world.setShape(World::Objects::BOX3, sh3);
    
    observer = world.getMainObserver();
    
    glutInit(&argc, argv);
     //Interface view = Interface();
    
    
    
    init();
    //glutInitDisplayMode( GLUT_SINGLE );//GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );

    //glutMainLoop(); // Enter GLUT's main loop
    
    return 0;
    
}
