//
//  RMXPhysics.swift
//  OC to Swift oGL
//
//  Created by Max Bilbow on 16/02/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

import Foundation

class RMXPhysics {//: RMXNamed {

    var name: String?
    var gravity, friction: Float
    let U_GRAVITY: Float = (0.01/50)
    let U_FRICTION: Float = 1.1

    init(name:String?){
        self.name = name
        gravity = U_GRAVITY
        friction = U_FRICTION
    }
    
    func toggleGravity(){
        gravity = (gravity == U_GRAVITY) ? 0 : U_GRAVITY
    }
        
    func addGravity(g:Float){
        gravity += g;
        if gravity<0{
            gravity = 0;
        }
        //[rmxDebugger add:4 n:self t:[NSString stringWithFormat:@" / Gravity: %f", gravity]];// +=  + to_string(gravity);
    }
    
    func getFriction()->Float
    {
        return friction;
    }
        
    func toggleFriction(){
        friction = (friction == U_FRICTION) ? 0 : U_FRICTION
    }
    
    func addFriction(f:Float){
        friction += f;
        if friction<0{
            friction = 0;
        }
        //[rmxDebugger add:4 n:self t:[NSString stringWithFormat:@" / Friction: %f",friction]];
    }


}