//
//  RMXDebugger.swift
//  OC to Swift oGL
//
//  Created by Max Bilbow on 16/02/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

import Foundation
//import SceneKit
//protocol RMXTestable {
//    //func debugger: RMXDebugger {get}
//    var label: String {get set}
//    mutating func debug(message: String)
//    //class func debug(key: String, message: String)
//    
//}
class RMXTester  {
    //let tester: UnsafeMutablePointer<RMX.Debugger> = UnsafeMutablePointer.alloc(sizeof(RMX.Debugger.self))
    
    class var debugger: RMXDebugger {
        return rmxDebugger
    }
    
    internal var label: String = ""
    
    init(label: String = "Unnamed Class"){
        self.label = label
    }
    
    func debug(message: String){
        rmxDebugger.add(self.label, message: message)
    }
    
    
    
}



class RMXDebugger : RMXTester {
    var no_checks = 10
    var tog = 0
    var lastCheck = ""
    
    //bool * print = new bool[10];
    
    var checks: [ String: String ]//new string[no_checks];
    var monitor: [String]
    var debugging = false
    //GLKVector2 win = new GLKVector2(0,0);
    
    init(){
        checks = [ "ERROR":"N/A", "Debug":"N/A"]
        monitor = [ "ERROR" , "Debug" ]
    }
    
    func feedback(print: [String:String])->String{
        var str: String = ""
        for (kind, report) in print{
            
            if ((kind==monitor[tog]) && (report != lastCheck)){
                str+=String("\(monitor[tog]):...\n\(report)\n")
                lastCheck = report
                checks[(monitor[tog])]=""
            }
        }
        return str
    }
    
    func print(){
        let print = self.feedback(checks)
        if (print != ""){
            println(print)
        }
    }
    
    
    
    func cycle(dir: Int){
        tog += dir
        if (tog>=monitor.count) {
            tog=0
        }else if (tog<0){
            tog = monitor.count-1
        }
    }
    
    func add(key: String, message: String) {
        if (nil == checks.indexForKey(key)){
            checks.updateValue(message, forKey: key)
            monitor.append(key)
        }
        else {
            checks[key]?.extend(message)
        }
        
    }
    
    class func debug(key: String, message: String = "TODO"){
        rmxDebugger.add(key, message: message)
    }
}


