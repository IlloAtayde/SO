#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/sched.h>

asmlinkage long sys_exp_kernel(pid_t pid, int index, int action, int *counter){
  /* Configurar o ponto de ancoragem */
  struct task_struct *task = &init_task;
  *counter = -1;/* counter recebe -1 para a logica de controle externa*/
  /* Percorrer a lista de tarefas, até atingir init_task novamente */
  do {

    if (task->pid == pid){
      if (action == 0){/* Se o pid coincidir e a ação for zero */
        task->contador[index] = 0;/* Apaga o índice referente */
        *counter = 0;/* Zera a variável counter para a lógica de controle externo */
        return 0;
      }
      *counter = task->contador[index];/* Se o pid coincidir e a ação for diferente de zero, counter recebe o valor do contador */
      return 0;
    }

  } while ( (task = next_task(task)) != &init_task );
  return 0;
}