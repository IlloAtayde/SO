#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <linux/types.h>
#include <stdlib.h>

int main(int argc, char const *argv[]){
long int retorno;
int pid,index,op,contador;

	if(argc == 4){
		pid = atoi(argv[1]);
		index = atoi(argv[2]);
		op = atoi(argv[3]);
		syscall(354,pid,index,op,&contador);
		if(contador < 0){
			printf("PID nao encontrado!\n");
			return -1;
		}
		if(contador == 0 && op == 0){
			printf("Contador da funcao %d zerado(0)\n",index);
			return 0;
		}
	printf("Quantidade de funcao %d = %d\n",index,contador);
	return 0;
	}else{
		printf("Uso correto %s [PID] [indice] [operacao]\n",argv[0]);
		return -1;
	     }

}

