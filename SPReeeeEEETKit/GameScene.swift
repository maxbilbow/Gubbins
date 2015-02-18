//
//  GameScene.swift
//  SPReeeeEEETKit
//
//  Created by Max Bilbow on 17/02/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

import SpriteKit
class RMX2DNode : SKSpriteNode , RMXInteface {

    //var position, velocity: [Float]
    var worldView: RMXWorld?
    var effectedByAccelerometer: Bool = false
    var gyro: RMXGyro?
    var frozen: Bool = false
    
    init(name: String) {
        effectedByAccelerometer = true
        super.init()
        self.name? = name
        gyro = RMXGyro(parent: self)
    }
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    override init(texture: SKTexture!, color: UIColor!, size: CGSize) {
        super.init(texture: texture, color: color, size: size)
        gyro = RMXGyro(parent: self)
        //effectedByAccelerometer = true
    }
    
    
    
    func update(){
        interpretAccelerometerData()
    }
    func interpretAccelerometerData() {
        if (self.effectedByAccelerometer) && (self.gyro? != nil) {
            if gyro?.deviceMotion != nil {
        
                self.position.x += CGFloat(gyro!.accelerometerData!.acceleration.x)
                self.position.y += CGFloat(gyro!.accelerometerData!.acceleration.y)
                
                
                RMXLog("--- Accelerometer Data")
                RMXLog("Motion: x\(gyro?.deviceMotion!.userAcceleration.x.toData()), y\(gyro?.deviceMotion!.userAcceleration.y.toData()), z\(gyro?.deviceMotion!.userAcceleration.z.toData())")
            }
            if gyro?.accelerometerData? != nil {
                let dp = "04.1"
                RMXLog("Acceleration: x\(gyro?.accelerometerData!.acceleration.x.toData()), y\(gyro?.accelerometerData!.acceleration.y.toData()), z\(gyro?.accelerometerData!.acceleration.z.toData())")
                RMXLog("=> upVector: x\(self.position.x), y\(self.position.y)")
            }
            RMXLog(self.description)
        }
    }
   
}
class GameScene: SKScene {
    override func didMoveToView(view: SKView) {
        /* Setup your scene here */
        let myLabel = SKLabelNode(fontNamed:"Helvetica")
        myLabel.text = "Balls!";
        myLabel.fontSize = 65;
        myLabel.position = CGPoint(x:CGRectGetMidX(self.frame), y:CGRectGetMidY(self.frame));
        
        self.addChild(myLabel)
    }
    
    override func touchesBegan(touches: NSSet, withEvent event: UIEvent) {
        /* Called when a touch begins */
        
        for touch: AnyObject in touches {
            let location = touch.locationInNode(self)
            
            let sprite = SKSpriteNode(imageNamed: "Spaceship")
            //sprite.initialize()
            //sprite.
            
            sprite.xScale = 0.5
            sprite.yScale = 0.5
            sprite.position = location
            
            let action = SKAction.rotateByAngle(CGFloat(M_PI), duration:1)
            
            sprite.runAction(SKAction.repeatActionForever(action))
            
            self.addChild(sprite)
        }
    }
   
   
}
