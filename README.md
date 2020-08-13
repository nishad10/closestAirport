# closestAirport
Find the closest airport from your location using this app using Great Circle(orthodromic) distance calculation with focus on performance.

Uses Great Circle distance or orthodromic distance to calculate the distance to the closest airport from your location.
This means it takes into consideration the curvature of the earth and does not find the airport based on a straight line distance through the surface of the earth.

Also uses bubble sort to filter through the big airport list and makes the algorithm faster performance wise.

You need a airport list in the location of the code and need to change the name of file of the list in the code.
Or you can name your airport data file as 'airports.dat' which is what the code tries to open to read.

Use this file for best results.

The file I used is from this site: https://openflights.org/data.html

Which forwards you to here:

https://raw.githubusercontent.com/jpatokal/openflights/master/data/airports.dat

NOTE: Keep the format same if you use a different file 

FORMAT OF INFORMATION : Example-

1,"Goroka Airport","Goroka","Papua New Guinea","GKA","AYGA",-6.081689834590001,145.391998291,5282,10,"U","Pacific/Port_Moresby","airport","OurAirports"



