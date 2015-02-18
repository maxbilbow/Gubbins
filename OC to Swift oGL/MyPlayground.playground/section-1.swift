// Playground - noun: a place where people can play

import Cocoa

var str = "Hello, playground"

func logFunctionName(string: String = __FUNCTION__) {
    let s = " :: \(string)"
    println(s)
}
func myFunction() {
    logFunctionName() // Prints "myFunction()".
}

myFunction()

