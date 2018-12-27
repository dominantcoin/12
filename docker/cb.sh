#! /bin/bash
PRESENTDIR=$(pwd)
if [ ! -d /shared/dmtc ] ; then
	git clone -b "$GITBRANCH" --depth 1 "$GITURI" /shared
	if [ -d /shared/dmtc ] ; then
  		cd /shared/dmtc/
  		./autogen.sh
  		./configure --disable-zerocoin --without-gui --enable-debug
  		make
  		sudo make install
  		mkdir /home/ubuntu/.dmtc
  		cp /home/ubuntu/dmtc.conf /home/ubuntu/.dmtc.conf
  		cd $PRESENTDIR
	else
  		echo "There was a problem with the clone"
	fi
else
	echo "/shared is not empty, should you be running pbr.sh?"	
fi
