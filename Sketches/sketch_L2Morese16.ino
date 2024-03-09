/*
  Morse code sketch created with the help from ChatGPT-4, 
  2024.03.03 
  Arduino UNO R4 WiFi

  David Haworth, WA9ONY
  https://github.com/WA9ONY/Arduino-Homework/blob/main/README.md#L2
  https://www.youtube.com/@WA9ONYHomework
  
  https://openai.com/
  https://youtu.be/S1NJJRpWHpA?si=_ztm3pw92w-hp72G
  https://en.wikipedia.org/wiki/Morse_code_abbreviations
  https://www.arrl.org/learning-morse-code

*/

/*
    WPM to unitTime Table
    This table shows the relationship between Words Per Minute (WPM) and the corresponding
    value of unitTime in milliseconds for Morse code transmission.

    | WPM | unitTime (ms) |
    |-----|---------------|
    | 3   | 400.0         |
    | 4   | 300.0         |
    | 5   | 240.0         |
    | 6   | 200.0         |
    | 7   | 171.43        |
    | 8   | 150.0         |
    | 9   | 133.33        |
    | 10  | 120.0         |
    | 11  | 109.09        |
    | 12  | 100.0         |
    | 13  | 92.31         |
    | 14  | 85.71         |
    | 15  | 80.0          |
    | 16  | 75.0          |
    | 17  | 70.59         |
    | 18  | 66.67         |
    | 19  | 63.16         |
    | 20  | 60.0          |
    | 21  | 57.14         |
    | 22  | 54.55         |
    | 23  | 52.17         |
    | 24  | 50.0          |
    | 25  | 48.0          |
    | 26  | 46.15         |
    | 27  | 44.44         |
    | 28  | 42.86         |
    | 29  | 41.38         |
    | 30  | 40.0          |
*/


////////////////////Library includes and defines/////////////////////////////////////////

#include <Arduino.h>

////////////////////Declarations/////////////////////////////////////////

const int ledPin = 13; // LED connected to digital pin 13

const int netArraySize = 3;
const int callSignsArraySize = 20;
const int lettersArraySize = 3;
const int punctuationsArraySize = 7;
const int prosignsArraySize = 1;
const int LunaArraySize = 16;

const int countryArraySize = 194;
const int numbersArraySize = 7;

bool farnsworthMode = false;

int unitTime = 60; // Base time unit in milliseconds for speed adjustment
int sideToneFreq = 750;
int farnsworthSpace = 2;  // 2 bit more spacing
int repeaterIndex = 0;

int netIndex = 0;
int lettersIndex = 0;
int LunaIndex = 0;

int qsoIndex = 0;

char messageQST[] = "QST DE WA9ONY ";  // QST
char messageEnd[] = "DE WA9ONY K ";  // QST

char messageText[] = "ABCDEFGHIJKLMNOPQRSTUVXYZ "; // Test alphanumeric characters
char messageTextSmall[] = "abcdefghijklmnopqrstuvwxyz "; // Test small alphanumeric characters

char messagePun[] = ".,?\\!()/&:;=+-_$@\" ";  // Punctuation test
char messagePun1[] = "..... ,,,,, ????? \\\\\\\\\\ !!!!! ";  // Punctuation test
char messagePun2[] = "((((( ))))) ///// &&&&& ::::: ";  // Punctuation test
char messagePun3[] = ";;;;; ===== +++++ ----- ";  // Punctuation test
char messagePun4[] = "_____ $$$$$ @@@@@ \"\"\"\"\" ";  // Punctuation test

char messageNum[] = "1234567890 "; // Numbers test
char messagePi[] =  "3.14159 26535 89793 23846 26433 83279 50288 41971 69399 37510";
char messageE[] =   "2.71828 18284 59045 23536 02874 71352 66249 77572 47093 69995";
char messageSqrt2[] =  "1.41421 35623 73095 04880 16887 24209 69807 85696 71875 37694";  
char messageSqrt3[] =  "1.73205 08075 68877 29352 74463 41505 87236 69428 05253 81038";


////////////////////Arrays/////////////////////////////////////////

// A  Morse code net message
const char* net[netArraySize] = {
"QST QST QST DE WA9ONY MORSE CODE PRACTICE ON SUNDAY AT 1900 ON WA7ABU REPEATER 145.290 MHZ ~",
"~ SPEED IS 10 WPM WITH FARNSWORTH SPACING ~ SIDE TONE 750 HZ ~ DE WA9ONY ]",
"~ CHECK YOU RECEIVING TEXT BY GOING TO WA9ONY AT QRZ.COM ~  DE WA9ONY ]"
};

// A  Morse code letters
const char* letters[lettersArraySize] = {
"A B C D E F G H I J K L M N O P Q R S T U V X Y Z",
"ABCDEFGHIJKLMNOPQRSTUVXYZ",
"abcdefghijklmnopqrstuvwxyz"
};

// Numbers
const char* numbers[numbersArraySize] = {
"12345 67890 09876 54321", 
"1 2 3 4 5 6 7 8 9 0 0 9 8 7 6  5 4 3 2 1", 
"299,792,458",                                                  // 1 to 0
"3.14159 26535 89793 23846 26433 83279 50288 41971 69399 37510",  // pi
"2.71828 18284 59045 23536 02874 71352 66249 77572 47093 69995",  // e
"1.41421 35623 73095 04880 16887 24209 69807 85696 71875 37694",  // square root of 2
"1.73205 08075 68877 29352 74463 41505 87236 69428 05253 81038"   // square root of 3
};

// Punctuation
const char* punctuations[punctuationsArraySize] = {
".,?\\!()/&:;=+-_$@\" ", 
". , ? \\ ! ( ) / & : ; = + - _ $ @ \"",               // Morse code punctuation 
".. ,, ?? \\\\ !! (( )) // && :: ;; == ++ -- __ $$ @@ \"\"",  
"..... ,,,,, ????? \\\\\\\\\\ !!!!! ",  // .,?\!
"((((( ))))) ///// &&&&& ::::: ",       // ()/&:
";;;;; ===== +++++ ----- ",             // ;=+-
 "_____ $$$$$ @@@@@ \"\"\"\"\" "        // _$@"
};

// Prosigns
const char* prosigns[prosignsArraySize] = {
"~ ] #"
};

// A predefined array of call signs 
const char* callSigns[callSignsArraySize] = {
  "WA9ONY",  "K7BBY", "K7CAO", "K7LAP", "K7JCD", "KA7VMX", "KC2AIW", "KE7BJQ", "KF5ZBY", "KG7CGK", 
  "KG7GDB", "KJ7ZFF", "KK7OAX", "KK7OR", "NW7OR", "W0EDF", "W1ARK", "W7LIN", "WA7ABU", "W7CCM"
};

