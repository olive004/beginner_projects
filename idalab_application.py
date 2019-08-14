#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Jul  5 23:21:32 2019

@author: oliviagallup
"""
# Python 
import numpy as np

numbers = np.arange(1, 101, 1)  

for number in numbers:
   if ((number%4 == 0) and (number%7 == 0)):
      print("fizzbuzz")
   elif (number%7 == 0):
      print("buzz")
   elif (number%4 == 0): 
      print("fizz")
   else:
      print(number)
