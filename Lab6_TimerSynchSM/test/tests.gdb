# Test file for "Lab6_TimerSynchSM"


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

# Example test:
#test "PINA: 0x00, PINB: 0x00 => PORTC: 0"
# Set inputs
#setPINA 0x00
#setPINB 0x00
# Continue for several ticks
#continue 2
# Set expect values
#expectPORTC 0
# Check pass/fail
#checkResult

# Add tests below
test "Counter starts at 7.. PINA: 0xFF => PORTB: 0x07"
 setPINA 0xFF
 timeContinue
 expectPORTB 0x07
 checkResult

test "Pressing Increment.. PINA: 0xFE  => PORTB: 0x08"
 setPINA 0xFE
 timeContinue
 expectPORTB 0x08
 checkResult

 #Still Pressing and 1500ms has passed
test "PINA: 0xFE => PORTB: 0X09"
 setPINA 0xFE
 timeContinue
 expectPortB 0x09
 checkResult

 #Releasing
test "PINA: 0xFF => PORTB: 0x09"
 setPINA 0xFF
 timeContinue 
 expectPORTB 0x09
 checkResult

 #Pressing Decrement
test "PINA: 0xFD => PORTB: 0x08"
 setPINA 0xFD
 timeContinue
 expectPORTB 0x08
 checkResult

#Still pressing and 1500ms has passed
test "PINA: 0xFD => PORTB: 0x07"
 setPINA 0xFD
 timeContinue
 expectPORTB 0x07
 checkResult

 #Releasing (Letting Go)
test "PINA: 0xFF => PORTB: 0x07"
 setPINA 0xFF
 timeContinue
 expectPORTB 0x07
 checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
