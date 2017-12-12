class IMU{
  public:
  // functions
  IMU();
  void setup();
  void printGyro();
  float getGyroZ();
  float getAccelX();
  float getAccelY();
  void updateIMU();

  private:
  float G_gain=.0053; // gyros gain factor for 250deg/sec 
  float A_gain=.15; // gyros gain factor for 250deg/sec

  float gyro_x; //gyro x val
  float gyro_y; //gyro x val
  float gyro_z; //gyro x val
  float gyro_xold; //gyro cummulative x value
  float gyro_yold; //gyro cummulative y value
  float gyro_zold; //gyro cummulative z value
  float gerrx; // Gyro x error
  float gerry; // Gyro y error
  float gerrz; // Gyro 7 error
  
  float accel_x; //gyro x val
  float accel_y; //gyro x val
  float accel_z; //gyro x val
  float accel_xold; //gyro cummulative x value
  float accel_yold; //gyro cummulative y value
  float accel_zold; //gyro cummulative z value
  float aerrx; // Accel x error
  float aerry; // Accel y error
  float aerrz; // Accel 7 error
  
  float vel_x, vel_y, vel_z;
  
  float dis_x, dis_y, dis_z;
  
  float G_Dt=0.020;    // Integration time (DCM algorithm)  We will run the integration loop at 50Hz if possible
  
  long timer=0;   //general purpose timer
  long timerBuffer=0;  
  long timerPrint=0;  

  // functions
  void gyroZero();
  void readGyro();
  void calDis();
  void Accel_Init();
  void accelZero();
  void readAccel();
  void complimentaryFilter();
};


