#define BILLION  1E9
#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <math.h>
#include <vector>
using namespace std;
struct timespec start, stop;
int num;
double accum;
char name[128] = {'\0'};
char city[128] = {'\0'};
char country[128] = {'\0'};
char code1[128] = {'\0'};
char code2[128] = {'\0'};
float lat;
float lon;
float alt;
char unknown[128] = {'\0'};
char unknown2[128] = {'\0'};
char unknown3[128] = {'\0'};
char unknown4[128] = {'\0'};


const static double EarthRadiusKm = 6372.8;
 
//COORDINATE CLASS THAT CONTAINS THE NAME LAT LONG AND DISTANCE FOR A COORDINATE
class Coordinate
{
public:
	Coordinate(string cname,double latitude ,double longitude, float distance):name(cname),lat(latitude), lon(longitude), dist(distance)
	{}
    string name;
    float dist;
    float lat;
	float lon;
	
};
// CONVERT DEGREE TO RADIAN
inline float DegreeToRadian(float angle)
{
	return 3.14 * angle / 180.0;
}
vector<Coordinate> bestOption(vector<Coordinate> carray,Coordinate curr,float radius)
{
    vector <Coordinate> small;
    for(int i=0;i<carray.size();i++)
       {
        //CHOOSE ONLY THE AIRPORTS IN 250KM NORTH OR SOUTH RANGE OF CURR LOCATION
           if(carray[i].lat>((curr.lat)-(radius/111.045)) && carray[i].lat<((curr.lat)+(radius/111.045)))
           {
               
               // IF IN RANGE of 250km NORTH/SOUTH THEN NOW AGAIN CHOOSE ONLY THAT ARE
               // IN RANGE OF 250km EAST/WEST
               // longitudes have a lot of distance so make it small
               if(((curr.lon)>90&&(curr.lon)<180)||(curr.lon<-90&&curr.lon>-180)){
                   
               if(carray[i].lon<((curr.lon)-(radius/(111.045 * cos(DegreeToRadian(curr.lon))))) && carray[i].lon>((curr.lon)+(radius/(111.045 * cos(DegreeToRadian(curr.lon))))))
                  {
                    //ADD TO THE ARRAY 
                      small.emplace_back(carray[i]);
                  }
               }
               
               
               else if(((curr.lon)>-90&&curr.lon<90)){
                   
               if(carray[i].lon>((curr.lon)-(radius/(111.045 * cos(DegreeToRadian(curr.lon))))) && carray[i].lon<((curr.lon)+(radius/(111.045 * cos(DegreeToRadian(curr.lon))))))
                  {
                    //ADD TO THE ARRAY 
                      small.emplace_back(carray[i]);
                  }
               }
               
           }
       }
    return small;
}

// CALCULATE DISTANCE USING GREAT CIRCLE DISTANCE
double HaversineDistance(const Coordinate& p1, const Coordinate& p2)
{
	double latRad1 = DegreeToRadian(p1.lat);
	double latRad2 = DegreeToRadian(p2.lat);
	double lonRad1 = DegreeToRadian(p1.lon);
	double lonRad2 = DegreeToRadian(p2.lon);
 
	double diffLa = latRad2 - latRad1;
	double doffLo = lonRad2 - lonRad1;
 
	double computation = asin(sqrt(sin(diffLa / 2) * sin(diffLa / 2) + cos(latRad1) * cos(latRad2) * sin(doffLo / 2) * sin(doffLo / 2)));
	return 2 * EarthRadiusKm * computation;
}

// BUBBLE SORT
void bubbleSort(std::vector<Coordinate> &vectorObject)
{
    for(int i = 1; i < vectorObject.size(); i++)
    {
        for(int j = 0; j < vectorObject.size()-i; j++)
        {
            if(vectorObject.at(j).dist > vectorObject.at(j+1).dist)
            {
                Coordinate temp = vectorObject.at(j);
                vectorObject.at(j) = vectorObject.at(j+1);
                vectorObject.at(j+1) = temp;
            }
        }
    }
}

 
int main(int argc, char* argv[])
{   
    float currlat=0;
    float currlon=0;
    float curralt=0;
    vector <Coordinate> carray;
    vector <Coordinate> ansarray;
    
    
    Coordinate curr("Default",currlat,currlon,0);
   FILE *fp = NULL;
   fp = fopen( (const char*) "airports.dat","r");
   if (fp)
   {
       char line[1024]={'\0'};
       while ( fgets(line,1024,fp) )
       {
/*
1,"Goroka Airport","Goroka","Papua New Guinea","GKA","AYGA",-6.081689834590001,145.391998291,5282,10,"U","Pacific/Port_Moresby","airport","OurAirports"
*/
           char *tok = strtok(line,(const char*) ",");
           num = atoi (tok);
           strcpy(name,strtok(NULL,(const char*) ",") );
           strcpy(city,strtok(NULL,(const char*) ",") );
           strcpy(country,strtok(NULL,(const char*) ",") );
           strcpy(code1,strtok(NULL,(const char*) ",") );
           strcpy(code2,strtok(NULL,(const char*) ",") );
           lat = atof(strtok(NULL,(const char*) ",") );
           lon = atof(strtok(NULL,(const char*) ",") );
           alt = atof(strtok(NULL,(const char*) ",") );
           
#if 0
                   // skip these
                   unknown,
                   unknown2,
                   unknown3,
                   unknown4;
#endif
        string sname(name);
           
           //CALL EMPLACE TO SAVE TIME THAN PUSH BACK
        carray.emplace_back(sname,lat,lon,0);
          
       
   }
       while(1)
       {    
           double radius=250.000;
           //TAKE INPUT LOOP
            printf("\nEnter your latitude,longitude,altitude [ 12 34 56] no commas needed:\n");
            cin >> currlat;
            cin >> currlon;
            cin >> curralt;

               if((currlat==-1)&&(currlon==-1)&&(curralt==-1))
               {
                   break;
               }
            curr.lat=currlat;
            curr.lon=currlon;
            
            // CHOOSE ONLY THE AIRPORTS IN A SQUARE RADIUS OF 250 KM
            vector <Coordinate> small;
           clock_gettime(CLOCK_REALTIME, &start);
                small=bestOption(carray,curr,radius);
           
           while(small.size()<5)
           {
               radius+=250.00;
               small=bestOption(carray,curr,radius);
               
           }
        
           //CALCULATE DISTANCE FOR THE NEW ARRAY WITH LESS AIRPORTS
           for(int i=0;i<small.size();i++)
           {
               small[i].dist=HaversineDistance(curr, small[i]);
           }
           
           
            //BUBBLE SORT IMPLEMENTED TO SORT THE VECTOR
           bubbleSort(small);
           clock_gettime(CLOCK_REALTIME, &stop);
           //PRINT STATEMENTS
          
          for(int i=0;i<5;i++)
          {
              
         printf("\nName of Airport :: %s\n",small[i].name.c_str());
              
              //convert to miles from KM
         printf("DISTANCE(Miles) = %f\n\n",small[i].dist*0.621371);
          }
           accum = ( stop.tv_sec - start.tv_sec )
          + ( stop.tv_nsec - start.tv_nsec )
            / BILLION;
            printf( "%lf\n", accum );
           //REINITIALIZE FOR NEW START
           small.clear();
           
       }
       }
    
       
   fclose (fp);
   return 0;
}