// QSO message
const char* qso[5] = {
"W7CCM DE WA9ONY GE OM TNX FER CALL UR RST 589 589 QSB QSB OP DAVID DAVID BTU W7CCM DE WA9ONY K",
"W7CCM DE WA9ONY QTH CAMAS, WA  CAMAS,  CAMAS, WA  CAMAS,WA BTU W7CCM DE WA9ONY K",
"W7CCM DE WA9ONY R R FB RIG ICON IC-9700 ANT VERT UP 20 FT BTU W7CCM DE WA9ONY K",
"W7CCM DE WA9ONY R R FB WX SNOWING WITH 4 INCHES BTU W7CCM DE WA9ONY K",
"W7CCM DE WA9ONY R R FB TNX FER QSO EQSL GL CU AGN 73 W7CCM DE WA9ONY EE"
};

const char* qCodesSig[3] = {
"QRM",
"QRN",
"QSB"
};

// https://en.wikipedia.org/wiki/Q_code
// https://www.skccgroup.com/member_services/beginners_corner/
const char* qCodes[20] = {
"QRL, Are you busy?",
"QRG, What's my exact frequency?",
"QRM, Are you being interfered with?",
"QRN, Are you troubled by static?",
"QRO, Shall I increase transmitter power?",
"QRP, Shall I decrease transmitter power?",
"QRQ, Shall I send faster?",
"QRS, Shall I send more slowly?",
"QRT, Shall I stop sending?",
"QRU, Have you got anything for me?",
"QRV, Are you ready?",
"QRX, When will you call me again?",
"QRZ, Who is calling me?",
"QSB, Is my signal fading?",
"QSL, Can you acknowledge receipt?",
"QSO, Can you communicate with ... direct or by relay?",
"QST, Should I repeat the prior message to all amateurs I contact?"
"QSY, Shall I change to another frequency?",
"QTH, What's your location?",
"QTR, What's the correct time?"
};

const char* greeting[2] = {
"GM",
"GE"
};

// https://en.wikipedia.org/wiki/Morse_code_abbreviations
// https://www.skccgroup.com/member_services/beginners_corner/
const char* abbreviations[21] = {
"AGN, Again",
"BURO, Bureau (for QSL cards)",
"B4, Before",
"BW, Best wishes",
"C, Yes (Affirmative)",
"CL, Going off air (Clear)",
"CONDX, Conditions",
"CPI, Copy",
"CU, See You",
"GE, Good Evening",
"GG, Going",
"GM, Good Morning",
"OM, Old Man (Term of endearment for a male operator)",
"PSE, Please",
"R, Received",
"TNX, Thanks",
"TU, Thank You",
"VY, Very",
"YL, Young Lady (Term of endearment for a female operator)",
"XYL, Ex-Young Lady (Wife of an operator)",
"WX, Weather" // The last element as per your example
};

// A predefined array of pangrams, all the letters of the alphabet.
const char* pangrams[22] = {
"The quick brown fox jumps over a lazy dog.",
"Pack my box with five dozen liquor jugs.",
"Jinxed wizards pluck ivy from the big quilt.",
"The five boxing wizards jump quickly.",
"How vexingly quick daft zebras jump!",
"Quick zephyrs blow, vexing daft Jim.",
"Sphinx of black quartz, judge my vow.",
"Two driven jocks help fax my big quiz.",
"Public junk dwarves quiz mighty fox.",
"Five quacking zephyrs jolt my wax bed.",
"The jay, pig, fox, zebra, and my wolves quack!",
"Vexed nymphs go for quick waltz job.",
"Glib jocks quiz nymph to vex dwarf.",
"Jackdaws love my big sphinx of quartz.",
"Quickly befriending the jovial wizard makes Pax's life cozy.",
"Vexing fjord nymphs quiz blackjack whiz.",
"Mr. Jock, TV quiz PhD, bags few lynx.",
"Jump by vow of quick, lazy strength in Oxford.",
"The quick onyx goblin jumps over the lazy dwarf.",
"Crazy Frederick bought many very exquisite opal jewels.",
"Sixty zippers were quickly picked from the woven jute bag."
};

// A predefined array of call signs 
const char* MarionRepeaters[17] = {
"145.1900 WA7ABU",
"145.2900 WA7ABU",
"145.4900 AB7BS",
"146.8600 W7SRA",
"147.3400 W7SAA",
"440.0500 K7RTL",
"440.2750 AC7RF",
"440.7250 KB7PPM",
"440.8625 KB7PPM",
"441.1750 W7DTV",
"441.2750 W7SRA",
"441.3750 AB7F",
"442.9750 KB7APU",
"443.1750 AD7ET",
"443.7250 W7SRA",
"444.2500 W7SAA",
"444.9500 WA7ABU"
};


// A predefined array of names 
const char* names[101] = {
// Boys
 "Aiden", "Alexander", "Anthony", "Asher", "Benjamin",
 "Carter", "Charles", "Christopher", "Daniel", "David",
 "Dylan", "Elijah", "Ethan", "Ezra", "Gabriel",
 "Grayson", "Henry", "Hudson", "Isaac", "Jack",
 "Jackson", "Jacob", "James", "Jayden", "John",
 "Joseph", "Josiah", "Julian", "Leo", "Levi",
 "Liam", "Lincoln", "Logan", "Lucas", "Luke",
 "Mason", "Mateo", "Matthew", "Maverick", "Michael",
 "Noah", "Oliver", "Owen", "Samuel", "Sebastian",
 "Theodore", "Thomas", "William", "Wyatt", "Zachary",
// Girls
 "Abigail", "Amelia", "Aria", "Aubrey", "Ava", "Avery",
 "Bella", "Brooklyn", "Camila", "Camille", "Charlotte", "Chloe",
 "Claire", "Delilah", "Eleanor", "Elizabeth", "Ella",
 "Emily", "Emma", "Eva", "Evelyn", "Gianna", "Grace",
 "Hannah", "Harper", "Isabella", "Ivy", "Jasmine",
 "Layla", "Leah", "Lily", "Luna", "Madison",
 "Mia",  "Mila", "Natalie", "Nora", "Olivia", "Penelope",
 "Riley", "Savannah", "Scarlett", "Sofia", "Sophia",
 "Stella", "Sue", "Susan", "Victoria", "Violet", "Zoe", "Zoey"
};

