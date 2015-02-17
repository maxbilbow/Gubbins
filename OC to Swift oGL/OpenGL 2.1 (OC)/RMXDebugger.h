//
//  WorldConstants.h
//  openglplus
//
//  Created by Max Bilbow on 02/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//


#define _INFINITY 99999
#define PI (3.14159265f)

#define U_DEPTH       2
#define U_HORIZONTAL  0
#define U_VERTICAL    1
#define TWIST_AXIS    1
#define NOD_AXIS      0
#define ROLL_AXIS     2
#define U_SPEED       0.05
#define PI_OVER_180 (PI / 180)

#define RMX_DEPRECATED(from, to) __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_##from, __MAC_##to, __IPHONE_NA, __IPHONE_NA)


//struct WorldConstants {
//    static const bool WATCHING = false;
//    //static const float PI_OVER_180 = PI/180;
//    static bool isWatching(bool local){
//        return (WATCHING || local);
//    }
//    
//    
//};
//
//namespace WC {
//    inline namespace WorldConstants{}
//};
//
//
//
//using namespace std;

@interface RMXDebugger : NSString
-(void)add:(int)index n:(id)name t:(NSString*)text;//, ...;
@end

@implementation RMXDebugger

    const int no_checks = 11;
    int tog = 1;
NSString *lastCheck;

    //bool * print = new bool[10];

NSString *checks[no_checks];
//=[
//                       @"FirstList",
//                       @"SecondList",
//                       @"ThirdList",@"",@"",@"",@"",@"",@"",@"",nil];// = [names objectAtIndex:0];

    int monitor=10;
    bool debugging = true;
    //GLKVector2 win = new GLKVector2(0,0);
- (instancetype)init
{
    self = [super init];
    if (self) {
//        checks = @[
//                   @"FirstList",
//                   @"SecondList",
//                   @"ThirdList",@"",@"",@"",@"",@"",@"",@""];
        lastCheck = @"";
        for (int i=0;i<no_checks;++i)
            checks[i]=@"";
    priorName = @"";
    }

    return self;
}

   // template <typename Print>


- (void)feedback//:(GLKVector2)win
{
        //feedback(checks);

        if ((![checks[monitor] isEqualToString:lastCheck])&&(debugging))
                NSLog(@"\nDEBUG #%i %@\n", monitor, checks[monitor]);
        
                
        lastCheck = checks[monitor];
    checks[monitor] = @"";
   // [checks setObject:(@"") atIndexedSubscript:(monitor)];// = "";//[NSString stringWithFormat: ""];
    }
    
-(void)cycle:(int)dir
{
    monitor += dir;
    if(monitor>no_checks-1)
        monitor = 0;
    if(monitor<0)
        monitor = no_checks-1;
}
NSString* priorName;
-(void)add:(int)index n:(id)object t:(NSString*)text//, ...
{
    
//    NSString* eachObject;
//    va_list argumentList;
//    if (text) // The first argument isn't part of the varargs list,
//    {                                   // so we'll handle it separately.
//        [eachObject stringByAppendingString: text];
//        va_start(argumentList, text); // Start scanning for arguments after firstObject.
//        while ((eachObject != nil)) // As many times as we can get an argument of type "id"
//           [eachObject stringByAppendingString: eachObject]; // that isn't nil, add it to self's contents.
//        va_end(argumentList);
//    }
    //NSLog(@"%@",text);
    NSString * s = ![[object description] isEqualToString: priorName] ? [NSString stringWithFormat:@"\n%@:\n ",[object description]] : @"";
    //NSString * s = [NSString stringWithFormat:@"\n%@: ",[object description]];
    priorName = [object description];
   // if [checks[index] isEqualToString:""]
    
    checks[index] = [NSString stringWithFormat:@"%@ %@        %@\n",checks[index],s, text];
//    [checks[index] stringByAppendingString:text];//(eachObject)];
    
}

@end




static RMXDebugger *rmxDebugger;

