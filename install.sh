#!bin/bash

if [ -f /usr/local/bin/trun ]; then
  echo "trun já está installado"
else  
  g++ trun.cpp -o trun
  sudo mv trun /usr/local/bin/
  echo "trun foi installado!"
fi
