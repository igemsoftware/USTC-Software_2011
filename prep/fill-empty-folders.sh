#!/bin/bash

if [ -n "$1"]; then
	find $1 \( -type d -empty \) -and \( -not -regex ./\.git.* \) -exec touch {}/.gitignore \;
else
	find . \( -type d -empty \) -and \( -not -regex ./\.git.* \) -exec touch {}/.gitignore \;
fi

