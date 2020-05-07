; 
 mov 8,STR 
LOOP:  jmp W  
prn -5 
  sub r1 
prn r7

 inc K       
                   
   bne L3 ,r3
END:  stop
 STR:  .string "abcdef" 
LENGTH: .data 6,-9,15 
K:  .data 22  
 