// A predefined array of town names 
const char* towns[98] = {
 // Marion county
 "Aumsville", "Aurora", "Detroit", "Donald", "Gates",
 "Gervais", "Hubbard", "Idanha", "Jefferson", "Keizer",
 "Mt. Angel", "St. Paul", "Salem", "Scotts Mills", "Silverton",
 "Stayton", "Sublimity", "Turner", "Woodburn", "Mill City",
 // Washington county
 "Aloha", "Banks", "Beaverton", "Bethany", "Bull Mountain",
 "Cedar Hills", "Cedar Mill", "Cherry Grove", "Cornelius", "Durham",
 "Forest Grove", "Garden Home-Whitford", "Gaston", "Hillsboro", "King City",
 "Lake Oswego", "Marlene Village", "Metzger", "North Plains", "Oak Hills",
 "Portland", "Raleigh Hills", "Rivergrove", "Rockcreek", "Sherwood",
 "Tigard", "Tualatin", "West Haven-Sylvan", "West Slope",
 // Poke county 
 "Dallas", "Falls City", "Independence", "Monmouth", "Salem", "Willamina",
 "Airlie", "Ballston", "Bethel", "Bethel Heights", "Black Rock", "Bridgeport", 
 "Broadmead", "Brush College", "Buell", "Buena Vista", "Chapman Corner", 
 "Ellendale", "Fir Villa", "Hopville", "Lewisville", "Lincoln", "McCoy", 
 "Modeville", "Oakdale", "Parker", "Pedee", "Perrydale", "Salemtowne", 
 "Stapleton", "Suver", "Valley Junction", "West Salem", "Zena",
 // Linn county
 "Albany", "Brownsville", "Cascadia", "Crabtree", "Crawfordsville", "Foster", "Halsey", "Harrisburg", "Lebanon", "Lyons",
 "Mill City", "Scio", "Shedd", "Sweet Home", "Tangent"
};

// A predefined array of state names 
const char* states[50] = {
  "Alabama", "Alaska", "Arizona", "Arkansas", "California",
  "Colorado", "Connecticut", "Delaware", "Florida", "Georgia",
  "Hawaii", "Idaho", "Illinois", "Indiana", "Iowa",
  "Kansas", "Kentucky", "Louisiana", "Maine", "Maryland",
  "Massachusetts", "Michigan", "Minnesota", "Mississippi", "Missouri",
  "Montana", "Nebraska", "Nevada", "New Hampshire", "New Jersey",
  "New Mexico", "New York", "North Carolina", "North Dakota", "Ohio",
  "Oklahoma", "Oregon", "Pennsylvania", "Rhode Island", "South Carolina",
  "South Dakota", "Tennessee", "Texas", "Utah", "Vermont",
  "Virginia", "Washington", "West Virginia", "Wisconsin", "Wyoming"
};

const char* capitals[50] = {
  "Montgomery", "Juneau", "Phoenix", "Little Rock", "Sacramento",
  "Denver", "Hartford", "Dover", "Tallahassee", "Atlanta",
  "Honolulu", "Boise", "Springfield", "Indianapolis", "Des Moines",
  "Topeka", "Frankfort", "Baton Rouge", "Augusta", "Annapolis",
  "Boston", "Lansing", "Saint Paul", "Jackson", "Jefferson City",
  "Helena", "Lincoln", "Carson City", "Concord", "Trenton",
  "Santa Fe", "Albany", "Raleigh", "Bismarck", "Columbus",
  "Oklahoma City", "Salem", "Harrisburg", "Providence", "Columbia",
  "Pierre", "Nashville", "Austin", "Salt Lake City", "Montpelier",
  "Richmond", "Olympia", "Charleston", "Madison", "Cheyenne"
};

const char* countries[countryArraySize] = {
"Afghanistan", "Albania", "Algeria", "Andorra", "Angola",
"Antigua and Barbuda", "Argentina", "Armenia", "Australia", "Austria",
"Azerbaijan", "Bahamas", "Bahrain", "Bangladesh", "Barbados",
"Belarus", "Belgium", "Belize", "Benin", "Bhutan",
"Bolivia", "Bosnia and Herzegovina", "Botswana", "Brazil", "Brunei",
"Bulgaria", "Burkina Faso", "Burundi", "Cabo Verde", "Cambodia",
"Cameroon", "Canada", "Central African Republic", "Chad", "Chile",
"China", "Colombia", "Comoros", "Congo, Democratic Republic of the", "Congo, Republic of the",
"Costa Rica", "Croatia", "Cuba", "Cyprus", "Czech Republic",
"Denmark", "Djibouti", "Dominica", "Dominican Republic", "East Timor (Timor-Leste)",
"Ecuador", "Egypt", "El Salvador", "Equatorial Guinea", "Eritrea",
"Estonia", "Eswatini", "Ethiopia", "Fiji", "Finland",
"France", "Gabon", "Gambia", "Georgia", "Germany",
"Ghana", "Greece", "Grenada", "Guatemala", "Guinea",
"Guinea-Bissau", "Guyana", "Haiti", "Honduras", "Hungary",
"Iceland", "India", "Indonesia", "Iran", "Iraq",
"Ireland", "Israel", "Italy", "Ivory Coast (Côte d'Ivoire)", "Jamaica",
"Japan", "Jordan", "Kazakhstan", "Kenya", "Kiribati",
"North Korea", "South Korea", "Kosovo", "Kuwait", "Kyrgyzstan",
"Laos", "Latvia", "Lebanon", "Lesotho", "Liberia",
"Libya", "Liechtenstein", "Lithuania", "Luxembourg", "Madagascar",
"Malawi", "Malaysia", "Maldives", "Mali", "Malta",
"Marshall Islands", "Mauritania", "Mauritius", "Mexico", "Micronesia",
"Moldova", "Monaco", "Mongolia", "Montenegro", "Morocco",
"Mozambique", "Myanmar", "Namibia", "Nauru", "Nepal",
"Netherlands", "New Zealand", "Nicaragua", "Niger", "Nigeria",
"North Macedonia", "Norway", "Oman", "Pakistan", "Palau",
"Panama", "Papua New Guinea", "Paraguay", "Peru", "Philippines",
"Poland", "Portugal", "Qatar", "Romania", "Russia",
"Rwanda", "Saint Kitts and Nevis", "Saint Lucia", "Saint Vincent and the Grenadines", "Samoa",
"San Marino", "Sao Tome and Principe", "Saudi Arabia", "Senegal", "Serbia",
"Seychelles", "Sierra Leone", "Singapore", "Slovakia", "Slovenia",
"Solomon Islands", "Somalia", "South Africa", "South Sudan", "Spain",
"Sri Lanka", "Sudan", "Suriname", "Sweden", "Switzerland",
"Syria", "Taiwan", "Tajikistan", "Tanzania", "Thailand",
"Tonga", "Trinidad and Tobago", "Tunisia", "Turkey", "Turkmenistan",
"Tuvalu", "Uganda", "Ukraine", "United Arab Emirates", "United Kingdom",
"United States", "Uruguay", "Uzbekistan", "Vanuatu", "Venezuela",
"Vietnam", "Yemen", "Zambia", "Zimbabwe"
};


