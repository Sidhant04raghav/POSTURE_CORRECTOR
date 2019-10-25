const int TP=4;
const int EP=3;
unsigned long tym=0;
int interval=10000;
long dur;
int dis=0,i,j;
float avgGOOD=0,avgBAD=0;
float avg,pcent,count;
boolean replay= true;
int rled=9;
int yled=8;
int gled=7;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(150);
  pinMode(TP,OUTPUT);
   pinMode(rled,OUTPUT);
    pinMode(yled,OUTPUT);
     pinMode(gled,OUTPUT);
  pinMode(EP,INPUT);
}

void loop() {
 if(replay==true){  
 Serial.println("----MAINTAIN A GOOD POSTURE----");
 delay(5000);
for(i=0;i<1000;i++)
{   digitalWrite(TP,LOW);//*******
    delayMicroseconds(2);
    digitalWrite(TP,HIGH);
    delayMicroseconds(10);
    digitalWrite(TP,LOW);
    dur=pulseIn(EP,HIGH);
    dis=dur*0.034/2;     //********

      
     if(dis<80)
        {//Serial.println(dis);
           
              avgGOOD+=dis;
        }
}avgGOOD=avgGOOD/1000;
Serial.println(avgGOOD);
delay(1000);
Serial.println("----GOOD----");
delay(5000);
Serial.println("----NOW MAINTAIN A TYPING POSTURE----");
delay(5000);
dis=0;
dur=0;
for(j=0;j<1000;j++)
{   digitalWrite(TP,LOW);//*******
    delayMicroseconds(2);
    digitalWrite(TP,HIGH);
    delayMicroseconds(10);
    digitalWrite(TP,LOW);
    dur=pulseIn(EP,HIGH);
    dis=dur*0.034/2;     //********

      
     if(dis<80)
        {//Serial.println(dis);
           
              avgBAD+=dis;
        }
}avgBAD=avgBAD/1000;
 
 Serial.println(avgBAD);
 delay(1000);
 }replay=false;
Serial.println("----READING IS BIENG TAKEN----");
delay(1000);
dis=0;
dur=0;
tym=millis();
while(((millis()-tym)<interval))
{digitalWrite(TP,LOW);//*******
    delayMicroseconds(2);
    digitalWrite(TP,HIGH);
    delayMicroseconds(10);
    digitalWrite(TP,LOW);
    dur=pulseIn(EP,HIGH);
    dis=dur*0.034/2;     //********

      
     if(dis < 80)
      { //Serial.println(dis);
        avg+=dis;
      count++;
      }
      

}avg=avg/count;
Serial.println(avg);
delay(1000);
if(avg<=avgBAD)
{Serial.println("TOOO NEAR TO SCREEN");
for(int bl=0;bl<=10;bl++)
{digitalWrite(rled,HIGH);
delay(200);

digitalWrite(rled,LOW);
delay(200);}
}

if(avg>avgGOOD)
{Serial.println("TOOO FAAR FROM SCREEN");
digitalWrite(gled,HIGH);
delay(500);

digitalWrite(gled,LOW);
delay(500);
digitalWrite(gled,HIGH);
delay(500);

digitalWrite(gled,LOW);
delay(500);}
pcent=(((avg-avgBAD)/(avgGOOD-avgBAD))*100);
Serial.println(pcent);
delay(2000);
if(pcent>0&&pcent<=33)
{Serial.println("----BAD POSTURE----");
 digitalWrite(rled,HIGH);
delay(2000);

digitalWrite(rled,LOW);
delay(2000);}
if(pcent>33&&pcent<=66)
{Serial.println("----MEDIUAMPOSTURE----");
digitalWrite(yled,HIGH);

delay(2000);

digitalWrite(yled,LOW);
delay(2000);}
if(pcent>66&&pcent<=100) 
{Serial.println("----GOOD POSTURE----");
digitalWrite(gled,HIGH);

delay(2000);

digitalWrite(gled,LOW);
delay(2000);}
 pcent=0; 
count=0;
avg=0;}
