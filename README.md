# Interactor
Interactor aims at developing a general design pattern meant for unified user interaction metaphors.
It is thought to be used whenever developing an editor or interactive system of some sorts.
The goal is to separate the data being accessed/modified from the interactions with it.

The main concept is that every user interaction is based on three elements.
The _start_ of an interaction is what sets it up. 
It should be executed at the beginning of the interaction (e.g. at mouse click).
The _tick_ of an interaction should be looped over while the interaction is performed.
Basically this should be executed at each iteration of an editor's main loop
The _stop_ of an interaction is meant to clean up what was required to perform it.

This repo explores how this pattern can be used and implements it as a C++ library.
It will also eventually implement a small interactive system to illustrate its usage.
