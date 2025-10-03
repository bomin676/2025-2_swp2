#define PIN_LED 9
#define PIN_TRIG 12
#define PIN_ECHO 13

#define SND_VEL 346.0
#define INTERVAL 25
#define PULSE_DURATION 10
#define _DIST_MIN 100
#define _DIST_MAX 300

#define TIMEOUT ((INTERVAL / 2) * 1000.0)
#define SCALE (0.001 * 0.5 * SND_VEL)

#define _EMA_ALPHA 0.5
#define N_SAMPLES 30

unsigned long last_sampling_time;
float dist_prev = _DIST_MAX;
float dist_ema;

float samples[N_SAMPLES];
int sample_index = 0;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  digitalWrite(PIN_TRIG, LOW);

  Serial.begin(57600);
}

void loop() {
  float dist_raw, dist_median;

  if (millis() < last_sampling_time + INTERVAL)
    return;

  dist_raw = USS_measure(PIN_TRIG, PIN_ECHO);

  samples[sample_index] = dist_raw;
  sample_index = (sample_index + 1) % N_SAMPLES;

  float temp_samples[N_SAMPLES];
  for (int i = 0; i < N_SAMPLES; i++) {
    temp_samples[i] = samples[i];
  }
  sort_array(temp_samples, N_SAMPLES);

  dist_median = temp_samples[N_SAMPLES / 2];

  Serial.print("Min:");
  Serial.print(_DIST_MIN);
  Serial.print(",raw:");
  Serial.print(dist_raw);
  Serial.print(",ema:");
  Serial.print(dist_ema);
  Serial.print(",median:");
  Serial.print(dist_median);
  Serial.print(",Max:");
  Serial.print(_DIST_MAX);
  Serial.println("");

  if ((dist_raw < _DIST_MIN) || (dist_median > _DIST_MAX))
    digitalWrite(PIN_LED, 1);
  else
    digitalWrite(PIN_LED, 0);

  last_sampling_time += INTERVAL;
}

float USS_measure(int TRIG, int ECHO) {
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(PULSE_DURATION);
  digitalWrite(TRIG, LOW);

  return pulseIn(ECHO, HIGH, TIMEOUT) * SCALE;
}

void sort_array(float arr[], int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        float temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}#define PIN_LED 9
#define PIN_TRIG 12
#define PIN_ECHO 13

#define SND_VEL 346.0
#define INTERVAL 25
#define PULSE_DURATION 10
#define _DIST_MIN 100
#define _DIST_MAX 300

#define TIMEOUT ((INTERVAL / 2) * 1000.0)
#define SCALE (0.001 * 0.5 * SND_VEL)

#define _EMA_ALPHA 0.5
#define N_SAMPLES 30

unsigned long last_sampling_time;
float dist_prev = _DIST_MAX;
float dist_ema;

float samples[N_SAMPLES];
int sample_index = 0;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  digitalWrite(PIN_TRIG, LOW);

  Serial.begin(57600);
}

void loop() {
  float dist_raw, dist_median;

  if (millis() < last_sampling_time + INTERVAL)
    return;

  dist_raw = USS_measure(PIN_TRIG, PIN_ECHO);

  samples[sample_index] = dist_raw;
  sample_index = (sample_index + 1) % N_SAMPLES;

  float temp_samples[N_SAMPLES];
  for (int i = 0; i < N_SAMPLES; i++) {
    temp_samples[i] = samples[i];
  }
  sort_array(temp_samples, N_SAMPLES);

  dist_median = temp_samples[N_SAMPLES / 2];

  Serial.print("Min:");
  Serial.print(_DIST_MIN);
  Serial.print(",raw:");
  Serial.print(dist_raw);
  Serial.print(",ema:");
  Serial.print(dist_ema);
  Serial.print(",median:");
  Serial.print(dist_median);
  Serial.print(",Max:");
  Serial.print(_DIST_MAX);
  Serial.println("");

  if ((dist_raw < _DIST_MIN) || (dist_median > _DIST_MAX))
    digitalWrite(PIN_LED, 1);
  else
    digitalWrite(PIN_LED, 0);

  last_sampling_time += INTERVAL;
}

float USS_measure(int TRIG, int ECHO) {
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(PULSE_DURATION);
  digitalWrite(TRIG, LOW);

  return pulseIn(ECHO, HIGH, TIMEOUT) * SCALE;
}

void sort_array(float arr[], int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        float temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}
