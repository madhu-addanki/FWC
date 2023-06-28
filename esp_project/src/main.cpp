#include <Arduino.h>
#ifdef ESP32
  #include <WiFi.h>
  #include <AsyncTCP.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);

const char* ssid = "Madhu";
const char* password = "1234567890";

const char* input_parameter00 = "input00";
const char* input_parameter01 = "input01";
const char* input_parameter02 = "input02";
const char* input_parameter10 = "input10";
const char* input_parameter11 = "input11";
const char* input_parameter12 = "input12";
const char* input_parameter20 = "input20";
const char* input_parameter21 = "input21";
const char* input_parameter22 = "input22";

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>COLLINEARITY</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    html {font-family: Times New Roman; display: inline-block; text-align: center;}
    h2 {font-size: 2.0rem; color: blue;}
  </style> 
  </head><body>
  <h2>TO FIND IF POINTS ARE COLLINEAR OR NOT</h2> 
  <p>Enter the values of points A,B,C
  <form action="/get">
    Enter the values of Point A: <input type="number" name="input00"><br><input type="number" name="input01"><br><input type="number" name="input02"><br>
    Enter the values of Point B: <input type="number" name="input10"><br><input type="number" name="input11"><br><input type="number" name="input12"><br>
    Enter the values of Point C: <input type="number" name="input20"><br><input type="number" name="input21"><br><input type="number" name="input22"><br>
    <input type="submit" value="Submit">
    

  </form><br>
</body></html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connecting...");
    return;
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    double A[3][1],B[3][1],C[3][1],d[3][1],e[3][1],l[3][3],f[1][3],one[1][1];
    A[0][0]=request->getParam(input_parameter00)->value().toDouble();
    A[1][0]=request->getParam(input_parameter01)->value().toDouble();
    A[2][0]=request->getParam(input_parameter02)->value().toDouble();
    B[0][0]=request->getParam(input_parameter10)->value().toDouble();
    B[1][0]=request->getParam(input_parameter11)->value().toDouble();
    B[2][0]=request->getParam(input_parameter12)->value().toDouble();
    C[0][0]=request->getParam(input_parameter20)->value().toDouble();
    C[1][0]=request->getParam(input_parameter21)->value().toDouble();
    C[2][0]=request->getParam(input_parameter22)->value().toDouble();
    
    int k=0;
  for(int i=0;i<3;i++)
  {
          for(int j=0;j<1;j++)
          {
                  d[i][j]=B[i][j]-A[i][j];
          }
  }
  for(int i=0;i<3;i++)
  {
          for(int j=0;j<1;j++)
          {
                  e[i][j]=C[i][j]-B[i][j];
          }
  }

 for(int i=0;i<3;i++)
 {
  for(int j=0;j<1;j++)
  {
	  l[i][k]=A[i][j];
  }
 }
  k+=1;
        
 for(int i=0;i<3;i++)
 {
  for(int j=0;j<1;j++)
  {
   l[i][k]=B[i][j];
  }
 }
  k+=1;

 for(int i=0;i<3;i++)
 {
  for(int j=0;j<1;j++)
  {
        l[i][k]=C[i][j];
  }
 }
int row,col,i,m=3,n=1,ra=m;
  double b;
        

  for(int row=0;row<ra;row++)
  {
   if(l[row][row])
   {
    for(int col=0;col<m;col++)
    {
     if(col!=row)
     {                          
         b=l[col][row]/l[row][row];
         for(i=0;i<ra;i++)                           
                 l[col][i]-=b*l[row][i];
                                }}}
     else
     {
        int reduce=1;
        for(i=row+1;i<m;i++)
        {
         if(l[i][row]){
            int j,temp;
            for(j=0;j<ra;j++)
            {
                    temp=l[row][j];
                    l[row][j]=l[i][j];
                    l[i][j]=temp;
            }
            reduce=0;
            break;
         }}
      if(reduce)
      {
        ra-=1;
        for(i=0;i<m;i++)
        {               
          l[i][row]=l[i][ra];
        }}
        row-=1;         
        }
      }

  if(ra<3)
  {
  int j=0;
  for(i=0;i<n;i++)
  {
   for(j=0;j<m;j++)
   {
         f[i][j]= e[j][i];
  }
 }
  int r1=n,c1=m,c2=n;
  for(i=0;i<r1;i++)
{
        for(j=0;j<c2;j++)
        {
                one[i][j]=0;
        }
}
for(i=0;i<r1;i++)
{
        for(j=0;j<c2;j++)
        {
                for(k=0;k<c1;k++)
                {
                        one[i][j]+=f[i][k]*d[k][j];
                }
        }
}
double norm;
 for(i=0;i<m;i++)
 {
norm = norm + e[i][0]*e[i][0];
}
double s;
s=one[0][0]/norm;
request->send(200, "text/html", "The points are collinear<b> B divides AC in the ratio: "+ String(s,2) + ")<br><a href=\"/\">Return to Home Page</a>");}


  else
  {
request->send(200, "text/html", "The points are not collinear <br><a href=\"/\">Return to Home Page</a>");
  }
  

  });
  server.onNotFound(notFound);
  server.begin();
}

void loop() {
  
}
