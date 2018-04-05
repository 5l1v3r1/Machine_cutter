/* By Kribo Tech
 *  Machine cutter 
 */

#define ult_echoport 4
#define ult_trigport 5
#define cut_motor1_1 6
#define cut_motor1_2 7 
#define rotate_motor2_1 9
#define rotate_motor2_2 10
#define c_en 8
#define r_en 11

long duration;
float distance;

int max_dist=10;  //cm
int min_dist=5;

long r;


void r_mtr_init()
{
  for (int j = 0; j <= 200; j++)
    { digitalWrite(rotate_motor2_1, HIGH);
      digitalWrite(rotate_motor2_2, LOW);
      analogWrite(r_en, j);
    }
}

void cuttr_mtrstop()
{
  digitalWrite(cut_motor1_1,LOW);
  analogWrite(c_en,0);
  digitalWrite(cut_motor1_2,LOW);
}

cuttr_mtrstop()
void rotate_mtrstop()
{
  digitalWrite(rotate_motor2_1,LOW);
  analogWrite(r_en,0);
  digitalWrite(rotate_motor2_2,LOW);
}


int cuttr_mtrfrwd(int pwm)
{
  digitalWrite(cut_motor1_1,HIGH);
  analogWrite(c_en,pwm);
  digitalWrite(cut_motor1_2,LOW);
}

int cuttr_mtrbk(int pwm)
{
  digitalWrite(cut_motor1_1,LOW);
  analogWrite(c_en,pwm);
  digitalWrite(cut_motor1_2,HIGH);
}

int rotate_mtrfrwd(int pwm)
{
  digitalWrite(rotate_motor2_1,HIGH);
  analogWrite(r_en,pwm);
  digitalWrite(rotate_motor2_2,LOW);
}

int rotate_mtrbk(int pwm)
{
  digitalWrite(rotate_motor2_1,LOW);
  analogWrite(r_en,pwm);
  digitalWrite(rotate_motor2_2,HIGH);
}


void setup() 
{
  pinMode(rotate_motor2_1,OUTPUT);
  pinMode(rotate_motor2_2,OUTPUT);  
  pinMode(cut_motor1_1,OUTPUT);  
  pinMode(cut_motor1_2,OUTPUT);
  pinMode( ult_trigport, OUTPUT );
  pinMode( ult_echoport, INPUT );
  Serial.begin(9600);
  r_mtr_init();
  
}


void loop() {

  int pwm=100;
  
  digitalWrite(ult_trigport, LOW);    
  digitalWrite(ult_trigport, HIGH);  
  delayMicroseconds( 100 );
  digitalWrite(ult_trigport, LOW);
  duration = pulseIn(ult_echoport, HIGH); 
  r = 3.4 * duration / 2;      
  distance = r / 100.00;
  
   
  Serial.print("duration: ");
  Serial.print(duration);
  Serial.print(" , ");
  Serial.print("distance: ");
   
  
  if( duration > 38000 ) 
  {Serial.println("out of reach");
  }
  else { 
    Serial.print(distance); Serial.println("cm");
    }
   delay( 1000 );

  if ((distance > min_dist) && (distance < max_dist))
  {
      cuttr_mtrfrwd(pwm);
      rotate_mtrfrwd(pwm);
  }
  else if (distance < min_dist)
  {
     cuttr_mtrbk(pwm);
     rotate_mtrbk(pwm);     
  }
  else
  {
    rotate_mtrfrwd(pwm);
    cuttr_mtrstop();    
  }
}
