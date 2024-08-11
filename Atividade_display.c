#include<18F4550.h>           
#fuses HS, NOWDT, CPUDIV1
#use delay (clock=20MHz)

int cicloDezena = 0;
int cicloUnidade = 0;

/*Matriz de 10 posi��es contendo o valor a ser enviado para a porta D a fim de
   mostrar o d�gito referente nos displays */
int digito[10] =
               {0b00111111,    //D�gito 0
                0b00000110,    //D�gito 1
                0b01011011,    //D�gito 2
                0b01001111,    //D�gito 3
                0b01100110,    //D�gito 4
                0b01101101,    //D�gito 5
                0b01111101,    //D�gito 6
                0b00000111,    //D�gito 7
                0b01111111,    //D�gito 8
                0b01101111     //D�gito 9
               };
               
void main()
{
port_b_pullups(true);   // Liga os pull ups
output_d(0);            // Desliga todas as portas D
SET_TRIS_B(0xFF);
SET_TRIS_D(0x00);


while(true){

delay_ms(1); //Caso retire o delay_ms(1), o c�digo inicia sem apertar B0.

// Verifica se o bot�o est� apertado e caso n�o, n�o permite a continua��o do c�digo.
   if(input(pin_b0) == 0){
// Parte do c�digo onde verifica se a contagem chegou a 47.
      for(int contGeral = 1; contGeral <= 47; contGeral++){
      
// Ciclo de repeti��o para fazer durar 1s = 250*4ms
         for(int contador = 1; contador <= 250; contador++){

// Esse if reseta a contagem se for apertado o bot�o B0.
            if(input(pin_b0) == 0){  
               contGeral = 0;
               cicloUnidade = 0;
               cicloDezena = 0;
            }
   
// Ciclo de repeti��o do dos 2 display LED's. dura��o 4ms (2ms + 2ms).
            for (int cont = 1; cont <= 2; cont++){
               switch(cont)
               {                      
                     case 1: OUTPUT_D(digito[cicloDezena]);
                             OUTPUT_A(0b00010000);
                             delay_ms(2);
                     break; 
                     
                     case 2: OUTPUT_D(digito[cicloUnidade]);
                             OUTPUT_A(0b00100000);
                             delay_ms(2);
                     break;
               }
            }
         }  
      cicloUnidade++;
      
// Reseta o ciclo unidade quando chega a 10 e adiciona mais 1 ao ciclo dezena.
         if (cicloUnidade == 10){
            cicloUnidade = 0;
            cicloDezena++; 
         }
      }
// Ao termino da contagem, a sa�da do grupo D � desligada.
      output_d(0);   // Desliga todas as portas D
   }
// Caso o B0 n�o esteja apertado, a saida do grupo D ser� desligada.
   else{
      output_d(0);   // Desliga todas as portas D
   }
   }
}
