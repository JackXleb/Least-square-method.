set terminal wxt persist
set xlabel 's'
set ylabel 'V(s)'
plot 'data.txt' with lines title '�����������', 'regression.dat' with lines title '����� ���������', 'fit.dat' with lines title '����������� �����������'
