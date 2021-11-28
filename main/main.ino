
const int circlesCount = 3;
int samplesNumbers[circlesCount] = {10, 20, 30};
int circlesRadius[circlesCount] = {150, 300, 450}; // millimeters
const int delayBetweenSamples = 300; // milliseconds
const int sampleVolume = 20; // millilitres
const int flushVolume = 40; // millilitres;
float stepsAtMilliliter = 10;
int backwardStepsNumber = 0;
int pauseAfterFilling = 0; // millilitres

class Carret {
  public:
    // Position of filter will be encoded in polar system:
    float r;
    float phi;

    Carret();
    void findStartPoint();
    void turn(float angle);

    /*
     * @param distance (millimenters) 
     */
    void setRadius(int radius);
    void flushFilter(int ml);
    void fillSample(int ml);
};

int calculateSteps(int ml) {
  return (int) stepsAtMilliliter * ml;
}

Carret::Carret(){
  this->r = 0;
  this->phi = 0;
}

void Carret::findStartPoint() {} // TODO
void Carret::turn(float angle) {} // TODO
void Carret::setRadius(int distance) {} // TODO

void Carret::flushFilter(int ml) {
  int forwardStepsNumber = calculateSteps(ml);
  moveStepper(forwardStepsNumber);
  delay(pauseAfterFilling);
  moveStepper(-backwardStepsNumber);
}

void Carret::fillSample(int ml) {
  int forwardStepsNumber = calculateSteps(ml);
  moveStepper(forwardStepsNumber);
  delay(pauseAfterFilling);
  moveStepper(-backwardStepsNumber);
}


Carret carret;

void setup() {
  // put your setup code here, to run once:
  // setup your stepper motors, buttons, etc

  carret.findStartPoint();
  carret.flushFilter(flushVolume);
}



/*
 * Low level stepper control.
 * turn stepper at specified number of steps
 */
void moveStepper(int steps) {} // TODO


void(* resetFunc) (void) = 0;


void loop() {

  for(int circle = 0; circle < circlesCount; circle++) {
    carret.setRadius(circlesRadius[circle]);
    float angle = 2 * M_PI / samplesNumbers[circle];
    for(int probe = 0; probe < samplesNumbers[circle]; probe++)
    {
      carret.turn(angle);
      carret.fillSample(sampleVolume);
      delay(delayBetweenSamples);
    }
  }

  carret.findStartPoint();
  resetFunc();
}
