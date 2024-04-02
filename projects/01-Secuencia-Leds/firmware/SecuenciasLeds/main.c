/*************************************************************************
 *                                                                       *
 *   Sistema de Secuencia de Leds                                        *
 *   Dispositivo: Arduino nano atmega328p                                *
 *   Lenguaje C                                                          *
 *   Rev: 1.0                                                            *
 *                                                                       *
 *   Autor:@Nestor-Martinez23                          Fecha: 02/03/24   *
 ************************************************************************/

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

//DDRX
#define LEDS_DDRD DDRD
#define BOTONES_DDRB DDRB
//PORTX
#define LEDS_PORTD PORTD
//PINX
#define BOTONES_PINB PINB
//PORTD
#define LED_1 PORTD1
#define LED_2 PORTD2
#define LED_3 PORTD3
#define LED_4 PORTD4
#define LED_5 PORTD5
#define LED_6 PORTD6
#define LED_7 PORTD7
//PINB
#define BOTON_1 PINB1
#define BOTON_2 PINB2

//Constantes
#define TIME 500


//Condiciones
#define BOTONES_00 !(BOTONES_PINB & (1 << BOTON_1)) && !(BOTONES_PINB & (1 << BOTON_2))
#define BOTONES_01 !(BOTONES_PINB & (1 << BOTON_1)) && (BOTONES_PINB & (1 << BOTON_2))
#define BOTONES_10 (BOTONES_PINB & (1 << BOTON_1)) && !(BOTONES_PINB & (1 << BOTON_2))
#define BOTONES_11 (BOTONES_PINB & (1 << BOTON_1)) && (BOTONES_PINB & (1 << BOTON_2))

// Funciones
void fantastico_init(void);
void apagados_init(void);
void libre_init(void);
void encendidos_init(void);

int main(void)

{
	LEDS_DDRD =0xFE;//Del DDRD1 al DDR7 son salidas
	BOTONES_DDRB = 0x00;
	while (1) {
		PORTD = 0X00;

		if (BOTONES_00) {
			fantastico_init();
			
			
		}
		else if (BOTONES_01) {
			apagados_init();

		}
		else if (BOTONES_10) {
			libre_init();

		}
		
		else if (BOTONES_11) {
			encendidos_init();

		}
		
	}
	
	
}

void fantastico_init(void){
	uint8_t B_Guard = BOTONES_00;
	while (BOTONES_00) {
		for (uint8_t i = 1; i <= 7; i++) {
			if(B_Guard != BOTONES_00){break;}
			LEDS_PORTD = 0x00;
			LEDS_PORTD = (1 << i);
			_delay_ms(TIME);
			if(B_Guard != BOTONES_00){break;}
		}
		for (uint8_t i = 7; i >= 1; i--) {
			if(B_Guard != BOTONES_00){break;}
			LEDS_PORTD = 0x00;
			LEDS_PORTD = (1 << i);
			_delay_ms(TIME);
			if(B_Guard != BOTONES_00){break;}
		}
	}
	
}

void apagados_init(void){
	while (BOTONES_01) {
		LEDS_PORTD =0x00;
	}
}

void libre_init(void){
	uint8_t B_Guard = BOTONES_00;	
	while (BOTONES_10){
		LEDS_PORTD |= (1 << LED_1);
		LEDS_PORTD |= (1 << LED_7);
				
		_delay_ms(TIME);
		if(B_Guard != BOTONES_00){break;}
		LEDS_PORTD |= (1 << LED_2);
		LEDS_PORTD |= (1 << LED_6);
		
		
		_delay_ms(TIME);
		if(B_Guard != BOTONES_00){break;}
		LEDS_PORTD |= (1 << LED_5);
		LEDS_PORTD |= (1 << LED_3);
				
		_delay_ms(TIME);
		if(B_Guard != BOTONES_00){break;}
		LEDS_PORTD |= (1 << LED_4);
		_delay_ms(TIME);
		if(B_Guard != BOTONES_00){break;}
		LEDS_PORTD &= ~(1 << LED_4);
		
		
		_delay_ms(TIME);
		if(B_Guard != BOTONES_00){break;}
		LEDS_PORTD &= ~(1 << LED_5);
		LEDS_PORTD &= ~(1 << LED_3);

		_delay_ms(TIME);
		if(B_Guard != BOTONES_00){break;}
		LEDS_PORTD &= ~(1 << LED_2);
		LEDS_PORTD &= ~(1 << LED_6);
		
		_delay_ms(TIME);
		if(B_Guard != BOTONES_00){break;}
		LEDS_PORTD &= ~(1 << LED_1);
		LEDS_PORTD &= ~(1 << LED_7);
		_delay_ms(TIME);
		if(B_Guard != BOTONES_00){break;}
		
	}
}

void encendidos_init(void){
	while(BOTONES_11){
		LEDS_PORTD =0xFE;
	}
}