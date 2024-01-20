NOEL – New Ollie Electronic Loud-hailer – A better Regatta Countdown Ollie Box 
An Ollie box is a box with air horns to sound signals at predetermined intervals to count down to the start of a sailboat race. 
There are typically two lengths of starting sequences: 3 minute and 5 minute sequences. Both are programmed into this device. The specific horn sequence is determined in advance of the racing, and when the race officials begin the sequence, it counts down and blows horns at various intervals to allow competitors to position themselves along the start line and be ready for the start.
In this Instructable I built on the work done by Instructables user harriken and Chris LaBorde, and Arduino code by Jose Berengueres for Sound_Schedule and Sound_Type_Length and LCD sample code by Mark Bramwellto. 
I built a box for myself, that added features I need when I run sailboat races. I call this a “New Ollie Electronic Loud-hailer” or NOEL after a long-time international judge, race officer, friend and mentor, Noel M. Field Jr. The enhancements include:
•	A button to toggle through the sequence options (press once for a 3- minute sequence, again for the 5-minute, again for the 3-minute), and will audibly (and visually on the display) indicate which sequence is current.
•	An additional wired button to allow the race officer to be a distance from the box – to sight the line, or attend other functions, while having the ability to manually operate the horn at anytime. 
•	Physically, I used a bigger waterproof box. It holds both the horns and corded button when not in use.
This is my very first Arduino project and I have zero electronics experience before I started, so its possible I have done something the hard way, misdescribed, mislabeled or otherwise confused what I did. Sorry for any difficulties this may cause. At the end of the Instructables, I include a section of “Possible Improvements” and a section for “Lessons Learned – don’t make the same mistake I did”
Step 1: Components Needed 
•	Arduino UNO
•	LCD shield (which adds a small display, and some pre-integrated buttons that I found helpful)
•	Horns, air hoses, relay and compressor (bought as a set), plus a longer length of air hose to allow positioning the horns in the best location (high and away from people) Ended up using a more typical Arduino relay because I couldn’t figure out how to wire the one that came in the set.
•	(1) piezo buzzer 
•	Toggle switch to turn power on
•	(3) interrupt buttons (a green, a yellow and a panel switch to manually operate the horn – my manual horn button is lighted and a different size to avoid confusion, “Lighted manual horn button”)
•	In-line push button switch (hand held, second manual horn button attached to wire)
•	(3) screw terminal strips (I call them buses: Power bus, compressor bus and ground bus.)
•	Water-proof panel mount 3-hole power outlet (to connect the wired button remote), and compatible 3 prong male plug
•	12V 7A battery (with charger)
•	Medium/Large waterproof “Pelican-style” equipment box
•	Right-sized waterproof electronics junction box (with clear top) to keep the Arduino safe
Cables, shrink tubes, connectors, solder, misc other stuff common to Arduino projects. (I used U.S. standard 120v plug and receptacle for my wired handheld button, so I can use any standard 3-prong extension cord to extend the length. And, I used lengths of spare 3-wire extension cord as the internal wiring where possible/appropriate for ruggedness and waterproof connections.)

Step 2: How to Charge 
1.	Charge the battery when needed: attach charger as designed to battery. (see note “Possible Improvement” 1(PI1)) 

Step 3: How to Use 
1.	Attach horn hoses to air nozzle on outside of box. Position/mount horns for best effect. I use spring clamps and long Velcro strips, but small line can also be used. (Avoid using tape)
2.	Attach wired horn button to panel plug on outside of box.
3.	Power on (test manual horn buttons) CAUTION: Horn is loud.
4.	At anytime, use either the lighted horn button on the box, or the wired handheld button to manually activate the horn. (e.g. to call attention to flag signals, as an “alert” signal before starting a sequence, to abandon a race or to indicate a competitor has finished the race.)
5.	Yellow button toggles through sequence options. Once pressed, there will be either 3 or 5 short tones to indicate the currently selected sequence. Current sequence also appears on the LCD screen.
6.	Green button starts the countdown. Once pressed, the sequence will start within a couple of seconds with short tones counting down 5 seconds before horn is activated. Similar tones sound 5 seconds before each horn signal. Time will count down on LCD screen. 
7.	While the sequence is underway, Green button cancels the current sequence.  
 
