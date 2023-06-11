#!/bin/bash


cp $1 Library/ac-library/
cd Library/ac-library/
python expander.py $1
rm $1
mv combined.cpp ../../
cd ../../
