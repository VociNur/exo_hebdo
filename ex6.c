#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <assert.h>

typedef struct {
  int id;
  sem_t *s_0, *s_1, *s_2;
} thread_args;

void *affiche(void* v_args){
  thread_args args = *((thread_args *) v_args); 
  //au début, 1 2 et 3 attendent 0
  if(args.id == 1 || args.id == 2 || args.id == 3){
    sem_wait(args.s_0);
  }

  // 4 attend 1 et 2
  if(args.id == 4){
    sem_wait(args.s_1);
    sem_wait(args.s_1);
  }

  //le 5 attend le 3 et le 4
  if(args.id == 5){
    sem_wait(args.s_2);
    sem_wait(args.s_2);
  }




  printf("%d\n", args.id);

  //0 et libère donc trois
  for(int i = 0; i < 3; i++){
    sem_post(args.s_0);
  }

  //1 et 2 libère chacun 1 fois pour le 4
  if(args.id == 1 || args.id == 2){
    sem_post(args.s_1);
  }

  if(args.id == 3 || args.id == 4){
    sem_post(args.s_2);
  }
  return NULL;
}

int main(void){
  fflush(stdout);
  //INIT
  int n_thread = 6;
  int n_sem = 3;
  sem_t *tab_sem = (sem_t *) malloc(n_sem * sizeof(sem_t));
  //SEM
  for(int i = 0; i < n_sem; i++){
    int val = sem_init(&tab_sem[i], 0, 0);
    assert(val == 0);
     
  }

  //THREAD
  pthread_t *tab_thread = (pthread_t *) malloc(n_thread*sizeof(pthread_t));
  thread_args *args = (thread_args *) malloc(n_thread*sizeof(thread_args));
  for(int i = 0; i<n_thread; i++){
    //printf("i: %d", i);
    thread_args a = {.id=i, .s_0=&tab_sem[0], .s_1=&tab_sem[1], .s_2=&tab_sem[2]};
    args[i] = a;
    int val = pthread_create(&tab_thread[i], NULL, affiche, &args[i]);
    assert(val == 0);
  }

  //JOIN
  for(int i = 0; i < n_thread; i++){
    int val = pthread_join(tab_thread[i], NULL);
    assert(val == 0);
  }

  //FREE/DESTROY
  //SEM
  for(int i = 0; i < n_sem;i ++){
    int val = sem_destroy(&tab_sem[i]);
    assert(val == 0);
  }
  free(tab_sem);
  
  //THREAD
  free(tab_thread);
  return 0;
}
