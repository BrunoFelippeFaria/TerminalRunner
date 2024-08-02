#!bin/bash

if [ -f "/usr/local/bin/trun" ]; then
  sudo rm /usr/local/bin/trun
  echo "trun foi desinstalado!"
else
  echo "trun não está installado"
fi
