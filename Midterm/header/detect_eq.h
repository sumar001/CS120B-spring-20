//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i



/*complete the state machine*/

void Detect_EQ()
{
    switch(detect_eq_state)
    {
        case DEQInit:
            //init variable(s) here.
	    detect_eq_state = NoQuake;
            break;

	   case NoQuake:
	    if(amp > 0)
	    {
		    i = 0;
		    detect_eq_state = Quake;
	    }
	    else {
		    detect_eq_state = NoQuake;
	    }
	    break;

	   case Quake:
	    if(amp <= 0) {
		    i = 0;
		    detect_eq_state = NoQuake;
	    }
	    else {
		    detect_eq_state = Quake;
	    }

        default:
            detect_eq_state = DEQInit;
            break;
    }
    switch(detect_eq_state)
    {
        case DEQInit:
            break;

	   case NoQuake:
	    quake = 0;
	    PORTB = 0x00;
	    break;

	   case Quake:
	    i++;
	    quake = 1;
	    B = 0x02;
		break;
        default:
            break;
    }
}
