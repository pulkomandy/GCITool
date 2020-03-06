#! /bin/sh
#
# Copyright (C) 2020 Viveris Technologies <adrien.destugues@opensource.viveris.com>
#
# Distributed under terms of the MIT license.
#

curl -H "Content-Type: application/json" --header "Authorization: Bearer $1" https://codein.withgoogle.com/api/program/current/tasks/ -X GET |python -m json.tool > tasks.json

