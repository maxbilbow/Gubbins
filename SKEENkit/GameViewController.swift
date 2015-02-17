//
//  GameViewController.swift
//  SKEENkit
//
//  Created by Max Bilbow on 17/02/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

import UIKit
import QuartzCore
import SceneKit
import CoreMotion

class AlwaysAction : SCNAction {
    
}

class GameViewController: RMXWorld , SCNSceneRendererDelegate {

    lazy var cameraNode = SCNNode()
    func renderer(aRenderer: SCNSceneRenderer, updateAtTime time: NSTimeInterval) {
        (self.view as SCNView).pointOfView!.position = RMXVector3Make(self.observer!.position)
//        cameraNode.position.x = self.observer()!.position[0]
//        cameraNode.position.y = self.observer()!.position[1]
//        cameraNode.position.z = self.observer()!.position[2]
        //cameraNode.position = (self.view as SCNView).pointOfView!.position
        //cameraNode.position.z += 15
        RMXLog("--- Camera Orientation")
        RMXLog("w\(cameraNode.orientation.w.toData()), x\(cameraNode.orientation.w.toData()), y\(cameraNode.orientation.w.toData()), z\(cameraNode.orientation.w.toData())")
        self.update()
    }
    override func viewDidLoad() {
        super.viewDidLoad()
        
        // create a new scene
        scene = SCNScene(named: "art.scnassets/ship.dae")!
        
        // create and add a camera to the scene
//        let cameraNode = SCNNode()
        cameraNode.camera = SCNCamera()
        scene!.rootNode.addChildNode(cameraNode)
        
        // place the camera
        cameraNode.position = SCNVector3(x: 0, y: 0, z: 15)
        
        // create and add a light to the scene
        let lightNode = SCNNode()
        lightNode.light = SCNLight()
        lightNode.light!.type = SCNLightTypeOmni
        lightNode.position = SCNVector3(x: 0, y: 10, z: 10)
        scene!.rootNode.addChildNode(lightNode)
        
        // create and add an ambient light to the scene
        let ambientLightNode = SCNNode()
        ambientLightNode.light = SCNLight()
        ambientLightNode.light!.type = SCNLightTypeAmbient
        ambientLightNode.light!.color = UIColor.darkGrayColor()
        scene!.rootNode.addChildNode(ambientLightNode)
        
        // retrieve the ship node
        let ship = scene!.rootNode.childNodeWithName("ship", recursively: true)!
        
        // animate the 3d object
        ship.runAction(SCNAction.repeatActionForever(SCNAction.rotateByX(0, y: 2, z: 0, duration: 1000)))
      
        // retrieve the SCNView
        let scnView = self.view as SCNView
        
        // set the scene to the view
        scnView.scene = scene
        
        // allows the user to manipulate the camera
        scnView.allowsCameraControl = false
        
        
        // show statistics such as fps and timing information
        scnView.showsStatistics = true
        
        // configure the view
        scnView.backgroundColor = UIColor.blackColor()
        
        
        // add a tap gesture recognizer
        
//        UITapGestureRecognizer
//        
//        UIPinchGestureRecognizer
//        
//        UIRotationGestureRecognizer
//        
//        UISwipeGestureRecognizer
//        
//        UIPanGestureRecognizer
//        
//        UIScreenEdgePanGestureRecognizer
        
        //UILongPressGestureRecognizer
        
        let tapGesture = UITapGestureRecognizer(target: self, action: "handleTap:")
        let pressGesture = UILongPressGestureRecognizer(target: self, action: "handlePress:")
        let gestureRecognizers = NSMutableArray()
        gestureRecognizers.addObject(tapGesture)
        gestureRecognizers.addObject(pressGesture)
        if let existingGestureRecognizers = scnView.gestureRecognizers {
            gestureRecognizers.addObjectsFromArray(existingGestureRecognizers)
        }
        
        //let moveMan =
        scnView.gestureRecognizers = gestureRecognizers
        scnView.delegate = self

        
    }
    
    func handlePress(gestureRecognize: UIGestureRecognizer) {
        self.observer!.frozen = !self.observer!.frozen
        

    }
    func handleTap(gestureRecognize: UIGestureRecognizer) {
        // retrieve the SCNView
        let scnView = self.view as SCNView
        
        // check what nodes are tapped
        let p = gestureRecognize.locationInView(scnView)
        if let hitResults = scnView.hitTest(p, options: nil) {
            // check that we clicked on at least one object
            if hitResults.count > 0 {
                // retrieved the first clicked object
                let result: AnyObject! = hitResults[0]
                
                // get its material
                let material = result.node!.geometry!.firstMaterial!
            
                // highlight it
                SCNTransaction.begin()
                SCNTransaction.setAnimationDuration(0.5)
                //self.observer!.frozen = true
                // on completion - unhighlight
                SCNTransaction.setCompletionBlock {
                    SCNTransaction.begin()
                    SCNTransaction.setAnimationDuration(0.5)
                    
                    material.emission.contents = UIColor.blackColor()
                    
                    SCNTransaction.commit()
                    self.observer!.frozen = false
                }
                
                material.emission.contents = UIColor.redColor()
                
                SCNTransaction.commit()
            } else {
                self.observer!.stop()
                self.observer!.position = [ 0 ,0 ,15]
            }
        }
    }
    
    override func shouldAutorotate() -> Bool {
        return true
    }
    
    override func prefersStatusBarHidden() -> Bool {
        return true
    }
    
    override func supportedInterfaceOrientations() -> Int {
        if UIDevice.currentDevice().userInterfaceIdiom == .Phone {
            return Int(UIInterfaceOrientationMask.AllButUpsideDown.rawValue)
        } else {
            return Int(UIInterfaceOrientationMask.All.rawValue)
        }
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Release any cached data, images, etc that aren't in use.
    }
    
  
}
