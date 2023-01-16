# Ecole 42: Philosohers

In this project I implemented a solution of dining philosophers problem - one of the classic problems used to describe synchronization issues in a multithreading progam. 

### How to build:

Clone repo, open `./philo` or `./philo_bonus`

The difference between them is philo represent each philosopher as thread whereas philo_bonus represent each philosoher as process.

To build program type:

```Bash
$ make
```

### How to launch:

Program takes 4 arguments:

| Argument | Description |
| --- | --- |
| `number_of_philosophers` | number of philosophers |
| `time_to_die` | time to die without food in millisecond  |
| `time_to_eat` | time spends to eat in milliseconds |
| `time_to_sleep` | time spends to sleep in milliseconds |

Run program with parameters:

```Bash
$ ./philo 5 800 200 200 7
```
