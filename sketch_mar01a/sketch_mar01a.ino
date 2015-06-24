float tempC = 0;                                                 // Variable for holding Celcius temp (floating for decimal points precision)
float tempf = 0;                                                 // variable for holding Fareghneit temp
int tempPin = 0;                                                 // Declaring the Analog input to be 0 (A0) of Arduino board.
float samples[8];                                                // Array to hold 8 samples for Average temp calculation
float maxi = 0,mini = 100;                                       // Max/Min temperature variables with initial values. LM35 in simple setup only measures Temp above 0.
int i;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);  

}

void loop() {
  Serial.println("");                                            // Blank line for spacing in the serial monitor
Serial.println("You are looking at a project built by WWC.");  // Print text to Serial monitor
Serial.print("Feal free to use and modife as needed.");
Serial.println("");                                            // Blank line for spacing in the serial monitor
Serial.print("LM35 Raw data: ");                               // Print text to Serial monitor 
Serial.println(analogRead(tempPin));                           // Displays on serial monitor the sampled value before conversion to real Temperature reading
 
                                                               // Start of calculations FOR loop.
for(i = 0;i<=7;i++){                                           // gets 8 samples of temperature
samples[i] = ( 4.4 * analogRead(tempPin) * 26) / 1024.0;    // conversion math of tmp36GZ sample to readable temperature and stores result to samples array. 

                                                             
                                                                                                                            
                                                             
Serial.println(samples[i]);                                    // Print samples [i] to sertiual monitor                                            
                                                                                                                        
                                                               // ( Serial note: line 1 is the second row, since counting begins with 0):                                           // Set Serial cursor position (column 0, row 0)
Serial.print("Current Temp is: ");                                // Print text to Serial
                                           // Set Serial cursor position (column 1, row 1)
Serial.print("  Celcius   ");                                     // Print text to Serial
                                         // Set Serial cursor position (column 12, row 1)
Serial.print(samples[i]);                                         // print current Temp sample to Serial
tempC = tempC + samples[i];                                    // do the addition for average temperature
delay(800);                                                    // wait 800ms

}                                                              // END of FOR loop

Serial.println("");                                            // Blank line for spacing in the serial monitor
Serial.println("");                                            // Blank line for spacing in the serial monitor
tempC = tempC/8.0;                                             // calculated the averare of 8 samples in Celcius

tempf = (tempC * 9)/ 5 + 32;                                   // converts to fahrenheit

if(tempC > maxi) {maxi = tempC;}                               // set max temperature
if(tempC < mini) {mini = tempC;}                               // set min temperature

                                                               // Send Results to Serial Monitor
Serial.println("New measurement:");
Serial.print(" Average Temperature in Celcius is " );          // Print text to Serial monitor
Serial.println(tempC);//send the data to the computer          // Send the data to the computer
Serial.print(" Average Temperature in Farenait is " );         // Print text to Serial monitor
Serial.println(tempf);//send the data to the computer          // Send the data to the computer
Serial.print(" MAX Temperature in Celcius is " );              // Print text to Serial monitor
Serial.println(maxi);//send the data to the computer           // Send the data to the computer
Serial.print(" MIN Temperature in Celcius is " );              // Print text to Serial monitor
Serial.println(mini);//send the data to the computer           // Send the data to the computer

                                                                  // Set Serial cursor position (column 0, line 1)
Serial.print(" Fahrenheit ");                                            // Set Serial cursor position (column 12, line 1)
Serial.print(tempf);                                              // Send the data to the Serial

delay(6000);                                                   // Wait 3 seconds to display the Fahrenheit temp and 3 seconds to display results to Serial screen befor starting the loop again = 6 seconds.
tempC = 0;                                                     // Set tempC to 0 so calculations can be done again
}


