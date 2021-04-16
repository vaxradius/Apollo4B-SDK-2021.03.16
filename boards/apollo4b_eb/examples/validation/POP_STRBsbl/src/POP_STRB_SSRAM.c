//*****************************************************************************
//
//! @file hello_world.c
//!
//! @brief A simple "Hello World" example.
//!
//! This example prints a "Hello World" message with some device info
//! over SWO at 1M baud. To see the output of this program, run AMFlash,
//! and configure the console for SWO. The example sleeps after it is done
//! printing.
//
//*****************************************************************************

//*****************************************************************************
//
// Copyright (c) 2021, Ambiq Micro, Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from this
// software without specific prior written permission.
//
// Third party software included in this distribution is subject to the
// additional license terms as defined in the /docs/licenses directory.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// This is part of revision b0-release-20210111-375-gc3201eeb4 of the AmbiqSuite Development Package.
//
//*****************************************************************************

#include "am_mcu_apollo.h"
#include "am_bsp.h"
#include "am_util.h"

//*****************************************************************************
//
// Insert compiler version at compile time.
//
//*****************************************************************************
#define STRINGIZE_VAL(n)                    STRINGIZE_VAL2(n)
#define STRINGIZE_VAL2(n)                   #n

#ifdef __GNUC__
#define COMPILER_VERSION                    ("GCC " __VERSION__)
#elif defined(__ARMCC_VERSION)
#define COMPILER_VERSION                    ("ARMCC " STRINGIZE_VAL(__ARMCC_VERSION))
#elif defined(__KEIL__)
#define COMPILER_VERSION                    "KEIL_CARM " STRINGIZE_VAL(__CA__)
#elif defined(__IAR_SYSTEMS_ICC__)
#define COMPILER_VERSION                    __VERSION__
#else
#define COMPILER_VERSION                    "Compiler unknown"
#endif


#define ENABLE_DEBUGGER

#if (defined (__ARMCC_VERSION))

__asm uint32_t
testPOP1(void)
{ 	
	  mov32   r0, 0x100a7494
	  mov     sp, r0// Set Stack pointor 
	  mov32   r5, 0x1009e304
	  mov32   r4, 0x1009e304
		mov32   r3, 0x1009e304
    push    {r3, r4, r5, lr}

	  pop     {r3, r4, r5, pc}
}

__asm uint32_t
testPOPA(uint32_t R0)
{ 	
	  mov     r1, sp
	  //mov32   r0, 0x100a7494
	  mov     sp, r0// Set Stack pointor 
	  mov   r6, r1
	  mov32   r5, 0xAAAAAAAA
	  //mov32   r4, 0xAAAAAAAA
	  //mov32   r3, 0xAAAAAAAA	
    push    {r3, r4, r5, r6}
	  pop     {r3, r4, r5, r6}
		mov     sp, r1
		bx      lr
}

__asm uint32_t
testPOP5(uint32_t R0)
{ 	
	  mov     r1, sp
	  //mov32   r0, 0x100a7494
	  mov     sp, r0// Set Stack pointor 
	  mov   r6, r1
	  mov32   r5, 0x55555555
	  //mov32   r4, 0xAAAAAAAA
	  //mov32   r3, 0xAAAAAAAA	
    push    {r3, r4, r5, r6}
	  pop     {r3, r4, r5, r6}
		mov     sp, r1
		bx      lr
}
#elif defined(__GNUC_STDC_INLINE__)
uint32_t __attribute__((naked))
testPOP(uint32_t R0)
{ 	
	  __asm("mov     sp, 0x100a748C");// Set Stack pointor 
	  __asm("mov     r5, 0xAAAAAAAA");
    __asm("push    {r3, r4, r5, lr}");
	  __asm("pop     {r3, r4, r5, pc}");
}
#endif

