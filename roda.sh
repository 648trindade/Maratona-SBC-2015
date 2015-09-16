#!/bin/bash
if [ $# = 2 ]
  then
    gcc $1.c -o t -O2 -lm
    for ((x=1;x<=$2;x++))
      do
        echo Testando $x...
        time ./t < $1/$1_$x.in > /tmp/$1_$x.sol
        echo Verificando $x...
        diff $1/$1_$x.sol /tmp/$1_$x.sol
      done
else
  echo Uso: bash $0 \<letra\> \<total\>
  echo \ \ letra \ \ : Letra do problema proposto
  echo \ \ total \ \ : Total de entradas/saidas
fi
