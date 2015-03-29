#!/usr/bin/perl
# Henry J Schmale
# March 22, 2015
# Random Number Generator For Perlin Vector Generator Bash Script

use strict;
use warnings;
use Math::Trig;

my $RndNum = rand(2 * pi) - pi;
printf("%.2f\n", $RndNum);
