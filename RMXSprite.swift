//
//  RMXSprite.swift
//  OC to Swift oGL
//
//  Created by Max Bilbow on 16/02/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

import Foundation
import SceneKit
import CoreMotion

//typealias RMXVector = Array<Float>
//
//extension RMXVector {
//    
//}
class RMXSprite : NSObject, RMXObserver , RMXInteface{
    
    var effectedByAccelerometer: Bool
    var name: String
    var position, velocity,acceleration, forwardVector, upVector, leftVector, forwardV, upV, leftV, anchor, itemPosition: [Float]
    var physics: RMXPhysics
    var accelerationRate, speedLimit,ground,rotationSpeed,jumpStrength,armLength, reach: Float
    var limitSpeed, drift: Bool
    var origin, itemInHand: RMXSprite?
   
    //@property Mouse *mouse
    //@property Particle * item
  
    
    required init(name: String) {
        position = [ 0, 0, 0 ]
        //position = GLKVector3Make(0, 0, 0)
        velocity = [ 0,0,0 ]
        acceleration = [ 0, 0, 0 ]
        forwardVector = [ 0, 0, 1 ]
        upVector = [ 0, 1, 0 ]
        leftVector = [ 1, 0, 0 ]
        forwardV = [ 0, 0, 0 ]
        upV = [ 0, 0, 0 ]
        leftV = [ 0, 0, 0 ]
        
        physics = RMXPhysics(name: name)
        accelerationRate=0.01
        speedLimit=0.20
        limitSpeed=true
        drift=false
        ground=0
          //[[Particle alloc]initWithName:@"Origin"]
        anchor = [ 0, 0, 0 ]
        rotationSpeed = -0.1
        jumpStrength=2.0

        //mouse = [[Mouse alloc]initWithName:name]
        self.itemInHand = self.origin
        itemPosition = [0,0,0]// itemInHand.position
        armLength = 2
        reach = 6
        //self.ground=1
        self.name = name
        self.effectedByAccelerometer = true
        super.init()
    }
    
    
    
    func accelerateForward(v: Float)
    {
    acceleration[2] = v * accelerationRate
    
    }
    
    func accelerateUp(v: Float)
    {
    acceleration[1] = v * accelerationRate
    //  accelerate()
    //       accelerate(GLKVector3Make(0,velocity*accelerationRate,0))
    }
    
    func accelerateLeft(v: Float)
    {
    acceleration[0] = v * accelerationRate
    //accelerate()//accelerate(GLKVector3Make(velocity*accelerationRate,0,0))
    }
    
    
    func forwardStop()
    {
    if (!drift) {
    acceleration[2] = 0
    //            if(getForwardVelocity()>0)
    //                acceleration.z = -physics.friction
    //            else if (getForwardVelocity()<0)
    //                acceleration.z = physics.friction
    //            else
    //                acceleration.z = 0//-velocity.z
    }
    }
    
    func upStop()
    {
    if (!drift) {
        acceleration[1] = 0// -velocity.y
    //accelerate()
    }
    }
    
    func leftStop()
    {
    if (!drift) {
    acceleration[0] = 0// -velocity.x
    //accelerate()
    }
    
    }
    
    func accelerate()
    {
    //acceleration.z =
    rmxDebugger.add(self.name, message:"FV: %f, LV: %f, UV: %f")
    acceleration[1] -= physics.gravity
    self.setVelocity(acceleration) //Need to calculate this
    
    if (limitSpeed){
        for (var i=0;i<3;++i){
            if (velocity[i] > speedLimit){
                //[rmxDebugger add:3 n:self.name t:[NSString stringWithFormat:@"speed%i = %f",i,[self velocity].v[i]]]
                velocity[i] = speedLimit
            } else if (velocity[i] < -speedLimit){
                //[rmxDebugger add:3 n:self.name t:[NSString stringWithFormat:@"speed%i = %f",i,[self velocity].v[i]]]
                velocity[i] = -speedLimit
            } else {
                rmxDebugger.add(self.name, message:"speed%i OK: %f ,i,[self velocity].v[i]")
            }
        }
    }
    
    
   // [rmxDebugger add:6 n:self t:[NSString stringWithFormat:@"accZ: %f, velZ: %f",[self acceleration].z,[self velocity].z]]
    
    
    }
    
    
    func isDrift()->Bool
    {
    return !self.drift
    }
    
    func setPosition(var v: [Float])
    {
        if v[1] < self.ground {
            v[1] = self.ground
        }
        position = v
    }
    
    
    func isZero(v: [Float])->Bool
    {
        var zero = true
        for value in v {
            if value != 0 {
                zero = false
            }
        }
        return zero
    }
    
    func translate()->Bool
    {
        if isZero(self.velocity) {
            return false
        }
        else {
            self.setPosition(self.position + self.velocity) //Might break
        }
    return true
    }
    
    func animate()
    {
        if self.effectedByAccelerometer {
            interpretAccelerometerData(motionManager.accelerometerData?)
        }
    self.accelerate()
    self.leftVector = RMXVector3CrossProduct(self.forwardVector,self.upVector)
        if !self.translate() {
                rmxDebugger.add(self.name, message:"no movement!")
        }
        self.manipulateItems()
    //[rmxDebugger add:2 n:self.name t:[NSString stringWithFormat:@"%@ POSITION: %p | PX: %f, PY: %f, PZ: %f",self.name,[self pMem],[self position].x,[self position].y,[self position].z ]]
    }
    

