//
//  RMXParticle.swift
//  OC to Swift oGL
//
//  Created by Max Bilbow on 16/02/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

import Foundation
import SceneKit

protocol RMXNamed {
    var name: String { get }
    init(name:String)
}
protocol RMXNode : RMXNamed{
        var position: [Float] { get set }
        var velocity: [Float] { get set }
        func animate()
}
protocol RMXSimpleParticle : RMXNode, RMXNamed {
    
    
    var acceleration: [Float] { get set }
    var forwardVector: [Float] { get set }
    var upVector: [Float] { get set }
    var leftVector: [Float] { get set }
    var forwardV: [Float] { get set }
    var upV: [Float] { get set }
    var leftV: [Float] { get set }
    var physics: RMXPhysics { get set }
    var accelerationRate: Float { get set }
    var speedLimit: Float { get set }
    var ground: Float { get set }
    var rotationSpeed: Float { get set }
    var jumpStrength: Float { get set }
    var limitSpeed: Bool { get set }
    var drift: Bool { get set }
    
    func accelerateForward(atSpeed: Float)
    func accelerateUp(atSpeed: Float)
    func accelerateLeft(atSpeed: Float)
    func forwardStop()
    func upStop()
    func leftStop()
    
}


protocol RMXParticle : RMXSimpleParticle , RMXNode, RMXNamed{
    
    var anchor: [Float] { get set }
    var origin: RMXSprite? { get }// = [[SimpleParticle alloc]init];
   
    //func setVelocity(v: [Float])
    func manipulateItems()
    func translate()->Bool
    func addGravity(g: Float)
    func toggleGravity()
    func hasGravity()->Bool
    func isGrounded()->Bool
   

}

protocol RMXObserver : RMXParticle, RMXSimpleParticle , RMXNode, RMXNamed {
    //    - (GLKVector3)getEye;
    //    - (GLKVector3)getCenter;
    //    - (GLKVector3)getUp;
    var itemInHand: RMXSprite? { get set }
    var itemPosition: [Float] { get }
    var armLength: Float { get set }
    var reach: Float { get set }
    
    func push(direction: [Float])
    func plusAngle(var theta: Float, var phi: Float)
    func jump()
    

}

