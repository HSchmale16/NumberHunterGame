#!/usr/bin/perl
# Henry J Schmale
# March 22, 2015
# Random Number Generator For Perlin Vector Generator Bash Script

use strict;
use warnings;

my $RndNum = rand(2) - 1.0;
printf("%.3f\n", $RndNum);
