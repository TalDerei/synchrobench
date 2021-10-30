#!/usr/local/bin/gnuplot
#set term postscript eps enhanced solid color "Arial-Bold,10"
set term postscript eps enhanced solid color "Helvetica-Bold, 10"
set encoding iso_8859_1
set xlabel "#Thread"
set ylabel "Throughput (Txs/s)"
set xrange [0:5]

set output "compare.eps"

set multiplot layout 1,4 rowsfirst
set title "Size = 1,024"
plot 'throughput-smart-1024.txt' u 1:2 w lp lc rgb "red" pt 4 lw 2 ti "smart", 'throughput-epoch-1024.txt' u 1:2 w lp lc rgb "blue" pt 6 lw 2 ti "epoch"
set title "Size = 2,048"
plot 'throughput-smart-2048.txt' u 1:2 w lp lc rgb "red" pt 4 lw 2 ti "smart", 'throughput-epoch-2048.txt' u 1:2 w lp lc rgb "blue" pt 6 lw 2 ti "epoch"
set title "Size = 4,096"
plot 'throughput-smart-4096.txt' u 1:2 w lp lc rgb "red" pt 4 lw 2 ti "smart", 'throughput-epoch-4096.txt' u 1:2 w lp lc rgb "blue" pt 6 lw 2 ti "epoch"
set title "Size = 8,192"
plot 'throughput-smart-8192.txt' u 1:2 w lp lc rgb "red" pt 4 lw 2 ti "smart", 'throughput-epoch-8192.txt' u 1:2 w lp lc rgb "blue" pt 6 lw 2 ti "epoch"
#set title "Size = 16,384"
#plot 'throughput-smart-16384.txt' u 1:2 w lp lc rgb "red" pt 4 lw 2 ti "smart", 'throughput-epoch-16384.txt' u 1:2 w lp lc rgb "blue" pt 6 lw 2 ti "epoch"


#set title "n = 9,876,437"
#plot 'out_tbb_9876437.txt' u 1:2:3 w yerrorlines lc rgb "dark-green" ps 1.5 pt 4 lw 2 ti 'tbb', 'out_static_9876437.txt' u 1:2:3 w yerrorlines lc rgb "red" ps 1.5 pt 6 lw 2 ti 'static', 'out_dynamic_9876437.txt' u 1:2:3 w yerrorlines lc rgb "blue" ps 1.5 pt 8 lw 2 ti 'dynamic'
#set title "n = 2,147,483,647"
#plot 'out_tbb_2147483647.txt' u 1:2:3 w yerrorlines lc rgb "dark-green" ps 1.5 pt 4 lw 2 ti 'tbb', 'out_static_2147483647.txt' u 1:2:3 w yerrorlines lc rgb "red" ps 1.5 pt 6 lw 2 ti 'static', 'out_dynamic_2147483647.txt' u 1:2:3 w yerrorlines lc rgb "blue" ps 1.5 pt 8 lw 2 ti 'dynamic'
unset multiplot
quit
#set key top left font "Helvetica-Bold, 8"
#set title "resid 5"
#plot 'hist_5_phi.dat' w l ti "phi-drude" lt rgb "pink" lw 2,  'hist_5_gao_phi.dat' w l ti "phi-additive" lt rgb "red" dt '-' lw 2, 'hist_5_psi.dat' w l ti "psi-drude" lt rgb "cyan" lw 2,  'hist_5_gao_psi.dat' w l ti "psi-additive" lt rgb "blue" dt '-' lw 2
#unset key
#set title "resid 6"
#plot 'hist_6_phi.dat' w l ti "phi-drude" lt rgb "pink" lw 2,  'hist_6_gao_phi.dat' w l ti "phi-additive" lt rgb "red" dt '-' lw 2, 'hist_6_psi.dat' w l ti "psi-drude" lt rgb "cyan" lw 2,  'hist_6_gao_psi.dat' w l ti "psi-additive" lt rgb "blue" dt '-' lw 2
#set title "resid 7"
#plot 'hist_7_phi.dat' w l ti "phi-drude" lt rgb "pink" lw 2,  'hist_7_gao_phi.dat' w l ti "phi-additive" lt rgb "red" dt '-' lw 2, 'hist_7_psi.dat' w l ti "psi-drude" lt rgb "cyan" lw 2,  'hist_7_gao_psi.dat' w l ti "psi-additive" lt rgb "blue" dt '-' lw 2
#set title "resid 8"
#plot 'hist_8_phi.dat' w l ti "phi-drude" lt rgb "pink" lw 2,  'hist_8_gao_phi.dat' w l ti "phi-additive" lt rgb "red" dt '-' lw 2, 'hist_8_psi.dat' w l ti "psi-drude" lt rgb "cyan" lw 2,  'hist_8_gao_psi.dat' w l ti "psi-additive" lt rgb "blue" dt '-' lw 2
#set title "resid 9"
#plot 'hist_9_phi.dat' w l ti "phi-drude" lt rgb "pink" lw 2,  'hist_9_gao_phi.dat' w l ti "phi-additive" lt rgb "red" dt '-' lw 2, 'hist_9_psi.dat' w l ti "psi-drude" lt rgb "cyan" lw 2,  'hist_9_gao_psi.dat' w l ti "psi-additive" lt rgb "blue" dt '-' lw 2
#set title "resid 10"
#plot 'hist_10_phi.dat' w l ti "phi-drude" lt rgb "pink" lw 2,  'hist_10_gao_phi.dat' w l ti "phi-additive" lt rgb "red" dt '-' lw 2, 'hist_10_psi.dat' w l ti "psi-drude" lt rgb "cyan" lw 2,  'hist_10_gao_psi.dat' w l ti "psi-additive" lt rgb "blue" dt '-' lw 2
#set title "resid 11"
#plot 'hist_11_phi.dat' w l ti "phi-drude" lt rgb "pink" lw 2,  'hist_11_gao_phi.dat' w l ti "phi-additive" lt rgb "red" dt '-' lw 2, 'hist_11_psi.dat' w l ti "psi-drude" lt rgb "cyan" lw 2,  'hist_11_gao_psi.dat' w l ti "psi-additive" lt rgb "blue" dt '-' lw 2
#set title "resid 12"
#plot 'hist_12_phi.dat' w l ti "phi-drude" lt rgb "pink" lw 2,  'hist_12_gao_phi.dat' w l ti "phi-additive" lt rgb "red" dt '-' lw 2, 'hist_12_psi.dat' w l ti "psi-drude" lt rgb "cyan" lw 2,  'hist_12_gao_psi.dat' w l ti "psi-additive" lt rgb "blue" dt '-' lw 2
#set title "resid 13"
#plot 'hist_13_phi.dat' w l ti "phi-drude" lt rgb "pink" lw 2,  'hist_13_gao_phi.dat' w l ti "phi-additive" lt rgb "red" dt '-' lw 2, 'hist_13_psi.dat' w l ti "psi-drude" lt rgb "cyan" lw 2,  'hist_13_gao_psi.dat' w l ti "psi-additive" lt rgb "blue" dt '-' lw 2
#unset multiplot