const char* LunaPoem[LunaArraySize] = {
"Luna the Aussie Ham, with headphones on,",
"Mic attached, she's always strong.",
"At her radio station, she sits with glee,",
"Ready to chat, for all to see.",

"From mountains high, to valleys deep,",
"Luna's voice travels far, where secrets keep.",
"With paws on the key, and voice so clear,",
"She connects with friends, both far and near.",

"Luna the Aussie Ham, with spirit bright,",
"She's a ham operator, filled with delight.",
"With passion and skill, she shares her love,",
"Of radio waves, from up above.",

"So raise a glass, to Luna the Ham,",
"The best darn ham operator, in the land.",
"May her signals reach, far and wide,",
"Bringing joy and cheer, with every stride."
};

////////////////////Functions/////////////////////////////////////////

// Function to print WPM from unitTime
void printWPMFromUnitTime(int unitTimeMs) {
  float unitTimeSeconds = unitTimeMs / 1000.0; // Convert milliseconds to seconds
  float elementsPerWord = 50.0; // Standard "PARIS " word length in elements
  float wpm = (1 / (unitTimeSeconds * elementsPerWord)) * 60;
  Serial.print("Morse code speed is ");
  Serial.print(wpm, 0); 
  Serial.println(" words per minute (WPM).");
}

void getWPM() {
  while (Serial.available() != 0) {
  Serial.read(); 
  }
  Serial.println("Enter WPM (3-40):");
  while (true){
  if (Serial.available() > 0) {
    int wpm = Serial.parseInt(); // Read the next integer from the Serial Monitor
    if (wpm >= 3 && wpm <= 40) {
      // Valid WPM input
      unitTime = calculateUnitTime(wpm);
      Serial.print("WPM: ");
      Serial.print(wpm);
      Serial.print(" - Unit Time (ms): ");
      Serial.println(unitTime);
      goto endOfLoop;
    } else {
      // Invalid WPM input
      Serial.println("Invalid input. Please enter a value between 3 and 40.");
    }
  }
  }
  endOfLoop:;
  Serial.read();
}

int calculateUnitTime(int wpm) {
  // Formula to calculate unitTime from WPM
  float unitTimeSeconds = (60.0 / (wpm * 50.0));
  return int(unitTimeSeconds * 1000); // Convert seconds to milliseconds and return
}

// Function to list states from start to end
String listMarionRepeaters(int start, int end) {
  String repeatersList = "";
  for (int i = start-1; i < end && i < 17; i++) {
    repeatersList += MarionRepeaters[i];
    if (i < end-1 && i < 16) { // Check to avoid adding a comma at the end
      repeatersList += ", ";
    }
  }
  return repeatersList;
}

String AllMarionRepeaters() {
int repeaterChoice = repeaterIndex; // 4
String Repeaters;
repeaterChoice++;
repeaterIndex++;
switch (repeaterChoice) {
      case 1:
        listMarionRepeaters(1, 5);
          Repeaters = AllMarionRepeaters();
          sendMorseMessage(Repeaters.c_str());  // Send Punctuation
        break;
      case 2:
        listMarionRepeaters(6, 10);
        break;
      case 3:
        listMarionRepeaters(11, 15);
        break;
      case 4:
        listMarionRepeaters(16, 17);
        break;
      default:
        Serial.println("Invalid choice. Please try again.");
        Serial.println(repeaterChoice);
        break;
}
}  

// Function to list states from start to end
String listStates(int start, int end) {
  String stateList = "";
  for (int i = start-1; i < end && i < 50; i++) {
    stateList += states[i];
    if (i < end-1 && i < 49) { // Check to avoid adding a comma at the end
      stateList += ", ";
    }
  }
  return stateList;
}

// Function to generate a string of 10 random states
String getRandomStates() {
  String randomStates = "";
  for (int i = 0; i < 10; i++) {
    int index = random(0, 50); // Generate a random index between 0 and 49
    randomStates += states[index];
    if (i < 9) { // Check to avoid adding a comma after the last state
      randomStates += ", ";
    }
  }
  return randomStates;
}

// Function to generate a string of 10 random capitals
String getRandomCapitals() {
  String randomCapitals = "";
  for (int i = 0; i < 10; i++) {
    int index = random(0, 50); // Generate a random index between 0 and 49
    randomCapitals += capitals[index];
    if (i < 9) { // Check to avoid adding a comma after the last state
      randomCapitals += ", ";
    }
  }
  return randomCapitals;
}

// Function to generate a string of 10 random countries
String getRandomCountries() {
  String randomCountries = "";
  for (int i = 0; i < 10; i++) {
    int index = random(0, 195); // Generate a random index between 0 and 194
    randomCountries += countries[index];
    if (i < 9) { // Check to avoid adding a comma after the last state
      randomCountries += ", ";
    }
  }
  return randomCountries;
}

// Function to list states from start to end
String listCallSigns(int start, int end) {
  String callSignsList = "";
  for (int i = start-1; i < end && i < 10; i++) {
    callSignsList += callSigns[i];
    if (i < end-1 && i < 49) { // Check to avoid adding a comma at the end
      callSignsList += ", ";
    }
  }
  return callSignsList;
}

int freeMemory() {
  char top;
  return &top - reinterpret_cast<char*>(malloc(4));
}

void farnsworthStatus(bool mode) {
 Serial.print("Farnsworth mode is ");
 if (mode){
   Serial.println("on.");
   Serial.print("Farnsworth extra character spacing is ");
   Serial.print(farnsworthSpace);
   Serial.println(" times dit width.");
 }
 else {
    Serial.println("off.");
 }
 // Serial.println(farnsworthMode);

}

int printSideTone(int tone) {
  Serial.print("Side tone frequency is ");
  Serial.print(tone);
  Serial.println(" Hz.");
}

int printUnitTime(int ditTime) {
  Serial.print("Morse code dit duration is ");
  Serial.print(ditTime);
  Serial.println(" micro seconds.");
}

int getValidTone() {
  int number = 0;
  bool isValid = false;
  while (!isValid) {
    while (Serial.available() == 0); // Wait for user input
    number = Serial.parseInt(); // Try to parse the input as an integer
    // Check if the number is within the valid range
    if (number >= 20 && number <= 20000) {
      isValid = true;
    } else {
      Serial.println("Invalid input. Please enter a number between 20 and 20,000:");
    }
  }
  return number;
}

