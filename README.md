<A NAME="INDEX"></A>
<P align="center"><A HREF="https://www.qrz.com/db/WA9ONY">WA9ONY</A> - <A HREF="https://www.youtube.com/@WA9ONYHomework">YouTube Homework</A> - <A HREF="https://www.youtube.com/user/DavidAHaworth">YouTube</A> - <A HREF="http://www.stargazing.net/david/RPi/index.html">RPi</A> - <A HREF="http://www.stargazing.net/david/index.html">Website</A> <A HREF="#P8">--&gt;</A><BR>
<A HREF="https://github.com/WA9ONY/AI">AI</A> - <A HREF="https://github.com/WA9ONY/Arduino">Arduino</A> - <A HREF="https://github.com/WA9ONY/Electronics">Electronics</A> - <A HREF="https://github.com/WA9ONY/GNURadio">GNURadio</A> - <A HREF="https://github.com/WA9ONY/Pico-RP2040">Pico-RP2040</A> - <A HREF="https://github.com/WA9ONY/Python">Python</A> - <A HREF="https://github.com/WA9ONY/Raspberry-Pi">Raspberry-Pi</A></P>  

<p align="center">
<img width="701" height="470" src="/Images/lessonMC.png"><BR>  
© David Haworth   
</p>

# Arduino Microcontrollers Homework Index
+ <A HREF="README.md#P1">YouTube Channel: Paul McWhorter Arduino Tutorials</A>
+ Lesson 1: <A HREF="README.md#L1">Getting Started for Absolute Beginners</A>


<A NAME="P1"></A>
<HR>
<P align="center"><A HREF="#INDEX">&lt;--</A> - <A HREF="https://www.youtube.com/channel/UCq4BzKarrZdc_Tcvf8AhlTA">YouTube Homework</A> - <A HREF="#L1">--&gt;</A></P>  
    
# YouTube Channel: Paul McWhorter Arduino Tutorials

