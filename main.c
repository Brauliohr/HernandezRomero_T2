// Diseño con Microcontroladores    //
// Tarea 2							//
// Autor: Braulio Hernández Romero  //
// Fecha: 01/06/2021				//

#include <stdio.h>
#include "pin_mux.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_common.h"
#define CORE_FREQ 21000000u
#define DELAY 1000000u


gpio_pin_config_t led_config = {             //Estructura de configuración para indicar si es I/O el LED
		kGPIO_DigitalOutput,
		1,
};

gpio_pin_config_t sw_config = {              //Estructura de configuración para indicar si es I/O el Switch
		kGPIO_DigitalInput,
		0,
};

#define PIN22       22u                      //Macro para el pin del LED Rojo  R
#define PIN26       26u                      //Macro para el pin del led Verde G
#define PIN21       21u                      //Macro para el pin del led Azul  B
#define PIN06        6u						 //Macro para el pin del SW2
#define PIN04        4u						 //Macro para el pin del SW3


int main(void){
	const port_pin_config_t porta_pin4_config = {
		    kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
		    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
		    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
		    kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
		    kPORT_HighDriveStrength,                                 /* High drive strength is configured */
		    kPORT_MuxAsGpio,                                         /* Pin is configured as PTA04 */
		    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
		  };

	const port_pin_config_t portc_pin6_config = {
			kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
			kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
			kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
			kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
			kPORT_HighDriveStrength,                                 /* High drive strength is configured */
			kPORT_MuxAsGpio,                                         /* Pin is configured as PTC06 */
			kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
		  };

	CLOCK_EnableClock(kCLOCK_PortB);                     //Enciende el reloj para el puerto B
	CLOCK_EnableClock(kCLOCK_PortC);					 //Enciende el reloj para el puerto C
	CLOCK_EnableClock(kCLOCK_PortE);                     //Enciende el reloj para el puerto E
	CLOCK_EnableClock(kCLOCK_PortA);                     //Enciende el reloj para el puerto A

	PORT_SetPinConfig(PORTC, PIN06, &portc_pin6_config);   //Establece la configuración para el SW2
	PORT_SetPinConfig(PORTA, PIN04, &porta_pin4_config);   //Establece la configuración para el SW3

	PORT_SetPinMux(PORTB, PIN22, kPORT_MuxAsGpio);       //Establece el Pin22 del PuertoB como GPIO
	PORT_SetPinMux(PORTE, PIN26, kPORT_MuxAsGpio);		 //Establece el Pin26 del PuertoE como GPIO
	PORT_SetPinMux(PORTB, PIN21, kPORT_MuxAsGpio);       //Establece el Pin22 del PuertoB como GPIO

	GPIO_PinInit(GPIOB, PIN22, &led_config);             //Establece el Pin22 del PuertoB como I/O
	GPIO_PinInit(GPIOC, PIN06, &sw_config); 			 //Establece el Pin06 del PuertoC como I/O
	GPIO_PinInit(GPIOE, PIN26, &led_config);             //Establece el Pin26 del PuertoE como I/O
	GPIO_PinInit(GPIOB, PIN21, &led_config);             //Establece el Pin22 del PuertoB como I/O
	GPIO_PinInit(GPIOA, PIN04, &sw_config); 			 //Establece el Pin04 del PuertoA como I/O

	while(1){

		/*Secuencia para el SW2*/
		if(!GPIO_PinRead(GPIOC, PIN06))                   //Lee el valor del sw2
		{
			/*Amarillo = Rojo + Verde*/
			GPIO_PortClear(GPIOB, 1u << PIN22);           //Enciende el Led rojo
			GPIO_PortClear(GPIOE, 1u << PIN26);           //Enciende el Led verde

			SDK_DelayAtLeastUs(DELAY, CORE_FREQ);         //Espera

			/*Rojo*/
			GPIO_PortSet(GPIOE, 1u << PIN26);	          //Apaga el led verde

			SDK_DelayAtLeastUs(DELAY, CORE_FREQ);         //Espera

			/*Morado*/
			GPIO_PortClear(GPIOB, 1u << PIN21);           //Enciende el Led Azul

			SDK_DelayAtLeastUs(DELAY, CORE_FREQ);         //Espera

			/*Azul*/
			GPIO_PortSet(GPIOB, 1u << PIN22);	          //Apaga el led rojo

			SDK_DelayAtLeastUs(DELAY, CORE_FREQ);         //Espera

			/*Verde*/
			GPIO_PortSet(GPIOB, 1u << PIN21);	          //Apaga el led azul
			GPIO_PortClear(GPIOE, 1u << PIN26);           //Enciende el Led verde

			SDK_DelayAtLeastUs(DELAY, CORE_FREQ);         //Espera

			GPIO_PortSet(GPIOE, 1u << PIN26);	          //Apaga el led verde

		}

		/*Secuencia para el SW3*/
		if(!GPIO_PinRead(GPIOA, PIN04))
		{
		/*Verde*/
		GPIO_PortClear(GPIOE, 1u << PIN26);      //Enciende el Led Verde

		SDK_DelayAtLeastUs(DELAY, CORE_FREQ);    //Espera

		GPIO_PortSet(GPIOE, 1u << PIN26);        //Apaga el led verde

		/*Azul*/
		GPIO_PortClear(GPIOB, 1u << PIN21);      //Enciende el Led Azul

		SDK_DelayAtLeastUs(DELAY, CORE_FREQ);    //Espera

		GPIO_PortSet(GPIOB, 1u << PIN21);        //Apaga el led Azul

		/*Morado*/
		GPIO_PortClear(GPIOB, 1u << PIN21);      //Enciende el led azul
		GPIO_PortClear(GPIOB, 1u << PIN22);      //Enciende el led rojo

		SDK_DelayAtLeastUs(DELAY, CORE_FREQ);    //Espera

		/*Rojo*/
		GPIO_PortSet(GPIOB, 1u << PIN21);        //Apaga el Led Azul

		SDK_DelayAtLeastUs(DELAY, CORE_FREQ);    //Espera

		/*Amarillo*/
		GPIO_PortClear(GPIOE, 1u << PIN26);      //Enciende el Led verde

		SDK_DelayAtLeastUs(DELAY, CORE_FREQ);    //Espera

		GPIO_PortSet(GPIOE, 1u << PIN26);        //Apaga el led verde
		GPIO_PortSet(GPIOB, 1u << PIN22);        //Apaga el led rojo

		}

		/*Color blanco al Presionar SW2 y SW3*/
		if(!GPIO_PinRead(GPIOA, PIN04) && GPIO_PinRead(GPIOC, PIN06))
		{
			GPIO_PortClear(GPIOB, 1u << PIN22);
			GPIO_PortClear(GPIOE, 1u << PIN26);
			GPIO_PortClear(GPIOB, 1u << PIN22);

			SDK_DelayAtLeastUs(DELAY, CORE_FREQ);

			GPIO_PortSet(GPIOB, 1u << PIN22);
			GPIO_PortSet(GPIOE, 1u << PIN26);
			GPIO_PortSet(GPIOB, 1u << PIN22);
		}
	}
	return 0;

}
