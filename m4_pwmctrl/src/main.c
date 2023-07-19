/*==========================================================
Code by G V V Sharma
March 17, 2021,
Released under GNU/GPL
https://www.gnu.org/licenses/gpl-3.0.en.html
/*==========================================================
 *
 *    File   : main.c
 *    Purpose: main for Pygmy blink onboard led
 *                                                          
 *=========================================================*/

#include "Fw_global_config.h"   // This defines application specific charactersitics

#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "timers.h"
#include "RtosTask.h"

/*    Include the generic headers required for QORC */
#include "eoss3_hal_gpio.h"
#include "eoss3_hal_rtc.h"
#include "eoss3_hal_timer.h"
#include "eoss3_hal_fpga_usbserial.h"
#include "ql_time.h"
#include "s3x_clock_hal.h"
#include "s3x_clock.h"
#include "s3x_pi.h"
#include "dbg_uart.h"

#include "hal_fpga_onion.h"
#include "hal_fpga_onion_pwmctrl.h"

#include "cli.h"


extern const struct cli_cmd_entry my_main_menu[];


const char *SOFTWARE_VERSION_STR;

#define a 16
#define b 17
#define c 18
#define d 19
#define e 20
#define f 21
#define g 22

/*
 * Global variable definition
 */


extern void qf_hardwareSetup();
static void nvic_init(void);
void PyHal_GPIO_SetDir(uint8_t gpionum,uint8_t iomode);
int PyHal_GPIO_Set(uint8_t gpionum, uint8_t gpioval);

typedef struct{
	uint8_t		shape_button_status[4];	// Cross, Square, Triangle, Circle
	int16_t		pwm_value[4];		// [0]: X pwm, [1]: Y pwm, [2] & [3]: dummy
}dabble_joystick_t;

int main(void)
{
    uint32_t i=0,j=0,k=0;
    volatile dabble_joystick_t joystick_data;  
    uint8_t* init_ptr = (uint8_t*)&joystick_data;
    int16_t* pwm_value = (int16_t*)&joystick_data.pwm_value;
	
    // Data initialization
    for(i=0; i<sizeof(joystick_data); i++) init_ptr[i] = 0;

    SOFTWARE_VERSION_STR = "qorc-onion-apps/qf_hello-fpga-gpio-ctlr";
    
    qf_hardwareSetup();
    nvic_init();

    S3x_Clk_Enable(S3X_M4_S12_S15_CLK);

    dbg_str("\n\n");
    dbg_str( "##########################\n");
    dbg_str( "Quicklogic QuickFeather FPGA GPIO CONTROLLER EXAMPLE\n");
    dbg_str( "SW Version: ");
    dbg_str( SOFTWARE_VERSION_STR );
    dbg_str( "\n" );
    dbg_str( __DATE__ " " __TIME__ "\n" );
    dbg_str( "##########################\n\n");

    dbg_str( "\n\nHello GPIO!!\n\n");	// <<<<<<<<<<<<<<<<<<<<<  Change me!

    CLI_start_task( my_main_menu );
	HAL_Delay_Init();
	
    PyHal_GPIO_SetDir(a,1);	
    PyHal_GPIO_SetDir(b,1);	
    PyHal_GPIO_SetDir(c,1);	
    PyHal_GPIO_SetDir(d,1);	
    PyHal_GPIO_SetDir(e,1);	
    PyHal_GPIO_SetDir(f,1);	
    PyHal_GPIO_SetDir(g,1);	
    // Write to mailbox, memory address of joystick data
    MISC_CTRL->SW_MB_1 = (uint32_t)&joystick_data;

    while(1)
    {
        if(joystick_data.shape_button_status[0]){
		if(joystick_data.pwm_value[0] < 0){
			PyHal_GPIO_Set(a, 1);	
			PyHal_GPIO_Set(b, 0);	
			PyHal_GPIO_Set(c, 0);	
			PyHal_GPIO_Set(d, 1);	
			PyHal_GPIO_Set(e, 1);	
			PyHal_GPIO_Set(f, 1);	
			PyHal_GPIO_Set(g, 1);	
		}
		else{
			PyHal_GPIO_Set(a, 0);	
			PyHal_GPIO_Set(b, 0);	
			PyHal_GPIO_Set(c, 1);	
			PyHal_GPIO_Set(d, 0);	
			PyHal_GPIO_Set(e, 0);	
			PyHal_GPIO_Set(f, 1);	
			PyHal_GPIO_Set(g, 0);	

		}
	}
	else if(joystick_data.shape_button_status[1]){
		if(joystick_data.pwm_value[1] < 0){
			PyHal_GPIO_Set(a, 0);	
			PyHal_GPIO_Set(b, 0);	
			PyHal_GPIO_Set(c, 0);	
			PyHal_GPIO_Set(d, 0);	
			PyHal_GPIO_Set(e, 1);	
			PyHal_GPIO_Set(f, 1);	
			PyHal_GPIO_Set(g, 0);	
		}
		else{

			PyHal_GPIO_Set(a, 1);	
			PyHal_GPIO_Set(b, 0);	
			PyHal_GPIO_Set(c, 0);	
			PyHal_GPIO_Set(d, 1);	
			PyHal_GPIO_Set(e, 1);	
			PyHal_GPIO_Set(f, 0);	
			PyHal_GPIO_Set(g, 0);	
		}
	}
	else{

			PyHal_GPIO_Set(a, 1);	
			PyHal_GPIO_Set(b, 1);	
			PyHal_GPIO_Set(c, 1);	
			PyHal_GPIO_Set(d, 1);	
			PyHal_GPIO_Set(e, 1);	
			PyHal_GPIO_Set(f, 1);	
			PyHal_GPIO_Set(g, 1);	
	
    }
	}
    /* Start the tasks and timer running. */
    vTaskStartScheduler();
    dbg_str("\n");

    while(1);
}

static void nvic_init(void)
 {
    // To initialize system, this interrupt should be triggered at main.
    // So, we will set its priority just before calling vTaskStartScheduler(), not the time of enabling each irq.
    NVIC_SetPriority(Ffe0_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
    NVIC_SetPriority(SpiMs_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
    NVIC_SetPriority(CfgDma_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
    NVIC_SetPriority(Uart_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
    NVIC_SetPriority(FbMsg_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
 }    

//needed for startup_EOSS3b.s asm file
void SystemInit(void)
{

}