int getDitTime() {
  int number = 0;
  bool isValid = false;
  while (!isValid) {
    while (Serial.available() == 0); // Wait for user input
    number = Serial.parseInt(); // Try to parse the input as an integer
    // Check if the number is within the valid range
    if (number >= 1 && number <= 500) {
      isValid = true;
    } else {
      Serial.println("Invalid dit time in uSec. Please enter a number between 1 and 500:");
    }
  }
  return number;
}

// Function to represent a dot
void dot() {
  tone(8, sideToneFreq, unitTime); // Play a 750Hz tone for unitTime on pin 8
  digitalWrite(ledPin, HIGH);
  delay(unitTime);
  digitalWrite(ledPin, LOW);
  delay(unitTime);
}

// Function to represent a dash
void dash() {
  tone(8, sideToneFreq, 3 * unitTime); // Play a 750Hz tone for unitTime on pin 8
  digitalWrite(ledPin, HIGH);
  delay(3 * unitTime);
  digitalWrite(ledPin, LOW);
  delay(unitTime);
}

// Blink Morse code for a given character
void blinkMorse(char character) {
  switch (character) {
    case 'A': case 'a': dot(); dash(); break;
    case 'B': case 'b': dash(); dot(); dot(); dot(); break;
    case 'C': case 'c': dash(); dot(); dash(); dot(); break;
    case 'D': case 'd': dash(); dot(); dot(); break;
    case 'E': case 'e': dot(); break;
    case 'F': case 'f': dot(); dot(); dash(); dot(); break;
    case 'G': case 'g': dash(); dash(); dot(); break;
    case 'H': case 'h': dot(); dot(); dot(); dot(); break;
    case 'I': case 'i': dot(); dot(); break;
    case 'J': case 'j': dot(); dash(); dash(); dash(); break;
    case 'K': case 'k': dash(); dot(); dash(); break;
    case 'L': case 'l': dot(); dash(); dot(); dot(); break;
    case 'M': case 'm': dash(); dash(); break;
    case 'N': case 'n': dash(); dot(); break;
    case 'O': case 'o': dash(); dash(); dash(); break;
    case 'P': case 'p': dot(); dash(); dash(); dot(); break;
    case 'Q': case 'q': dash(); dash(); dot(); dash(); break;
    case 'R': case 'r': dot(); dash(); dot(); break;
    case 'S': case 's': dot(); dot(); dot(); break;
    case 'T': case 't': dash(); break;
    case 'U': case 'u': dot(); dot(); dash(); break;
    case 'V': case 'v': dot(); dot(); dot(); dash(); break;
    case 'W': case 'w': dot(); dash(); dash(); break;
    case 'X': case 'x': dash(); dot(); dot(); dash(); break;
    case 'Y': case 'y': dash(); dot(); dash(); dash(); break;
    case 'Z': case 'z': dash(); dash(); dot(); dot(); break;

    // Numbers
    case '0': dash(); dash(); dash(); dash(); dash(); break;
    case '1': dot(); dash(); dash(); dash(); dash(); break;
    case '2': dot(); dot(); dash(); dash(); dash(); break;
    case '3': dot(); dot(); dot(); dash(); dash(); break;
    case '4': dot(); dot(); dot(); dot(); dash(); break;
    case '5': dot(); dot(); dot(); dot(); dot(); break;
    case '6': dash(); dot(); dot(); dot(); dot(); break;
    case '7': dash(); dash(); dot(); dot(); dot(); break;
    case '8': dash(); dash(); dash(); dot(); dot(); break;
    case '9': dash(); dash(); dash(); dash(); dot(); break;
  
  // Punctuation
    case '.': dot(); dash(); dot(); dash(); dot(); dash(); break; // Full stop .-.-.-
    case ',': dash(); dash(); dot(); dot(); dash(); dash(); break; // Comma --..--
    case '?': dot(); dot(); dash(); dash(); dot(); dot(); break; // Question mark ..--..
    case '\\': dot(); dash(); dash(); dash(); dash(); dot(); break; // Apostrophe .----.
    case '!': dash(); dot(); dash(); dot(); dash(); dash(); break; // Exclamation mark (non-standard) -.-.--
    case '/': dash(); dot(); dot(); dash(); dot(); break; // Slash -..-.
    case '(': dash(); dot(); dash(); dash(); dot(); break; // Left parenthesis -.--.
    case ')': dash(); dot(); dash(); dash(); dot(); dash(); break; // Right parenthesis (with closing dash) -.--.-
    case '&': dot(); dash(); dot(); dot(); dot(); break; // Ampersand .-...
    case ':': dash(); dash(); dash(); dot(); dot(); dot(); break; // Colon ---...
    case ';': dash(); dot(); dash(); dot(); dash(); dot(); break; // Semicolon -.-.-.
    case '=': dash(); dot(); dot(); dot(); dash(); break; // Equals sign -,,,-
    case '+': dot(); dash(); dot(); dash(); dot(); break; // Plus .-.-.
    case '-': dash(); dot(); dot(); dot(); dot(); dash(); break; // Hyphen or minus -....-
    case '_': dot(); dot(); dash(); dash(); dot(); dash(); break; // Underscore ..--.-
    case '"': dot(); dash(); dot(); dot(); dash(); dot(); break; // Quotation mark .-..-.
    case '$': dot(); dot(); dot(); dash(); dot(); dot(); dash(); break; // Dollar sign (non-standard) ...-..-
    case '@': dot(); dash(); dash(); dot(); dash(); dot(); break; // At sign .--.-.
    case '\'': dot(); dash(); dash(); dash(); dash(); dot(); break; // Single quote .----. 
 

  // Prosigns
    case '~':  dash(); dot(); dot(); dot(); dash(); break; // BT 
    case '`':  break; //  
    case '#':  dot(); dot(); dot(); dot(); dot(); dot(); dot(); dot(); break; //  HH Error
    case '%':  break; //  
    case '^':  break; //  
    case '*':  break; //  
    case '|':  break; //  
    case '[':  break; //  
    case ']':  dot(); dash(); dot(); dash(); dot(); break; //  AR End of transission
    case '{':  break; //  
    case '}':  break; //  
//    case '\'':  break; //  
    case '<':  break; //  
    case '>':  break; //    

    case ' ':              // Handle space between words
      delay(7 * unitTime); // Space between words, longer than between letters
      break;

    default: break; // Handle unsupported characters
  }
  if ( farnsworthMode = true ) {
    delay((3+farnsworthSpace) * unitTime); // Space between letters
    }
    else {
    delay(3 * unitTime); // Space between letters
    }
}

