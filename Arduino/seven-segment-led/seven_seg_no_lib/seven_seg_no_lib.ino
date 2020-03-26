bool common_anode = true;

const int anode_pin = 8;   // common anode/cathode pin
const int seg_a = 0;
const int seg_b = 1;
const int seg_c = 2;
const int seg_d = 3;
const int seg_e = 4;
const int seg_f = 5;
const int seg_g = 6;
const int seg_dp = 7;

byte seg_cathode[10][7] = { 
//  a, b, c, d, e, f, g
  { 1, 1, 1, 1, 1, 1, 0 },  // 0
  { 0, 1, 1, 0, 0, 0, 0 },  // 1
  { 1, 1, 0, 1, 1, 0, 1 },  // 2
  { 1, 1, 1, 1, 0, 0, 1 },  // 3
  { 0, 1, 1, 0, 0, 1, 1 },  // 4
  { 1, 0, 1, 1, 0, 1, 1 },  // 5
  { 1, 0, 1, 1, 1, 1, 1 },  // 6
  { 1, 1, 1, 0, 0, 0, 0 },  // 7
  { 1, 1, 1, 1, 1, 1, 1 },  // 8
  { 1, 1, 1, 0, 0, 1, 1 }   // 9
};

// Anode is opposite of cathode
byte seg_anode[10][7] = { 
//  a, b, c, d, e, f, g
  { 0, 0, 0, 0, 0, 0, 1 },  // 0
  { 1, 0, 0, 1, 1, 1, 1 },  // 1
  { 0, 0, 1, 0, 0, 1, 0 },  // 2
  { 0, 0, 0, 0, 1, 1, 0 },  // 3
  { 1, 0, 0, 1, 1, 0, 0 },  // 4
  { 0, 1, 0, 0, 1, 0, 0 },  // 5
  { 0, 1, 0, 0, 0, 0, 0 },  // 6
  { 0, 0, 0, 1, 1, 1, 1 },  // 7
  { 0, 0, 0, 0, 0, 0, 0 },  // 8
  { 0, 0, 0, 1, 1, 0, 0 }   // 9
};

void setup() {
  pinMode(anode_pin, OUTPUT); // anode
  pinMode(seg_a, OUTPUT); // a
  pinMode(seg_b, OUTPUT); // b
  pinMode(seg_c, OUTPUT); // c
  pinMode(seg_d, OUTPUT); // d
  pinMode(seg_e, OUTPUT); // e
  pinMode(seg_f, OUTPUT); // f
  pinMode(seg_g, OUTPUT); // g
  pinMode(seg_dp, OUTPUT); // DP
  
  write_dp(0);  // start with the decimal point off

  if (common_anode) {
    digitalWrite(anode_pin, 1); // anode is receiving power    
  }
}

void write_dp(byte state) {
  if (common_anode) {
    if (state) state = 0;
    else state = 1;
  }
  digitalWrite(seg_dp, state);
}

void sevenSegWrite(byte digit) {
    if (common_anode) {
    digitalWrite(seg_a, seg_anode[digit][0]);
    digitalWrite(seg_b, seg_anode[digit][1]);
    digitalWrite(seg_c, seg_anode[digit][2]);
    digitalWrite(seg_d, seg_anode[digit][3]);
    digitalWrite(seg_e, seg_anode[digit][4]);
    digitalWrite(seg_f, seg_anode[digit][5]);
    digitalWrite(seg_g, seg_anode[digit][6]);    
  }
  else {
    digitalWrite(seg_a, seg_cathode[digit][0]);
    digitalWrite(seg_b, seg_cathode[digit][1]);
    digitalWrite(seg_c, seg_cathode[digit][2]);
    digitalWrite(seg_d, seg_cathode[digit][3]);
    digitalWrite(seg_e, seg_cathode[digit][4]);
    digitalWrite(seg_f, seg_cathode[digit][5]);
    digitalWrite(seg_g, seg_cathode[digit][6]);    
  }
}

void loop() {
  for (byte count = 0; count < 10; ++count) {
    delay(1000);
    sevenSegWrite(count);
  }
  delay(3000);
}
