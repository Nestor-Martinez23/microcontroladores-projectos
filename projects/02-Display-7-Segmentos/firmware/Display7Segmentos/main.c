/*************************************************************************
 *                                                                       *
 *   Sistema de Secuencia de Leds                                        *
 *   Dispositivo: Arduino nano atmega328p                                *
 *   Lenguaje C                                                          *
 *   Rev: 1.0                                                            *
 *                                                                       *
 *   Autor:@Nestor-Martinez23                          Fecha: 03/04/24   *
 ************************************************************************/
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>


// DDRX
#define SEGS_DDRD DDRD
#define LEDS_DDRB DDRB
#define BOTONES_DDRC DDRC
// PORTX
#define SEGS_PORTD PORTD
#define LEDS_PORTB PORTB
#define BOTONES_PORTC PORTC
// PINX
#define BOTONES_PINC PINC
// PORTD
#define SEG_A PORTD1
#define SEG_B PORTD2
#define SEG_C PORTD3
#define SEG_D PORTD4
#define SEG_E PORTD5
#define SEG_F PORTD6
#define SEG_G PORTD7
// PORTB
#define LED_1 PORTB1
#define LED_2 PORTB2
#define LED_3 PORTB3
#define LED_4 PORTB4

// PINB
#define BOTON_1 PINC1
#define BOTON_2 PINC2
#define BOTON_3 PINC3

// Constantes
#define TIME 1000

// Macros
#define  INPUT_1_PRESS (BOTONES_PINC & (1 << BOTON_1))
#define  INPUT_2_PRESS (BOTONES_PINC & (1 << BOTON_2))
#define  INPUT_3_PRESS (BOTONES_PINC & (1 << BOTON_3))

// Condiciones
#define BOTONES_000 (!INPUT_1_PRESS && !INPUT_2_PRESS && !INPUT_3_PRESS)
#define BOTONES_001 (!INPUT_1_PRESS && !INPUT_2_PRESS && INPUT_3_PRESS)
#define BOTONES_010 (!INPUT_1_PRESS && INPUT_2_PRESS && !INPUT_3_PRESS)
#define BOTONES_011 (!INPUT_1_PRESS && INPUT_2_PRESS && INPUT_3_PRESS)
#define BOTONES_100 (INPUT_1_PRESS)

// Funciones Display 7 Segmentos
void Muestra_E(void);
void Muestra_1(void);
void Muestra_2(void);
void Muestra_P(void);
void Muestra_F(void);

// Funciones Estado Leds
void Estado_Centro_Orilla(void);
void Estado_Derecha_Izquierda(void);
void Estado_Izquierda_Derecha(void);
void Estado_Todos_Parpadean(void);
void Estado_Todos_Encendidos(void);

int main(void){
	SEGS_DDRD = 0xFE; // DDRD1-DDRD7 Salidas
	LEDS_DDRB = 0x1E; // DDRB1-DDRB4 Salidas
	BOTONES_DDRC = 0x00;
	LEDS_PORTB = 0x00;
	
	while (1) {
		
		SEGS_PORTD = 0x00;
		BOTONES_PORTC = 0x0E;
		

		if (BOTONES_000) {
			Muestra_E();
			Estado_Centro_Orilla();
			
		}
		else if (BOTONES_001) {
			Muestra_1();
			Estado_Derecha_Izquierda();

		}
		else if (BOTONES_010) {
			Muestra_2();
			Estado_Izquierda_Derecha();

		}
		else if (BOTONES_011) {
			Muestra_P();
			Estado_Todos_Parpadean();
		}
		else if (BOTONES_100){
			Muestra_F();
			Estado_Todos_Encendidos();
		}
	}
}

void Muestra_E(void){
	SEGS_PORTD |= (1 << SEG_A) | (1 << SEG_F) | (1 << SEG_G) | (1 << SEG_E) | (1 << SEG_D);
	_delay_ms(300);
}

void Muestra_1(void){
	SEGS_PORTD |= (1 << SEG_B) | (1 << SEG_C);
	_delay_ms(300);
}

void Muestra_2(void){
	SEGS_PORTD |= (1 << SEG_A) | (1 << SEG_B) | (1 << SEG_G) | (1 << SEG_E) | (1 << SEG_D);
	_delay_ms(300);
}

void Muestra_P(void){
	SEGS_PORTD |= (1 << SEG_A) | (1 << SEG_B) | (1 << SEG_G) | (1 << SEG_F) | (1 << SEG_E);
	_delay_ms(300);
}

void Muestra_F(void){
	SEGS_PORTD |= (1 << SEG_A) | (1 << SEG_G) | (1 << SEG_F) | (1 << SEG_E);
	_delay_ms(300);
}

// Funciones Estado Leds
void Estado_Centro_Orilla(void){
	LEDS_PORTB |= (1 << LED_2) | (1 << LED_3);
	_delay_ms(TIME);
	
	LEDS_PORTB &= ~((1 << LED_2) | (1 << LED_3));
	LEDS_PORTB |= (1 << LED_1) | (1 << LED_4);
	
	_delay_ms(TIME);
	LEDS_PORTB &= ~((1 << LED_1) | (1 << LED_4));
}

void Estado_Derecha_Izquierda(void){
	int8_t i = LED_1;
	while(i <= LED_4) {
		LEDS_PORTB = (1 << i);
		_delay_ms(TIME);
		i++;
	}
}

void Estado_Izquierda_Derecha(void){
	int8_t i = LED_4;
	while(i >= LED_1) {
		LEDS_PORTB = (1 << i);
		_delay_ms(TIME);
		i--;
	}
}

void Estado_Todos_Parpadean(void){
	_delay_ms(TIME);
	LEDS_PORTB = 0x1E;
	_delay_ms(TIME);
	LEDS_PORTB = 0x00;
}

void Estado_Todos_Encendidos(void){
	LEDS_PORTB = 0x1E;
}