void prosignBT() {
  Serial.print("-BT- ");
  dash(); dot(); dot(); dot(); dash();  // Send BT
  delay(7 * unitTime);   // Send BT
}

String generateRandomString(int type) {
  String characters;
  switch (type) {
    case 1: // Alphanumeric (uppercase + numbers)
      characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,?\\!()/&:;=+-_$@\"";
      break;
    case 2: // Uppercase letters only
      characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
      break;
    case 3: // Numbers only
      characters = "0123456789";
      break;
     case 4: // Punctuation only
      characters = ".,?\\!()/&:;=+-_$@\"";
      break;  
    default:
      // This should not happen
      return "Error";
  }

  String randomString = "";
  for (int i = 0; i < 5; i++) {
    int randomIndex = random(characters.length());
    randomString += characters[randomIndex];
  }

  // Add a space after the five characters
  randomString += " ";
  return randomString;
}

// This function waits for any keyboard input through the Serial Monitor
void waitForInput() {
  Serial.println("Waiting for input...");
  while (!Serial.available()) {
    // Do nothing until a character is received
  }
  // Clear the serial buffer to remove the received character
  while (Serial.available()) {
    Serial.read();
  }
  Serial.println("Input received.");
}

void sendMorseMessage(const char* message) {
  Serial.println(message);  // Print the message to the Serial monitor
  int messageLength = strlen(message);  // Get the length of the message
  for (int i = 0; i < messageLength; i++) {
    Serial.print(message[i]);  // Print each character to the Serial monitor
    blinkMorse(message[i]);  // Blink the Morse code for each character
  }
  Serial.println(" "); 
  delay(7 * unitTime); // Space between messages
}

String getRandomCallSign() {
  String callSign = "";

  // First character: K or W
  if (random(2) == 0) {
    callSign += "K";
  } else {
    callSign += "W";
  }

  // Second character: Any letter A-Z
  callSign += char('A' + random(0, 26));

  // Third character: Any digit 0-9
  callSign += char('0' + random(0, 10));

  // Last three characters: Any letters A-Z
  for (int i = 0; i < 3; i++) {
    callSign += char('A' + random(0, 26));
  }

  return callSign;
}



//////////////////////////////////////////////////////////////////////////
void menuItem1() {
  Serial.println("Send Arduino UNO R4 WiFi lesson 2 homework message SOS");
//  sendMorseMessage(messageSOS);  // Send homework SOS
}

void menuItem3() {
 farnsworthMode = !farnsworthMode;
}


void menuItem4() {
 Serial.println("Please enter a tone number between 20 and 20,000:");
  // Call the function to get a valid number
  sideToneFreq = getValidTone();
  Serial.print("You entered a valid number: ");
  Serial.println(sideToneFreq);
  while (Serial.available() > 0) {
      Serial.read();
  }
}

void menuItem5() {
 Serial.println("Please enter a dit time number between 1 and 500 uSec:");
  // Call the function to get a valid number
  unitTime = getDitTime();
  Serial.print("You entered a valid number: ");
  Serial.println(unitTime);
  while (Serial.available() > 0) {
      Serial.read();
  }
}

void menuItem6() {
  Serial.println("Send square root of 2");
  sendMorseMessage(messageSqrt2);  // Send homework SOS
}

void menuItem7() {
  Serial.println("Send square root of 3");
  sendMorseMessage(messageSqrt3);  // Send homework SOS
}


void menuItem8() {
  Serial.println("Send pi");
  sendMorseMessage(messagePi);  // Send homework SOS
}

void menuItem9() {
  for (int index = 0; index < 21; index++){
    String abbreviation = abbreviations[index];
    sendMorseMessage(abbreviation.c_str());
    prosignBT();
  }
}

void menuItem10() {
  String moreseCharacters;
  Serial.println("Send 5 groups of 5");
  // 1 is text + numbers + punctuation
  // 2 is text
  // 3 is numbers
  // 4 is punctuation
  moreseCharacters = generateRandomString(2)+generateRandomString(2)+generateRandomString(2)+generateRandomString(2)+generateRandomString(2);
  sendMorseMessage(moreseCharacters.c_str());
  moreseCharacters = generateRandomString(3)+generateRandomString(3)+generateRandomString(3)+generateRandomString(3)+generateRandomString(3);
  sendMorseMessage(moreseCharacters.c_str());
  moreseCharacters = generateRandomString(4)+generateRandomString(4)+generateRandomString(4)+generateRandomString(4)+generateRandomString(4);
  sendMorseMessage(moreseCharacters.c_str());
  moreseCharacters = generateRandomString(2)+generateRandomString(3)+generateRandomString(4);
  sendMorseMessage(moreseCharacters.c_str());
  moreseCharacters = generateRandomString(1)+generateRandomString(1)+generateRandomString(1)+generateRandomString(1)+generateRandomString(1);
  sendMorseMessage(moreseCharacters.c_str());
}

void menuItem11() {
  Serial.println("Send Punctuation: . .-.-.-  , --..--  ? ..--..  \\ .----.  ! -.-.--");
  sendMorseMessage(messagePun1);  // Send Punctuation
  Serial.println("Send Punctuation: ( -.--.  ) -.--.-  / -..-.  & .-...  : ---...");
  sendMorseMessage(messagePun2);  // Send Punctuation
  Serial.println("Send Punctuation: ; -.-.-.  = -,,,-  + .-.-.  - -....-");
  sendMorseMessage(messagePun3);  // Send Punctuation
  Serial.println("Send Punctuation: _ ..--.-  $ ...-..-  @ .--.-.  \" .-..-.");
  sendMorseMessage(messagePun4);  // Send Punctuation
}

void menuItem12() {
  Serial.println("Send: QST DE WA9ONY ");
  sendMorseMessage(messageQST);  
  String pangram = pangrams[0];
  Serial.println(pangram);
  sendMorseMessage(pangram.c_str());
  Serial.println("Send: DE WA9ONY K ");
  sendMorseMessage(messageEnd);  
}

void menuItem13() {
  Serial.println("Send: QST DE WA9ONY ");
  sendMorseMessage(messageQST);  
  String pangram = pangrams[1];
  Serial.println(pangram);
  sendMorseMessage(pangram.c_str());
  Serial.println("Send: DE WA9ONY K ");
  sendMorseMessage(messageEnd);  
}

void menuItem14() {
  String pangram = qso[qsoIndex];
  sendMorseMessage(pangram.c_str());
  qsoIndex++;
  if (qsoIndex == 4){ netIndex = 0;}
}

