#!/bin/bash
# Henry J Schmale
# March 19, 2015
# Perlin Noise Initial Vector Generator
# Generates the data to use in Dynamic Background Generator System

for y in {0..1000} ; do
    for x in {0..1000}; do
        for a in 0 1 ; do
            echo $y $x $a
        done
    done
done
