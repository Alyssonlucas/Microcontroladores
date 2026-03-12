		;ES422	- MICROCOMPUTADORES -  2026.1
		;Carregando	um imediato grande (maior que 8 bits)
		;AUTOR:	Jose R. de Oliveira Neto,
		;OBJETIVO:	carregar o numero #0x031045 em um registrador
		MOV		R1, #0x03     ; carrega a parte mais signficativa do numero
		LSL		R1, R1, #8    ; desloca o numero de bits necessarios para adicionar a proxima parte do numero
		ADD		R1, R1, #0x10 ; adiciona a proxima parte do numero
		LSL		R1, R1, #8    ; faz o procedimento o numero de vezes necessarios;
		ADD		R1, R1, #0x45    ;
