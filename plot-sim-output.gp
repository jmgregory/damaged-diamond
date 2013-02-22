title_string = "plot-sim-output.gp"
if (exists("iteration")) title_string = "Iteration " . iteration

set term aqua enhanced size 450,700 font "Times-Roman" 18 title title_string

set style data lines
unset grid
set tics scale 1 nomirror
unset key
implcolor = "#000000"
unimplcolor = "#C2554F"
myBlue = "#1F4291"

set multiplot

plotheight = 0.86
graphcount = 6
graphcounter = graphcount + 1
boxheight = plotheight / graphcount
tbmarg = (1 - plotheight) / 2
horizshift = 0
xmin = -3
xmax = 158
vs = 17.52
lineW = 1.5

unset title
set rmargin screen 0.98
set lmargin screen 0.08
set key nobox height 1
unset key
set border front


# TEM

#graphcounter = graphcounter - 1
#set bmargin screen tbmarg + boxheight * (graphcounter - 1)
#set tmargin screen tbmarg + boxheight * graphcounter
#set ylabel "TEM" offset -0.5
#unset ytics
set object 1 rectangle from second 16483*0.1*1e-3, screen tbmarg to second 17704*0.1*1e-3, screen (1 - tbmarg - boxheight) lw 2 fc rgb myBlue fs transparent solid 0.12 noborder behind
#plot [xmin:xmax] [-525:0] \
#     'TEM-3e16-detail.rgb' binary array=1087x527 format="%uchar" dx=1*1000/17.52/308 dy=1 flipy center=(85.24,-260) with rgbimage


# TRIM

#graphcounter = graphcounter - 1
set bmargin screen tbmarg + boxheight * (graphcounter - 1)
set tmargin screen tbmarg + boxheight * graphcounter
set x2tics mirror
set x2label "Sample Depth ({/Symbol m}m)" offset 0,-0.6
set xlabel ""
set format x ""
set format y ""
set x2range [xmin*vs/1000:xmax*vs/1000]
set format x2 "%.1f"
unset ytics
unset xtics
set ylabel "TRIM"
set format x2 "%.1f"
#set label 1 "TRIM" at second xmin*vs*1e-3,screen 1 - tbmarg - 0.05
set key nobox at graph 0.4,graph 1 spacing 0.65 vertical
set arrow 1 from second 16483*1e-4,0.0226384/2 to second 17704*1e-4,0.0226384/2 lc rgb "#000000" lw 2 heads front size 0.2,30
set label 2 "FWHM" at second 18500*1e-4,0.0226384/2

set style fill solid 0.25

unset label 2
unset arrow 1
unset object 1
unset label 1
#set ylabel "{/Symbol D}R/R {/Symbol \264} 10^{6}"
set x2tics nomirror
unset ytics



# 3e14 CAP

graphcounter = graphcounter - 1
set bmargin screen tbmarg + boxheight * (graphcounter - 1)
set tmargin screen tbmarg + boxheight * graphcounter

set xtics nomirror
set ylabel "3{/Symbol \264}10^{14} cm^{{/Symbol -}2}"
set key
plot [xmin:xmax] [-4:4] \
     'sim-output/cap-e6bi-3e14-800-400.dat' using ($1+horizshift):($2*1e6) ls 1 lw lineW lc rgb unimplcolor   title "Experiment", \
     'sim-output/cap-e6bi-3e14-800-400.dat' using ($1+horizshift):($3*1e6) ls 2 lw lineW lc rgb implcolor   title "Simulation"
unset key

# 1e15 CAP

graphcounter = graphcounter - 1
set bmargin screen tbmarg + boxheight * (graphcounter - 1)
set tmargin screen tbmarg + boxheight * graphcounter
set format x2 ""
set x2label ""

set ylabel "1{/Symbol \264}10^{15} cm^{{/Symbol -}2}"
plot [xmin:xmax] [-26:26] \
     'sim-output/cap-e6gi-1e15-800-400.dat' using ($1+horizshift):($2*1e6) ls 1 lw lineW lc rgb unimplcolor   title "Experiment", \
     'sim-output/cap-e6gi-1e15-800-400.dat' using ($1+horizshift):($3*1e6) ls 2 lw lineW lc rgb implcolor   title "Simulation"


# 3e15 CAP

set ylabel "3{/Symbol \264}10^{15} cm^{{/Symbol -}2}"
graphcounter = graphcounter - 1
set bmargin screen tbmarg + boxheight * (graphcounter - 1)
set tmargin screen tbmarg + boxheight * graphcounter
set ytics nomirror 15
unset ytics

plot [xmin:xmax] [-26:26] \
     'sim-output/cap-e6ei-3e15-800-400.dat' using ($1+horizshift):($2*1e6) ls 1 lw lineW lc rgb unimplcolor   title "Experiment", \
     'sim-output/cap-e6ei-3e15-800-400.dat' using ($1+horizshift):($3*1e6) ls 2 lw lineW lc rgb implcolor   title "Simulation"



# 8e15 CAP

set ylabel "8{/Symbol \264}10^{15} cm^{{/Symbol -}2}"
graphcounter = graphcounter - 1
set bmargin screen tbmarg + boxheight * (graphcounter - 1)
set tmargin screen tbmarg + boxheight * graphcounter
unset xlabel
set format x ""

plot [xmin:xmax] [-5:5] \
     'sim-output/cap-e6ai-8e15-800-400.dat' using ($1+horizshift):($2*1e6) ls 1 lw lineW lc rgb unimplcolor   title "Experiment", \
     'sim-output/cap-e6ai-8e15-800-400.dat' using ($1+horizshift):($3*1e6) ls 2 lw lineW lc rgb implcolor   title "Simulation"



# 1e16 CAP

set ylabel "1{/Symbol \264}10^{16} cm^{{/Symbol -}2}"
graphcounter = graphcounter - 1
set bmargin screen tbmarg + boxheight * (graphcounter - 1)
set tmargin screen tbmarg + boxheight * graphcounter

plot [xmin:xmax] [-9:9] \
     'sim-output/cap-e6fi-1e16-800-400.dat' using ($1+horizshift):($2*1e6) ls 1 lw lineW lc rgb unimplcolor   title "Experiment", \
     'sim-output/cap-e6fi-1e16-800-400.dat' using ($1+horizshift):($3*1e6) ls 2 lw lineW lc rgb implcolor   title "Simulation"


# 3e16 CAP

set ylabel "3{/Symbol \264}10^{16} cm^{{/Symbol -}2}"
graphcounter = graphcounter - 1
set bmargin screen tbmarg + boxheight * (graphcounter - 1)
set tmargin screen tbmarg + boxheight * graphcounter
set format x "%.0f"
set xlabel "Time Delay (ps)" offset 0,0.6
set xtics scale 1
set for [ii=0:7] arrow from ii*20,-7.7 to ii*20,-9 nohead front ls -1

plot [xmin:xmax] [-9:9] \
     'sim-output/cap-e6gi-3e16-800-400.dat' using ($1+horizshift):($2*1e6) ls 1 lw lineW lc rgb unimplcolor   title "Experiment", \
     'sim-output/cap-e6gi-3e16-800-400.dat' using ($1+horizshift):($3*1e6) ls 2 lw lineW lc rgb implcolor   title "Simulation"




unset multiplot
