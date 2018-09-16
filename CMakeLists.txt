cmake_minimum_required(VERSION 3.0)

project(MyFirstProject CXX)

set (SOURCE
	src/main.cpp
	src/solid.h
	)
	
add_executable(MFP ${SOURCE})
