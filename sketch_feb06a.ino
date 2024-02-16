int Valve_3 = 5;    
int Valve_2 = 6;    
int Valve_1 = 7;    
int Manual = 8; 
String serin = " ";
int delay1 = 100;
int delay2 = 400;
int delay3 = 300;              

void setup() {
pinMode (Valve_1, OUTPUT);        
pinMode (Valve_2, OUTPUT);  
pinMode (Valve_3, OUTPUT);
pinMode (Manual, OUTPUT);
Serial.begin(9600, SERIAL_8N1);
}

void loop() {
  while(Serial.available())
  {
    Serial.println("Starting Pressure Calibration:");
    Serial.println("To continue press \'y\' or press \'n\' to skip");
    serin=Serial.readString();
    while(Serial.available()==0)
      continue;
    serin=Serial.readString();
    if(serin.equals("y"))
      if(calibration().equals("calibrated succeessfully"))
        Serial.println("Calibration Completed");
      else
        Serial.println("Calibration not Completed succeessfully press \'y\' to retry");
    else if(serin.equals("n"))
      while(1)
      {
        serin=" ";
        Serial.println("Welcome to controls");
        Serial.println("Press \'w\' to go forward or press \'m\' to give maunal control or any key to exit"); 
        while(Serial.available()==0)
            continue;
        serin=Serial.readString();
        if(serin.equals("w"))
        {
          Serial.println("Press any key to exit automatic forward");
          while(1)
          {
            serin=" ";
            if(forward()==1)
              continue;
            else
            {
              serin=" ";
              delay(2000);
              break;
            }
          }
        }
        else if(serin.equals("m"))
        {
          serin=" ";
          while(1)
          {
            Serial.println("Give maunal control \'w\'\\'/a\'\/\'d\' or \'n\' to exit manual control"); 
            while(Serial.available()==0)
              continue;
            serin=Serial.readString();
            if(serin.equals("w"))
              valve1();
            else if(serin.equals("a"))
              valve2();
            else if(serin.equals("d"))
              valve3();
            else
            {
              serin=" ";
              delay(2000);
              break;
            }
          }
        }
        else
        {
          break;  
        }
      }
    else
      Serial.println("invalid");
  }
}

int cylinder(int a)
{
  Serial.println("Press \'s\' to start,end and \'r\' to reset the duty cycle"); 
  while(Serial.available()==0)
      continue;
  serin=Serial.readString();
  if(serin.equals("s"))
  {
    delay(1000);
    int lastCheck = millis();
    digitalWrite(a,HIGH);
    while(Serial.available()==0)
      continue;
    delay(200);
    int d = millis() - lastCheck; 
    digitalWrite(a,LOW);
    Serial.println("cylinder delay=");
    Serial.println(d);
    serin=" ";
    return d;    
  }
  if(serin.equals("r"))
  {
    serin=" ";
    return 0;
  }
}

String calibration()
{
  Serial.println("Starting to calibrate cylinder 1:");
  Serial.println("Press \'y\' to continue or \'r\' to reset the duty cycle");
  while(Serial.available()==0)
    continue;
  serin=Serial.readString(); 
  if(serin.equals("r"))
  {
    serin=" ";
    return "not calibrated succeessfully";
  }
  delay1=cylinder(Valve_1);
  if(delay1==0)
    return "not calibrated succeessfully";
  Serial.println("Starting to calibrate cylinder 2:");
  Serial.println("Press \'y\' to continue or \'r\' to reset the duty cycle");
  while(Serial.available()==0)
    continue;
  serin=Serial.readString(); 
  if(serin.equals("r"))
  {
    serin=" ";
    return "not calibrated succeessfully";
  }
  delay2=cylinder(Valve_2);
  if(delay2==0)
    return "not calibrated succeessfully";
  Serial.println("Starting to calibrate cylinder 3:");
  Serial.println("Press \'y\' to continue or \'r\' to reset the duty cycle");
  while(Serial.available()==0)
    continue;
  serin=Serial.readString(); 
  if(serin.equals("r"))
  {
    serin=" ";
    return "not calibrated succeessfully";
  }
  delay3=cylinder(Valve_3);
  if(delay3==0)
    return "not calibrated succeessfully";
  Serial.println("the dutycycle is as follows - ");
  Serial.print("cylinder 1:");
  Serial.println(delay1);
  Serial.print("cylinder 2:");
  Serial.println(delay2);
  Serial.print("cylinder 3:");
  Serial.println(delay3);
  return "calibrated succeessfully";
}

