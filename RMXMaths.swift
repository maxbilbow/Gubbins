//
//  RMXMaths.swift
//  OC to Swift oGL
//
//  Created by Max Bilbow on 16/02/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

import Foundation
//import Metal
import SceneKit


//var rm: [[Float]] = RMXMatrix4MakeRotation(phi,self.leftVector[0], self.leftVector[1], self.leftVector[2])

//self.forwardVector=RMXMatrix4MultiplyVector3WithTranslation(rm, self.forwardVector)

func RMXMatrix4MakeRotation(angle:Float,x:Float,y:Float,z:Float)-> SCNMatrix4 {
   return SCNMatrix4MakeRotation(angle,x, y, z)
//    var rmxM: [[Float]] = [
//    [ rm.m11 , rm.m12, rm.m13, rm.m14 ],
//    [ rm.m21 , rm.m22, rm.m23, rm.m24 ],
//    [ rm.m31 , rm.m32, rm.m33, rm.m34 ],
//    [ rm.m41 , rm.m42, rm.m43, rm.m44 ]
//    ]
   // return SCNMatrix4ToMat4(rm)
}

func RMXMatrix4MultiplyVector3WithTranslation(matrix: SCNMatrix4, vector: [Float])->[Float]{
    //println("RMXMatrix4MultiplyVector3WithTranslation not applied")
    //let v = SCNMat(vector[0], vector[1], vector[2])
    //let v = SCNVector3Make(vector[0], vector[1], vector[2])
    //let tm = SCNMatrix4MakeTranslation(vector[0], vector[1], vector[2])
    //let res = SCNMatrix4Mult(matrix, tm)
    let tm = SCNMatrix4Translate(matrix,vector[0], vector[1], vector[2])
    
    return [tm.m41,tm.m42,tm.m43]
    
}

/**
* Calculates the distance between two SCNVector3. Pythagoras!
*/
func RMXVectorDistance(left: [Float],right: [Float]) -> Float {
    return RMXVectorLength(left - right)// .length()
}

func RMXVectorLength(var v:[Float])->Float{
    var i: Int = 0
    var res: Float = 0
    for f in v {
        res += f*f
        ++i
    }
    return sqrtf(res)
}


/**
* Increments a [Float] with the value of another.
*/
func += (inout left: [Float], right: [Float]) {
    left = left + right
}

/**
* Subtracts two [Float] vectors and returns the result as a new [Float].
*/
func - (var left: [Float], right: [Float]) -> [Float] {
    var i: Int = 0
    var res: Float = 0
    for v in right{
        left[i] -= v
        ++i
    }
    return left
}

/**
* Decrements a [Float] with the value of another.
*/
func -= (inout left: [Float], right: [Float]) {
    left = left - right
}

/**
* Multiplies two [Float] vectors and returns the result as a new [Float].
*/
//func * (left: [Float], right: [Float]) -> [Float] {
//    return [Float]Make(left.x * right.x, left.y * right.y, left.z * right.z)
//}

/**
* Multiplies a [Float] with another.
*/
//func *= (inout left: [Float], right: [Float]) {
//    left = left * right
//}

/**
* Multiplies the x, y and z fields of a [Float] with the same scalar value and
* returns the result as a new [Float].
*/
func * (var left: [Float], scalar: Float) -> [Float] {
    var i = 0
    for f in left {
        left[i] = f*scalar
        ++i
    }
    return left
}

/**
* Multiplies the x and y fields of a [Float] with the same scalar value.
*/
func *= (inout vector: [Float], scalar: Float) {
    vector = vector * scalar
}

/**
* Divides two [Float] vectors abd returns the result as a new [Float]
*/
//func / (left: [Float], right: [Float]) -> [Float] {
//    return [Float]Make(left.x / right.x, left.y / right.y, left.z / right.z)
//}

/**
* Divides a [Float] by another.
*/
//func /= (inout left: [Float], right: [Float]) {
//    left = left / right
//}

/**
* Divides the x, y and z fields of a [Float] by the same scalar value and
* returns the result as a new [Float].
*/
func / (var left: [Float], scalar: Float) -> [Float] {
    var i = 0
    for f in left {
        left[i] = f/scalar
        ++i
    }
    return left
}

/**
* Divides the x, y and z of a [Float] by the same scalar value.
*/
func /= (inout vector: [Float], scalar: Float) {
    vector = vector / scalar
}

/**
* Adds two [Float] vectors and returns the result as a new [Float].
*/
func + (var left: [Float], right: [Float])-> [Float]{
    var i: Int = 0
    //var ret: Float = 0
    for v in left {
        left[i] += right[i]
        ++i
    }
    return left
}

func RMXVectorAdd(var left: [Float], right: [Float])->[Float]{
    var i: Int = 0
    //var ret: Float = 0
    for v in left {
        left[i] += right[i]
        ++i
    }
    return left
}

func RMXVectorDivideScalar(inout left: [Float],scalar: Float) {
    //println("Vector3DivideScalar May not be correct")
    var i = 0
    for f in left {
        left[i] = f/scalar
        ++i
    }

//    let x = vector.x / Float(scalar)
//    let y = vector.y / Float(scalar)
//    let z = vector.z / Float(scalar)
//    return [Float]Make(x, y,z)
}

/**
* Calculates the dot product between two [Float] vectors
*/
func RMXVectorDotProduct(left: [Float], right: [Float]) -> Float {
    var i: Int = 0
    var ret: Float = 0
    for v in left {
        ret += left[i] * right[i]
        ++i
    }
    return ret
}

/**
* Calculates the cross product between two [Float] vectors
*/
func RMXVector3CrossProduct(left: [Float], right:[Float])->[Float]{
    let x = left[1] * right[2] - left[2] * right[1]
    let y = left[2] * right[0] - left[0] * right[2]
    let z = left[0] * right[1] - left[1] * right[0]
    return [ x,y,z]
}



func RMXVectorNegate(inout v: [Float]) {
    var i = 0
    for f in v {
        v[i] = -1*f
        ++i
    }
}