void menuItem15() {  
  String pangram = net[netIndex];
  sendMorseMessage(pangram.c_str());
  netIndex++;
  if (netIndex == 2){ netIndex = 0;}
}

void menuItem16() {  
  String letter = letters[netIndex];
  sendMorseMessage(letter.c_str());
  lettersIndex++;
  if (lettersIndex == 2){ lettersIndex = 0;}
}


void menuItem17() {  
  String prosign = prosigns[0];
  sendMorseMessage(prosign.c_str());
//  lettersIndex++;
//  if (lettersIndex == 2){ lettersIndex = 0;}
}

void menuItem18() { 
  for (int index =0; index < 16; index++){
    menuItem18b();
  }
}   

void menuItem18b() {  
  String Luna = LunaPoem[LunaIndex];
  sendMorseMessage(Luna.c_str());
  LunaIndex++;
  if (LunaIndex == 16){ LunaIndex = 0;}
}



void menuItem16a() {
  Serial.println("Send e");
  sendMorseMessage(messageE);  // Send homework SOS
}

void menuItem17a() {
  Serial.println("Executing Menu Item 1...");
  sendMorseMessage(messageQST);  // Send QST QST DE WA9ONY WA9ONY
  printWPMFromUnitTime(unitTime);
 // sendMorseMessage(messageWPM10);  // Send QST QST DE WA9ONY WA9ONY
   sendMorseMessage(messageText);  // Send test text
 // sendMorseMessage(messageTextSmall);  // Send small test text
  sendMorseMessage(messageNum);  // Send test numbers
  sendMorseMessage(messagePun);  // Send Punctuation 
  sendMorseMessage(messageEnd);  // Send Punctuation 
}

void menuItem18a() {
  String callSigns = listCallSigns(1, 10);
  sendMorseMessage(callSigns.c_str());  // Send Punctuation
  Serial.println("Send: DE WA9ONY K ");
  sendMorseMessage(messageEnd);  // Send Punctuation
}

void menuItem19() {
  Serial.println("Send: DE WA9ONY K ");
  sendMorseMessage(messageEnd);  // Send Punctuation
}

void menuItem20() {
  String tenRandomStates = getRandomStates();
  sendMorseMessage(tenRandomStates.c_str());  // Send Punctuation
  Serial.println("Send: DE WA9ONY K ");
  sendMorseMessage(messageEnd);  // Send Punctuation
}

void menuItem21() {
  String allStates = listStates(1, 10);
  sendMorseMessage(allStates.c_str());  // Send Punctuation
  Serial.println("Send: DE WA9ONY K ");
  sendMorseMessage(messageEnd);  // Send Punctuation
}

void menuItem22() {
  String allStates = listStates(11, 20);
  sendMorseMessage(allStates.c_str());  // Send Punctuation
  Serial.println("Send: DE WA9ONY K ");
  sendMorseMessage(messageEnd);  // Send Punctuation
}

void menuItem23() {
  String allStates = listStates(21, 30);
  sendMorseMessage(allStates.c_str());  // Send Punctuation
  Serial.println("Send: DE WA9ONY K ");
  sendMorseMessage(messageEnd);  
}

void menuItem24() {
  String allStates = listStates(31, 40);
  sendMorseMessage(allStates.c_str());  
  Serial.println("Send: DE WA9ONY K ");
  sendMorseMessage(messageEnd);  
}

void menuItem25() {
  String allStates = listStates(41, 50);
  Serial.println(allStates);
  sendMorseMessage(allStates.c_str());  
  Serial.println("Send: DE WA9ONY K ");
  sendMorseMessage(messageEnd); 
}

void menuItem26() {
  String tenRandomCapitals = getRandomCapitals();
  sendMorseMessage(tenRandomCapitals.c_str());  
  Serial.println("Send: DE WA9ONY K ");
  sendMorseMessage(messageEnd);  
}

void menuItem27() {
  String tenRandomCountries = getRandomCountries();
  sendMorseMessage(tenRandomCountries.c_str());  
  Serial.println("Send: DE WA9ONY K ");
  sendMorseMessage(messageEnd); 
}

void menuItem28() {
  while (Serial.available() == 0) {
    String tenRandomCapitals = getRandomCapitals();
    sendMorseMessage(tenRandomCapitals.c_str());  
    Serial.println("Send: DE WA9ONY K ");
    sendMorseMessage(messageEnd);  
  }
  Serial.read();
}

void menuItem29() {
   String tenRandomCapitals = getRandomCapitals();
   sendMorseMessage(tenRandomCapitals.c_str());  
   Serial.println("Send: DE WA9ONY K ");
   sendMorseMessage(messageEnd); 
   while (true) {
    while (Serial.available() == 0) { }
    while (Serial.available() > 0) { 
      if (Serial.read() == 113) {
        goto endOfLoop;
        }
    }
    tenRandomCapitals = getRandomCapitals();
    sendMorseMessage(tenRandomCapitals.c_str());  
    Serial.println("Send: DE WA9ONY K ");
    sendMorseMessage(messageEnd); 
   }
   endOfLoop:;
   if (Serial.available() > 0) {
    Serial.parseInt(); // Read the choice
    // Clear the Serial buffer
    while (Serial.available() > 0) {
      Serial.read();
    }
   }
     
}

void menuItem30() {
    String callSign = getRandomCallSign();
    sendMorseMessage(callSign.c_str());  
    Serial.println("Send: DE WA9ONY K ");
    sendMorseMessage(messageEnd);  
}

void menuItem31() {
  String ORtowns = towns[97];
  sendMorseMessage(ORtowns.c_str());  
  Serial.println("Send: DE WA9ONY K ");
  sendMorseMessage(messageEnd);  
}


void menuItem32() {
  String name = names[98];
  sendMorseMessage(name.c_str());  
  Serial.println("Send: DE WA9ONY K ");
  sendMorseMessage(messageEnd);  
}

void menuItem33() {
  Serial.println("Press Enter key to exit pangrams.");
  for (int index = 0; index < 22; index++){
    String pangram = pangrams[index];
    sendMorseMessage(pangram.c_str());
    if (Serial.available() > 0) {
      break;
    } 
  prosignBT();
  }
  Serial.read();
}

void menuItem34() {
  for (int index = 0; index < countryArraySize; index++){
    String country = countries[index];
    sendMorseMessage(country.c_str());;
  }
}

void menuItem40() {
  for (int index = 0; index < numbersArraySize; index++){
    String number = numbers[index];
    sendMorseMessage(number.c_str());;
  }
}
void menuItem41() {
  for (int index = 0; index < countryArraySize; index++){
    String country = countries[index];
    sendMorseMessage(country.c_str());;
  }
}

