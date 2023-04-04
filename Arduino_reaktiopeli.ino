const uint8_t blue = 3;
const uint8_t red = 5;
const uint8_t green = 6;

const uint8_t sw1 = 8;
const uint8_t sw2 = 10;
const uint8_t sw3 = 9;
const uint8_t sw4 = 11;

long RGN;
unsigned long lasttime = 0;
unsigned long bluewin = 0;
unsigned long redwin = 0;

unsigned long redcomp = 1;
unsigned long bluecomp = 1;

unsigned long uuspeli = 0;

void (*resetFunc)(void) = 0;

void setup() {
  Serial.begin(9600);

  pinMode(blue, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);

  pinMode(sw1, INPUT_PULLUP);
  pinMode(sw2, INPUT_PULLUP);
  pinMode(sw3, INPUT_PULLUP);
  pinMode(sw4, INPUT_PULLUP);

  digitalWrite(sw1, HIGH);
  digitalWrite(sw2, HIGH);
  digitalWrite(sw3, HIGH);
  digitalWrite(sw4, HIGH);

  digitalWrite(blue, LOW);
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);

  randomSeed(analogRead(0));
}

void loop() {
  int potikka = analogRead(A0);
  RGN = random(5000) * 0.01 * (potikka + 1);
  Serial.println(RGN);
  if (digitalRead(sw1) == LOW) {
    uuspeli = 1;
  }
  if (redwin == 3) {
    while (true) {
      digitalWrite(red, HIGH);
      if (digitalRead(sw4) == LOW) {
        digitalWrite(green, LOW);
        digitalWrite(red, HIGH);
        digitalWrite(blue, HIGH);
        delay(1000);
        resetFunc();
      }
    }
  }

if (bluewin == 3) {
    while (true) {
      digitalWrite(blue, HIGH);
      if (digitalRead(sw4) == LOW) {
        digitalWrite(green, LOW);
        digitalWrite(red, HIGH);
        digitalWrite(blue, HIGH);
        delay(1000);
        resetFunc();
      }
    }
  }

  if (uuspeli == 1) {
    digitalWrite(blue, HIGH);
    digitalWrite(red, HIGH);
    digitalWrite(green, HIGH);
    delay(300);
    digitalWrite(blue, LOW);
    digitalWrite(red, LOW);
    digitalWrite(green, LOW);
    odotus();
  }
  if (digitalRead(green) == 1) {
    digitalWrite(green, LOW);
  }
}

void odotus(void) {
  while (true) {
    unsigned long time = millis();
    if (digitalRead(sw1) == LOW) {
      uuspeli = 0;
      digitalWrite(blue, HIGH);
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH);
      delay(300);
      digitalWrite(blue, LOW);
      digitalWrite(red, LOW);
      digitalWrite(green, LOW);
      delay(300);
      digitalWrite(blue, HIGH);
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH);
      delay(300);
      digitalWrite(blue, LOW);
      digitalWrite(red, LOW);
      digitalWrite(green, LOW);
      delay(300);
      digitalWrite(blue, HIGH);
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH);
      delay(300);
      digitalWrite(blue, LOW);
      digitalWrite(red, LOW);
      digitalWrite(green, LOW);
      delay(300);
      digitalWrite(blue, HIGH);
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH);
      delay(1000);
      digitalWrite(blue, LOW);
      digitalWrite(red, LOW);
      digitalWrite(green, LOW);
      break;
    }
    if (uuspeli == 1) {
      uuspeli = 0;
      lasttime = time;
    }
    if (time - lasttime >= (500 + RGN)) {
      lasttime = time;
      peli();
      break;
    }

    if (digitalRead(sw2) == LOW) {
      int puna = 255;

      while (true) {
        analogWrite(red, puna);
        puna = puna - 1;
        delay(5);
        if (puna <= 5) {
          digitalWrite(red, LOW);
          break;
        }
      }
      redcomp = 0;
      lasttime = time;
      uuspeli = 1;
      break;
    }

    if (digitalRead(sw3) == LOW) {
      int sini = 255;

      while (true) {
        analogWrite(blue, sini);
        sini = sini - 1;
        delay(5);
        if (sini <= 5) {
          digitalWrite(blue, LOW);
          break;
        }
      }
      bluecomp = 0;
      lasttime = time;
      uuspeli = 1;
      break;
    }

    if (digitalRead(sw4) == LOW) {
      digitalWrite(green, LOW);
      digitalWrite(red, HIGH);
      digitalWrite(blue, HIGH);
      delay(1000);
      resetFunc();
    }
  }
}

void peli(void) {
  while (true) {
    digitalWrite(green, HIGH);

    if ((digitalRead(sw2) == LOW) && redcomp == 1) {
      redwin = redwin + 1;
      digitalWrite(green, LOW);
      int loopnum = 0;
      while (true) {
        digitalWrite(red, HIGH);
        delay(200);
        digitalWrite(red, LOW);
        delay(200);
        loopnum = loopnum + 1;
        if (loopnum == redwin) {
          break;
        }
      }
      delay(500);
      digitalWrite(red, HIGH);
      delay(1000);
      digitalWrite(red, LOW);
      break;
    }

    if ((digitalRead(sw3) == LOW) && bluecomp == 1) {
      bluewin = bluewin + 1;
      digitalWrite(green, LOW);
      int loopnum = 0;
      while (true) {
        digitalWrite(blue, HIGH);
        delay(200);
        digitalWrite(blue, LOW);
        delay(200);
        loopnum = loopnum + 1;
        if (loopnum == bluewin) {
          break;
        }
      }
      delay(500);
      digitalWrite(blue, HIGH);
      delay(1000);
      digitalWrite(blue, LOW);
      break;
    }

    if (digitalRead(sw4) == LOW) {
      digitalWrite(green, LOW);
      digitalWrite(red, HIGH);
      digitalWrite(blue, HIGH);
      delay(1000);
      resetFunc();
    }
    if ((redcomp == 0) && (bluecomp == 0)) {
      break;
    }
  }
  bluecomp = 1;
  redcomp = 1;
  uuspeli = 1;
}
