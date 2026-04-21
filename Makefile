CC = gcc
CFLAGS = -O3

SRC = main.c read.c initialize.c initialize_hyperGA.c \
      calc_fitness.c hyper_calc_fitness.c \
      selection_tournament.c selection_roulette.c \
      crossover_pmx.c mutation_reverse.c mutation_swap.c \
      hyper_selection_tournament.c hyper_mutation_replacement.c \
      hyper_crossover_onepoint.c

runGA:
	$(CC) $(CFLAGS) $(SRC) -o runGA