Step 4: Determine Layout Inside Splash Proof Box
1.	Find a splash proof box with gasket seal. I used a large equipment/camera case about 28”x21”x8” – large enough to hold Arduino, compressor, and components, and to store the horns, air hoses and the manual horn button attached to wire inside when not in use. I have seen “ammo box”, tool boxes and electric tool storage boxes used. 
2.	Determine layout/placement of components – battery, compressor, Arduino inside electronic project box, terminal strips (buses), buttons, penetration for air hose, panel mount outlet, etc.
a.	Consider placement of terminal strips (“buses”) to be sure the screws are easily accessible when all the components are in place (and wires are run). May not be possible to both keep screw accessible and connecting wires “out of harms way”, but that’s the balance.
b.	Consider how the Horn and air hoses will fit in the box and around the electronics, and not get tangled on any wiring. 
c.	Consider how the wired horn button will be stored
d.	Consider how the buttons are accessible from the outside when the box is closed
e.	I also store a compressed air horn and a whistle in the box in case things break.
3.	Consider how wires will run between components – maybe long the edge, or maybe under a rug or foam pad. (See Lesson Learned A (LL.A))
   
Step 5: Programming the Arduino 
1.	To program the Arduino: Download the Arduino IDE to your laptop. Upload the code to the Arduino with a USB cable. Source is here: https://xxx (PI2)    the time units is 100ths of second and the time resolution < 10ms approx.
2.	Stack the LCD shield on the Arduino board. 
3.	TEST:  The ”Left” and “Select” buttons on the shield should properly control the Arduino and display on the LCD: with Arduino plugged into power, push the “left” button on shield, LCD screen should indicate the “3-minute” or “5-minute” sequence. Press button again to cycle back and forth. 
Press the “Select” button. The LCD panel will begin counting down. Press button again to cancel the sequence. 
Step 6: How to Wire 
As noted above, this is my first electronics project, so I have tried to be complete, but may have left out obvious or subtle steps. Sorry. Please use caution when working with live wires. Shorts can damage circuits and may cause injury. Only make final connection to battery when testing or finally complete. (LL.B)
1.	Wire battery 
a.	Connect battery “+” to power button, 
b.	Connect battery “-“ to “ground bus“
c.	Connect power button to “power bus”. 
d.	Connect “power bus” to Arduino VIN
2.	Wire compressor 
a.	Connect compressor “+” to “compressor bus”
b.	Connect compressor “-“ to “ground bus”
c.	Connect the lighted manual horn button between “power bus”, “compressor bus” and “ground bus”
d.	TEST: Lighted manual horn button should be functional: with power on, press button, compressor should activate. 
3.	Wire panel mount 3-hole button outlet
a.	Connect to “power bus”
b.	Connect to “compressor bus”
4.	Build Wired Handheld Button
a.	On a length of extension cord (any convenient length from a foot to 10 feet), wire In-line push button switch to two wires on one end.
b.	Connect other end of extension cord wire to 3-prong male plug using ground and one other prong to prevent completing an electrical circuit if plug is accidentally plugged into a live electrical socket.
c.	TEST: Wired handheld button should be functional: Plug wired handheld button into 3-hole button outlet, turn power on, press button and compressor should activate.
d.	(optional) insert additional 3-prong extension cord of any length between wired handheld button and button outlet to extend length of wired handheld button.
5.	Wire horn relay
a.	Connect Horn relay COMM to “power bus”. 
b.	Connect Horn relay NO (normally open) to “compressor bus”
c.	Connect Horn relay SIG to D11
d.	Connect Horn relay GND to “ground bus”
e.	Connect Horn relay VIN to Arduino 5v
6.	Wire Piezo
a.	Connect Piezo SIG to D2 
b.	Connect Piezo GRND to “ground bus”
c.	Connect Piezo VIN to Arduino 5v
7.	Wire control buttons
a.	Connect the Yellow “Choose” button NC and Comm to the LCD push button 'LEFT'. I soldered curved header pins to the switch solder points on the LCD shield. The spacing made “3-gang” header pin easy to hold in place, with the center pin not attached to anything. (The push button will now activate the LCD 'LEFT' button) (LL.C)
b.	TEST:  “Choose” button should be functional: with power on, press button, Piezo buzzer should indicate 3 or 5 tones, and LCD panel should indicate “3-minute” or “5-minute” sequence. Press button again to cycle back and forth, hearing appropriate number of tones each time. 
c.	Connect the Green “Activate/Cancel” button NC and Comm to the LCD push button 'SELECT' (same approach as “LEFT” button) 
d.	TEST:  “Activate/Cancel” button should be functional: with power on, press button. Within a few seconds, Piezo buzzer should provide 5 short tones before the compressor activates indicating the start of the “3-minute” or “5-minute” sequence and LCD panel count down from 3 or 5 minutes. Press button again to cancel the sequence.
e.	DEBUG: when the sequence is underway, the LCD shows a countdown timer. For each horn scheduled for whole minutes during the sequence (5, 4, 2, 1 and 0 minutes for the 5 minute sequence and 3, 2, 1 and 0 for the 3 minute sequence), the piezo buzzer will count down the last 5 seconds before the horn and a “B” will appear next to the countdown timer. When the Horn is supposed to sound, an “H” will appear next to the countdown timer. This visual clue may help debug the wiring if a sound is not occurring when expected. 
8.	Wiring Diagram
a.	Arduino should have wires attached to:
i.	D11 and D2
ii.	VIN (from the “power bus”)
iii.	5V (to horn relay and piezo)
iv.	GRND (to “ground bus” and horn relay GRND)
b.	Ground bus should have wires attached to:
i.	Battery “-“
ii.	Arduino GRND
iii.	Piezo GRND
iv.	Lighted manual horn button
v.	Compressor “-“
c.	Power bus should have wires attached to:
i.	Power button
ii.	Lighted manual horn button
iii.	3-hole power outlet 
iv.	Arduino VIN
d.	Compressor bus should have wires attached to:
i.	Lighted manual horn button
ii.	3-hole power outlet
iii.	Horn relay
iv.	Compressor “+”
e.	Horn relay bus should have wires attached to:
i.	Arduino 5v
ii.	Arduino GRND
iii.	Arduino D11
iv.	“Power bus”
v.	“Compressor bus”
f.	(Lesson Learned LL.D)
 

