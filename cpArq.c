/*


int open(const char *path, int oflags);
int open(const char *path, int oflags, mode_t mode);
size_t read(int fildes, void *buf, size_t nbytes);


Oflag values for open().  POSIX Table 6-4. 

#define O_CREAT        00100	creat file if it doesn't exist
#define O_EXCL         00200	exclusive use flag
#define O_NOCTTY       00400	do not assign a controlling terminal
#define O_TRUNC        01000	truncate flag

File status flags for open() and fcntl().  POSIX Table 6-5.

#define O_APPEND       02000	set append mode
#define O_NONBLOCK     04000	no delay

File access modes for open() and fcntl().  POSIX Table 6-6.

#define O_RDONLY           0	open(name, O_RDONLY) opens read only
#define O_WRONLY           1	open(name, O_WRONLY) opens write only
#define O_RDWR             2	open(name, O_RDWR) opens read/write

modeflags

S_IRWXU 00700 user (file owner) has read, write and execute permission
S_IRUSR 00400 user has read permission
S_IWUSR 00200 user has write permission
S_IXUSR 00100 user has execute permission
S_IRWXG 00070 group has read, write and execute permission
S_IRGRP 00040 group has read permission
S_IWGRP 00020 group has write permission
S_IXGRP 00010 group has execute permission
S_IRWXO 00007 others have read, write and execute permission
S_IROTH 00004 others have read permission
S_IWOTH 00002 others have write permission
S_IXOTH 00001 others have execute permission

*/
#include <unistd.h>
#include <fcntl.h>

#define BUFFER 5

void imprimeNaTela(const char* texto);
int tamStr(const char* string);

int main(int argc, char const *argv[])	
{
	char buffer[BUFFER];
	size_t charsLidos = 0;
    int teste = 0;

	if(argc != 3){

		imprimeNaTela("Digite na forma :~$ cparq <arquivo de origem> <arquivo de destino>\n");
		_exit(0);//Abortar daqui
	}

	int idArqOrigem, idArqDestino, modeUG__rw_;

	modeUG__rw_ = (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

	//Tenta abrir o arquivo de origem passado no primeiro argumento

    if((idArqOrigem = open(argv[1], O_RDONLY)) < 0){

        imprimeNaTela("Arquivo de origem inexistente!\n");
        _exit(0);//Abortar daqui
    }

    //Tenta abrir o arquivo de destino passado no segundo argumento

    if((idArqDestino = open(argv[2], O_WRONLY | O_CREAT | O_EXCL | O_TRUNC | O_APPEND, modeUG__rw_)) < 0){

    	imprimeNaTela("Arquivo de destino ja existe!\n");

    	if(close(idArqOrigem) < 0){
    		imprimeNaTela("Falha ao fechar arquivo de origem!\n");
    	}

    	_exit(0);//Abortar daqui
    }
    //Efetuar a cópia de origem para destino a partir daqui

    /*charsLidos = read(idArqOrigem,buffer,BUFFER);
    charsLidos = read(idArqOrigem,buffer,BUFFER);
    write(idArqDestino,buffer,charsLidos);
    */

	while ((charsLidos = read(idArqOrigem, buffer, BUFFER)) > 0){

        if (write(idArqDestino, buffer, charsLidos) != charsLidos){

            imprimeNaTela("Problemas na copia do arquivo!");
            _exit(0);//Abortar daqui
        }
        teste++;
    }
    if (charsLidos == -1){

        imprimeNaTela("Erro de leitura!");

        if(close(idArqOrigem) < 0){

    		imprimeNaTela("Falha ao fechar arquivo de origem!\n");
    	}

    	if(close(idArqDestino) < 0){

    		imprimeNaTela("Falha ao fechar arquivo de destino!\n");
    	}

    	_exit(0);//Abortar daqui
    }
    printf("%d\n",teste );
    return 0;
}

void imprimeNaTela(const char* string){
	write(1,string,tamStr(string));
}

int tamStr(const char* string){
	int len = 0;
	while(string[len++] != '\0'){
	}
	return len;
}