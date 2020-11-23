bool cur_segtype;
bool last_segtype;

/*Current Segment*/

int cur_b_lat = 385; /*segbegin*/
int cur_b_lon = 129; /*segbegin*/
int cur_e_lat;   /*segend*/
int cur_e_lon; /*segend*/
int cur_b_h = 0; /*begin heading*/
int cur_e_h; /*end heading*/

 int bank = 10;
 int arc = 1;
 int tas = 80;

/*Last Segment*/

int las_e_lat; 
int las_e_lon;
int las_e_h;

bool begin = true;

c_decl{
         \#include "function.h"
}
c_code{
         \#include <stdio.h>
}

active proctype way ()
{
   if 
   :: (begin) ->
   do
       :: (cur_b_lat < 410 && begin)-> 
          cur_b_lat = cur_b_lat + 1
       :: (cur_b_lon < 132 && begin)->
          cur_b_lon = cur_b_lon + 1
       :: (begin) ->
          begin = false
       :: (!begin) ->
          break
   od
   fi
}

active proctype curve () 
{	   
      
      atomic{
         bank = 10;
         arc = 1;
         tas = 80;
         bool tasflag = true;
         bool bankflag = true;
         cur_segtype = false;
         cur_b_lat = las_e_lat;
         cur_b_lon = las_e_lon;*/

         /*true airspeed*/
         do
            :: (tas < 97 && tasflag) ->
               tas = tas + 1
            :: tasflag -> 
               tasflag = false;
            :: (!tasflag) -> break
         od
         /*bank angle*/
         do
            :: (bank < 30 && bankflag) ->
               bank = bank + 5
            :: bankflag ->
               bankflag = false;
            :: (!bankflag) -> break
         od
         c_code {
            now.cur_e_lat = lat_curve(now.tas,now.bank,now.arc,now.las_e_h,now.las_e_lat,now.las_e_lon);
         }

         las_e_lat = cur_e_lat;
         las_e_lon = cur_e_lon;
         las_e_h = cur_e_h;
         	
      }
}

active proctype straight ()
{
   if
      :: (!begin) ->
         atomic{
            cur_segtype = true;
         }
      :: else
   fi
} 
