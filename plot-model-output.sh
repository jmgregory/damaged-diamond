#!/bin/bash
make PrintModelOutput
filename=model-$1-temp.dat
./PrintModelOutput $* > $filename && gnuplot << EOF
lineSize = 2
call "~/Documents/Research/graph-templates/color-fix.gp"
set term aqua enhanced size 640,640 title "$*"
set title "$*"
set style data lines
set logscale x
set xrange [1e18:1e24]
set grid
set format x ""
set mxtics 10
unset key

highest_peak_C_V = 1e17 * 2695.34E-05 * 1e8
lattice_collapse_C_V = .16 * 1.77e23
set arrow 1 from highest_peak_C_V,graph 0 to highest_peak_C_V,graph 1 nohead
set arrow 2 from lattice_collapse_C_V,graph 0 to lattice_collapse_C_V,graph 1 nohead
set label 1 "Highest experimental C_V" at highest_peak_C_V/1.3,graph 0.1 rotate by 90
set label 2 "Lattice Collapse C_V" at lattice_collapse_C_V/1.3,graph 0.1 rotate by 90

plot_count = 3
bottom = 0.1
top = 0.9
plot_height = (top - bottom) / plot_count
set lmargin screen 0.15
set rmargin screen 0.95

set multiplot
set tmargin screen top - plot_height * 0
set bmargin screen top - plot_height * 1
set ylabel "n" offset 2
plot "$filename" using 1:2 ls 1 title "n"


unset title
unset label 1
unset label 2
set tmargin screen top - plot_height * 1
set bmargin screen top - plot_height * 2
set ylabel "kappa" offset 1
plot "$filename" using 1:3 ls 2 title "kappa"


set tmargin screen top - plot_height * 2
set bmargin screen top - plot_height * 3
set xlabel "Vacancy Concentration (cm^{-3})"
set format x "10^{%T}"
set ylabel "p_{12}" offset 1
plot "$filename" using 1:4 ls 3 title "p12"

unset multiplot

EOF
rm $filename
