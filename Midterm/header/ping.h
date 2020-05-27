
//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i



/*complete the state machine*/
unsigned char i;
unsigned char low;
unsigned char hight; //duty cycle * period

void Ping()
{
    switch(ping_state)
    {
        case PInit:
		ping_state = Low;
            break;

	   case High:
	    	if(i > 10) {
			i = 0;
			ping_state = Low;
		}
		else {
			ping_state = High;
		}
	    		break;

	   case Low:
		if( i > 90 ) {
			i = 0;
			ping_state = High;
		}
		else {
			ping_state = Low;
		}
		break;

        default:
            ping_state = PInit;
            break;
    }
    switch(ping_state)
    {
        case PInit:
            break;

	   case High:
	     B = 0x01;
	     break;

	   case Low:
	     B = 0x00;
	     break;

        default:
            break;
    }
}
