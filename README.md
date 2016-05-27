Block Scheduler
=================

Allows admins to schedule the visibility of blocks

HOW TO INSTALL:
---------------
- Install this module using the official Backdrop CMS instructions at 
https://backdropcms.org/guide/modules


Usage
---------------
This module will add a new Visibility Condition to blocks which provides a 
visibility time.

There is also an option to determine which timezone to use to determine the
current time: using the website timezone will enable visibility of the block 
according to the website server time, which may be different from the user's 
time.

At least one time option is required. If only the start time is given, 
visibility will be turned on from the start time. If only the end time is 
supplied, visibility will be turned on immediately and turned off at the end 
time. If both options are supplied, visibility turns on at the start time and 
off at the end time. If the negate option is checked, both start and end times 
are also required, in which case visibility will be on only outside of the 
given range.
      
LICENSE
---------------    

This project is GPL v2 software. See the LICENSE.txt file in this directory 
for complete text.

CURRENT MAINTAINERS
---------------    

@docwilmot
