#! /bin/bash
#
# import.sh
# Copyright (C) 2017 pulkomandy <pulkomandy@shredder>
#
# Distributed under terms of the MIT license.
#

while read -r a ; do
	echo -e "\n----\n"
	curl -H "Content-Type: application/json" --header "Authorization: Bearer $1" https://codein.withgoogle.com/api/program/current/tasks/ -X POST -d "$(echo $a)"
done < clean.json

