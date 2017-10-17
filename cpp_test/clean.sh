#/bin/sh

for file in `ls /root/c++`;
do
  expr index $file ".cpp";
  echo $index,$file;
  #if [ index = -1 ]; then
  #  echo $file;
  #fi;
done
