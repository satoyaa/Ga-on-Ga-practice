set terminal png
set output "iteration_graph.png"

set xlabel "Iteration"
set ylabel "Value"
plot "Iteration.txt" with lines title "Data"