// Send homework SOS
void menuItem99() {
  Serial.println("Send Arduino UNO R4 WiFi lesson 2 homework message SOS");
  for (int index = 0; index < 10; index++) {
      sendMorseMessage("SOS ");
  }
  
}

////////////////////Main Menu Function/////////////////////////////////////////

void printMenu() {
  tone(9, sideToneFreq); // Trun on key mode
  Serial.println(" ");  // Clear Serial Monitor
  Serial.println(" ");  // Clear Serial Monitor
  Serial.println("********************* Status ****************************");
  printWPMFromUnitTime(unitTime);
  printUnitTime(unitTime);
  farnsworthStatus(farnsworthMode);  // https://www.arrl.org/files/file/Technology/x9004008.pdf
  printSideTone(sideToneFreq);
  Serial.print("Free RAM is ");  // Print the free RAM to the serial monitor
  Serial.print(freeMemory()); 
  Serial.println(" out of 32,768 RAM.");
  Serial.println(" ");
 
  Serial.println("********************** Preferences Menu ***************");
  Serial.println("Please enter the number in the Serial Monitor:");
  Serial.println("1. Send lesson two homework message SOS");
  Serial.println("2. Set WPM 3-40");
  Serial.println("3. Toggle Farnsworth mode");
  Serial.println("4. Set side tone frequency");
  Serial.println("5. Set dit time in uSec, 120 - 10 WPM, 60 - 20 WPM, 30 - 40 WPM");
 
  Serial.println("********************** Morse Code Net Menu **************");
  Serial.println("6. Send square root of 2, 60 digits");
  Serial.println("7. Send square root of 3, 60 digits");
  Serial.println("8. Send pi, 60 digits");
  Serial.println("9. Send Morse code abbreviations");
  Serial.println("10. Send random text");
  Serial.println("11. Send punctuation");
  Serial.println("12. Send QST DE WA9ONY The quick brown fox jumps over a lazy dog. DE WA9ONY K");
  Serial.println("13. Send QST DE WA9ONY Pack my box with five dozen liquor jugs. DE WA9ONY K");
  Serial.print("14. Send QSO, index: ");
  Serial.println(qsoIndex);
  Serial.print("15. Send Morse code net message, index: ");
  Serial.println(netIndex);
  Serial.println("16. Send e, 60 digits");
  Serial.println("17. Send: QST alpha, nums & pun");
  Serial.println("18. Send: call signs 1-10 DE WA9ONY K");
  Serial.println("19. Send Marion county repeaters DE WA9ONY K");
  Serial.println("20. Send 10 random states DE WA9ONY K");
  Serial.println("21. Send States 1-10 DE WA9ONY K");
  Serial.println("22. Send States 11-20 DE WA9ONY K");
  Serial.println("23. Send States 21-30 DE WA9ONY K");
  Serial.println("24. Send States 31-40 DE WA9ONY K");
  Serial.println("25. Send States 41-50 DE WA9ONY K");
  Serial.println("26. Send 10 random capitals DE WA9ONY K");
  Serial.println("27. Send 10 random countries DE WA9ONY K");
  Serial.println("28. Send Continuously 10 random capitals DE WA9ONY K, stop if any key is pressed");
  Serial.println("29. Send and wait for any key entry, 10 random capitals DE WA9ONY K");
  Serial.println("30. Send random call sign with DE WA9ONY K");
  Serial.println("31. Send random town with DE WA9ONY K");
  Serial.println("32. Send random name with DE WA9ONY K");
  Serial.println("33. Send: pangrams");
 
  Serial.println("********************** Morse Code Menu *****************");
  Serial.println("40. Send numbers");
  Serial.println("41. Send countries");

  Serial.println("******* Arduino UNO R4 WiFi Lesson 2 Homework ***********");
  Serial.println("99. Send lesson two homework message SOS");

}

////////////////////Setup Function/////////////////////////////////////////

void setup() {
  pinMode(ledPin, OUTPUT);
  // Initialize serial communication at a baud rate of 9600  
  Serial.begin(9600);
  randomSeed(analogRead(0)); // Initialize random number generator with a somewhat random input
  while (!Serial) {
    ; // Wait for serial port to connect. Needed for native USB port only
  }
  delay(2000);
  Serial.println(" ");
  Serial.println(" ");
  Serial.println(" ");
  Serial.println(" ");
  Serial.println(" "); 
  printMenu();
}

////////////////////Loop Function/////////////////////////////////////////

void loop() {

 // Check if data is available to read
  if (Serial.available() > 0) {
    int choice = Serial.parseInt(); // Read the choice
    // Clear the Serial buffer
    while (Serial.available() > 0) {
      Serial.read();
    }
    // Execute the function based on the choice
    noTone(9);  // Turn off key mode
    switch (choice) {
      case 1:
        menuItem1();
        break;
      case 2:
        getWPM();
        break;
      case 3:
        menuItem3();
        break;
      case 4:
        menuItem4();
        break;
      case 5:
        menuItem5();
        break;
      case 6:
        menuItem6();
        break;
      case 7:
        menuItem7();
        break;
      case 8:
        menuItem8();
        break;
      case 9:
        menuItem9();
        break;
      case 10:
        menuItem10();
        break;
      case 11:
        menuItem11();
        break;
      case 12:
        menuItem12();
        break;
      case 13:
        menuItem13();
        break;
      case 14:
        menuItem14();
        break;
      case 15:
        menuItem15();
        break;
      case 16:
        menuItem16();
        break;
      case 17:
        menuItem17();
        break;
      case 18:
        menuItem18();
        break;
      case 19:
        menuItem19();
        break;
      case 20:
        menuItem20();
        break;
      case 21:
        menuItem21();
        break;
      case 22:
        menuItem22();
        break;
      case 23:
        menuItem23();
        break;
      case 24:
        menuItem24();
        break;
      case 25:
        menuItem25();
        break;
      case 26:
        menuItem26();
        break;
      case 27:
        menuItem27();
        break;
      case 28:
        menuItem28();
        break;
      case 29:
        menuItem29();
        break;
      case 30:
        menuItem30();
        break;
      case 31:
        menuItem31();
        break;
      case 32:
        menuItem32();
        break;
      case 33:
        menuItem33();
        break;
      case 34:  // Countrie
        menuItem34();
        break;
/*      case 35:  // Numbers
        menuItem35();
*/        break;
      case 40:  // Numbers
        menuItem40();
        break;
      case 41:  // Numbers
        menuItem41();
        break;

      case 99:
        menuItem99();
        break;

      default:
        Serial.println("Invalid choice. Please try again.");
        break;
    }
    // Print the menu again for subsequent choices
    printMenu();
  }

}
