/**
 * Storing Input. 
 * 
 * Move the mouse across the screen to change the position
 * of the circles. The positions of the mouse are recorded
 * into an array and played back every frame. Between each
 * frame, the newest value are added to the end of each array
 * and the oldest value is deleted. 
 */

int num = 60;
float mx[] = new float[num];
float my[] = new float[num];

boolean started = false;
int frameCounter = 0;

float scale = 0;

PVector[] points = new PVector[4];
PVector[] offsets = new PVector[4];
PVector[] vectors = new PVector[4];

void setup() {
  size(360, 360);

  float radius = 100;
  for (int i = 0; i < points.length; i ++) {
    float theta = (i / (float)points.length) * PI*2;
    float x = sin(theta) * radius + 180;
    float y = cos(theta) * radius + 180;
    println(theta, x, y);
    points[i] = new PVector(x, y);
    offsets[i] = new PVector(random(PI*2), random(PI * 2));
    vectors[i] = new PVector(x - random(5.0)-2.5, y + random(5.0)-2.5);
  }
}

void draw() {

  background(255); 

  stroke(0);
  fill(0);
  beginShape();

  PVector c1, c2, pos;
  PVector prevPos = new PVector();
  PVector center = new PVector(width / 2, height/2); 

  float theta =millis() * 0.001;

  if (theta < PI*2) {
    scale =1.0 - (cos(theta) + 1.0) / 2.0;

    for (int i = 0; i < points.length + 1; i++) {
      int index = i % points.length;

      PVector point = PVector.lerp(center, vectors[index], scale);
      PVector nextPoint = PVector.lerp(center, vectors[(index + 1) % vectors.length], scale);

      //line(width / 2, height / 2, point.x, point.y);

      pos = PVector.lerp(point, nextPoint, 0.5);

      if ( i== 0) {
        vertex(pos.x, pos.y);
      } else {

        c1 = PVector.lerp(prevPos, point, 0.66);
        c2 = PVector.lerp(pos, point, 0.66);

        // ellipse(c1.x, c1.y, 10, 10);
        // ellipse(c2.x, c2.y, 5, 5);

        bezierVertex(c1.x, c1.y, c2.x, c2.y, pos.x, pos.y);
      }
      prevPos = new PVector(pos.x, pos.y);
    }
    for (int i = 0; i < vectors.length; i ++) {
      //vectors[0].x += (noise(millis()*0.3) - 0.5) * 3.0;
      vectors[i].x += sin(millis() * 0.001 + i*0.4 + random(0.3) + offsets[i].x)*0.5;
      vectors[i].y += cos (millis() * 0.003 + i*0.2 + random(0.3) + offsets[i].x)*0.5;
    }
    fill(0);
    endShape(CLOSE);
    saveFrame();
  } else
    exit();
}