unsigned long start_time = 0;
unsigned long end_time = 0;

#define test_type int
test_type x = 1;
test_type y = 2;
test_type z = 3;

void setup() 
{
  Serial.begin(57600);
  Serial.println("SparkFun datatype demo.");
  Serial.println("Addition with int: x+y=z");
  Serial.print("x=");
  Serial.println(x);
  Serial.print("y=");
  Serial.println(y);
}

void loop() 
{
  start_time = micros();
  z=x+y;
  end_time = micros();
  Serial.print("z=");
  Serial.println(z);
  Serial.print("Start time: ");
  Serial.println(start_time);
  Serial.print("End time: ");
  Serial.println(end_time);
  Serial.print("Elapsed time: ");
  Serial.println(end_time - start_time);
  while(1); 
  
  start_time = micros();
  z = (int) x;
  end_time = micros(); 
  Serial.print("Start time: ");
  Serial.println(start_time);
  Serial.print("End time: ");
  Serial.println(end_time);
  Serial.print("Elapsed time: ");
  Serial.println(end_time - start_time);
}

