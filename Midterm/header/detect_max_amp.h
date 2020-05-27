//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i

/* complete the state machine. */

static unsigned char amp ;
static unsigned char tmpA = 0x00;
void Detect_Max_Amp()
{
    switch(detect_max_amp_state)
    {
        case DMAInit:
            break;
	   
	 case No_amp:
	    	if(tmpA == 0xF8) {
			detect_max_amp_state = Ampdetected;
		}
		else {
			detect_max_amp_state = No_amp;
		}
		break;

	 case Ampdetected:
		if(!(tmpA == 0xF8)){
		       detect_max_amp_state = No_amp;
	       	}
 		else {
			detect_max_amp_state = Ampdetected;
		}
			break;		

        
        default:
            break;
    }
    switch(detect_max_amp_state)
    {
        case DMAInit:
            break;

	  case Ampdetected :
	    amp = 1;
	    quake = 1;
	    PORTB = 0x02;
	    break;

	  case No_amp:
	    amp = 0;
	    quake = 0;
	    PORTB = 0x00;
	    break;

        default:
            break;
    }
}
