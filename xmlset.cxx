#include <tinyxml2.h>
#include <iostream> 
#include <string>
#include <string_view>
#include <vector>
#include <algorithm>

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

vector<string> wordsFromStr(char* str, const char* del=":=") 
{ 
    vector<string> words;

    // Returns first token  
    char *token = strtok(str, del); 
    while (token != NULL) { 
      words.push_back(token);
      token = strtok(NULL, del); 
    } 
    return words;
} 

int main(int argc, char** argv) {
  if (argc < 3) {
    cout << "Usage \n";
    cout << argv[0] << " xml prntag \n";
    return EXIT_SUCCESS;
  }

  auto xmlCfg(argv[1]);
  auto elemPath = wordsFromStr(argv[2]);

  XMLDocument xmlDoc;
  if (xmlDoc.LoadFile(xmlCfg) != XML_SUCCESS) {
    cout << "Input XML file " << xmlCfg << " error " << endl;
    return xmlDoc.ErrorID();
  } 
  auto inode = std::begin(elemPath);
  auto tagElem =  xmlDoc.FirstChildElement(inode++->c_str());
  for_each(std::begin(elemPath)+1,std::end(elemPath),[&](auto node){ 
    tagElem = tagElem->FirstChildElement(node.c_str());
  });

  XMLPrinter streamer;
  if (!tagElem) {
    cout << "Input XML file " << xmlCfg << " has no " << elemPath.back() << endl;
    return EXIT_FAILURE;
  }
  if (argc < 4) {
    tagElem->Accept(&streamer);
    cout << streamer.CStr();
  } else {
    for (int iarg = 3; iarg < argc; ++iarg) {
        auto at_v = wordsFromStr(argv[iarg]);
        tagElem->SetAttribute(at_v[0].c_str(), at_v[1].c_str());
    }
  }
  xmlDoc.SaveFile(xmlCfg);
  return EXIT_SUCCESS;
}