Paul McWhorter YouTube [channel](https://www.youtube.com/@paulmcwhorter) has extensive video [25 playlist](https://www.youtube.com/@paulmcwhorter/playlists) tutorials.
+ Free All New Arduino R4 WiFi LESSONS for Absolute Beginners [25 videos playlist](https://www.youtube.com/playlist?list=PLGs0VKk2DiYyn0wN335MXpbi3PRJTMmex)
  + [SunFounder Elite Explorer Kit with Official Arduino Uno R4 WiFi](https://amzn.to/3SciApZ)
  + [Arduino® UNO R4 WiFi](https://store-usa.arduino.cc/products/uno-r4-wifi?_gl=1*yqp6c9*_ga*MTI3MTU1MzUwOS4xNzA2NDIwNzk1*_ga_NEXN8H46L5*MTcwNjQyMDc5NC4xLjEuMTcwNjQyMDg0MS4wLjAuMA..*_fplc*NlclMkJmOXkyQXVOJTJGT3FHSiUyQmw0OCUyRmtNa1VmalJXRFY5JTJCUmlFYlhoUnJMOSUyQkhZa3MzcEw1SW9iTXdaZTgzREc2OFVFb3RsVUZGdWFSWVhEdGJ1bjdhVmFDcmlobGg3eXozcm5PS1lXRzc5VUhpWEVhQUd2Sm94MHVxU1haUXlnJTNEJTNE&selectedStore=us)
---
I use the following [chatbots](https://en.wikipedia.org/wiki/Chatbot) for additional information, tutorials, create code, etc. 
<BR><B>Warning chatbots do make errors which are called [AI hallucinations](https://www.ibm.com/topics/ai-hallucinations).</B> [Hallucination (artificial intelligence)](https://en.wikipedia.org/wiki/Hallucination_(artificial_intelligence))
  + OpenAI [ChatGPT](https://openai.com/)
    + ChatGPT 4 is [$20/month](https://openai.com/chatgpt/pricing)
    + ChatGPT 3.4 is [free](https://openai.com/chatgpt/pricing). 
  + Google [Brad](https://bard.google.com/chat)
  + Microsoft [Bing chat](https://www.bing.com/search?iscopilotedu=1&sendquery=1&q=What%27s%20a%20good%20budget%20hotel%20chain%20that%20usually%20has%20a%20pool%3F&form=MA13G9&showconv=1)

<A NAME="L1"></A>
<HR>
<P align="center"><A HREF="#P1">&lt;--</A> - <A HREF="https://www.youtube.com/@WA9ONYHomework">YouTube Homework</A>  - <A HREF="#INDEX">Index</A> - <A HREF="#L2">--&gt;</A></P>  
    
# [LESSON 1](https://youtu.be/S66Iwhk2V7A?si=Kvs1WDEJrwfAtRaq): Arduino Uno R4 Wifi LESSON 1: Getting Started for Absolute Beginners

These are homework and notes for [LESSON 1](https://youtu.be/S66Iwhk2V7A?si=Kvs1WDEJrwfAtRaq)

Homework assignment is to determine the minimum delay time to see the blinking LED. 
+ [OpenAI](https://openai.com/) ChatGPT-4 [Persistence of vision](https://chat.openai.com/share/65a410fb-a6f3-4570-8d73-f6a093e37d2c) conversation.
  + Persistence of vision frequency is 24 to 30 Hz. Period is 41.6 ms to 33.3 ms.  Delay is 20.8 ms to 16.7 ms.

Blinking LED persistence of vision howework video.
+ [OpenAI](https://openai.com/) ChatGPT-4 [Arduino Blinking LED Lession 1](https://chat.openai.com/share/a3e6c923-2132-417c-9ea7-c0c1ffd34d1c) conversation.

+ [OpenAI](https://openai.com/) ChatGPT-4 prompt:
  + You are a teacher. Today you're teaching your class about the Arduino Uno R3 microcontroller. You're going to teach your students to create their first program called Blink to turn on and off the LED at 1 Hz. Please give the sketch code and the details how to use the Arduino development environment version 1.8 to run this sketch.
ChatGPT

## Lession 1: Arduino blinking LED script by ChatGPT.

```c++

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // Initialize the digital pin as an output.
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // Turn the LED on (HIGH is the voltage level)
  delay(1000);                       // Wait for a second (1000 milliseconds)
  digitalWrite(LED_BUILTIN, LOW);    // Turn the LED off by making the voltage LOW
  delay(1000);                       // Wait for a second
}


```
---

+ [OpenAI](https://openai.com/) ChatGPT-4 prompt:
  + The next program is to vary the frequency of the blink from 1 Hertz to 100 Hertz in steps of 1 Hertz. The duration of a step should be 3 seconds. At the beginning of each step, please print out the frequency of the blink. Please create this sketch.
---
## Lession 1: Arduino blinking LED persistence of vision script by ChatGPT.

```c++

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // Initialize the LED pin as an output.
  Serial.begin(9600); // Start serial communication at 9600 baud rate.
}

void loop() {
  for (int freq = 1; freq <= 100; ++freq) { // Loop from 1 Hz to 100 Hz
    long onTime = 500 / freq; // Calculate the time the LED should be ON. 500ms is half the period for 1 Hz.
    long offTime = 500 / freq; // Calculate the time the LED should be OFF.

    Serial.print("Frequency: ");
    Serial.print(freq);
    Serial.println(" Hz");

    long startTime = millis(); // Remember the start time
    while (millis() - startTime < 3000) { // Continue blinking for 3 seconds
      digitalWrite(LED_BUILTIN, HIGH); // Turn the LED on
      delay(onTime); // Wait for onTime milliseconds
      digitalWrite(LED_BUILTIN, LOW); // Turn the LED off
      delay(offTime); // Wait for offTime milliseconds
    }
  }
}

```
---
Homework YouTube videos as of 1/28/2024
+ https://www.youtube.com/watch?v=3WfvOFglzKg
+ https://youtu.be/SlDcf9h6jrA?si=XuGxh4ILnD6S26lS
  + https://www.youtube.com/@lorisrobots
+ https://youtu.be/Oa2eWjEvMB8
+ https://youtu.be/CPVfMoP-3k4
  

