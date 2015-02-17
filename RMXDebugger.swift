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
struct RMX  {
    //let tester: UnsafeMutablePointer<RMX.Debugger> = UnsafeMutablePointer.alloc(sizeof(RMX.Debugger.self))
    
    static var tog = 0
    static var lastCheck = ""
    static var logs: [String] = Array<String>()
    //bool * print = new bool[10];
    
    static var checks: [ String: String ] = [ "ERROR":"N/A", "Debug":"N/A"]
    static var monitor: [ String ] = [ "ERROR" , "Debug" ]
    static var debugging = true
    //GLKVector2 win = new GLKVector2(0,0);
    
    
    static func feedback(print: [String:String])->String{
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
    
    static func print(){
        let print = self.feedback(checks)
        if (print != ""){
            println(print)
        }
    }
    

    
    static func cycle(dir: Int){
        tog += dir
        if (tog>=monitor.count) {
            tog=0
        }else if (tog<0){
            tog = monitor.count-1
        }
    }
    
    static func add(key: String, message: String) {
        if (nil == checks.indexForKey(key)){
            checks.updateValue(message, forKey: key)
            monitor.append(key)
        }
        else {
            checks[key]?.extend(message)
        }
        
    }
    
    static func debug(key: String, message: String = "TODO"){
        add(key, message: message)
    }
    
    
   
    static func log(log: String){
        self.logs.append(log)
    }
    
    static func printLog() {
        
        logs.append(feedback(checks))
        var output: String = "\n"//log
        var longest:Int = 0
        for log in logs {
            if log.utf16Count > longest {
                longest = log.utf16Count
            }
        }
        for log in logs {
            let diff:Int = longest - log.utf16Count
            let spacer: String = log.hasPrefix("---") ? "-" : " "
            for (var i:Int = 0; i<diff;++i){
                output += spacer
            }
            output += log
            output += "\n"
        }
        
        NSLog(output)
        logs.removeAll(keepCapacity: true)
    }
}

func RMXLog(logs: String...) {
    for log in logs {
        RMX.log(log)
    }
}

func RMXLog(object: RMXNamed, message: String...) {
    for log in message {
        RMX.add(object.name, message: log)
    }
}
