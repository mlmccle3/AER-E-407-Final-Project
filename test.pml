bool cur_segtype;
bool last_segtype;

/*Current Segment*/

int cur_b_lat = 385; /*segbegin*/
int cur_b_lon = 129; /*segbegin*/
int cur_e_lat;   /*segend*/
int cur_e_lon; /*segend*/
int cur_b_h = 0; /*begin heading*/
int cur_e_h; /*end heading*/
int las_e_h = 0; /*last seg end heading*/

int bank = 10;
int arc = 1;
int tas = 80;

/*Last Segment*/

int las_e_lat; 
int las_e_lon;

/*Spec Flags*/

bool h_flag;
bool lat_flag;
bool lon_flag;

bool begin = true;

c_decl{
         \#include "function1.h"
}
c_code{
         \#include <stdio.h>
}

ltl h_flag_spec {!<>(!h_flag && !cur_segtype)}
ltl lat_flag_spec {!<>(!lat_flag && !cur_segtype)}
ltl lon_flag_spec {!<>(!lon_flag && !cur_segtype)}

active proctype way ()
{
   if 
   :: (begin) ->
   do
       /*latitude*/
       :: (cur_b_lat < 410 && begin)-> 
          cur_b_lat = cur_b_lat + 1
      /*longitude*/
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
         cur_b_lon = las_e_lon;
         cur_b_h = las_e_h;

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
            now.cur_e_lon = lon_curve(now.tas,now.bank,now.arc,now.las_e_h,now.las_e_lat,now.las_e_lon);
            now.cur_e_h = eh_curve(now.tas,now.bank,now.arc,now.las_e_h,now.las_e_lat,now.las_e_lon);
            now.h_flag = h_spec(now.cur_b_h,now.las_e_h);
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
            bool start = true;
            cur_b_lat = 385;
            cur_b_lon = 129;
            cur_e_lat = 385;
            cur_e_lon = 129;
            /*establishes waypoints*/
            do
               /*first waypoint*/
               :: (cur_b_lat < 410 && begin)-> 
                cur_b_lat = cur_b_lat + 1
               :: (cur_b_lon < 132 && begin)->
                cur_b_lon = cur_b_lon + 1

               /*second waypoint*/
               :: (cur_e_lat < 410 && begin)-> 
                cur_e_lat = cur_b_lat + 1
               :: (cur_e_lon < 132 && begin)->
                cur_e_lon = cur_b_lon + 1

               /*do exit conditions*/
               :: (start) ->
                start = false
               :: (!start) ->
                break
            od

            c_code {
               now.cur_e_h = straight_h(now.cur_b_lat,now.cur_b_lon,now.cur_e_lat,now.cur_e_lon,now.las_e_lat,now.las_e_lon);
               
            }
         
            las_e_h = cur_e_h;

         }
        :: else
   fi
} 
