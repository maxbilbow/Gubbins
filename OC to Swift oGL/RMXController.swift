//
//  RMXSpriteReceiver.swift
//  OC to Swift oGL
//
//  Created by Max Bilbow on 16/02/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

import Foundation
import UIKit
import CoreMotion
//let motionManager: RMXController = RMXController()

class RMXController : CMMotionManager {//: UIAccelerometerDelegate {
    
    var gvc: RMXWorld?
    override init(){
        gvc = nil
        super.init()
        self.startAccelerometerUpdates()
        println("AVAILABLE: \(self.accelerometerAvailable)")
        println("   Active: \(self.accelerometerActive)")
        println("     DATA: \(self.accelerometerData?)")
        
    }
    init(gvc: GameViewController?){
        self.gvc = gvc
        super.init()
        println("AVAILABLE: \(self.accelerometerAvailable)")
        println("   Active: \(self.accelerometerActive)")
        println("     DATA: \(self.accelerometerData?)")
        
    }
    
   
    
    

}


protocol RMXInteface  {
    var effectedByAccelerometer: Bool { get set }
    var gyro: RMXGyro? { get set }
    //func interpretAccelerometerData(data:CMAccelerometerData?)
}