Step 7: Install Components in the waterproof box
1.	Install Arduino inside electronic project box, making penetrations for wires. (I had several holes, grouped by component). Consider orientation of the LCD screen in relationship to the open box. (LL.E). I also included the horn relay inside the project box to protect the relay. (PI3)
2.	The specific instructions to install the components in the waterproof box will depend on your layout and the size of your box. But consider:
a.	Wires need to be out of the way. (LL.F)
b.	I used hot glue to attach components to the box. (LL.G) 
3.	I made several holes in the waterproof box (making it slightly less waterproof – each of the 4 switches on the handle side (Choose, Activate/CANX, Manual Horn and Power (on/off)). I mounted the compressor through the right side. I made a penetration for the air hose and for the 3-hole outlet. Size those holes as best as possible to improve fitment.
4.	Piezo buzzer should be installed against the side of the box to allow the box to vibrate and amplify the sound of the buzzer. (LL.G)


(PI) Possible Improvement Notes:
1.	Battery – instead of typical 12v brick, use a “power wheel adaptor” and a compatible electric tool battery and charger. Might be convenient to remove battery and charge it separately. (I’ve never had a battery run out, so a “spare” battery may only be necessary in very high use applications (college team race events, match race events etc.))
2.	 Add additional sequence options: consider adding “Rolling 5 minute” sequence, where the next class of boats start 5 minutes after the last. This may require a “Case” statement in the code, or substituting one sequence for another.
3.	Replace the fragile horn relay with a more robust (water resistant or waterproof) relay.
(LL) Lesson Learned Notes: (i.e. don’t make the same mistake I did)
A.	Complete box layout before completing any wiring. (Its exciting to dig in, but if you are time crunched, doing the layout first will save time “rewiring” when wired components are too close or too far apart.) I rebuilt all the wiring 2 times before my first operational use. And completely rewired and modified the layout after my first season to better optimize internal layout. I should have drafted a more formal wiring diagram early in the process. I started by hand drawing the wiring on a big piece of construction paper. Eventually I used Powerpoint, because I am pretty fluent. Its not a perfect tool, but I didn’t have to learn a new application. I made several versions – simplifying the layout in PPT, and that helped me simplify the eventual “as-built” layout, too.  If you are familiar with Powerpoint, “connectors” are not great for wiring diagrams… they reset whenever you move a connected component. Eventually I created segmented mockups of 2- and 3-strand wires, with segments that connect at different points around small circle “joints”. I could move the joints, and all the “wires” connected to the joint would realign in close parallel. Then I could connect the end “strands” to the electrical components. Moving a component still required repositioning the joints, but it would move all the connected wires together. 
B.	The use of “D2” and “D11” for the Piezo and Horn relay are easily configurable in the code. They are convenient, but may not be the MOST convenient for your internal box layout. Consider and test. On my LCD shield, it was difficult to identify D11, and then difficult to attach to it. So I needed to solder a header pin to a solder point on the shield. Not impossible, but I realized later, I could have chosen a more accessible pin. 
C.	The instructions I followed suggested soldering wires straight to the solder points of the selector buttons. That made me uncomfortable – I was concerned I might use too much heat and melt the connection on the board. It took me a long time to convince myself that it was OK to soldered curved header pins to the selector buttons on the shield. Worked great once I committed.
D.	In my draft wiring diagram, I initially created a “5v bus” that would have had a single wire to Arduino 5v and wires to the Horn Relay GRND and the Piezo GRND. But as I reviewed it, I realized that it didn’t really simplify the wiring. And if the bus was outside the project box, it would require more penetrations of the project box (5v out, then a 5v back in to attach to the horn relay. I decided to split the 5v wire inside the project box, to power the Horn relay and then exit the box to power the Piezo buzzer. I also considered moving the horn relay outside the project box: that would have reduced the wires penetrating the box, but the relay looked too vulnerable to water and jostling. I would make a different decision with a more robust relay housing. (PI3)
E.	For some reason, I thought it would be better to put the holes in the clear top of my box. However, that put wires in the way of the lid whenever I opened the project box. I also had to put enough slack in the wires to allow the lid to be moved out of the way. The slack wire needs to be pushed back inside the box whenever I close the lid. Next time, I will make penetrations on the sides of the project box. 
F.	I installed my wires along the sides, mostly the handle edge. Only later did I consider installing wires along the floor of the box, and then covering the wires with a fitted section of carpet. Certainly, easier to install, possibly easier to maintain (wires would be more easily accessible) and excess wire length can be more easily “hidden” and out of the way. 
G.	I have seen other implementations where components are attached by straps or screws to a fitted piece of plywood. And, once fully installed and tested, the board is placed in the box. (Bevel the edges of the plywood to ensure a better fit in a box with rounded corners.) This seems like an excellent and convenient approach, I should have done it this way!
H.	I initially installed the piezo inside my first project box, a plastic food storage box. But it wasn’t loud enough to hear when the waterproof case was closed. Eventually I found I needed to attach the piezo to the side of the case, and that dramatically amplified the buzzer sound. That installation also required (3) additional wires to penetrate the project box. 
 
