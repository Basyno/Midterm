///////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2019 Cadence Design Systems, Inc. All rights reserved worldwide.
//
// The code contained herein is the proprietary and confidential information
// of Cadence or its licensors, and is supplied subject to a previously
// executed license and maintenance agreement between Cadence and customer.
// This code is intended for use with Cadence high-level synthesis tools and
// may not be used with other high-level synthesis tools. Permission is only
// granted to distribute the code as indicated. Cadence grants permission for
// customer to distribute a copy of this code to any partner to aid in designing
// or verifying the customer's intellectual property, as long as such
// distribution includes a restriction of no additional distributions from the
// partner, unless the partner receives permission directly from Cadence.
//
// ALL CODE FURNISHED BY CADENCE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
// KIND, AND CADENCE SPECIFICALLY DISCLAIMS ANY WARRANTY OF NONINFRINGEMENT,
// FITNESS FOR A PARTICULAR PURPOSE OR MERCHANTABILITY. CADENCE SHALL NOT BE
// LIABLE FOR ANY COSTS OF PROCUREMENT OF SUBSTITUTES, LOSS OF PROFITS,
// INTERRUPTION OF BUSINESS, OR FOR ANY OTHER SPECIAL, CONSEQUENTIAL OR
// INCIDENTAL DAMAGES, HOWEVER CAUSED, WHETHER FOR BREACH OF WARRANTY,
// CONTRACT, TORT, NEGLIGENCE, STRICT LIABILITY OR OTHERWISE.
//
////////////////////////////////////////////////////////////////////////////////

#include "bubblesort.h"
#include <iostream>
#include <systemc>
using namespace sc_core;
using namespace std;

// The thread function for the design
void bubblesort::thread1()
{

	// Reset the interfaces
	// Also initialize any variables that are part of the module class here
	{
		HLS_DEFINE_PROTOCOL( "reset" );
		din.reset();
		dout.reset();
		wait();
	}
  
	int i,j,t,k;
//    sc_time p1;
//	sc_time p2;
	
	while( true )
	{
	  //p1 = sc_time_stamp();
	  //cout<<p1<<endl;
      for(k=0;k<100; k++){
        
	    {
	     HLS_DEFINE_PROTOCOL( "input" );
	     input_t in_val = din.get();     // get the next value
	     buffer[k] = in_val;
	     // cout << buffer[k] << endl;
	     wait(5);
        } 
      }	
	  if(k==100){

      for(i = 99; i > 0; i--){
         for(j = 0; j <= i-1; j++){
            if( buffer[j] > buffer[j+1]){  
               
			   t = buffer[j];
               buffer[j] = buffer[j+1];
               buffer[j+1] = t;

			   //p2 = sc_time_stamp();
	           //cout<<p2<<endl;
            }
		  
         }
	
      }
	
	  for(i=0;i<100;i++){
	   {
	    HLS_DEFINE_PROTOCOL( "output" ); 
	    output_t out_val = buffer[i];  // process it
	    wait(5);
	    dout.put( out_val );           // output the result
	   }

	  }
	
	}	
	
	
	}
	
}
