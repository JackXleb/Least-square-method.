set xlabel 't'
set ylabel 'V'
plot 'data.txt' using 1:2 with points title '����������������� ������', 'data.txt' using 1:3 with lines title '����� ���������'
