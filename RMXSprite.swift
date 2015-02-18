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

extension  RMXSprite :RMXInteface{
    
    //func interpretAccelerometerData() { RMXFatalError("interpretAccelerometerData() has not been implemented") }

    func interpretAccelerometerData() {
        if (self.effectedByAccelerometer) && (self.gyro? != nil) {
            if gyro?.deviceMotion != nil {
                self.upVector[0] = -Float(self.gyro!.accelerometerData!.acceleration.x)
                self.upVector[1] = -Float(self.gyro!.accelerometerData!.acceleration.y)
                self.upVector[2] = -Float(self.gyro!.accelerometerData!.acceleration.z)
                
                
                RMXLog("--- Accelerometer Data")
                RMXLog("Motion: x\(gyro?.deviceMotion!.userAcceleration.x.toData()), y\(gyro?.deviceMotion!.userAcceleration.y.toData()), z\(gyro?.deviceMotion!.userAcceleration.z.toData())")
            }
            if gyro?.accelerometerData? != nil {
                let dp = "04.1"
                RMXLog("Acceleration: x\(gyro?.accelerometerData!.acceleration.x.toData()), y\(gyro?.accelerometerData!.acceleration.y.toData()), z\(gyro?.accelerometerData!.acceleration.z.toData())")
                RMXLog("=> upVector: x\(self.upVector[0].toData(dp: dp)), y\(self.upVector[1].toData(dp: dp)), z\(self.upVector[2].toData(dp: dp))")
            }
            RMXLog(self.description)
        }
    }

}

class RMXSprite : SCNNode, RMXObserver , RMXNode, RMXInteface{
    var pos: (x:Float,y:Float,z:Float) = ( x:0.0,y:0.0,z:0.0)
    var gyro: RMXGyro?
    var effectedByAccelerometer: Bool = false
    //var name: String?
    var positionf: [Float] {
        return self.position.v
    }

    var velocity, acceleration, forwardVector, upVector, leftVector, forwardV, upV, leftV, anchor, itemPosition: [Float]
    var physics: RMXPhysics
    var accelerationRate, speedLimit,ground,rotationSpeed,jumpStrength,armLength, reach: Float
    var limitSpeed, drift: Bool
    var origin, itemInHand: RMXSprite?
    var frozen = false
   
    //@property Mouse *mouse
    //@property Particle * item
  
    var worldView: RMXWorld?
    required init(name: String?, worldView: RMXWorld?, coder aDecoder: NSCoder? = nil) {
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
        super.init()
        self.name = name
        self.effectedByAccelerometer = true
        self.worldView = worldView
        self.position = SCNVector3( x: 0, y: 0, z: 15 )
        self.gyro = RMXGyro(parent: self)
        
    }

    required init(coder aDecoder: NSCoder) {
        RMXFatalError(sender: "init(coder:) has not been implemented")
    }
    
    
    
    func accelerateForward(v: Float)
    {
        acceleration[2] = v * accelerationRate
    }
    
    func accelerateUp(v: Float) {
        acceleration[1] = v * accelerationRate
    }