int forward()
{
  while(Serial.available())
    return 0;
  int a=0,b=0,c=0;
  a=min(delay1,min(delay2,delay3));
  if((delay1-a)==0)
  {
    b=delay2-delay1;
    c=delay3-delay1;
    if(b>c)
    {
      b=b-c;
      digitalWrite(Valve_1,HIGH);
      digitalWrite(Valve_2,HIGH);
      digitalWrite(Valve_3,HIGH);
      delay(a);
      digitalWrite(Valve_1,LOW);
      delay(c);
      digitalWrite(Valve_3,LOW);
      delay(b);
      digitalWrite(Valve_2,LOW);  
      delay(1000);    
    }
    else
    {
      c=c-b;
      digitalWrite(Valve_1,HIGH);
      digitalWrite(Valve_2,HIGH);
      digitalWrite(Valve_3,HIGH);
      delay(a);
      digitalWrite(Valve_1,LOW);
      delay(b);
      digitalWrite(Valve_2,LOW);
      delay(c);
      digitalWrite(Valve_3,LOW);
      delay(1000);
    }
    return 1;
  }
  else if((delay2-a)==0)
  {
    b=delay1-delay2;
    c=delay3-delay2; 
    if(b>c)
    {
      b=b-c;
      digitalWrite(Valve_1,HIGH);
      digitalWrite(Valve_2,HIGH);
      digitalWrite(Valve_3,HIGH);
      delay(a);
      digitalWrite(Valve_2,LOW);
      delay(c);
      digitalWrite(Valve_3,LOW);
      delay(b);
      digitalWrite(Valve_1,LOW);
      delay(1000);      
    }
    else
    {
      c=c-b;
      digitalWrite(Valve_1,HIGH);
      digitalWrite(Valve_2,HIGH);
      digitalWrite(Valve_3,HIGH);
      delay(a);
      digitalWrite(Valve_2,LOW);
      delay(b);
      digitalWrite(Valve_1,LOW);
      delay(c);
      digitalWrite(Valve_3,LOW);
      delay(1000);
    }
    return 1;
  }
  else
  {
    b=delay1-delay3;
    c=delay2-delay3;
    if(b>c)
    {
      b=b-c;
      digitalWrite(Valve_1,HIGH);
      digitalWrite(Valve_2,HIGH);
      digitalWrite(Valve_3,HIGH);
      delay(a);
      digitalWrite(Valve_3,LOW);
      delay(c);
      digitalWrite(Valve_2,LOW);
      delay(b);
      digitalWrite(Valve_1,LOW);
      delay(1000);      
    }
    else
    {
      c=c-b;
      digitalWrite(Valve_1,HIGH);
      digitalWrite(Valve_2,HIGH);
      digitalWrite(Valve_3,HIGH);
      delay(a);
      digitalWrite(Valve_3,LOW);
      delay(b);
      digitalWrite(Valve_1,LOW);
      delay(c);
      digitalWrite(Valve_2,LOW);
      delay(1000);
    }
    return 1;
  }
  return 0;
}

void valve1()
{
  digitalWrite(Valve_1,HIGH);
  delay(delay1);
  digitalWrite(Valve_1,LOW);
  delay(1000);
}

void valve2()
{
  digitalWrite(Valve_2,HIGH);
  delay(delay2);
  digitalWrite(Valve_2,LOW);
  delay(1000);
}

void valve3()
{
  digitalWrite(Valve_3,HIGH);
  delay(delay3);
  digitalWrite(Valve_3,LOW);
  delay(1000);
}
