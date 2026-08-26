# Philosophers 🍝🤔

## 📌 Sobre o Projeto
Este projeto é uma introdução prática à programação concorrente e à sincronização de threads na linguagem C. O objetivo é resolver o clássico problema dos **Filósofos Jantando** (*Dining Philosophers problem*), proposto por Edsger Dijkstra.

A simulação exige o gerenciamento de múltiplos filósofos que alternam entre comer, pensar e dormir. Como os garfos são recursos compartilhados e limitados, o desafio é criar um sistema que evite *deadlocks* (impasses) e *data races* (condições de corrida), garantindo que nenhum filósofo morra de fome.

## 🛠️ Tecnologias e Conceitos
* **Linguagem:** C (padrão C99/C11)
* **Threads:** Criadas e gerenciadas com a biblioteca `<pthread.h>` (`pthread_create`, `pthread_join`, `pthread_detach`).
* **Sincronização:** Proteção de memória compartilhada utilizando **Mutexes** (`pthread_mutex_init`, `pthread_mutex_lock`, `pthread_mutex_unlock`, `pthread_mutex_destroy`).
* **Prevenção de Erros:** Controle rigoroso de concorrência para impedir *data races* e vazamentos de memória.

## ⚙️ Uso e Argumentos
O programa aceita os seguintes parâmetros de execução:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

```

* **`number_of_philosophers`**: Quantidade de filósofos (e também de garfos).
* **`time_to_die`** (ms): Tempo máximo em milissegundos que um filósofo pode ficar sem comer antes de morrer.
* **`time_to_eat`** (ms): Tempo necessário para um filósofo comer.
* **`time_to_sleep`** (ms): Tempo que o filósofo passa dormindo.
* **`[number_of_times_each_philosopher_must_eat]`** *(Opcional)*: Se especificado, a simulação para quando todos os filósofos comerem pelo menos esse número de vezes.

## 🚀 Como Compilar e Executar

1. Clone o repositório:
```bash
git clone [https://github.com/seu-usuario/philosophers.git](https://github.com/seu-usuario/philosophers.git)
cd philosophers/philo

```


2. Compile o projeto:
```bash
make

```


3. Teste a simulação (exemplo com 4 filósofos):
```bash
./philo 4 410 200 200

```



```

```
