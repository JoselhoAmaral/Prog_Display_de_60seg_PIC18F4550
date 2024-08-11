#include<18F4550.h>           
#fuses HS, NOWDT, CPUDIV1
#use delay (clock=20MHz)

int cicloDezena = 0;
int cicloUnidade = 0;

/*Matriz de 10 posições contendo o valor a ser enviado para a porta D a fim de
   mostrar o dígito referente nos displays */
int digito[10] =
               {0b00111111,    //Dígito 0
                0b00000110,    //Dígito 1
                0b01011011,    //Dígito 2
                0b01001111,    //Dígito 3
                0b01100110,    //Dígito 4
                0b01101101,    //Dígito 5
                0b01111101,    //Dígito 6
                0b00000111,    //Dígito 7
                0b01111111,    //Dígito 8
                0b01101111     //Dígito 9
               };
               
void main()
{
port_b_pullups(true);   // Liga os pull ups
output_d(0);            // Desliga todas as portas D
SET_TRIS_B(0xFF);
SET_TRIS_D(0x00);


while(true){

delay_ms(1); //Caso retire o delay_ms(1), o código inicia sem apertar B0.

// Verifica se o botão está apertado e caso não, não permite a continuação do código.
   if(input(pin_b0) == 0){
// Parte do código onde verifica se a contagem chegou a 47.
      for(int contGeral = 1; contGeral <= 47; contGeral++){
      
// Ciclo de repetição para fazer durar 1s = 250*4ms
         for(int contador = 1; contador <= 250; contador++){

// Esse if reseta a contagem se for apertado o botão B0.
            if(input(pin_b0) == 0){  
               contGeral = 0;
               cicloUnidade = 0;
               cicloDezena = 0;
            }
   
// Ciclo de repetição do dos 2 display LED's. duração 4ms (2ms + 2ms).
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
// Ao termino da contagem, a saída do grupo D é desligada.
      output_d(0);   // Desliga todas as portas D
   }
// Caso o B0 não esteja apertado, a saida do grupo D será desligada.
   else{
      output_d(0);   // Desliga todas as portas D
   }
   }
}
