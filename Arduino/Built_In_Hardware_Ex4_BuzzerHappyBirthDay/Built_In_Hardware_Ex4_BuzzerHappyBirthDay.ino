int length = 28;
char notes[] = "GGAGcB GGAGdc GGxecBA yyecdc";
int beats[] = {2,2,8,8,8,16,1,2,2,8,8,8,16,1,2,2,8,8,8,8,16,1,2,2,8,8,8,16};
int   tempo = 200;

void playTone(int tone, int duration)   {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(WIO_BUZZER,   HIGH);
    delayMicroseconds(tone);
    digitalWrite(WIO_BUZZER, LOW);
    delayMicroseconds(tone);
  }
}

void   playNote(char note, int duration) {
  char names[] = {'C', 'D', 'E', 'F', 'G',   'A', 'B', 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'x', 'y' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275,   1136, 1014, 956,  834,  765,  593,  468,  346,  224, 655 , 715 };
  int SPEE = 5;

  for (int i = 0; i < 17; i++) {

    if (names[i] ==   note) {
      int newduration = duration/SPEE;
      playTone(tones[i], newduration);
      }
  }
}

void setup() {
pinMode(WIO_BUZZER, OUTPUT);
}

void   loop() {
for (int i = 0; i < length; i++) {
   if (notes[i] == ' ') {
      delay(beats[i] * tempo); // delay between notes
   } else {
     playNote(notes[i],   beats[i] * tempo);
   }
   delay(tempo);
}
}