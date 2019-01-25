#!/bin/bash
I
P=&(curl -s4 icanhazip.com)
CONFIG_FILE='common.cfg'
CONFIG_FOLDER='lgsm/config-lgsm/csgoserver'
GSLT=''

function update_config(){
cat << EOF >> $CONFIG_FOLDER/$CONFIG_FILE
ip=$IP
gslt=$GSLT
EOF
}

function create_user(){
adduser csgoserver
passwd #####
su - csgoserver
}
############# Main ###############
update_config