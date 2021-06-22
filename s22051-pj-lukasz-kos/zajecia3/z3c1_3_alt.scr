#!/bin/bash

FILENAME=$(basename $0)
NAME="${FILENAME%.*}"
EXT="${FILENAME##*.}"

if [ ${EXT} != "sh" ]; then
	mv ${0} ${0}.sh
fi