    //MOVEMENT
    
    func stop()
    {
    self.setVelocity([0,0,0])
        //setRotationalVelocity(GLKVector3Make(0,0,0))
    }
    
    
    
    func plusAngle(var theta: Float, var phi: Float)
    {
    theta *= GLKMathDegreesToRadians(self.rotationSpeed)
    phi *= GLKMathDegreesToRadians(self.rotationSpeed)
    self.rotateAroundVerticle(theta)
    self.rotateAroundHorizontal(phi)
    //[rmxDebugger add:2 n:self.name t:[NSString stringWithFormat:@"plusAngle: THETA %f, PHY: %f",theta,phi]]
    }
    
    func rotateAroundVerticle(theta:Float) {
        var rm = RMXMatrix4MakeRotation(theta, self.upVector[0], self.upVector[1], self.upVector[2])
        
        
    //GLKMatrix4RotateWithVector3(GLKMatrix4MakeYRotation(theta), theta, getUpVector())
    self.forwardVector=RMXMatrix4MultiplyVector3WithTranslation(rm, self.forwardVector)
    //leftVector = GLKMatrix4MultiplyVector3WithTranslation(rm, leftVector)
    //free(rm)
    }
    func rotateAroundHorizontal(phi:Float){
    // leftVector = GLKVector3CrossProduct(getForwardVector(), getUpVector()) // Set the Right Vector
       var rm = RMXMatrix4MakeRotation(phi,self.leftVector[0], self.leftVector[1], self.leftVector[2])
    
        self.forwardVector=RMXMatrix4MultiplyVector3WithTranslation(rm, self.forwardVector)
    
    }
    
    func setVelocity(acceleration:[Float])
    {
        var forward = acceleration[2]
        var left = -acceleration[0]
        var up = acceleration[1]
       // [rmxDebugger add:1 n:self.name t:[NSString stringWithFormat:@"FV: %f, LV: %f, UV: %f",forward,left,up]]
        self.forwardV = self.forwardVector * forward
        //forwardV = GLKVector3DivideScalar(forwardV, physics.friction)
        self.upV = self.upVector * up
        self.leftV = self.leftVector * left
        // GLKVector3 tm = GLKVector3Project(acceleration, forwardVector)
        //GLKVector3 tm
        
        self.velocity += self.forwardV + self.leftV
        self.velocity /= self.physics.getFriction()
        self.velocity += self.upV
    
    }
    
    
    
    func addGravity(g:Float)
    {
        self.physics.addGravity(g)
    }
    
    func toggleGravity()
    {
        self.physics.toggleGravity()
    }
    
    func hasGravity()->Bool{
        return self.physics.gravity > 0
    }
    
    func isGrounded()->Bool{
    return self.position[1] == self.ground
    }
    
    func push(direction:[Float])
    {
        self.setVelocity(self.velocity+direction)
    }
    
    
    
    
    func getEye()->[Float]
    {
    return self.position
    }
    
    func getCenter()->[Float]
    {
        return self.position + self.forwardVector
    }
    
    func getUp()->[Float]
    {
        return self.upVector
    }

    
    
    func jump() {
        if (self.hasGravity()&&self.isGrounded()) {
            self.accelerateUp(self.jumpStrength)
        }
    }
    
    func grabObject(i: RMXSprite)
    {
        if (self.itemInHand == i||RMXVectorDistance(self.position, i.position)>self.reach) {
            self.releaseObject()
        } else {
            self.itemInHand = i
            itemPosition = i.position
            armLength = RMXVectorDistance(self.getCenter(), itemPosition)
        }
    
    }
    
    func releaseObject() {
    //origin.setPosition(anchor->getCenter())
        self.itemInHand = self.origin//[[Particle alloc]init]
    }
    
    func manipulateItems() {
    //item->setAnchor(this->getPosition())
        itemInHand?.position = self.getCenter()+(self.forwardVector*self.armLength)
    }
    
    func extendArmLength(i: Float) {
        if (armLength+i>1) {
            armLength += i
        }
    }
    
    
   override var description: String {
        return "      EYE x\(getEye()[0]), y\(getEye()[1]), z\(getEye()[2])\n   CENTRE x\(getCenter()[0]), y\(getCenter()[1]), z\(getCenter()[2])\n      UP: x\(getUp()[0]), y\(getUp()[1]), z\(getUp()[2])"
    }

    func interpretAccelerometerData(data:CMAccelerometerData?){
        if (data != nil) {
            self.setVelocity([Float(data!.acceleration.x), Float(data!.acceleration.y),Float(data!.acceleration.z) ])
//            self.accelerateForward(Float(data!.acceleration.z))
//            self.accelerateLeft(Float(data!.acceleration.x))
//            self.accelerateUp(Float(data!.acceleration.y))
            println("Accelerometer \nx:\(round(data!.acceleration.x))\n y:\(round(data!.acceleration.y))\n z:\(round(data!.acceleration.z))")

        }
        
            }
    
    func setEffectedByAccelerometer(set: Bool=true){
        self.effectedByAccelerometer=set
    }
    
    func isEffectedByAccelerometer() -> Bool{
        return self.effectedByAccelerometer
    }
    
}