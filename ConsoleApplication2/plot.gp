set terminal wxt persist
set xlabel 's'
set ylabel 'V(s)'
plot 'data.txt' with lines title 'Эксперимент', 'regression.dat' with lines title 'Линия регрессии', 'fit.dat' with lines title 'Подобранная зависимость'
