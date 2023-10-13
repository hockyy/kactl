/**
 * Author: cos65535, hocky
 * Date: 2023-10-06
 * License: Unlicense
 * Source: https://github.com/cos65535/ICPCLibrary/blob/master/Geometry/
 * Description: visualize geometric objects
 * Status: tested manually
*/

string HTML = "<html><script>function line(x,y,a,b){c.b();c.moveTo(x,y);c.lineTo(a,b);c.s();}"
"function circle(x,y,r){c.b();c.arc(x,y,r,0,7,0);c.s();}" 
"window.onload=function(){d=document;d.i=d.getElementById;"
"c=d.i('c').getContext('2d');c.b=c.beginPath;c.s=c.stroke;"
"d.i('s').src='data.js?';};</script>"
"<body><canvas id='c' width='2000' height='2000'"
"style='border:1px solid #000;'></canvas>"
"<script id='s'></script></body></html>";

const int zoom = 200, CANVAS = 2000, OX = 20, OY = 20;
typedef pair<double, double> PDD;
void changeColor(string color = "red") {
  // can use rgb(%d, %d, %d) as well
  fprintf(stderr, "c.strokeStyle = '%s';\n", color.c_str());
}
void drawLine(const PDD &a, const PDD &b) {
  fprintf(stderr, "c.lineWidth = 3;\n");
  fprintf(stderr, "line(%d, %d, %d, %d)\n",
      (int)(OX+zoom*a.fi), CANVAS-OY-(int)(zoom*a.se),
      (int)(OX+zoom*b.fi), CANVAS-OY-(int)(zoom*b.se));
}
void drawCircle(const PDD &p, double r = 0.02) {
  fprintf(stderr, "c.lineWidth = 1;\n");
  fprintf(stderr, "circle(%d, %d, %d)\n",
      (int)(OX + zoom * p.fi), CANVAS - OY - (int)(zoom * p.se), (int)(zoom * r));
}
int main() {
  freopen("data.js","w",stderr);
}