#!/bin/bash
# Henry J Schmale
# March 19, 2015
# Perlin Noise Initial Vector Generator
# Generates the data to use in Dynamic Background Generator System

TEN=10 # Bash is really annoying about not using straight up numeric constants

echo '{' # Opening Brace
for y in {0..999} ; do
    echo '    {'
    for x in {0..999}; do
        let "l = $x % 5"
        if [ "$l" -eq 1 ] ; then
            echo -n '        {'
        else
            echo -n '{'
        fi
        for a in 0 1 ; do
            # Write the actual Numbers Here
            v=$[100 + (RANDOM % 100)]$[1000 + (RANDOM % 1000)]
            v=0.${v:1:2}${v:4}
            echo -n $v
            if [ $a -ne 1 ] ; then
                echo -n ', '
            fi
        done
        if [ $l -eq 0 ] ; then
            echo '},'
        else
            echo -n '},'
        fi
    done
    if [ $y -ne 999 ] ; then
        echo '    },'
    else
        echo '    }'
    fi
done
echo '};'  # Closing Brace