    func accelerateLeft(v: Float) {
        acceleration[0] = v * accelerationRate
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
    
    func upStop()    {
        if (!drift) {
            acceleration[1] = 0// -velocity.y
        }
    }
    
    func leftStop() {
        if (!drift) {
            acceleration[0] = 0
        }
    }
    
    func accelerate() {
    //acceleration.z =
        RMXLog(self, "FV: %f, LV: %f, UV: %f")
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
                    RMXLog(self,"speed%i OK: %f ,i,[self velocity].v[i]")
                }
            }
        }
    
    }
    
    
    func isDrift()->Bool {
        return !self.drift
    }
    
    func setPosition(var v: [Float]) {
        if v[1] < self.ground {
            v[1] = self.ground
        }
        position = RMXVector3Make(v)
    }
    
    func isZero(v: [Float])->Bool {
        var zero = true
            for value in v {
                if value != 0 {
                    zero = false
            }
        }
        return zero
    }
    
    
    func update()
    {
        if frozen { stop(); return } else {
        interpretAccelerometerData()
        self.accelerate()
        self.leftVector = RMXVector3CrossProduct(self.forwardVector,self.upVector)
        if !self.translate() {
                RMXLog(self,"no movement!")
        }
        self.manipulateItems()
        }
    }

    func stop() {
        self.setVelocity([0,0,0])
    }
    
    func plusAngle(var theta: Float, var phi: Float) {
        theta *= GLKMathDegreesToRadians(self.rotationSpeed)
        phi *= GLKMathDegreesToRadians(self.rotationSpeed)
        self.rotateAroundVerticle(theta)
        self.rotateAroundHorizontal(phi)
    }
    
    func rotateAroundVerticle(theta:Float) {
        var rm = RMXMatrix4MakeRotation(theta, self.upVector[0], self.upVector[1], self.upVector[2])
        self.forwardVector=RMXMatrix4MultiplyVector3WithTranslation(rm, self.forwardVector)
    }
    
    func rotateAroundHorizontal(phi:Float){
        var rm = RMXMatrix4MakeRotation(phi,self.leftVector[0], self.leftVector[1], self.leftVector[2])
        self.forwardVector=RMXMatrix4MultiplyVector3WithTranslation(rm, self.forwardVector)
    }
    
    func setVelocity(acceleration:[Float]) {
        var forward = acceleration[2]
        var left = -acceleration[0]
        var up = acceleration[1]
        self.forwardV = self.forwardVector * forward
        self.upV = self.upVector * up
        self.leftV = self.leftVector * left
        self.velocity += self.forwardV + self.leftV
        self.velocity /= self.physics.getFriction()
        self.velocity += self.upV
    }
    

    
    
    func addGravity(g:Float){
        self.physics.addGravity(g)
    }
    
    func toggleGravity(){
        self.physics.toggleGravity()
    }
    
    func hasGravity()->Bool{
        return self.physics.gravity > 0
    }
    
    func isGrounded()->Bool{
        return self.positionf[1] == self.ground
    }
    
    func push(direction:[Float]) {
        self.setVelocity(self.velocity+direction)
    }
    
    
    
    
    func getEye()->[Float] {
        return self.positionf
    }
    
    func getCenter()->[Float] {
        return self.positionf + self.forwardVector
    }
    
    func getUp()->[Float] {
        return self.upVector
    }

   
    
    var viewTarget: SCNVector3? { return RMXVector3Make(self.positionf + self.forwardVector) }
    //var upView: SCNVector3? { return RMXVector3Make(self.upVector) }
    
    
    func jump() {
        if (self.hasGravity()&&self.isGrounded()) {
            self.accelerateUp(self.jumpStrength)
        }
    }
    
    
    
    func releaseObject() {
    //origin.setPosition(anchor->getCenter())
        self.itemInHand = self.origin//[[Particle alloc]init]
    }
    
    func manipulateItems() {
    //item->setAnchor(this->getPosition())
        itemInHand?.position = RMXVector3Make(self.getCenter()+(self.forwardVector*self.armLength))
    }
    
    func extendArmLength(i: Float) {
        if (armLength+i>1) {
            armLength += i
        }
    }
    
    
   override var description: String {
        if (RMX.debugging) {
            let dp:String = "03.0"
            RMXLog("--- SPRITE DATA")
            RMXLog("      EYE: x\(getEye()[0].toData(dp: dp)), y\(getEye()[1].toData(dp: dp)), z\(getEye()[2].toData(dp: dp))")
            RMXLog("   CENTRE: x\(getCenter()[0].toData(dp: dp)), y\(getCenter()[1].toData(dp: dp)), z\(getCenter()[2].toData(dp: dp))")
            RMXLog("       UP: x\(getUp()[0].toData(dp: dp)), y\(getUp()[1].toData(dp: dp)), z\(getUp()[2].toData(dp: dp))")
            
            return ""
        }
    
        return "      EYE: x\(getEye()[0].toData()), y\(getEye()[1].toData()), z\(getEye()[2].toData())\n   CENTRE: x\(getCenter()[0].toData()), y\(getCenter()[1].toData()), z\(getCenter()[2].toData())\n       UP: x\(getUp()[0].toData()), y\(getUp()[1].toData()), z\(getUp()[2].toData())"
    }

    
    
    
    //func translate()->Bool { RMXFatalError("translate() has not been implemented"); return false    } override
    func translate()->Bool
    {
        if isZero(self.velocity) {
            return false
        }
        else {
            self.setPosition(self.positionf + self.velocity) //Might break
        }
        return true
    }
//    func grabObject(i: RMXSprite) {};
    func grabObject(i: RMXSprite)
    {
        if (self.itemInHand == i||RMXVectorDistance(self.positionf, i.positionf)>self.reach) {
            self.releaseObject()
        } else {
            self.itemInHand = i
            itemPosition = i.positionf
            armLength = RMXVectorDistance(self.getCenter(), itemPosition)
        }
        
    }
    
}