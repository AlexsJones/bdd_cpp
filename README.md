Installation
===========

deps: jnxlibc [ git@github.com:AlexsJones/jnxlibc.git ]

make

sudo make install

Usage
=====


pickle -g

//Generates step_definitions in your CWD from features/*

pickle

//Runs tests


Structure
========


features/
		example.feature

step_definitions/
				(generated) example.c
				(user created) example.pickled - Object reference file

pickled files
==============

.pickled files are used so that during the compilation process we can pull the refs needed for generating object files.

e.g. echo "../*.c another_example.c " >> example.pickled