//*****************************************************************************
//
// Main
//
//*****************************************************************************
int
main(void)
{
	 uint32_t temp =0;
#if defined (AM_PART_APOLLO4B)
    uint32_t ui32dcuVal;
#endif // AM_PART_APOLLO4B

	//
    // Set the default cache configuration
    //
    //am_hal_cachectrl_config(&am_hal_cachectrl_defaults);
    //am_hal_cachectrl_enable();

    //
    // Configure the board for low power operation.
    //
    // am_bsp_low_power_init();  // turns off CRYPTO block which we need active for example to work.

#if defined (AM_PART_APOLLO4B)
    if ((PWRCTRL->DEVPWRSTATUS_b.PWRSTCRYPTO == 1) && (CRYPTO->HOSTCCISIDLE_b.HOSTCCISIDLE == 1))
    {
        am_hal_dcu_get(&ui32dcuVal);
        // Enable SWO
        if ( !(ui32dcuVal & AM_HAL_DCU_CPUTRC_TPIU_SWO) &&
             (am_hal_dcu_update(true, AM_HAL_DCU_CPUTRC_TPIU_SWO) != AM_HAL_STATUS_SUCCESS) )
        {
            // Cannot enable SWO
            while(1);
        }
    }
#endif // AM_PART_APOLLO4B
    //
    // Initialize the printf interface for ITM output
    //
    am_bsp_debug_printf_enable();

    //
    // Print the banner.
    //
    am_util_stdio_terminal_clear();
    

		am_util_stdio_printf("\nTest POP SSRAM!\n\n");
		
		am_util_stdio_printf("\n\nTest pattern 0xAAAAAAAA\n\n");
		//0x10060000 0x00100000
		for(uint32_t i = 0x10060000; i < (0x10060000+0x00100000); i+=4)
		{
			*(uint32_t*)(i-4) = 0x00000000;
			*(uint32_t*)(i-8) = 0x00000000;
			*(uint32_t*)(i-12) = 0x00000000;
			*(uint32_t*)(i-16) = 0x00000000;

			testPOPA(i);

			temp = *(uint32_t*)(i-8);

			if(temp !=0xAAAAAAAA)
				am_util_stdio_printf("0x%08X:0x%08X\n",(i-8),temp);

		}
		am_util_stdio_printf("\n\nTest pattern 0x55555555\n\n");
		for(uint32_t i = 0x10060000; i < (0x10060000+0x00100000); i+=4)
		{
			*(uint32_t*)(i-4) = 0x00000000;
			*(uint32_t*)(i-8) = 0x00000000;
			*(uint32_t*)(i-12) = 0x00000000;
			*(uint32_t*)(i-16) = 0x00000000;

			testPOP5(i);

			temp = *(uint32_t*)(i-8);

			if(temp !=0x55555555)
				am_util_stdio_printf("0x%08X:0x%08X\n",(i-8),temp);

		}
		
		am_util_stdio_printf("\nDone\n");

		
    am_util_stdio_printf("Test STRB+SSRAM(0x10060000 to 0x00100000)\n\n");
	

		am_util_stdio_printf("\n\nTest pattern 0x55\n\n");
		for(uint32_t i=0x10060000; i < 0x10060000+0x00100000 ;i++)
		{
			*(uint8_t *)(i) = 0x55;
		}
		
		for(uint32_t i=0x10060000; i < 0x10060000+0x00100000 ;i++)
		{
			*(uint8_t *)(i) = 0x55;
			if(*(uint8_t*)(i) != 0x55)
				am_util_stdio_printf("0x%x:0x%x ", (i),*(uint8_t*)(i));
		}

		for(uint32_t i=0x10060000; i < 0x10060000+0x00100000 ;i++)
		{
			if(*(uint8_t*)(i) != 0x55)
				am_util_stdio_printf("0x%x:0x%x ", (i),*(uint8_t*)(i));
		}
		
		am_util_stdio_printf("\n\nTest pattern 0xAA\n\n");
		for(uint32_t i=0x10060000; i < 0x10060000+0x00100000 ;i++)
		{
			*(uint8_t *)(i) = 0xAA;
		}
		
		for(uint32_t i=0x10060000; i < 0x10060000+0x00100000 ;i++)
		{
			*(uint8_t *)(i) = 0xAA;
			if(*(uint8_t*)(i) != 0xAA)
				am_util_stdio_printf("0x%x:0x%x ", (i),*(uint8_t*)(i));
		}

		for(uint32_t i=0x10060000; i < 0x10060000+0x00100000 ;i++)
		{
			if(*(uint8_t*)(i) != 0xAA)
				am_util_stdio_printf("0x%x:0x%x ", (i),*(uint8_t*)(i));
		}
		
		

		
		am_util_stdio_printf("\nDone\n");
		
		
		
		


    
		//
    // Loop forever while sleeping.
    //
    while (1)
    {
        //
        // Go to Deep Sleep.
        //
        am_hal_sysctrl_sleep(AM_HAL_SYSCTRL_SLEEP_NORMAL);
    }



}
