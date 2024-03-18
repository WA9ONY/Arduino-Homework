/*
  Morse code sketch created with the help from ChatGPT-4, 
  2024.03.03 
  Arduino UNO R4 WiFi

  David Haworth, WA9ONY

  Purpose:
  Homework for Arduino UNO R4 WiFi lesson 2.
  Send SOS on external LED.
  
  Exploring byond the homework.
    Create a full sysbol Morse code generator.
    Relearn the Morse code upto 20 WPM.
    Use this program on the Sunday evening Morse code net.
    Use ChatGPT-4 to create Arduino C++ functions. 
    Use ChatGPT-4 to teach how to use Arduino C++.
    ChatGPT learning cutoff date is April 2023, therefore, It doe not know about the R4.
    Use ChatGPT-4 to learn about Morse code.
    All the ChatGPT-4 conversations are in one file at
      https://github.com/WA9ONY/Arduino-Homework/tree/main/ChatGPT
    Current sketch is at
      https://github.com/WA9ONY/Arduino-Homework/tree/main/Sketches        

  Reference URLs:
    https://github.com/WA9ONY/Arduino-Homework/blob/main/README.md#L2
    https://www.youtube.com/@WA9ONYHomework
  
    https://openai.com/
    https://youtu.be/S1NJJRpWHpA?si=_ztm3pw92w-hp72G
    https://en.wikipedia.org/wiki/Morse_code_abbreviations
    https://www.arrl.org/learning-morse-code


**********************************************************************************
  The following bit duration table was created by ChatGPT-4
  The WPM uses the "Paris" standard.

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

//////////////////// Includes Library //////////////////////////////////////////
#include <Arduino.h>

//////////////////// Constant Declarations /////////////////////////////////////
const int ledPin = 13; // LED connected to digital pin 13

const int ramSize = 32768;

/////////////////// Const chars array sizes /////////////////////////////////////
/////////////////// QSO array sizes /////////////////////////////////////////////
const int callSignsArraySize = 21;
const int netArraySize = 5;
const int qsoArraySize = 5;
const int wxArraySize = 16;
const int signalProblemArraySize = 3;
const int greetingArraySize = 5;

//////////////////// Pratic receiving Mores Code data arry sizes ////////////////
const int lettersArraySize = 121;
const int lettersAWJNGPArraySize = 50;
const int lettersTMOEISHArraySize = 48;
const int numbersArraySize = 9;
const int punctuationsArraySize = 13;
const int prosignsArraySize = 7;
const int qCodesArraySize = 20;
const int abbrArraySize = 21;
const int pangramsArraySize = 21;
const int MarionRepeatersArraySize = 17;
const int namesArraySize = 102;
const int townsArraySize = 98;
const int capitalsStatsArraySize = 50;
const int statesArraySize = 50;
const int capitalsArraySize = 50;
const int oregonCountiesArraySize = 36;
const int countriesArraySize = 194;
const int LunaPoemArraySize = 16;
const int oscar1ArraySize = 12;

//////////////////// Variable  Declarations ////////////////////////////////////////

bool farnsworthMode = true;
bool timerMode = true;
bool statusDisplayMode = true;
bool menuDisplayMode = true;
bool sendln = true;

int unitTime = 120; // Base time unit in milliseconds for speed adjustment
int sideToneFreq = 750;
int farnsworthSpace = 2;  // 2 bit more spacing
int ramUsed = 0;
unsigned long startTime = millis();
unsigned long endTime = 0;
unsigned long duration = 0;
int mesgNum = 1;

////////////////////////// Array indexs //////////////////////////////////////////
int callSignToIndex = 1;
int callSignFromIndex = 0;
int netIndex = 0;
int qsoIndex = 0;
int wxIndex = 0;
int signalProblemIndex = 0;
int greetingIndex = 0;

int lettersIndex = 0;
int lettersAWJNGPIndex = 0;
int lettersTMOEISHIndex = 0;
int numbersIndex = 0;
int punctuationsIndex = 0;
int prosignsIndex = 0;
int callSignsIndex = 0;
int qCodesIndex = 0;
int abbrIndex = 0;
int pangramsIndex = 0;
int MarionRepeatersIndex = 0;
int namesIndex = 0;
int townsIndex = 0;
int capitalsStatsIndex = 0;
int statesIndex = 0;
int capitalsIndex = 0;
int oregonCountiesIndex = 0;
int countriesIndex = 0;
int LunaPoemIndex = 0;
int oscar1Index = 0;


//////////////////// Net, QSO & const char arrays data ////////////////////////////
//////////////////// Some of these arrays were created by ChatGPT-4 ///////////////
// A  Morse code net messages
const char* net[netArraySize] = {
"QST QST QST DE WA9ONY MORSE CODE PRACTICE ON SUNDAY AT 1900, WORDS WITH T, M, O, E, I, S, H ~",
"~ MORSE CODE PRACTICE ON SUNDAY AT 1900 ON WA7ABU REPEATER 145.290 MHZ ~",
"~ TEXT IS SENT FOR LESS THAN 3 MINUTES LIMITED BY REPEATER TIME OUT ~",
"~ STARTING MORSE CODE SPEED IS 10 WPM WITH FARNSWORTH SPACING ~",
"~ CHECK YOUR COPY TEXT ACCURACY AT WA9ONY ON QRZ.COM ~"
};

// QSO contact messages
const char* qso[qsoArraySize] = {
"CQ CQ CQ DE ",
"GE OM TNX FER CALL UR RST 589 QSB ~ OP DAVID BTU ",
"R R QTH CAMAS, WA ~ CAMAS, WA BTU ",
"R R FB RIG ICON IC-9700 ~ ANT VERT UP 20 FT BTU ",
"R R FB TNX FER QSO EQSL GL CU AGN 73 "
};

// QSO WX message
const char* wx[wxArraySize] = {
"R R FB WX CLEAR AND HOT TODAY BTU ",
"R R FB WX CLEAR AND WARM TODA BTU ",
"R R FB WX CLEAR AND FAIR TODA BTU ",
"R R FB WX CLEAR AND COOL TODA BTU ",
"R R FB WX CLEAR AND COLD TODA BTU ",
"R R FB WX CLOUDY AND HOT TODA BTU ",
"R R FB WX CLOUDY AND WARM TODA BTU ",
"R R FB WX CLOUDY AND FAIR TODA BTU ",
"R R FB WX CLOUDY AND COOL TODA BTU ",
"R R FB WX CLOUDY AND COLD TODA BTU ",
"R R FB WX RAINING AND HOT TODA BTU ",
"R R FB WX RAINING AND WARM TODA BTU ",
"R R FB WX RAINING AND FAIR TODA BTU ",
"R R FB WX RAINING AND COOL TODA BTU ",
"R R FB WX RAINING AND COLD TODA BTU ",
"R R FB WX SNOWING AND COLD TODA BTU "
};

// Signal quality problems
const char* qCodesSig[signalProblemArraySize] = {
"QRM", // man made interference
"QRN", // nature noise
"QSB"  // signal fading
};

//QSO contact greetings
const char* greeting[greetingArraySize] = {
"GD",  // Good day
"GM",  // Good morning
"GE",  // Good evening
"GN"   // Good night
};

//////////////////// Pratice Copy Data Arrays /////////////////////////////////////////
// Letters
const char* letters[lettersArraySize] = {
"~ LETTERS: A B C D E F G H I J K L M N O P Q R S T U V W X Y Z ~",
"~ LETTERS: Z Y X W V U T S R Q P O N M L K J I H G F E D C B A ~",
"~ ABCDE FGHIJ KLMNO PQRST UVWXYZ ~",
"~ ZYXWV UTSRQ PONML KJIHG FEDCBA ~",
"~ The satellite name OSCAR stands for Orbiting Satellite Carrying Amateur Radio. ~",
// 50 words 5 character long
"~ apple, brick, crane, drive, eagle ~",
"~ frame, grape, house, ivory, joker ~",
"~ knife, light, mango, night, opera ~",
"~ pride, quark, rover, spear, tiger ~",
"~ ultra, vivid, water, xerox, yacht ~",
"~ zebra, alert, bench, chill, dance ~",
"~ elbow, flint, globe, honor, input ~",
"~ jolly, kneel, lemon, mirth, nerve ~",
"~ ocean, pilot, quilt, ridge, shine ~",
"~ track, unity, vapor, wheat, xenon ~",
// 50 words 7 character long
"~ example", "battery", "digital", "arduino", "circuit",
"~ program", "library", "display", "network", "adapter",
"~ storage", "service", "connect", "project", "station",
"~ message", "system", "control", "source", "charge",
"~ signal", "button", "switch", "module", "sensor",
"~ record", "output", "input", "process", "thread",
"~ binary", "device", "update", "utility", "virtual",
"~ analog", "compile", "config", "debug", "firmware",
"~ ground", "header", "import", "logic", "memory",
"~ object", "packet", "queue", "reset", "serial"
// 55 words 10 character long
"~ automobile", "processor", "middleware", "peripheral", "framework",
"~ algorithm", "broadcast", "component", "retrieval", "encryption",
"~ integrate", "synthetic", "prototype", "magnitude", "navigation",
"~ objective", "parameter", "quantizer", "reduction", "schematic",
"~ telemetry", "usermode", "validity", "workspace", "xenophobe",
"~ yieldable", "zeolitica", "aesthetic", "biometric", "cleansing",
"~ detection", "elevation", "federated", "gradient", "holograph",
"~ isometric", "juxtapose", "kangaroo", "laminated", "morphogen",
"~ necrosis", "obfuscate", "polarized", "quixotic", "relevance",
"~ symbiotic", "turquoise", "unanimous", "vibration", "wavelength",
"~ xenocracy", "youngster", "zirconium", "aerodrome", "benchmark",
"~ abcdefghijklmnopqrstuvwxyz ~"  // Test small letters
};

// Letters: A, W, J, N, G, P 
const char* lettersAWJNGP[lettersAWJNGPArraySize] = {
"JAW", "WAG", "PAN", "NAP", "GAP", "JAW", "WAG", "PAN", 
"NAP", "GAP", "JAW", "WAG", "PAN", "NAP", "GAP", "JAW", 
"WAG", "PAN", "NAP", "GAP", "JAW", "WAG", "PAN", "NAP", 
"GAP", "JAW", "WAG", "PAN", "NAP", "GAP", "JAW", "WAG", 
"PAN", "NAP", "GAP", "JAW", "WAG", "PAN", "NAP", "GAP", 
"JAW", "WAG", "PAN", "NAP", "GAP", "JAW", "WAG", "PAN", 
"NAP", "GAP"
};

// Letters: A, W, J, N, G, P
const char*  lettersTMOEISH[lettersTMOEISHArraySize] = {
"SOME", "ETHOS", "TIE", "MISTO", "MISO", 
"SMOTE", "THE", "TIMES", "SHE", "MOTHS", 
"SMITE", "HOTS", "MESH", "HOIST", "HEIST", 
"HITS", "MOST", "HOST", "OMIT", "TOES", 
"TIES", "SOMETH", "MIST", "MOTH", "SHOE", 
"HOT", "HIS", "MITE", "EMIT", "HIT",
"TIME", "THEM", "TOME", "ITEM", "ITEMS", 
"HOSE", "MOTES", "HEM", "THIS", "STEM", 
"SET", "MOIST", "MOSE", "HOME", "SMITH", 
"SITE", "SIT", "HIM"
};


// Numbers
const char* numbers[numbersArraySize] = {
"~ NUMBERS: 1 2 3 4 5 6 7 8 9 0 0 9 8 7 6 5 4 3 2 1 11 22 33 44 55 66 77 88 99 00 ~",
"~ 12345 67890 09876 54321 ~",
"~ RST 599, RST 489, RST 379, RST 269, RST 159, RST 149, RST 139, RST 129, RST 119 ~", 
"~ Speed of light: 299,792,458 meters per second ~ 983,571,088 feet per second ~", 
"~ The charge of an electron is approximately -1.602 x 10 to the-19 coulombs. ~",                                                 // 1 to 0
"~ The value of pi: 3.14159 26535 89793 23846 26433 83279 50288 41971 69399 37510 ~",  
"~ The value of e: 2.71828 18284 59045 23536 02874 71352 66249 77572 47093 69995 ~",  
"~ Square root of 2: 1.41421 35623 73095 04880 16887 24209 69807 85696 71875 37694 ~",  
"~ Square root of 3: 1.73205 08075 68877 29352 74463 41505 87236 69428 05253 81038 ~"  
};

// Punctuation
const char* punctuations[punctuationsArraySize] = {
"~ PUNCTUATION: . , / ? \\ ! ( ) & : ; = + - _ $ @ \" \' ~", 
"~ PUNCTUATION: .. ,, // ?? \\\\ !! (( )) && :: ;; == ++ -- __ $$ @@ \"\" \'\' ~", 
"~ .,?\\!()/&:;=+-_$@\" ~", 
"~ . , ? \\ ! ( ) / & : ; = + - _ $ @ \" ~",               // Morse code punctuation 
"~ .. ,, ?? \\\\ !! (( )) // && :: ;; == ++ -- __ $$ @@ \"\" ~",  
"~ . . . ~ , , , ~ ? ? ? ~ \\ \\ \\ ~ ! ! ! ~",  // .,?\!
"~ ..... ,,,,, ????? \\\\\\\\\\ !!!!! ~",  // .,?\!
"~ ( ( ( ) ) ) / / / & & & : : : ~",       // ()/&:
"~ ((((( ))))) ///// &&&&& ::::: ~",       // ()/&:
"~ ; ; ; = = = + + + - - - ~",             // ;=+-
"~ ;;;;; ===== +++++ ----- ~",             // ;=+-
"~ _ _ _ $ $ $ @ @ @ \" \" \" ~",           // _$@"
"~ _____ $$$$$ @@@@@ \"\"\"\"\" ~"         // _$@"
};

// Prosigns
// ASCII charcaters not used in amateur radio communications are use for special prosigns
const char* prosigns[prosignsArraySize] = {
"K K K K K ] ] ] ] ] } } } } } ~ ~ ~ ~ ~ # # # # # ",
"K ] } ~ #",
"K K K K K ",  // K: invitation to transmit
"] ] ] ] ] ",  // AR: end of message
"} } } } } ",  // SK: end of contact
"~ ~ ~ ~ ~ ",  // BT: separator, new topic, new pargraph
"# # # # # "    // HH: error
};

// Call signs 
const char* callSigns[callSignsArraySize] = {
"WA9ONY ", "W7CCM ", "K7JCD ", "WA7ABU ",  "K7BBY ", 
"K7CAO ", "K7LAP ", "KA7VMX ", "KC2AIW ", "KE7BJQ ", 
"KF5ZBY ", "KG7CGK ", "KG7GDB ", "KJ7ZFF ", "KK7OAX ", 
"KK7OR ", "NG7R ", "NW7OR ", "W0EDF ", "W1ARK ", 
"W7LIN "
};

// Q Codes for amateur radio Morse code operation
// https://en.wikipedia.org/wiki/Q_code
// https://www.skccgroup.com/member_services/beginners_corner/
const char* qCodes[qCodesArraySize] = {
"~ QRL, Are you busy? ~",
"~ QRG, What's my exact frequency? ~",
"~ QRM, Are you being interfered with? ~",
"~ QRN, Are you troubled by static? ~",
"~ QRO, Shall I increase transmitter power? ~",
"~ QRP, Shall I decrease transmitter power? ~",
"~ QRQ, Shall I send faster? ~",
"~ QRS, Shall I send more slowly? ~",
"~ QRT, Shall I stop sending? ~",
"~ QRU, Have you got anything for me? ~",
"~ QRV, Are you ready? ~",
"~ QRX, When will you call me again? ~",
"~ QRZ, Who is calling me? ~",
"~ QSB, Is my signal fading? ~",
"~ QSL, Can you acknowledge receipt? ~",
"~ QSO, Can you communicate with ... direct or by relay? ~",
"~ QST, Should I repeat the prior message to all amateurs I contact? ~"
"~ QSY, Shall I change to another frequency? ~",
"~ QTH, What's your location? ~",
"~ QTR, What's the correct time? ~"
};

// Abbreviations for amateur radio Morse code operation
// https://en.wikipedia.org/wiki/Morse_code_abbreviations
// https://www.skccgroup.com/member_services/beginners_corner/
const char* abbreviations[abbrArraySize] = {
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

// Pangrams, all the letters of the alphabet in one sentence.
const char* pangrams[pangramsArraySize] = {
"~ The quick brown fox jumps over a lazy dog. ~",
"~ Pack my box with five dozen liquor jugs. ~",
"~ Jinxed wizards pluck ivy from the big quilt. ~",
"~ The five boxing wizards jump quickly. ~",
"~ How vexingly quick daft zebras jump! ~",
"~ Quick zephyrs blow, vexing daft Jim. ~",
"~ Sphinx of black quartz, judge my vow. ~",
"~ Two driven jocks help fax my big quiz. ~",
"~ Public junk dwarves quiz mighty fox. ~",
"~ Five quacking zephyrs jolt my wax bed. ~",
"~ The jay, pig, fox, zebra, and my wolves quack! ~",
"~ Vexed nymphs go for quick waltz job. ~",
"~ Glib jocks quiz nymph to vex dwarf. ~",
"~ Jackdaws love my big sphinx of quartz. ~",
"~ Quickly befriending the jovial wizard makes Pax's life cozy. ~",
"~ Vexing fjord nymphs quiz blackjack whiz. ~",
"~ Mr. Jock, TV quiz PhD, bags few lynx. ~",
"~ Jump by vow of quick, lazy strength in Oxford. ~",
"~ The quick onyx goblin jumps over the lazy dwarf. ~",
"~ Crazy Frederick bought many very exquisite opal jewels. ~",
"~ Sixty zippers were quickly picked from the woven jute bag. ~"
};

// Marion county Oregon FM repeater
const char* MarionRepeaters[MarionRepeatersArraySize] = {
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

// Boys and grils names 
const char* names[namesArraySize] = {
// Boys
"Aiden", "Alexander", "Anthony", "Asher", "Benjamin",
"Carter", "Charles", "Christopher", "Daniel", "David", "Dave",
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

// Towns in Oregon counties 
const char* towns[townsArraySize] = {
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

// State capitals with state abbreviations
const char* capitalsStats[capitalsStatsArraySize] = {
"Montgomery, AL",
"Juneau, AK",
"Phoenix, AZ",
"Little Rock, AR",
"Sacramento, CA",
"Denver, CO",
"Hartford, CT",
"Dover, DE",
"Tallahassee, FL",
"Atlanta, GA",
"Honolulu, HI",
"Boise, ID",
"Springfield, IL",
"Indianapolis, IN",
"Des Moines, IA",
"Topeka, KS",
"Frankfort, KY",
"Baton Rouge, LA",
"Augusta, ME",
"Annapolis, MD",
"Boston, MA",
"Lansing, MI",
"Saint Paul, MN",
"Jackson, MS",
"Jefferson City, MO",
"Helena, MT",
"Lincoln, NE",
"Carson City, NV",
"Concord, NH",
"Trenton, NJ",
"Santa Fe, NM",
"Albany, NY",
"Raleigh, NC",
"Bismarck, ND",
"Columbus, OH",
"Oklahoma City, OK",
"Salem, OR",
"Harrisburg, PA",
"Providence, RI",
"Columbia, SC",
"Pierre, SD",
"Nashville, TN",
"Austin, TX",
"Salt Lake City, UT",
"Montpelier, VT",
"Richmond, VA",
"Olympia, WA",
"Charleston, WV",
"Madison, WI",
"Cheyenne, WY"
};

// State names 
const char* states[statesArraySize] = {
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

// State capital names
const char* capitals[capitalsArraySize] = {
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

// Oregon county names
const char* oregonCounties[oregonCountiesArraySize] = {
"Baker", "Benton", "Clackamas", "Clatsop", "Columbia", 
"Coos", "Crook", "Curry", "Deschutes", "Douglas", 
"Gilliam", "Grant", "Harney", "Hood River", "Jackson", 
"Jefferson", "Josephine", "Klamath", "Lake", "Lane", 
"Lincoln", "Linn", "Malheur", "Marion", "Morrow", 
"Multnomah", "Polk", "Sherman", "Tillamook", "Umatilla", 
"Union", "Wallowa", "Wasco", "Washington", "Wheeler", "Yamhill"
};

// Country names
const char* countries[countriesArraySize] = {
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

// Luna Aussie poem by ChatGPT
// Luna photo at
// https://www.qrz.com/db/WA9ONY
const char* LunaPoem[LunaPoemArraySize] = {
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

// OSCAR-1 Morse code information
const char* oscar1[oscar1ArraySize] = {
"The first amateur radio satellite OSCAR-1 was launched on December 12, 1961.",  
"OSCAR-1 convey temperature information, but not through the \"HI\" Morse Code message directly.",
"The \"HI\" Morse Code message was a simple beacon signal meant for identification.",
"Also, it demonstrate the satellite's operational status to amateur radio operators worldwide.",
"However, the innovative aspect of OSCAR-1's design was that it used the duration of the dits (the dots in Morse Code) and ",
"the pauses between the \"HI\" messages to indicate the internal temperature of the satellite.",
"As the temperature inside OSCAR-1 increased, the oscillators would drift, causing the timing of the dits and the pauses between the \"HI\" messages to change.",
"Amateur radio operators tracking the satellite could monitor these variations in the signal's timing to estimate the internal temperature of OSCAR-1.",
"This method of temperature indication was a clever use of the technology available at the time, showcasing early ingenuity in satellite design and telemetry.",
"By providing this temperature data, OSCAR-1 not only served as a beacon for amateur radio communication ", 
"but also contributed valuable information on the behavior of electronic components in the space environment, ", 
"adding to the scientific understanding of space's impact on satellite technology."
};

//////////////////// Program Settings Functions /////////////////////////////////////////
// Determine free RAM available
int freeMemory() {
  char top;
  return &top - reinterpret_cast<char*>(malloc(4));
}

// Print WPM from unitTime
void printWPMFromUnitTime(int unitTimeMs) {
  float unitTimeSeconds = unitTimeMs / 1000.0; // Convert milliseconds to seconds
  float elementsPerWord = 50.0; // Standard "PARIS " word length in elements
  float wpm = (1 / (unitTimeSeconds * elementsPerWord)) * 60;
  Serial.print("Morse code speed is ");
  Serial.print(wpm, 0); 
  Serial.println(" words per minute (WPM).");
}

// Create WPM message from unitTime
String wpmMessage(int unitTimeMs) {
  float unitTimeSeconds = unitTimeMs / 1000.0; // Convert milliseconds to seconds
  float elementsPerWord = 50.0; // Standard "PARIS " word length in elements
  float wpm = (1 / (unitTimeSeconds * elementsPerWord)) * 60;
  int wpmInt = (int)wpm;
  String wpmStr = String(wpmInt);
  return "~ Morse code speed is "+wpmStr+" words per minute (WPM). ~";
}

// Create Farnsworth message 
String farnsworthMess() {
String farnsworthStatus; 
 if (farnsworthMode){
  farnsworthStatus = "on";
 }
 else{
  farnsworthStatus = "off";
 }
  return "~ Farnsworth spacing is "+farnsworthStatus+". ~";
}

// Side tone message 
String sideToneMess() { 
String sideToneStr = String(sideToneFreq);
return "~ Side tone frequency is "+sideToneStr+" Hz. ~";
}

// Set WPM from Serial Monitor
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

// Calculate unitTime from WPM
int calculateUnitTime(int wpm) {
  // Formula to calculate unitTime from WPM
  float unitTimeSeconds = (60.0 / (wpm * 50.0));
  return int(unitTimeSeconds * 1000); // Convert seconds to milliseconds and return
}

// Print Farnsworth mode status
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
}

// Print side tone frequency
int printSideTone(int tone) {
  Serial.print("Side tone frequency is ");
  Serial.print(tone);
  Serial.println(" Hz.");
}

// Print dit unit of time
int printUnitTime(int ditTime) {
  Serial.print("Morse code dit duration is ");
  Serial.print(ditTime);
  Serial.println(" milli seconds.");
}

// Set side tone from user by Serial Monitor
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

// Set dit unit of time from user by Serial Monitor
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

// Timer in minutes & seconds
void timerDuration(){
  if (timerMode) {
  unsigned long durationMin;
  unsigned long durationSec;
  endTime = millis();
  duration = (endTime - startTime )/1000;
  durationMin = duration/60;
  durationSec  = duration&60;
  Serial.print(durationMin);
  Serial.print(":");
  Serial.println(durationSec);
  }
}

// Up time in hours, minutes & seconds
void timeSincePwrUp(){
 if (timerMode) {
  unsigned long durationHr; 
  unsigned long durationMin; 
  unsigned long durationSec;
  endTime = millis();
  duration = (endTime - startTime )/1000;
  durationHr = duration/(60*60);
  duration = duration&(60*60);
  durationMin = duration/60;
  durationSec  = duration&60;
  Serial.print(durationHr);
  Serial.print(":");
  Serial.print(durationMin);
  Serial.print(":");
  Serial.println(durationSec);
 }
}

//////////////////// Low Level Morese Code Character Functions ///////////////////
// Morse code dot
void dot() {
  tone(8, sideToneFreq, unitTime); // Play a 750Hz tone for unitTime on pin 8
  digitalWrite(ledPin, HIGH);
  delay(unitTime);
  digitalWrite(ledPin, LOW);
  delay(unitTime);
}

// Morse code dash
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
 
  // Prosigns using ASCII charater not used in amateur radio Morse code communications
    case '~':  dash(); dot(); dot(); dot(); dash(); break; // BT new topic, new section
    case '`':  break; //  
    case '#':  dot(); dot(); dot(); dot(); dot(); dot(); dot(); dot(); break; //  HH Error
    case '%':  break; //  
    case '^':  break; //  
    case '*':  break; //  
    case '|':  break; //  
    case '[':  break; //  
    case ']':  dot(); dash(); dot(); dash(); dot(); break; //  AR End of transission
    case '{':  break; //  
    case '}':  dot(); dot(); dot(); dash(); dot(); dash(); break; // SK End
//  case '\'':  break; //  
    case '<':  break; //  
    case '>':  break; //    

// Word space is 7 dits long
    case ' ':              // Handle space between words
      delay(7 * unitTime); // Space between words, longer than between letters
      break;

    default: break; // Handle unsupported characters
  }
  if (farnsworthMode) {
    delay((3+farnsworthSpace) * unitTime); // Space between letters
    }
    else {
    delay(3 * unitTime); // Space between letters
    }
}

// Prosign BT used before using ~ as BT
void prosignBT() {
  Serial.print("-BT- ");
  dash(); dot(); dot(); dot(); dash();  // Send BT
  delay(7 * unitTime);   // Send BT
}

//
void sendMorseMessage(const char* message) {
  if (sendln) {Serial.println(message);}
    // Print the message to the Serial monitor
  int messageLength = strlen(message);  // Get the length of the message
  for (int i = 0; i < messageLength; i++) {
      if (true) {Serial.print(message[i]);}  // Print each character to the Serial monitor
    blinkMorse(message[i]);  // Blink the Morse code for each character
  }
  if (sendln) { Serial.println(" "); }
  delay(7 * unitTime); // Space between messages
}

///////////////// Send Messages

// Function to list states from start to end

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

//
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

//
  String randomString = "";
  for (int i = 0; i < 5; i++) {
    int randomIndex = random(characters.length());
    randomString += characters[randomIndex];
  }
  randomString += " ";  // Add a space after the five characters
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

String getRandomCallSign() {
  String callSign = "";
  if (random(2) == 0) {   // First character: K or W
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

///////////////////////////////////////////////////////
//*********** 1-9 Program Settings Menu ***************
void menuItem1() {
  statusDisplayMode = !statusDisplayMode;
  menuDisplayMode = !menuDisplayMode;
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
  netIndex = 0;
  mesgNum = 1;
  qsoIndex = 0;
  callSignToIndex = 1;
  lettersIndex = 0;
  lettersAWJNGPIndex = 0;
  lettersTMOEISHIndex = 0;
  numbersIndex = 0;
  punctuationsIndex = 0;
  prosignsIndex = 0;
  callSignsIndex = 0;
  qCodesIndex = 0;
  abbrIndex = 0;
  pangramsIndex = 0;
  MarionRepeatersIndex = 0;
  namesIndex = 0;
  townsIndex = 0;
  capitalsStatsIndex = 0;
  statesIndex = 0;
  capitalsIndex = 0;
  oregonCountiesIndex = 0;
  countriesIndex = 0;
  LunaPoemIndex = 0;
  oscar1Index = 0;
  Serial.println("Reset indexes to zero or one.");
}

void menuItem7() {
 for (int index=0;index<callSignsArraySize;index++){
  if (index == 10){ Serial.println(" ");}
  Serial.print(index);
  Serial.print(" ");
  Serial.print(callSigns[index]);
 } 
 callSignToIndex++;
 Serial.println(" ");
 Serial.print(callSignToIndex);
 Serial.print(" ");
 Serial.println(callSigns[callSignToIndex]);
}

void menuItem8() {
 for (int index=0;index<callSignsArraySize;index++){
  if (index == 10){ Serial.println(" ");}
  Serial.print(index);
  Serial.print(" ");
  Serial.print(callSigns[index]);
 } 
 callSignToIndex--;
 Serial.println(" ");
 Serial.print(callSignToIndex);
 Serial.print(" ");
 Serial.println(callSigns[callSignToIndex]);
}

//******** 10-19 QSO Menu ***************
void menuItem10() { 
  String strData1 = qso[0];
  String strData2 = callSigns[callSignFromIndex];
  String strData3 = strData1 + strData2 + strData2 + "K";
  sendMorseMessage(strData3.c_str());
}

void qsoMsg(int index) { 
  String strData1 = callSigns[callSignToIndex];
  String strData2 = callSigns[callSignFromIndex];
  String strData3 = qso[index];
  String strData4 = strData1 + "DE " + strData2 + strData3 + strData1 + "DE " + strData2 + "K";
  sendMorseMessage(strData4.c_str());
}

////////// 20-39 QSO WX Menu //////////////////////
void wxMessages(int wxIndexMsg){
  String strData1 = callSigns[callSignToIndex];
  String strData2 = callSigns[callSignFromIndex];
  String strData3 = wx[wxIndexMsg];
  String strData4 = strData1 + "DE " + strData2 + strData3 + strData1 + "DE " + strData2 + "K";
  sendMorseMessage(strData4.c_str());
}

//******** 40-59 Morse Code Net Menu *******************
void menuItem40() {  
  startTime = millis();
  String netStr = net[netIndex];
  sendMorseMessage(netStr.c_str());
  netIndex++;
  if (netIndex == netArraySize){ netIndex = 0;}
  timerDuration();
}

void menuItem41() {  
  sendln = false;
  startTime = millis();
  prosignBT();
  for(int index=0; index<18; index++){
    menuItem96();
    sendMorseMessage(" ");
  }
  prosignBT();
  timerDuration();
  sendln = true;
}

//******** 60-99 Morse Code Practice Copying Menu ******
void menuItem60() {  
  String strData = letters[lettersIndex];
  sendMorseMessage(strData.c_str());
  lettersIndex++;
  if (lettersIndex == lettersArraySize){ lettersIndex = 0;}
}

void menuItem160() { 
  for (int index = 0; index < lettersArraySize; index++ ) {
    String strData = letters[index];
    sendMorseMessage(strData.c_str());
  }
}

void menuItem61() {  
  int lettersIndex = random(0, lettersArraySize);
  Serial.print("Array index is ");
  Serial.print(lettersIndex); 
  Serial.print(", array size is ");
  Serial.println(lettersArraySize); 
  String strData = letters[lettersIndex];
  sendMorseMessage(strData.c_str());
}

void menuItem62() {  
  String strData = numbers[numbersIndex];
  sendMorseMessage(strData.c_str());
  numbersIndex++;
  if (numbersIndex == numbersArraySize){ numbersIndex = 0;}
}

void menuItem162() { 
  for (int index = 0; index < numbersArraySize; index++ ) {
    String strData = numbers[index];
    sendMorseMessage(strData.c_str());
  }
}

void menuItem63() {  
  int numbersIndex = random(0, lettersArraySize);
  Serial.print("Array index is ");
  Serial.print(numbersIndex);
  Serial.print(", array size is ");
  Serial.println(numbersArraySize); 
  String strData = numbers[numbersIndex];
  sendMorseMessage(strData.c_str());
}

void menuItem64() {  
  String strData = punctuations[punctuationsIndex];
  sendMorseMessage(strData.c_str());
  punctuationsIndex++;
  if (punctuationsIndex == punctuationsArraySize){ punctuationsIndex = 0;}
}

void menuItem164() { 
  for (int index = 0; index < punctuationsArraySize; index++ ) {
    String strData = punctuations[index];
    sendMorseMessage(strData.c_str());
  }
}

void menuItem65() {  
  int punctuationsIndex = random(0, punctuationsArraySize);
  Serial.print("Array index is ");
  Serial.print(punctuationsIndex);
  Serial.print(", array size is ");
  Serial.println(punctuationsArraySize); 
  String strData = punctuations[punctuationsIndex];
  sendMorseMessage(strData.c_str());
}

void menuItem66() {  
  String strData = prosigns[prosignsIndex];
  sendMorseMessage(strData.c_str());
  prosignsIndex++;
  if (prosignsIndex == prosignsArraySize){prosignsIndex = 0;}
}

void menuItem166() { 
  for (int index = 0; index < prosignsArraySize; index++ ) {
    String strData = prosigns[index];
    sendMorseMessage(strData.c_str());
  }
}

void menuItem67() {  
  int saveIndex = prosignsIndex;
  int prosignsIndex = random(0, prosignsArraySize);
  Serial.print("Array index is ");
  Serial.print(prosignsIndex);
  Serial.print(", array size is ");
  Serial.println(prosignsArraySize);
  String strData = prosigns[prosignsIndex];
  sendMorseMessage(strData.c_str());
  prosignsIndex = saveIndex;
}

void menuItem68() {  
  String strData = callSigns[callSignsIndex];
  sendMorseMessage(strData.c_str());
  callSignsIndex++;
  if (callSignsIndex == callSignsArraySize){ callSignsIndex = 0;}
}

void menuItem168() { 
  for (int index = 0; index < callSignsArraySize; index++ ) {
    String strData = callSigns[index];
    sendMorseMessage(strData.c_str());
  }
}

void menuItem69() {  
  int callSignsIndex = random(0, callSignsArraySize);
  Serial.print("Array index is ");
  Serial.print(callSignsIndex);
  Serial.print(", array size is ");
  Serial.println(callSignsArraySize);
  String strData = callSigns[callSignsIndex];
  sendMorseMessage(strData.c_str());
}

void menuItem70() {  
  String strData = qCodes[qCodesIndex];
  sendMorseMessage(strData.c_str());
  qCodesIndex++;
  if (qCodesIndex == qCodesArraySize){qCodesIndex = 0;}
}

void menuItem170() { 
  for (int index = 0; index < qCodesArraySize; index++ ) {
    String strData = qCodes[index];
    sendMorseMessage(strData.c_str());
  }
}

void menuItem71() {  
  int index = random(0, qCodesArraySize);
  Serial.print("Array index is ");
  Serial.print(index);
  Serial.print(", array size is ");
  Serial.println(qCodesArraySize);
  String strData = callSigns[index];
  sendMorseMessage(strData.c_str());
}

void menuItem72() {  
  String strData = abbreviations[abbrIndex];
  sendMorseMessage(strData.c_str());
  abbrIndex++;
  if (abbrIndex == abbrArraySize){abbrIndex = 0;}
}

void menuItem172() { 
  for (int index = 0; index < abbrArraySize; index++ ) {
    String strData = abbreviations[index];
    sendMorseMessage(strData.c_str());
  }
}

void menuItem73() {  
  int index = random(0, abbrArraySize);
  Serial.print("Array index is ");
  Serial.print(index);
  Serial.print(", array size is ");
  Serial.println(abbrArraySize);
  String strData = abbreviations[index];
  sendMorseMessage(strData.c_str());
}

void menuItem74() {  
  String strData = pangrams[pangramsIndex];
  sendMorseMessage(strData.c_str());
  pangramsIndex++;
  if (pangramsIndex == pangramsArraySize){pangramsIndex = 0;}
}

void menuItem174() { 
  for (int index = 0; index < pangramsArraySize; index++ ) {
    String strData = pangrams[index];
    sendMorseMessage(strData.c_str());
  }
}

void menuItem75() {  
  int index = random(0, pangramsArraySize);
  Serial.print("Array index is ");
  Serial.print(index);
  Serial.print(", array size is ");
  Serial.println(pangramsArraySize);
  String strData = pangrams[index];
  sendMorseMessage(strData.c_str());
}

void menuItem76() {  
  String strData = MarionRepeaters[MarionRepeatersIndex];
  sendMorseMessage(strData.c_str());
  MarionRepeatersIndex++;
  if (MarionRepeatersIndex == MarionRepeatersArraySize){MarionRepeatersIndex = 0;}
}

void menuItem176() { 
  for (int index = 0; index < MarionRepeatersArraySize; index++ ) {
    String strData = MarionRepeaters[index];
    sendMorseMessage(strData.c_str());
  }
}

void menuItem77() {  
  int index = random(0, MarionRepeatersArraySize);
  Serial.print("Array index is ");
  Serial.print(index);
  Serial.print(", array size is ");
  Serial.println(MarionRepeatersArraySize);
  String strData = MarionRepeaters[index];
  sendMorseMessage(strData.c_str());
}

void menuItem78() {  
  String strData = names[namesIndex];
  sendMorseMessage(strData.c_str());
  namesIndex++;
  if (namesIndex == namesArraySize){namesIndex = 0;}
}

void menuItem178() { 
  for (int index = 0; index < namesArraySize; index++ ) {
    String strData = names[index];
    sendMorseMessage(strData.c_str());
  }
}

void menuItem79() {  
  int index = random(0, namesArraySize);
  Serial.print("Array index is ");
  Serial.print(index);
  Serial.print(", array size is ");
  Serial.println(namesArraySize);
  String strData = names[index];
  sendMorseMessage(strData.c_str());
}

void menuItem80() {  
  String strData = towns[townsIndex];
  sendMorseMessage(strData.c_str());
  townsIndex++;
  if (townsIndex == townsArraySize){townsIndex = 0;}
}

void menuItem180() { 
  for (int index = 0; index < townsArraySize; index++ ) {
    String strData = towns[index];
    sendMorseMessage(strData.c_str());
  }
}

void menuItem81() {  
  int index = random(0, townsArraySize);
  Serial.print("Array index is ");
  Serial.print(index);
  Serial.print(", array size is ");
  Serial.println(townsArraySize);
  String strData = towns[index];
  sendMorseMessage(strData.c_str());
}

void menuItem82() {  
  String strData = capitalsStats[capitalsStatsIndex];
  sendMorseMessage(strData.c_str());
  capitalsStatsIndex++;
  if (capitalsStatsIndex == capitalsStatsArraySize){capitalsStatsIndex = 0;}
}

void menuItem182() { 
  for (int index = 0; index < capitalsStatsArraySize; index++ ) {
    String strData = capitalsStats[index];
    sendMorseMessage(strData.c_str());
  }
}

void menuItem83() {  
  int index = random(0, capitalsStatsArraySize);
  Serial.print("Array index is ");
  Serial.print(index);
  Serial.print(", array size is ");
  Serial.println(capitalsStatsArraySize);
  String strData = capitalsStats[index];
  sendMorseMessage(strData.c_str());
}

void menuItem84() {  
  String strData = states[statesIndex];
  sendMorseMessage(strData.c_str());
  statesIndex++;
  if (statesIndex == statesArraySize){statesIndex = 0;}
}

void menuItem184() { 
  for (int index = 0; index < statesArraySize; index++ ) {
    String strData = states[index];
    sendMorseMessage(strData.c_str());
  }
}

void menuItem85() {  
  int index = random(0, statesArraySize);
  Serial.print("Array index is ");
  Serial.print(index);
  Serial.print(", array size is ");
  Serial.println(statesArraySize);
  String strData = states[index];
  sendMorseMessage(strData.c_str());
}

void menuItem86() {  
  String strData = capitals[capitalsIndex];
  sendMorseMessage(strData.c_str());
  capitalsIndex++;
  if (capitalsIndex == capitalsArraySize){capitalsIndex = 0;}
}

void menuItem186() { 
  for (int index = 0; index < capitalsArraySize; index++ ) {
    String strData = capitals[index];
    sendMorseMessage(strData.c_str());
  }
}

void menuItem87() {  
  int index = random(0, capitalsArraySize);
  Serial.print("Array index is ");
  Serial.print(index);
  Serial.print(", array size is ");
  Serial.println(capitalsArraySize);
  String strData = capitals[index];
  sendMorseMessage(strData.c_str());
}

void menuItem88() {  
  String strData = oregonCounties[oregonCountiesIndex];
  sendMorseMessage(strData.c_str());
  oregonCountiesIndex++;
  if (oregonCountiesIndex == oregonCountiesArraySize){oregonCountiesIndex = 0;}
}

void menuItem188() { 
  for (int index = 0; index < oregonCountiesArraySize; index++ ) {
    String strData = oregonCounties[index];
    sendMorseMessage(strData.c_str());
  }
}

void menuItem89() {  
  int index = random(0, oregonCountiesArraySize);
  Serial.print("Array index is ");
  Serial.print(index);
  Serial.print(", array size is ");
  Serial.println(oregonCountiesArraySize);
  String strData = oregonCounties[index];
  sendMorseMessage(strData.c_str());
}

void menuItem90() {  
  String strData = countries[countriesIndex];
  sendMorseMessage(strData.c_str());
  countriesIndex++;
  if (countriesIndex == countriesArraySize){countriesIndex = 0;}
}

void menuItem190() { 
  for (int index = 0; index < countriesArraySize; index++ ) {
    String strData = countries[index];
    sendMorseMessage(strData.c_str());
  }
}

void menuItem91() {  
  int index = random(0, countriesArraySize);
  Serial.print("Array index is ");
  Serial.print(index);
  Serial.print(", array size is ");
  Serial.println(countriesArraySize);
  String strData = countries[index];
  sendMorseMessage(strData.c_str());
}

void menuItem92() {  
  String strData = LunaPoem[LunaPoemIndex];
  sendMorseMessage(strData.c_str());
  LunaPoemIndex++;
  if (LunaPoemIndex == LunaPoemArraySize){LunaPoemIndex = 0;}
}

void menuItem192() { 
  for (int index = 0; index < LunaPoemArraySize; index++ ) {
    String strData = LunaPoem[index];
    sendMorseMessage(strData.c_str());
  }
}

void menuItem93() {  
  String strData = oscar1[oscar1Index];
  sendMorseMessage(strData.c_str());
  oscar1Index++;
  if (oscar1Index == oscar1ArraySize){oscar1Index = 0;}
}

void menuItem193() { 
  for (int index = 0; index < oscar1ArraySize; index++ ) {
    String strData = oscar1[index];
    sendMorseMessage(strData.c_str());
  }
}

void menuItem94() {  
  String strData = lettersAWJNGP[lettersAWJNGPIndex];
  sendMorseMessage(strData.c_str());
  lettersAWJNGPIndex++;
  if (lettersAWJNGPIndex == lettersAWJNGPArraySize){lettersAWJNGPIndex = 0;}
}

void menuItem194() { 
  for (int index = 0; index < lettersAWJNGPArraySize; index++ ) {
    String strData = lettersAWJNGP[index];
    sendMorseMessage(strData.c_str());
  }
}

void menuItem95() {  
  int index = random(0, lettersAWJNGPArraySize);
  Serial.print("Array index is ");
  Serial.print(index);
  Serial.print(", array size is ");
  Serial.println(lettersAWJNGPArraySize);
  String strData = lettersAWJNGP[index];
  sendMorseMessage(strData.c_str());
}

void menuItem96() {  
  String strData = lettersTMOEISH[lettersTMOEISHIndex];
  sendMorseMessage(strData.c_str());
  lettersTMOEISHIndex++;
  if (lettersTMOEISHIndex == lettersTMOEISHArraySize){lettersTMOEISHIndex = 0;}
}

void menuItem196() { 
  for (int index = 0; index < lettersTMOEISHArraySize; index++ ) {
    String strData = lettersTMOEISH[index];
    sendMorseMessage(strData.c_str());
  }
}
void menuItem97() {  
  int index = random(0, lettersTMOEISHArraySize);
  Serial.print("Array index is ");
  Serial.print(index);
  Serial.print(", array size is ");
  Serial.println(lettersTMOEISHArraySize);
  String strData = lettersTMOEISH[index];
  sendMorseMessage(strData.c_str());
}



//******* 100 Number to Send ****
void sendNumbers(int index) {  
  String strData = numbers[index];
  sendMorseMessage(strData.c_str());
}

//******* 110 Punctuation to Send ****
void sendPunctuation(int index) {  
  String strData = punctuations[index];
  sendMorseMessage(strData.c_str());
}

//******* 130 Pangrams to Send ****
void sendPangram(int index) {  
  String strData = pangrams[index];
  sendMorseMessage(strData.c_str());
}

//******* 200 Arduino UNO R4 WiFi Lesson 2 Homework ****
// Send homework SOS
void menuItem200() {
  const int numberOfSOSs = 5;
  Serial.println("Send Arduino UNO R4 WiFi lesson 2 homework message SOS");
  for (int index = 0; index < numberOfSOSs; index++) {
      sendMorseMessage("SOS ");
  }
}

///////////////////////////////////////////////////////////////////////////////
////////////////////Main Menu Function/////////////////////////////////////////
void printMenu() {
  tone(9, sideToneFreq); // Trun on straight key mode while waiting for menu entry.
  if (statusDisplayMode){
    Serial.println(" ");   // Clear Serial Monitor
    Serial.println(" ");   // Clear Serial Monitor
    Serial.println("********************* Morse Code Program Status ****************************");
    printWPMFromUnitTime(unitTime);
    printUnitTime(unitTime);
    farnsworthStatus(farnsworthMode);  // https://www.arrl.org/files/file/Technology/x9004008.pdf
    printSideTone(sideToneFreq);
    ramUsed = ramSize - freeMemory();     // Arduino R4 WiFi RAM status
    Serial.print("RAM available is ");      // Print the free RAM to the serial monitor
    Serial.println(ramSize); 
    Serial.print("Free RAM is ");           // Print the free RAM to the serial monitor
    Serial.println(freeMemory()); 
    Serial.print("RAM used is ");
    Serial.println(ramUsed);
    Serial.print("Status disply mode is");
    if (statusDisplayMode){Serial.println(" on");} else {Serial.println(" off");}
    Serial.print("Menu display mode is ");
    if (menuDisplayMode){Serial.println(" on");} else {Serial.println(" off");}    
    Serial.print("Timer mode is");
    if (timerMode){Serial.println(" on");} else {Serial.println(" off");}
    Serial.print("Up time since power on ");
    timeSincePwrUp();
    Serial.print("Call sign to index is ");
    Serial.println(callSignToIndex);
    Serial.print("Call sign from index is ");
    Serial.println(callSignFromIndex);
  }
  if (menuDisplayMode){
  Serial.println("*********** 1-9 Morse Code Program Settings Menu ***************");
  Serial.println("Please enter the number in the Serial Monitor.");
  Serial.println("1. Toggle status and menu display on/off");
  Serial.println("2. Set WPM 3-40");
  Serial.println("3. Toggle Farnsworth mode");
  Serial.println("4. Set side tone frequency");
  Serial.println("5. Set dit time in milSec, 120 - 10 WPM, 60 - 20 WPM, 30 - 40 WPM");
  Serial.println("6. Reset all data array indexes to zero");
  Serial.println("7. ++ Select to-station");
  Serial.println("8. -- Select to-station");

  Serial.println("******** 10-39 Morse Code Contact Menu ***************");
  Serial.println("10. Send CQ DE from-station");
  Serial.println("11. Send to-station DE from-station GE OM TNX FER CALL UR RST 589 QSB ~ OP DAVID BTU to-station DE from-station K");
  Serial.println("12. Send to-station DE from-station QTH CAMAS, WA ~ CAMAS, WA BTU to-station DE from-station K");
  Serial.println("13. Send to-station DE from-station R R FB RIG ICON IC-9700 ~ ANT VERT UP 20 FT BTU to-station DE from-station K");
  Serial.println("14. Send to-station DE from-station R R FB TNX FER QSO EQSL GL CU AGN 73 to-station DE from-station K");
 
  Serial.println("******** 20-39 Morse Code Contact WX Menu ***************");
  Serial.println("20. Send to-station DE from-station R R FB WX CLEAR AND HOT TODAY BTU to-station DE from-station K");
  Serial.println("21. Send to-station DE from-station R R FB WX CLEAR AND WARM TODA BTU to-station DE from-station K");
  Serial.println("22. Send to-station DE from-station R R FB WX CLEAR AND FAIR TODA BTU to-station DE from-station K");
  Serial.println("23. Send to-station DE from-station R R FB WX CLEAR AND COOL TODA BTU to-station DE from-station K");
  Serial.println("24. Send to-station DE from-station R R FB WX CLEAR AND COLD TODA BTU to-station DE from-station K");
  Serial.println("25. Send to-station DE from-station R R FB WX CLOUDY AND HOT TODA BTU to-station DE from-station K");
  Serial.println("26. Send to-station DE from-station R R FB WX CLOUDY AND WARM TODA BTU to-station DE from-station K");
  Serial.println("27. Send to-station DE from-station R R FB WX CLOUDY AND FAIR TODA BTU to-station DE from-station K");
  Serial.println("28. Send to-station DE from-station R R FB WX CLOUDY AND COOL TODA BTU to-station DE from-station K");
  Serial.println("29. Send to-station DE from-station R R FB WX CLOUDY AND COLD TODA BTU to-station DE from-station K");
  Serial.println("30. Send to-station DE from-station R R FB WX RAINING AND HOT TODA BTU to-station DE from-station K");
  Serial.println("31. Send to-station DE from-station R R FB WX RAINING AND WARM TODA BTU to-station DE from-station K");
  Serial.println("32. Send to-station DE from-station R R FB WX RAINING AND FAIR TODA BTU to-station DE from-station K");
  Serial.println("33. Send to-station DE from-station R R FB WX RAINING AND COOL TODA BTU to-station DE from-station K");
  Serial.println("34. Send to-station DE from-station R R FB WX RAINING AND COLD TODA BTU to-station DE from-station K");
  Serial.println("35. Send to-station DE from-station R R FB WX SNOWING AND COLD TODA BTU to-station DE from-station K");

  Serial.println("******** 40-59 Morse Code Net Menu *******************");
  Serial.print("40. Send net message, index: ");
  Serial.println(netIndex);
  Serial.print("41. Send 10 words with T, M, P, E, I, S & H letters ");

  Serial.println("******** 60-99 Morse Code Practice Copying Menu ******");
  Serial.print("60. Send letters, index: ");
  Serial.println(lettersIndex);
  Serial.println("61. Send randon letters");
  Serial.print("62. Send numbers, index: ");
  Serial.println(numbersIndex);
  Serial.println("63. Send randon numbers");
  Serial.print("64. Send punctuation, index: ");
  Serial.println(punctuationsIndex);
  Serial.println("65. Send randon punctuation");
  Serial.print("66. Send prosigns, index: ");
  Serial.println(prosignsIndex);
  Serial.println("67. Send randon prosign");
  Serial.print("68. Send callsign, index: ");
  Serial.println(callSignsIndex);
  Serial.println("69. Send randon callsign");
  Serial.print("70. Send Q codes, index: ");
  Serial.println(qCodesIndex);
  Serial.println("71. Send randon Q code");
  Serial.print("72. Send abbreviations, index: ");
  Serial.println(abbrIndex);
  Serial.println("73. Send randon abbreviations");
  Serial.print("74. Send pangrams, index: ");
  Serial.println(pangramsIndex);
  Serial.println("75. Send randon pangrams");
  Serial.print("76. Send Marion county FM repeaters, index: ");
  Serial.println(MarionRepeatersIndex);
  Serial.println("77. Send randon repeater");
  Serial.print("78. Send names, index: ");
  Serial.println(namesIndex);
  Serial.println("79. Send randon names");
  Serial.print("80. Send towns, index: ");
  Serial.println(townsIndex);
  Serial.println("81. Send randon towns");
  Serial.print("82. Send capital with stats, index: ");
  Serial.println(capitalsStatsIndex);
  Serial.println("83. Send randon capital with stats");
  Serial.print("84. Send stats, index: ");
  Serial.println(statesIndex);
  Serial.println("85. Send randon stats");
  Serial.print("86. Send stats capitals, index: ");
  Serial.println(capitalsIndex);
  Serial.println("87. Send randon state capitals");
  Serial.print("88. Send Oregon counties, index: ");
  Serial.println(oregonCountiesIndex);
  Serial.println("89. Send randon Oregon counties");
  Serial.print("90. Send countries, index: ");
  Serial.println(countriesIndex);
  Serial.println("91. Send randon countries");
  Serial.print("92. Send lines of Luna poem , index: ");
  Serial.println(LunaPoemIndex);
  Serial.print("93. Send lines of Oscar 1 information , index: ");
  Serial.println(oscar1Index);
  Serial.print("94. Send words with A, W, J, N, G & P letters: ");
  Serial.println(lettersAWJNGPIndex);
  Serial.println("95. Send randon words with A, W, J, N, G & P letters");
  Serial.print("96. Send words with T, M, P, E, I, S & H letters: ");
  Serial.println(lettersTMOEISHIndex);
  Serial.println("97. Send randon words with T, M, P, E, I, S & H letters");

  Serial.println("******* 100 Number to Send ****");
  Serial.println("100. BT NUMBERS: 1 2 3 4 5 6 7 8 9 0 0 9 8 7 6 5 4 3 2 1 11 22 33 44 55 66 77 88 99 00 BT");
  Serial.println("101. BT 12345 67890 09876 54321 BT");
  Serial.println("102. BT RST 599, RST 489, RST 379, RST 269, RST 159, RST 149, RST 139, RST 129, RST 119 BT"); 
  Serial.println("103. BT Speed of light: 299,792,458 meters per second ~ 983,571,088 feet per second BT");
  Serial.println("104. BT The charge of an electron is approximately -1.602 x 10 to the-19 coulombs. BT");                                                 // 1 to 0
  Serial.println("105. BT The value of pi: 3.14159 26535 89793 23846 26433 83279 50288 41971 69399 37510 BT");  
  Serial.println("106. BT The value of e: 2.71828 18284 59045 23536 02874 71352 66249 77572 47093 69995 BT");  
  Serial.println("107. BT Square root of 2: 1.41421 35623 73095 04880 16887 24209 69807 85696 71875 37694 BT");  
  Serial.println("108. BT Square root of 3: 1.73205 08075 68877 29352 74463 41505 87236 69428 05253 81038 BT"); 

  Serial.println("******* 110 Punctuation to Send ****");
  Serial.println("110. BT PUNCTUATION: . , / ? \\ ! ( ) & : ; = + - _ $ @ \" \' BT"); 
  Serial.println("111. BT PUNCTUATION: .. ,, // ?? \\\\ !! (( )) && :: ;; == ++ -- __ $$ @@ \"\" \'\' BT"); 
  Serial.println("112. BT .,?\\!()/&:;=+-_$@\" BT"); 
  Serial.println("113. BT . , ? \\ ! ( ) / & : ; = + - _ $ @ \" BT");               // Morse code punctuation 
  Serial.println("114. BT .. ,, ?? \\\\ !! (( )) // && :: ;; == ++ -- __ $$ @@ \"\" BT");  
  Serial.println("115. BT . . . ~ , , , ~ ? ? ? ~ \\ \\ \\ ~ ! ! ! BT");   // .,?\!
  Serial.println("116. BT ..... ,,,,, ????? \\\\\\\\\\ !!!!! BT");  // .,?\!
  Serial.println("117. BT ( ( ( ) ) ) / / / & & & : : : BT"); 
  Serial.println("118. BT ((((( ))))) ///// &&&&& ::::: BT");       // ()/&:
  Serial.println("119. BT ; ; ; = = = + + + - - - BT");
  Serial.println("120. BT ;;;;; ===== +++++ ----- BT");  
  Serial.println("121. BT _ _ _ $ $ $ @ @ @ \" \" \" BT");           // ;=+-
  Serial.println("122. BT _____ $$$$$ @@@@@ \"\"\"\"\" BT");       // _$@"

  Serial.println("******* 130 Pangrams to Send ****");
  Serial.println("130. BT The quick brown fox jumps over a lazy dog. BT");
  Serial.println("131. BT Pack my box with five dozen liquor jugs. BT");
  Serial.println("132. BT Jinxed wizards pluck ivy from the big quilt. BT");
  Serial.println("133. BT The five boxing wizards jump quickly. BT");
  Serial.println("134. BT How vexingly quick daft zebras jump! BT");
  Serial.println("135. BT Quick zephyrs blow, vexing daft Jim. BT");
  Serial.println("136. BT Sphinx of black quartz, judge my vow. BT");
  Serial.println("137. BT Two driven jocks help fax my big quiz. BT");
  Serial.println("138. BT Public junk dwarves quiz mighty fox. BT");
  Serial.println("139. BT Five quacking zephyrs jolt my wax bed. BT");
  Serial.println("140. BT The jay, pig, fox, zebra, and my wolves quack! BT");
  Serial.println("141. BT Vexed nymphs go for quick waltz job. BT");
  Serial.println("142. BT Glib jocks quiz nymph to vex dwarf. BT");
  Serial.println("143. BT Jackdaws love my big sphinx of quartz. BT");
  Serial.println("144. BT Quickly befriending the jovial wizard makes Pax's life cozy. BT");
  Serial.println("145. BT Vexing fjord nymphs quiz blackjack whiz. BT");
  Serial.println("146. BT Mr. Jock, TV quiz PhD, bags few lynx. BT");
  Serial.println("147. BT Jump by vow of quick, lazy strength in Oxford. BT");
  Serial.println("148. BT The quick onyx goblin jumps over the lazy dwarf. BT");
  Serial.println("149. BT Crazy Frederick bought many very exquisite opal jewels. BT");
  Serial.println("150. BT Sixty zippers were quickly picked from the woven jute bag. BT");
  Serial.println("******* 160 Send all data in an array ****");
  Serial.println("160. Send all letters array");
  Serial.println("162. Send all numbers array");
  Serial.println("164. Send all punctuation array");
  Serial.println("166. Send all prosign array");
  Serial.println("168. Send all call signs array");
  Serial.println("170. Send all Q codes array");
  Serial.println("172. Send all abbreviations array");
  Serial.println("174. Send all pangrams array");
  Serial.println("176. Send all Marion county repeaters array");
  Serial.println("178. Send all boys and girls names array");
  Serial.println("180. Send all towns array");
  Serial.println("182. Send all state capital with state array");
  Serial.println("184. Send all state names array");
  Serial.println("186. Send all state capital names array");
  Serial.println("188. Send all Oregon counties array");
  Serial.println("190. Send all countries array");
  Serial.println("192. Send all Luna Poem array");
  Serial.println("193. Send all OSCAR-1 array");
  Serial.println("194. Send all words with A, W, J, N, G & P letters array");
  Serial.println("196. Send all words with T, M, P, E, I, S & H letters array");

  Serial.println("******* 200 Arduino UNO R4 WiFi Lesson 2 Homework ****");
  Serial.println("200. Send lesson two homework message SOS");
  }
  Serial.print("To-station: ");
  Serial.println(callSigns[callSignToIndex]);
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
//*********** 1-9 Program Settings Menu ***************
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

//******** 10-19 QSO Menu ***************
      case 10:
        menuItem10();
        break;
      case 11:
        qsoMsg(1);
        break;
      case 12:
        qsoMsg(2);
        break;
      case 13:
        qsoMsg(3);
        break;
      case 14:
        qsoMsg(4);
        break;

//******** 20-39 QSO Menu ***************
      case 20:
        wxMessages(0);
        break;
      case 21:
        wxMessages(1);
        break;
      case 22:
        wxMessages(2);
        break;
      case 23:
        wxMessages(3);
        break;
      case 24:
        wxMessages(4);
        break;
      case 25:
        wxMessages(5);
        break;
      case 26:
        wxMessages(6);
        break;
      case 27:
        wxMessages(7);
        break;
      case 28:
        wxMessages(8);
        break;
      case 29:
        wxMessages(9);
        break;
      case 30:
        wxMessages(10);
        break;
      case 31:
        wxMessages(11);
        break;
      case 32:
        wxMessages(12);
        break;
      case 33:
        wxMessages(13);
        break;
      case 34:
        wxMessages(14);
        break;
      case 35:
        wxMessages(15);
        break;

//******** 40-59 Morse Code Net Menu *******************
      case 40:
        menuItem40();
        break; 
      case 41:
        menuItem41();
       break;

//******** 60-99 Send Practice Copying Menu ******
      case 60:
        menuItem60();
        break;
      case 61:
        menuItem61();
        break;
      case 62:
        menuItem62();
        break;
      case 63:
        menuItem63();
        break;
      case 64:
        menuItem64();
        break;
      case 65:
        menuItem65();
        break;
      case 66:
        menuItem66();
        break;
      case 67:
        menuItem67();
        break;
      case 68:
        menuItem68();
        break;
      case 69:
        menuItem69();
        break;
      case 70:
        menuItem70();
        break;
      case 71:
        menuItem71();
        break;
      case 72:
        menuItem72();
        break;
      case 73:
        menuItem73();
        break;
      case 74:
        menuItem74();
        break;
      case 75:
        menuItem75();
        break;
      case 76:
        menuItem76();
        break;
      case 77:
        menuItem77();
        break;
      case 78:
        menuItem78();
        break;
      case 79:
        menuItem79();
        break;
      case 80:
        menuItem80();
        break;
      case 81:
        menuItem81();
        break;
     case 82:
        menuItem82();
        break;
      case 83:
        menuItem83();
        break;
     case 84:
        menuItem84();
        break;
      case 85:
        menuItem85();
      case 86:
        menuItem86();
        break;
      case 87:
        menuItem87();
        break;
      case 88:
        menuItem88();
        break;
      case 89:
        menuItem89();
        break;
      case 90:
        menuItem90();
        break;
      case 91:
        menuItem91();
        break;
      case 92:
        menuItem92();
        break;
      case 93:
        menuItem93();
        break;
      case 94:
        menuItem94();
        break;
      case 95:
        menuItem95();
        break;
      case 96:
        menuItem96();
        break;
      case 97:
        menuItem97();
        break;

//******* 100 Send Numbers ****
      case 100:
        sendNumbers(0);
        break;
      case 101:
        sendNumbers(1);
        break;
      case 102:
        startTime = millis();
        sendNumbers(2);
        timerDuration();
        break;
      case 103:
        sendNumbers(3);
        break;
      case 104:
        sendNumbers(4);
        break;
      case 105:
        sendNumbers(5);
        break;
      case 106:
        sendNumbers(6);
        break;
      case 107:
        sendNumbers(7);
        break;
      case 108:
        sendNumbers(8);
        break;

//******* 110 Send Punctuation ****
      case 110:
        sendPunctuation(0);
        break;
      case 111:
        sendPunctuation(1);
        break;
      case 112:
        sendPunctuation(2);
        break;
      case 113:
        sendPunctuation(3);
        break;
      case 114:
        sendPunctuation(4);
        break;
      case 115:
        sendPunctuation(5);
        break;
      case 116:
        sendPunctuation(6);
        break;
      case 117:
        sendPunctuation(7);
        break;
      case 118:
        sendPunctuation(8);
        break;
      case 119:
        sendPunctuation(9);
        break;
      case 120:
        sendPunctuation(10);
        break;
      case 121:
        sendPunctuation(11);
        break;
      case 122:
        sendPunctuation(12);
        break;

//******* 130 Send Pangram ****
      case 130:
        sendPangram(0);
        break;
      case 131:
        sendPangram(1);
        break;
      case 132:
        sendPangram(2);
        break;
      case 133:
        sendPangram(3);
        break;
      case 134:
        sendPangram(4);
        break;
      case 135:
        sendPangram(5);
        break;
      case 136:
        sendPangram(6);
        break;
      case 137:
        sendPangram(7);
        break;
      case 138:
        sendPangram(8);
        break;
      case 139:
        sendPangram(9);
        break;
      case 140:
        sendPangram(10);
        break;
      case 141:
        sendPangram(11);
        break;
      case 142:
        sendPangram(12);
        break;
      case 143:
        sendPangram(13);
        break;
      case 144:
        sendPangram(14);
        break;
      case 145:
        sendPangram(15);
        break;
      case 146:
        sendPangram(16);
        break;
      case 147:
        sendPangram(17);
        break;
      case 148:
        sendPangram(18);
        break;
      case 149:
        sendPangram(19);
        break;
      case 150:
        sendPangram(20);
        break;
      case 160:
        menuItem160();
        break;
      case 162:
        menuItem162();
        break;
      case 164:
        menuItem164();
        break;
      case 166:
        menuItem166();
        break;
       case 168:
        menuItem168();
        break;
      case 170:
        menuItem170();
        break;
      case 172:
        menuItem172();
        break;
      case 174:
        menuItem174();
        break;
      case 176:
        menuItem176();
        break;
      case 178:
        menuItem178();
        break;
      case 180:
        menuItem180();
        break;
      case 182:
        menuItem182();
        break;
      case 184:
        menuItem184();
        break;
      case 186:
        menuItem186();
        break;
      case 188:
        menuItem188();
        break;
      case 190:
        menuItem190();
        break;
      case 192:
        menuItem192();
        break;
      case 193:
        menuItem193();
        break;
      case 194:
        menuItem194();
        break;
      case 196:
        menuItem196();
        break;

//******* 200 Send Arduino UNO R4 WiFi Lesson 2 Homework SOS ****
      case 200:
        menuItem200();
        break;

      default:
        Serial.println("Invalid choice. Please try again.");
        break;
    }
    // Print the menu again for subsequent choices
    printMenu();
  }

}


/*
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

void menuItem40() {
 switch (mesgNum) {
      case 1:
        menuItem41();
        break;
      case 2:
//        menuItem10();
        break;
      case 3:
        menuItem60();
        break;
      case 4:
        menuItem7();
        break;
      case 7:
//        menuItem11();
        break;
      case 8:
//        menuItem12();
        break;
      case 9:
        menuItem61();
        break;
       case 10:
        menuItem14();
        break;
      case 11:
        menuItem14();
        break;
      case 12:
        menuItem14();
        break;
      case 13:
        menuItem14();
        break;
      case 14:
        menuItem14();
        break;
   default:
        Serial.println("Invalid msgNum.");
        break;
    }
mesgNum++;
if(mesgNum==15){mesgNum=1;}
}
*/
