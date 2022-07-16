

const int CH_4_PIN = 10;//Right/Left
const int CH_3_PIN = 2;//FWD/Rev


// Parameters

const int deadzone = 25; // Anything between -25 and 25 is stop


void setup()
{

//Configure pins

    Serial.begin(9600);
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);
    pinMode(CH_3_PIN,INPUT);
    pinMode(CH_4_PIN,INPUT);
}


void loop()
{

// Read pulse width from receiver

  int y = pulseIn(CH_3_PIN, HIGH, 25000);
  delay(5);
  int x = pulseIn(CH_4_PIN, HIGH, 25000);


// Convert to PWM value (-255 to 255)

  y = pulseToPWM(y);//FWD/REV

  x = pulseToPWM(x);//LEFT/RIGHT


// Mix for arcade drive

  int left = y + x;

  int right = y - x;
  Serial.print( left);
  Serial.print(":" );
  Serial.println(right);
// Drive motor

drive(left, right);
delay(5);
}

void drive(int speed_a, int speed_b)
{


// Limit speed between -255 and 255

    speed_a = constrain(speed_a, -255, 255);
    speed_b = constrain(speed_b, -255, 255);


// Set direction for motor A
    if ( speed_a == 0 )
      {

        digitalWrite(12, LOW);
      } 
      
     else if ( speed_a > 0)
      {

        digitalWrite(12, HIGH);

      } 

      else
      {
        digitalWrite(12, LOW);
      }
   
// Set direction for motor B

    if ( speed_b == 0 )
      {

        digitalWrite(13, HIGH);
      }
    
    else if ( speed_b > 0 ) 
      {

        digitalWrite(13, LOW);

      }
    else
      {

        digitalWrite(13, HIGH);

      }
//Serial.println(speed_a);

// Set speed

     analogWrite(3, abs(speed_a));

     analogWrite(11, abs(speed_b));

}


// Convert RC pulse value to motor PWM value

int pulseToPWM(int pulse) 
{
  //Serial.println(pulse);
  

// If we're receiving numbers, convert them to motor PWM
    if ( pulse > 900 ) 
      {

        pulse = map(pulse, 900, 2100, -500, 500);
        pulse = constrain(pulse, -255, 255);
      } 
    else 
      {
        pulse = 0;
      }


// Anything in deadzone should stop the motor

    if ( abs(pulse) <= deadzone )
      {
        pulse = 0;
      }
  return pulse;

}

