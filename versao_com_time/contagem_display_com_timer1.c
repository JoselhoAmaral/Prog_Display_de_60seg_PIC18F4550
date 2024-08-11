#include<18F4550.h>           
#fuses HS, NOWDT, CPUDIV1
#use delay (clock=20MHz)
#int_timer1

void funcao_contador(){
   
   static unsigned int miliSegundo;
   static unsigned int unidade;
   static int dezena;
   static boolean flag = 0;
   set_timer1(34286 + get_timer1());
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
   if (((input(PIN_B0)) == 0)&&(flag == 1)){
   flag = 0;
   }
   if (((input(PIN_B0)) == 0)&&(flag == 0)){
      flag = 1;
      milisegundo = 0;
      unidade = 0;
      dezena = 0;
   }
   
   if ((flag != 0)&&(((dezena*10)+unidade) < 48)){
   
      boolean opcao = miliSegundo%2;
      switch (opcao){
         case 0:
            OUTPUT_D(digito[unidade]);
            OUTPUT_A(0b00100000);
         break;
         
         case 1:
            OUTPUT_D(digito[dezena]);
            OUTPUT_A(0b00010000);
         break;
      }
      
      miliSegundo++;
      if(miliSegundo == 20){
   // Se a interrupção for 0,05s, será if (miliSegundo == 20)
   // Se a interrupção for 0,02s, será if (miliSegundo == 50)
         unidade++;
         miliSegundo = 0;
      }   
      if (unidade == 10){
            dezena++;
            unidade = 0;
      }   
      if (dezena == 10){
            dezena = 0;
      }
   }
   else{
      OUTPUT_D(0b00000000);
   }
}

void main(){
   port_b_pullups(true);   // Liga os pull ups
   output_d(0);            // Desliga todas as portas D
   SET_TRIS_B(0xFF);
   SET_TRIS_D(0x00);
   
   setup_timer_1 (T1_INTERNAL|T1_DIV_BY_8);
   set_timer1(34286); // Quando 34286, a interrupção ocorrerá a cada 0,05s
                      // Quando 53036, a interrupção ocorrerá a cada 0,02s 
   enable_interrupts(GLOBAL);
   enable_interrupts(INT_TIMER1);
   
   while (true)
   { }
}
