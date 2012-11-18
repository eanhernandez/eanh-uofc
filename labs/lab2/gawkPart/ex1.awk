#!/bin/sh
gawk '
 {
      FS = "\t"
      if(match($2,"CA"))
      {
         CAp=CAp+$4
         CAc=CAc+1
      }
      if(match($2,"TX"))
      {
         TXp=TXp+$4
         TXc=TXc+1
      }
      if(match($2,"AK"))
       {
         AKp=AKp+$4
         AKc=AKc+1
      }
   }

   END {
      print "state" "\t" "total" "\t" "average"
      print "CA" "\t" CAp "\t" CAp/CAc
      print "TX" "\t" TXp "\t" TXp/TXc
      print "AK" "\t" AKp  "\t" AKp/AKc
   }
'
