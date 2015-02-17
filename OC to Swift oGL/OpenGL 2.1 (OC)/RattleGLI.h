//
//  RattleGLI.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 23/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef OpenGL_2_0_RattleGLI_h
#define OpenGL_2_0_RattleGLI_h


#endif

class RattleGLI {
    Particle * observer;
    
public:
    void setObserver(Particle  &observer){
        this->observer = &observer;
    }
    
    Particle * getObserver(){
        return observer;
    }
    
};