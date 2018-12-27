#! /bin/bash
PRESENTDIR=$(pwd)
cd /shared
# attempt to pull and then rebuild...
if [ -d /shared/dmtc ] ; then
	PULLRESLT=$(git pull)
	if [[ ($PULLRESLT==0 || $PULLRESLT=="Already up-to-date.")]] ; then
  		cd /shared/dmtc/
		#./autogen.sh
  		#./configure --disable-zerocoin --without-gui --enable-debug
  		make
  		sudo make install
  		dmtcd -debug
  		cd $PRESENTDIR
	else 
		echo "git pull ERROR:$PULLRESLT"
	fi
else 
	echo "There is no /shared/dmtc folder, do you need to run cbr.sh instead?"
fi
