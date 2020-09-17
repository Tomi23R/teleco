#!/bin/sh

if [ $# -lt 3 ] ; then
      echo "./plot_cdf file title xaxis"
      exit 0
fi
file=$1
title="$2"			
xaxis="$3"			

echo $file,$title

echo "

set terminal png enhanced font Vera 11
set output '${file}.png'
set grid
set title '${title}'
set nokey
set xlabel '${xaxis}'
set ylabel 'F(x)'
plot '${file}' using 2:1 with lines
"|gnuplot
			


