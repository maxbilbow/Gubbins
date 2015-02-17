//
//  RMXWorld.swift
//  OC to Swift oGL
//
//  Created by Max Bilbow on 16/02/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

import Foundation
import UIKit
import SceneKit


protocol _RMXWorld : RMXNamed {
    var sprites: [RMXSprite] { get }
    var observerName: String { get set }
 //float dt;
    func closestObject()->RMXSprite?
    func update()
    func insert(object: RMXSprite)
    func objectWithName(name: String)->RMXSprite
    func setObserverWithId(observer:RMXSprite)
}

class RMXWorld : UIViewController, _RMXWorld {
//@synthesize name = _name, sprites = _sprites, observerName, dt;//, mainObserver = _mainObserver;
    let W_GRAVITY = (0.01/50)
    let W_FRICTION = 1.1
    var name, observerName: String
    var sprites: [RMXSprite]
    
    var scene: SCNScene?
    required init(coder aDecoder: NSCoder) {
        self.name = "World"
        observerName = "Main Observer"
        sprites = [RMXSprite]()
        super.init(coder: aDecoder)
        //motionManager.gvc = self
        //motionManager.gvc = self
        sprites.append(RMXSprite(name:observerName,worldView: self,coder: aDecoder))
        NSLog("WORLD SAFE")
//        fatalError("init(coder:) has not been implemented")
    }

    
    var observer: RMXSprite? {
        return sprites.first
    }
    
    func setObserverWithId(observer:RMXSprite){
        sprites.insert(observer, atIndex: 0)
//        if ([_sprites valueForKey:name])
//        observerName = name;
//        else
//        NSLog(@"ERROR: Object '%@' not found in sprites array",name);
        
    }
    
func objectWithName(name: String)->RMXSprite {
        //observerName = name
       // sprites.
    return RMXSprite(name: name, worldView: self)
    }
                
    func insert(object: RMXSprite){
        sprites.append(object)
    }
    
    
    func update() {
        for sprite in sprites {
            sprite.update()
            //println(sprite)
        }
//        if UIDeviceOrientation == UIDeviceOrientation.Portrait {
//                println("Hello, Portrate")
//        }
        RMX.printLog()
    }
    
        
    func closestObject()->RMXSprite? {
               /* id closest = [_sprites objectAtIndex:1];
                float dista=GLKVector3Distance([self observer].position, ((Particle*)[_sprites objectAtIndex:1]).position);
                for (Particle* sprite in _sprites){
                    float distb = GLKVector3Distance([self observer].position, sprite.position);
                    NSString *lt = @" < ";
                    if(distb<dista&&distb!=0){
                        closest = sprite;
                        //shapes[i];
                        lt = @" > ";
                        // cout << i-1 << ": "<< dista << lt << (i) <<": "<< distb << endl;
                        dista = distb;
                    }
                    
                }
                //cout << "closest: "<< closest << ", dist:" << dista << endl;
                return closest;//shapes[closest]; */
                return nil
    }
        
        
}

//RMXWorld *world;