#include <tinyxml2.h>
#include <iostream> 
#include <string>
#include <string_view>

using namespace std;
using namespace tinyxml2;

void writeSample() {
  XMLDocument xmlDoc;
  XMLNode * pRoot = xmlDoc.NewElement("Root");
  xmlDoc.InsertFirstChild(pRoot);
  XMLElement * pElement = xmlDoc.NewElement("IntValue");
  pElement->SetText(10);
  pRoot->InsertEndChild(pElement);
  pElement = xmlDoc.NewElement("FloatValue");
  pElement->SetText(0.5f);
  pRoot->InsertEndChild(pElement);
  pElement = xmlDoc.NewElement("Date");
  pElement->SetAttribute("day", 26);
  pElement->SetAttribute("month", "April");
  pElement->SetAttribute("year", 2014);
  pElement->SetAttribute("dateFormat", "26/04/2014");
  pRoot->InsertEndChild(pElement);
  XMLError eResult = xmlDoc.SaveFile("sampleXML.xml");
}

int main(int argc, char** argv) {
  if (argc != 3) {
    cout << "Usage \n";
    cout << argv[0] << " xml prntag \n";
    return EXIT_SUCCESS;
  }

  auto xmlCfg(argv[1]);
  auto tag(argv[2]);
  
  XMLDocument xmlDoc;
  if (xmlDoc.LoadFile(xmlCfg) != XML_SUCCESS) {
    cout << "Input XML file " << xmlCfg << " error " << endl;
    return xmlDoc.ErrorID();
  } 
  auto tagElem = xmlDoc.FirstChildElement("Root")->FirstChildElement(tag);
  XMLPrinter streamer;
  if (tagElem){
    tagElem->Accept(&streamer);
  } else {
    cout << "Input XML file " << xmlCfg << " has no " << tag << endl;
  }
    
  cout << streamer.CStr();

  return EXIT_SUCCESS;
}