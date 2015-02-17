//
//  kernal.c
//  kernal
//
//  Created by Max Bilbow on 17/02/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

#include <mach/mach_types.h>

kern_return_t kernal_start(kmod_info_t * ki, void *d);
kern_return_t kernal_stop(kmod_info_t *ki, void *d);

kern_return_t kernal_start(kmod_info_t * ki, void *d)
{
    return KERN_SUCCESS;
}

kern_return_t kernal_stop(kmod_info_t *ki, void *d)
{
    return KERN_SUCCESS;
}
